#include "DopeSheet.h"
#ifdef _DEBUG
#include "Externals/imgui/imgui.h"
#include <vector>
#include <string>

namespace ImGuiCommon {
    inline ImVec2 operator+(const ImVec2& lhs, const ImVec2& rhs)
    {
        return ImVec2(lhs.x + rhs.x, lhs.y + rhs.y);
    }
    inline ImVec2 operator-(const ImVec2& lhs, const ImVec2& rhs)
    {
        return ImVec2(lhs.x - rhs.x, lhs.y - rhs.y);
    }

    struct Keyframe {
        float frame;
        bool selected;
    };

    struct Track {
        std::string name;
        std::vector<Keyframe> keyframes;
    };

    void DopeSheet()
    {
        static float timelineScale = 1.0f;
        static float scrollOffset = 0.0f;
        static float currentFrame = 0;
        static std::vector<Track> tracks = {
            {"Position", {{10, false}, {20, false}, {30, false}}},
            {"Rotation", {{15, false}, {25, false}, {35, false}}},
            {"Scale", {{12, false}, {22, false}, {32, false}}}
        };

        ImGui::Begin("Dope Sheet");

        // ズームスライダー
        ImGui::SliderFloat("ズーム", &timelineScale, 0.1f, 10.0f, "Zoom %.1f");

        ImVec2 contentRegion = ImGui::GetContentRegionAvail();
        ImDrawList* drawList = ImGui::GetWindowDrawList();

        // タイムラインの背景を描画
        drawList->AddRectFilled(ImGui::GetCursorScreenPos(), ImGui::GetCursorScreenPos() + contentRegion, IM_COL32(50, 50, 50, 255));

        // スクロール
        ImGui::BeginChild("TimelineRegion", ImVec2(contentRegion.x, contentRegion.y), false, ImGuiWindowFlags_HorizontalScrollbar);
        ImGui::SetScrollX(scrollOffset);

        // タイムラインの目盛りとキーフレームを描画
        for (size_t t = 0; t < tracks.size(); ++t) {
            Track& track = tracks[t];
            float trackHeight = 40.0f;
            ImVec2 trackStart = ImGui::GetCursorScreenPos() + ImVec2(0.0f, t * trackHeight);
            drawList->AddRectFilled(trackStart, trackStart + ImVec2(contentRegion.x, trackHeight), IM_COL32(60, 60, 60, 255));
            ImGui::SetCursorScreenPos(trackStart);
            ImGui::Text("%s", track.name.c_str());

            for (Keyframe& keyframe : track.keyframes) {
                float keyframePos = keyframe.frame * 10.0f * timelineScale - scrollOffset;
                ImVec2 keyframeCenter = trackStart + ImVec2(keyframePos, trackHeight / 2);
                drawList->AddCircleFilled(keyframeCenter, 5.0f, keyframe.selected ? IM_COL32(0, 255, 0, 255) : IM_COL32(255, 0, 0, 255));

                // キーフレームをドラッグ可能にする
                ImGui::SetCursorScreenPos(keyframeCenter - ImVec2(5.0f, 5.0f));
                ImGui::InvisibleButton("##Keyframe", ImVec2(10, 10));
                if (ImGui::IsItemActive() && ImGui::IsMouseDragging(ImGuiMouseButton_Left)) {
                    keyframe.frame += ImGui::GetIO().MouseDelta.x / (10.0f * timelineScale);
                    if (keyframe.frame < 0) keyframe.frame = 0;
                }
                if (ImGui::IsItemClicked(ImGuiMouseButton_Right)) {
                    keyframe.selected = !keyframe.selected;
                    ImGui::OpenPopup("KeyframeContextMenu");
                }
            }
        }

        // コンテキストメニュー
        if (ImGui::BeginPopup("KeyframeContextMenu")) {
            if (ImGui::MenuItem("追加")) {
                for (Track& track : tracks) {
                    track.keyframes.push_back({ (scrollOffset / (10.0f * timelineScale)), false });
                }
            }
            if (ImGui::MenuItem("削除")) {
                for (Track& track : tracks) {
                    track.keyframes.erase(
                        std::remove_if(track.keyframes.begin(), track.keyframes.end(), [](const Keyframe& kf) { return kf.selected; }),
                        track.keyframes.end()
                    );
                }
            }
            ImGui::EndPopup();
        }

        ImGui::EndChild();
        ImGui::End();
    }
}
#endif // _DEBUG
