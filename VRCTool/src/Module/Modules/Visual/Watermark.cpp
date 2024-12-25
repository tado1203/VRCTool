#include "pch.h"

#include "Watermark.h"

#include <iomanip>

#include "../../../UI/FontManager.h"
#include "../../../UI/FontsData/IconsFontAwesome6.h"
#include "../../../Utils/Utils.h"
#include "../../../Game/Functions.h"

void Watermark::OnImGuiRender() {
    if (isEnabled) {
        ImDrawList* drawList = ImGui::GetForegroundDrawList();
        const ImGuiIO& io = ImGui::GetIO();

        constexpr float padding = 10.0f;
        constexpr float maxRowWidth = 600.0f;

        static float updateTimer = 0.5f;
        static int fps = 0;
        static std::string fpsStr;

        updateTimer += io.DeltaTime;
        if (updateTimer >= 0.5f) { // 0.5 sec passed
            fps = static_cast<int>(io.Framerate);
            fpsStr = std::to_string(fps);
            fpsStr.insert(0, " ");
            updateTimer = 0.0f;
        }

        // Get current system time
        auto now = std::chrono::system_clock::now();
        auto time = std::chrono::system_clock::to_time_t(now);

        std::tm timeTm;
        localtime_s(&timeTm, &time);

        // Format the time as HH:MM:SS
        std::ostringstream timeStream;
        timeStream << std::put_time(&timeTm, "%H:%M:%S");
        std::string timeStr = timeStream.str();
        timeStr.insert(0, " ");

        // Texts to display
        std::vector<std::string> texts = { "VRCTool", ICON_FA_CHART_LINE + fpsStr + "fps", ICON_FA_CLOCK + timeStr };

        if (Functions::Networking::GetLocalPlayer() != nullptr) {
            auto localPlayer = Functions::Networking::GetLocalPlayer();
            texts.emplace_back(ICON_FA_USER" " + Utils::ConvertSystemStringToStdString(localPlayer->fields.displayName));
        }

        ImGui::PushFont(FontManager::robotoMedium);

        // Calculate positions and draw rectangles and texts
        float x = padding;
        float y = padding * 2.0f; // y pos of the first row is 20.0f

        for (const auto& text : texts) {
            const ImVec2 textSize = ImGui::CalcTextSize(text.c_str());
            ImVec2 rectMin(x, y);
            ImVec2 rectMax(x + textSize.x + padding * 2, y + textSize.y + padding * 2);

            // If the rectangle exceeds the maximum row width, move to the next line
            if (rectMax.x > maxRowWidth) {
                x = padding;
                y += textSize.y + padding * 2 + padding;

                rectMin = ImVec2(x, y);
                rectMax = ImVec2(x + textSize.x + padding * 2, y + textSize.y + padding * 2);
            }

            // Draw rectangle
            drawList->AddRectFilled(rectMin, rectMax, ImColor(0.0f, 0.0f, 0.0f, 0.6f), 10.0f);

            // Draw text
            drawList->AddText(ImVec2(x + padding, y + padding), ImColor(255, 255, 255), text.c_str());

            // Update x position for the next rectangle
            x += textSize.x + padding * 2 + padding;
        }

        ImGui::PopFont();
    }
}
