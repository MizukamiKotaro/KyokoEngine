#include "AudioManager.h"
#include <cassert>
#include <fstream>

#include "Audio.h"

AudioManager* AudioManager::GetInstance() {
	static AudioManager instance;
	return &instance;
}

void AudioManager::Initialize() {

	HRESULT hr = XAudio2Create(&xAudio2_, 0, XAUDIO2_DEFAULT_PROCESSOR);
	assert(SUCCEEDED(hr));
	hr = xAudio2_->CreateMasteringVoice(&masterVoice_);
	assert(SUCCEEDED(hr));

	Audio::StaticInitialize();
}

void AudioManager::Update()
{
	for (const std::unique_ptr<Voice>& voice : voices_) {
		if (!IsPlaying(voice->handle)) {
			if (voice->sourceVoice) {
				voice->sourceVoice->DestroyVoice();
				voice->sourceVoice = nullptr;
			}
		}
	}
}

void AudioManager::Finalize() {

	xAudio2_.Reset();

	for (const std::unique_ptr<SoundData>& soundData : soundDatas_) {
		Unload(soundData.get());
	}
}

uint32_t AudioManager::LoadWave(const std::string& filename) {

	std::string fileName = directoryPath_ + filename;

	for (const std::unique_ptr<SoundData>& soundData : soundDatas_) {
		if (soundData->name == fileName) {
			return soundData->handle;
		}
	}

	std::ifstream file;

	file.open(fileName, std::ios_base::binary);

	assert(file.is_open());

	RiffHeader riff;
	file.read((char*)&riff, sizeof(riff));

	if (strncmp(riff.chunk.id, "RIFF", 4) != 0) {
		assert(0);
	}

	if (strncmp(riff.type, "WAVE", 4) != 0) {
		assert(0);
	}

	FormatChunk fmt = {};

	file.read((char*)&fmt.chunk, sizeof(ChunkHeader));
	while (strncmp(fmt.chunk.id, "fmt ", 4) != 0) {
		// 読み取りチャンクを検出した場合
		file.seekg(fmt.chunk.size, std::ios_base::cur);
		// 再読み込み
		file.read((char*)&fmt.chunk, sizeof(ChunkHeader));
	}

	std::vector<char> fmtData(fmt.chunk.size);
	file.read(fmtData.data(), fmt.chunk.size);
	memcpy(&fmt.fmt, fmtData.data(), sizeof(fmt.fmt));

	ChunkHeader data;
	file.read((char*)&data, sizeof(data));

	while (strncmp(data.id, "data", 4) != 0) {
		// 読み取りチャンクを検出した場合
		file.seekg(data.size, std::ios_base::cur);
		// 再読み込み
		file.read((char*)&data, sizeof(data));
	}

	std::vector<BYTE> pBuffer(data.size);
	file.read(reinterpret_cast<char*>(pBuffer.data()), data.size);

	file.close();

	SoundData soundData = {};

	soundData.wfex = fmt.fmt;
	soundData.pBuffer = pBuffer;
	soundData.bufferSize = data.size;
	soundData.name = fileName;
	soundData.handle = static_cast<uint32_t>(soundDatas_.size());

	soundDatas_.push_back(std::make_unique<SoundData>(soundData));

	return soundDatas_.back()->handle;

}

void AudioManager::Unload(SoundData* soundData) {

	soundData->pBuffer.clear();
	soundData->bufferSize = 0;
	soundData->wfex = {};
}

void AudioManager::DestroyVoice(uint32_t handle)
{
	for (const std::unique_ptr<Voice>& voice : voices_) {
		if (voice->handle == handle) {
			if (voice->sourceVoice) {
				voice->sourceVoice->DestroyVoice();
				voice->sourceVoice = nullptr;
			}
			break;
		}
	}
}

AudioManager::Voice* AudioManager::FindUnusedVoice()
{
	for (const std::unique_ptr<Voice>& voice : voices_) {
		if (!voice->sourceVoice) {
			return voice.get();
		}
	}
	Voice voice;
	voice.sourceVoice = nullptr;
	voice.handle = static_cast<uint32_t>(voices_.size());
	voices_.push_back(std::make_unique<Voice>(voice));

	return voices_.back().get();
}

AudioManager::SoundData* AudioManager::FindSoundData(uint32_t handle)
{
	for (const std::unique_ptr<SoundData>& soundData : soundDatas_) {
		if (soundData->handle == handle) {
			return soundData.get();
		}
	}
	return nullptr;
}

uint32_t AudioManager::Play(uint32_t soundDataHandle, bool loopFlag, float volume) {

	HRESULT hr;

	Voice* voice = FindUnusedVoice();
	SoundData* soundData = FindSoundData(soundDataHandle);

	hr = xAudio2_->CreateSourceVoice(&voice->sourceVoice, &soundData->wfex);
	assert(SUCCEEDED(hr));

	XAUDIO2_BUFFER buf{};
	buf.pAudioData = soundData->pBuffer.data();
	buf.AudioBytes = soundData->bufferSize;
	buf.Flags = XAUDIO2_END_OF_STREAM;

	if (loopFlag) {
		buf.LoopCount = XAUDIO2_LOOP_INFINITE;
	}

	hr = voice->sourceVoice->SubmitSourceBuffer(&buf);
	assert(SUCCEEDED(hr));
	hr = voice->sourceVoice->Start();
	assert(SUCCEEDED(hr));
	hr = voice->sourceVoice->SetVolume(volume);

	return voice->handle;
}

void AudioManager::Stop(uint32_t voiceHandle) {

	DestroyVoice(voiceHandle);
}

bool AudioManager::IsPlaying(uint32_t voiceHandle)
{
	for (const std::unique_ptr<Voice>& voice : voices_) {
		if (voice->handle == voiceHandle) {
			if (voice->sourceVoice) {
				XAUDIO2_VOICE_STATE state{};
				voice->sourceVoice->GetState(&state);
				if (state.BuffersQueued != 0) {
					return true;
				}
				return false;
			}
		}
	}
	
	return false;
}

void AudioManager::Pause(uint32_t voiceHandle)
{
	for (const std::unique_ptr<Voice>& voice : voices_) {
		if (voice->handle == voiceHandle) {
			if (voice->sourceVoice) {
				voice->sourceVoice->Stop();
				break;
			}
		}
	}
}

void AudioManager::ReStart(uint32_t voiceHandle)
{
	for (const std::unique_ptr<Voice>& voice : voices_) {
		if (voice->handle == voiceHandle) {
			if (voice->sourceVoice) {
				voice->sourceVoice->Start();
				break;
			}
		}
	}
}

void AudioManager::SetVolume(uint32_t voiceHandle, float volume) {
	for (const std::unique_ptr<Voice>& voice : voices_) {
		if (voice->handle == voiceHandle) {
			voice->sourceVoice->SetVolume(volume);
			break;
		}
	}
}