#pragma once
#include <menu/menu.h>
#include <sdk/sdk.h>

void menu::enhancements_tab() {
    
    if (ImGui::CollapsingHeader("Custom Server")) {
        if (ImGui::BeginChild("###customserver", AUTOSIZE(2.f), true)) {
            imwrap::checkbox("Enable###custom", opt::custom_server_on, "You can use this to connect to private servers too");
            ImGui::SameLine();
            imwrap::inputstring("##serverval", &opt::custom_server_val, 0);
            ImGui::Text("Works with growtopia2 (gt1 is usually broken), and private servers.");
            ImGui::EndChild();
        }
    }
    if (ImGui::CollapsingHeader("Login info spoofing")) {
        if (ImGui::BeginChild("###loginspoof", ImVec2(ImGui::GetWindowWidth() * 0.93f, 60.f), true)) {
            ImGui::Checkbox("Enable###spoof", &opt::spoof_login);
            ImGui::SameLine();
            imwrap::checkbox("spoof name", opt::spoof_name, "sets requestedName to randomized string");

            //  menu::InputTextSTL("##serverval", &opt::custom_server_val);
            ImGui::EndChild();
        }
    }

    ImGui::Columns(3);

    ImGui::Checkbox("Block sendpacketraw", &opt::cheat::block_sendpacketraw);
    ImGui::Checkbox("Antighost", &opt::cheat::antighost);
    ImGui::Checkbox("See ghosts", &opt::see_ghosts);

    ImGui::NextColumn();

    ImGui::Checkbox("Mod zoom", &opt::mod_zoom);
    ImGui::Checkbox("Dev zoom", &opt::cheat::dev_zoom);
    ImGui::Checkbox("TP on click (CTRL)", &opt::tp_click);

  //TODO: clean up enhancements and cheats, sort them out and add missing options

    ImGui::NextColumn();

    ImGui::Checkbox("Spoof login info", &opt::spoof_login);
    //if (imwrap::checkbox("Use Alt Server", opt::alt_server, "Always uses the alternative server, which fixes the issues of freezing upon logon")) {
    //    *(bool*)((uintptr_t)global::gt + 0x5EA071) = opt::alt_server; //very ghetto, but theres no way to sig this
    //}
    ImGui::EndColumns();

}