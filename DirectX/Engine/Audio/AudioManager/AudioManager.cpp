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

	for (int i = 0; i < kSoundVoiceMaxNum; i++) {
		voices_[i] = std::make_unique<Voice>();
	}

	Audio::StaticInitialize();
}

void AudioManager::Update()
{
	for (uint32_t i = 0; i < kSoundVoiceMaxNum; i++) {
		if (!IsPlaying(i)) {
			DestroyVoice(i);
		}
	}
}

void AudioManager::Finalize() {

	xAudio2_.Reset();

	for (SoundData soundData : soundDatas_) {
		Unload(&soundData);
	}
}

uint32_t AudioManager::LoadWave(const std::string& filename) {

	std::string fileName = directoryPath_ + filename;

	for (uint32_t soundDataNum = 0; soundDataNum < static_cast<uint32_t>(soundDatas_.size()); soundDataNum++) {

		if (soundDatas_[soundDataNum].name == fileName) {
			return soundDataNum;
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

	soundDatas_.push_back(soundData);

	return static_cast<uint32_t>(soundDatas_.size() - 1);

}

void AudioManager::Unload(SoundData* soundData) {

	soundData->pBuffer.clear();
	soundData->bufferSize = 0;
	soundData->wfex = {};
}

void AudioManager::DestroyVoice(uint32_t handle)
{
	if (voices_[handle]->sourceVoice) {
		voices_[handle]->sourceVoice->DestroyVoice();
		voices_[handle]->sourceVoice = nullptr;
	}
}

AudioManager::Voice* AudioManager::FindUnusedVoice()
{
	for (int i = 0; i < kSoundVoiceMaxNum; i++) {
		if (voices_[i]->sourceVoice == nullptr) {
			voices_[i]->handle = i;
			return voices_[i].get();
		}
	}
	return nullptr;
}

uint32_t AudioManager::Play(uint32_t soundDataHandle, bool loopFlag, float volume) {

	HRESULT hr;

	//voices_.push_back(std::make_unique<Voice>());
	Voice* voice = FindUnusedVoice();

	hr = xAudio2_->CreateSourceVoice(&voice->sourceVoice, &soundDatas_[soundDataHandle].wfex);
	assert(SUCCEEDED(hr));

	XAUDIO2_BUFFER buf{};
	buf.pAudioData = soundDatas_[soundDataHandle].pBuffer.data();
	buf.AudioBytes = soundDatas_[soundDataHandle].bufferSize;
	buf.Flags = XAUDIO2_END_OF_STREAM;

	if (loopFlag) {
		buf.LoopCount = XAUDIO2_LOOP_INFINITE;
	}

	hr = voice->sourceVoice->SubmitSourceBuffer(&buf);
	assert(SUCCEEDED(hr));
	hr = voice->sourceVoice->Start();
	assert(SUCCEEDED(hr));
	hr = voice->sourceVoice->SetVolume(volume);

	//voices_.back()->handle = static_cast<uint32_t>(voices_.size() - 1);

	return voice->handle;
}

void AudioManager::Stop(uint32_t voiceHandle) {

	DestroyVoice(voiceHandle);
}

bool AudioManager::IsPlaying(uint32_t voiceHandle)
{
	if (voices_[voiceHandle]->sourceVoice) {
		XAUDIO2_VOICE_STATE state{};
		voices_[voiceHandle]->sourceVoice->GetState(&state);
		if (state.BuffersQueued != 0) {
			return true;
		}
	}

	return false;
}

void AudioManager::Pause(uint32_t voiceHandle)
{
	if (voices_[voiceHandle]->sourceVoice) {
		voices_[voiceHandle]->sourceVoice->Stop();
	}
}

void AudioManager::ReStart(uint32_t voiceHandle)
{
	if (voices_[voiceHandle]->sourceVoice) {
		voices_[voiceHandle]->sourceVoice->Start();
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