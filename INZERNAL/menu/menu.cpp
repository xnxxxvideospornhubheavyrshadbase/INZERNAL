#pragma once
#include <core/utils.h>
#include <menu/menu.h>

void menu::EndScene(IDirect3DDevice9* device, bool active) {
    if (!global::load) { //init imgui
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        ImGui_ImplDX9_Init(device);

        ImGui::StyleColorsDark();
        //load_config();
        ImGui::GetStyle().ItemSpacing = ImVec2(5.5, 5.5);
        auto & _style = ImGui::GetStyle();
        _style.Alpha = 1.0f;                          // Global alpha applies to everything in ImGui
        _style.WindowPadding = ImVec2(10, 10);        // Padding within a window
        _style.WindowMinSize = ImVec2(32, 32);        // Minimum window size
        _style.WindowRounding = 0.0f;                 // Radius of window corners rounding. Set to 0.0f to have rectangular windows
        _style.WindowTitleAlign = ImVec2(0.0f, 0.5f); // Alignment for title bar text
        _style.ChildRounding = 0.0f;                  // Radius of child window corners rounding. Set to 0.0f to have rectangular child windows
        _style.FramePadding = ImVec2(4, 4);           // Padding within a framed rectangle (used by most widgets)
        _style.FrameRounding = 0.0f;                  // Radius of frame corners rounding. Set to 0.0f to have rectangular frames (used by most widgets).
        _style.ItemSpacing = ImVec2(5, 5);            // Horizontal and vertical spacing between widgets/lines
        _style.ItemInnerSpacing = ImVec2(6, 4);       // Horizontal and vertical spacing between within elements of a composed widget (e.g. a slider and its label)
        _style.TouchExtraPadding = ImVec2(0,
            0); // Expand reactive bounding box for touch-based system where touch position is not accurate enough. Unfortunately we don't sort widgets so priority on overlap will always be given to the first widget. So don't grow this too much!
        _style.IndentSpacing = 21.0f;                // Horizontal spacing when e.g. entering a tree node. Generally == (FontSize + FramePadding.x*2).
        _style.ColumnsMinSpacing = 6.0f;             // Minimum horizontal spacing between two columns
        _style.ScrollbarSize = 16.0f;                // Width of the vertical scrollbar, Height of the horizontal scrollbar
        _style.ScrollbarRounding = 0.0f;             // Radius of grab corners rounding for scrollbar
        _style.GrabMinSize = 10.5f;                  // Minimum width/height of a grab box for slider/scrollbar
        _style.GrabRounding = 0.0f;                  // Radius of grabs corners rounding. Set to 0.0f to have rectangular slider grabs.
        _style.ButtonTextAlign = ImVec2(0.5f, 0.5f); // Alignment of button text when button is larger than text.
        _style.DisplayWindowPadding =
            ImVec2(22, 22); // Window positions are clamped to be IsVisible within the display area by at least this amount. Only covers regular windows.
        _style.DisplaySafeAreaPadding =
            ImVec2(4, 4); // If you cannot see the edge of your screen (e.g. on a TV) increase the safe area padding. Covers popups/tooltips as well regular windows.
        _style.AntiAliasedLines = true; // Enable anti-aliasing on lines/borders. Disable if you are really short on CPU/GPU.
        _style.AntiAliasedFill = true;  // Enable anti-aliasing on filled shapes (rounded rectangles, circles, etc.)
        _style.CurveTessellationTol =
            1.25f; // Tessellation tolerance. Decrease for highly tessellated curves (higher quality, more polygons), increase to reduce quality.
        _style.FrameBorderSize = 1.f;

        utils::printc("93", "dx9 and imgui init done");
        global::load = true;
    }
    if (global::load) {
        ImGui_ImplDX9_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        ImGui::SetNextWindowPos(ImVec2{ 0, 0 }, ImGuiCond_Once);
        ImGui::SetNextWindowSize(ImVec2{ 800, 400 }, ImGuiCond_Once);

        if (global::draw && ImGui::Begin(std::string("INZERNAL " + global::version).c_str(), &global::draw, ImGuiWindowFlags_NoCollapse)) {
           
            	static char* tab_names[] = { (char*)"Enhancements", (char*)"Cheats", (char*)"Framework" };
            static int active_tab = 0;

            auto& style = ImGui::GetStyle();
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, style.WindowPadding.y });

            float group_w = ImGui::GetCurrentWindow()->Size.x - style.WindowPadding.x * 2;
            ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 10));
            {
                ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 0.f);
                imwrap::horizontal_tabs(tab_names, active_tab, group_w / _countof(tab_names), 33.0f);
            }
            ImGui::PopStyleVar(3);

            switch (active_tab) {
                case 0: 
                    enhancements_tab();
                    break;
                case 1: 
                    cheats_tab();
                    break;
                case 2: 
                    framework_tab();
                    break;
            }
            ImGui::End();
        }
        ImGui::EndFrame();
        ImGui::Render();
        ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
    }
}

bool menu::WndProc(HWND wnd, UINT msg, WPARAM wparam, LPARAM lparam) {
    static bool init = false;
    if (global::load && !init) {
        ImGui_ImplWin32_Init(wnd);
        init = true;
    }

    if (msg == WM_KEYUP && wparam == VK_INSERT)
        global::draw = !global::draw;

    /*  if (msg == WM_KEYUP && wparam == VK_F4)
        load_config();*/

    return ImGui_ImplWin32_WndProcHandler(wnd, msg, wparam, lparam);
}
