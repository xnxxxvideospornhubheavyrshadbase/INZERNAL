#include "imwrap.h"

void imwrap::tooltip(const char* tip) {
    if (tip) {
        if (ImGui::IsItemHovered() && GImGui->HoveredIdTimer > 0.2f) //we do not want to hover when mouse just passes by the item therefore delay
            ImGui::SetTooltip(tip);
    }
}

//taken straight out of imgui_stdlib.cpp, since im using older imgui
bool imwrap::inputstring(const char* label, std::string* str, ImGuiInputTextFlags flags, const char* tip) {
    IM_ASSERT((flags & ImGuiInputTextFlags_CallbackResize) == 0);
    flags |= ImGuiInputTextFlags_CallbackResize;

    InputTextCallback_UserData cb_user_data;
    cb_user_data.Str = str;
    cb_user_data.ChainCallback = nullptr;
    cb_user_data.ChainCallbackUserData = nullptr;
    auto retval = ImGui::InputText(label, (char*)str->c_str(), str->capacity() + 1, flags, InputTextCallback, &cb_user_data);
    tooltip(tip);
    return retval;
}
