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
        float subFrame;
        bool selected;
    };

    struct Track {
        std::string name;
        std::vector<Keyframe> keyframes;
    };

    void DrawTimelineLabels(ImDrawList* drawList, ImVec2 startPos, ImVec2 endPos, float scale, float offset)
    {
        for (int i = 0; i < endPos.x / (10.0f * scale); ++i)
        {
            float linePos = i * 10.0f * scale - offset;
            ImVec2 lineStart = startPos + ImVec2(linePos, 0.0f);
            ImVec2 lineEnd = lineStart + ImVec2(0.0f, endPos.y - startPos.y);
            if (i % 10 == 0)
            {
                drawList->AddText(lineStart, IM_COL32(255, 255, 255, 255), std::to_string(i).c_str()); // 数値を描画
            }
            else if (i % 5 == 0)
            {
                drawList->AddText(lineStart, IM_COL32(255, 255, 255, 255), std::to_string(i).c_str()); // 数値を描画
            }
            //else
            //{
            //    drawList->AddText(lineStart, IM_COL32(255, 255, 255, 255), std::to_string(i).c_str()); // 数値を描画
            //}
        }
    }

    void DrawTimelineLines(ImDrawList* drawList, ImVec2 startPos, ImVec2 endPos, float scale, float offset)
    {
        for (int i = 0; i < endPos.x / (10.0f * scale); ++i)
        {
            float linePos = i * 10.0f * scale - offset;
            ImVec2 lineStart = startPos + ImVec2(linePos, 0.0f);
            ImVec2 lineEnd = lineStart + ImVec2(0.0f, endPos.y - startPos.y);
            if (i % 10 == 0)
            {
                drawList->AddLine(lineStart, lineEnd, IM_COL32(255, 255, 255, 255), 2.0f); // 濃いライン
            }
            else if (i % 5 == 0)
            {
                drawList->AddLine(lineStart, lineEnd, IM_COL32(200, 200, 200, 255), 1.0f); // 普通のライン
            }
            else
            {
                drawList->AddLine(lineStart, lineEnd, IM_COL32(150, 150, 150, 255), 0.5f); // 薄いライン
            }
        }
    }

    void DopeSheet()
    {
        static float timelineScale = 1.0f;
        static float scrollOffset = 0.0f;
        static int currentFrame = 0;
        static std::vector<Track> tracks = {
            {"Position", {{10,10, false}, {20,20, false}, {30,30, false}}},
            {"Rotation", {{15,15, false}, {25,25, false}, {35,35, false}}},
            {"Scale", {{12,12, false}, {22,22, false}, {32,32, false}}}
        };

        ImGui::Begin("Dope Sheet");

        // ズームスライダー
        ImGui::SliderFloat("ズーム", &timelineScale, 0.1f, 10.0f, "Zoom %.1f");

        ImVec2 contentRegion = ImGui::GetContentRegionAvail();
        ImDrawList* drawList = ImGui::GetWindowDrawList();

        ImVec2 cursorScreenPos = ImGui::GetCursorScreenPos();

        // タイムラインの背景を描画
        drawList->AddRectFilled(cursorScreenPos, cursorScreenPos + contentRegion, IM_COL32(50, 50, 50, 255));


        // タイムラインの目盛りを描画
        DrawTimelineLabels(drawList, cursorScreenPos + ImVec2(100.0f, 0.0f), cursorScreenPos + ImVec2(100.0f, 0.0f) + ImVec2(contentRegion.x - 150.0f, 20.0f), timelineScale, scrollOffset);

        // スクロールバーのサイズを設定
        ImGui::BeginChild("TimelineRegion", ImVec2(contentRegion.x, contentRegion.y), true, ImGuiWindowFlags_HorizontalScrollbar | ImGuiWindowFlags_AlwaysVerticalScrollbar);
        ImGui::SetScrollX(scrollOffset);

        // トラックごとに描画
        for (size_t t = 0; t < tracks.size(); ++t) {
            Track& track = tracks[t];
            float trackHeight = 20.0f;
            ImVec2 trackStart = cursorScreenPos + ImVec2(0.0f, t * trackHeight + 2.0f * (t + 1) + 20.0f);
            ImVec2 keyframeStart = trackStart + ImVec2(100.0f, 0.0f); // 名前とキーフレームの間にスペースを追加

            // トラック名を描画
            drawList->AddRectFilled(trackStart, trackStart + ImVec2(100.0f, trackHeight), IM_COL32(60, 60, 60, 255));
            ImGui::SetCursorScreenPos(trackStart);
            ImGui::Text("  %s", track.name.c_str());

            // キーフレーム行を描画
            drawList->AddRectFilled(keyframeStart, keyframeStart + ImVec2(contentRegion.x - 150.0f, trackHeight), IM_COL32(80, 80, 80, 255));

            // トラックの境界線を描画
            drawList->AddLine(ImVec2(trackStart.x, trackStart.y + trackHeight), ImVec2(trackStart.x + contentRegion.x, trackStart.y + trackHeight), IM_COL32(100, 100, 100, 255));

            // タイムラインの目盛りを描画
            DrawTimelineLines(drawList, keyframeStart, keyframeStart + ImVec2(contentRegion.x - 150.0f, trackHeight), timelineScale, scrollOffset);

            for (Keyframe& keyframe : track.keyframes) {
                float keyframePos = keyframe.frame * 10.0f * timelineScale - scrollOffset;
                ImVec2 keyframeCenter = keyframeStart + ImVec2(keyframePos, trackHeight / 2);
                drawList->AddCircleFilled(keyframeCenter, 5.0f, keyframe.selected ? IM_COL32(0, 255, 0, 255) : IM_COL32(255, 0, 0, 255));

                // キーフレームをドラッグ可能にする
                ImGui::SetCursorScreenPos(keyframeCenter - ImVec2(5.0f, 5.0f));
                ImGui::InvisibleButton("##Keyframe", ImVec2(10, 10));
                if (ImGui::IsItemClicked(ImGuiMouseButton_Right)) {
                    keyframe.selected = !keyframe.selected;
                    ImGui::OpenPopup("KeyframeContextMenu");
                }
                if (ImGui::IsItemActive() && ImGui::IsMouseDragging(ImGuiMouseButton_Left)) {
                    if (keyframe.selected) {
                        keyframe.subFrame += ImGui::GetIO().MouseDelta.x / (10.0f * timelineScale);
                        keyframe.frame = float(int(keyframe.subFrame));
                        if (keyframe.subFrame < 0) {
                            keyframe.frame = 0;
                            keyframe.subFrame = 0;
                        }
                    }
                }
            }
        }

        // コンテキストメニュー
        if (ImGui::BeginPopup("KeyframeContextMenu")) {
            if (ImGui::MenuItem("追加")) {
                for (Track& track : tracks) {
                    bool isSelected = false;
                    for (Keyframe& kf : track.keyframes) {
                        if (kf.selected) {
                            isSelected = true;
                            break;
                        }
                    }
                    if (isSelected) {
                        track.keyframes.push_back({ float(static_cast<int>(scrollOffset / (10.0f * timelineScale))), false });
                    }
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
