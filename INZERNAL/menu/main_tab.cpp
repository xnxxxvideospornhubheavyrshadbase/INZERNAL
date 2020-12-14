#pragma once
#include <menu/menu.h>
#include <sdk/sdk.h>
void menu::main_tab() {
    ImGui::Text("Menu will be updated in later versions.");

    ImGui::ToggleButton("test", &opt::cheat::punch_cooldown_on, ImVec2{ 50, 25 }, 0);
    if (ImGui::CollapsingHeader("Punch/build cooldown changer")) {
        if (ImGui::BeginChild("###cooldownchanger", ImVec2(ImGui::GetWindowWidth() * 0.93f, 60.f), true)) {
            ImGui::Checkbox("Enable###punch", &opt::cheat::punch_cooldown_on);
            ImGui::SameLine();
            ImGui::SliderFloat("####pcoold", &opt::cheat::punch_cooldown_val, 0.05f, 0.4f, "%0.2f");
            ImGui::Text("Shouldn't ban but low values will disconnect.");
            ImGui::EndChild();
        }
    }
    if (ImGui::CollapsingHeader("Gravity changer")) {
        if (ImGui::BeginChild("###gravitychanger", AUTOSIZE(2), true)) {
            ImGui::Checkbox("Enable###grav", &opt::cheat::gravity_on);
            ImGui::SameLine();
            ImGui::SliderFloat("###grav", &opt::cheat::gravity_val, -500.0f, 2000.f, "%0.0f");
            ImGui::Text("Shouldn't ban except negative/zero gravity when in air for too long.");
            ImGui::EndChild();
        }
    }

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
    //ImGui::SetColumnWidth(0, ImGui::GetWindowWidth() * 0.365f);


    ImGui::Checkbox("Block sendpacketraw", &opt::cheat::block_sendpacketraw);
    ImGui::Checkbox("Antighost", &opt::cheat::antighost);
    ImGui::Checkbox("See ghosts", &opt::see_ghosts);

    ImGui::NextColumn();

    ImGui::Checkbox("Mod zoom", &opt::mod_zoom);
    ImGui::Checkbox("Dev zoom", &opt::cheat::dev_zoom);
    ImGui::Checkbox("TP on click (CTRL)", &opt::tp_click);

    ImGui::NextColumn();

    ImGui::Checkbox("Spoof login info", &opt::spoof_login);

    ImGui::EndColumns();

    ImGui::Text("gamelogic: %llx", sdk::GetGameLogic());
    ImGui::Text("tilemap: %llx", sdk::GetGameLogic()->GetTileMap());
    ImGui::Text("world: %llx", sdk::GetGameLogic()->GetWorld());
    ImGui::Text("renderer: %llx", sdk::GetGameLogic()->GetWorldRenderer());
    auto client = sdk::GetClient();
    if (client) {
        ImGui::Text("enetclient: %llx", client);
        ImGui::Text("peer: %llx, host %llx", client->peer, client->host);
        ImGui::InputInt("tracking_tick", &client->tracking_tick);
        ImGui::InputInt("conn_status", &client->conn_status);
        ImGui::InputInt("another_timer", &client->another_timer);

        /*   if (client->connection_timer < 1)
            client->connection_timer = 1;*/
    }

    if (ImGui::Button("SDK test")) {
        auto tilemap = sdk::GetGameLogic()->GetTileMap();

        if (tilemap) {
            printf("tiles: %d %d %zd\n", tilemap->size.x, tilemap->size.y, tilemap->tiles.size());
            auto tile = tilemap->GetTileSafe(5, 24);
            printf("%d %d\n", (int)tile->position_x, (int)tile->position_y);
        }
    }
    ImGui::SameLine();
    if (ImGui::Button("Get fz/zf of fz.exe")) {
        uint32_t size{};
        auto file = utils::read_file("fz.exe", size);

        if (!file)
            printf("File fz.exe does not exist!\n");
        else {
            auto fz = size;
            auto zf = HashString((const char*)file, size);

            printf("fz: %d, zf: %d\n", fz, zf);
            free(file);
        }
    }
}