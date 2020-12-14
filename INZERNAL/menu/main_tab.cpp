#pragma once
#include <menu/menu.h>
#include <sdk/sdk.h>
void menu::main_tab() {
    ImGui::Text("Menu will be updated in later versions.");

    if (ImGui::CollapsingHeader("Punch/build cooldown changer")) {
        if (ImGui::BeginChild("###cooldownchanger", ImVec2(ImGui::GetWindowWidth() * 0.93f, 60.f), true)) {
            ImGui::Checkbox("Enable", &opt::cheat::punch_cooldown_on);
            ImGui::SameLine();
            ImGui::SliderFloat("####pcoold", &opt::cheat::punch_cooldown_val, 0.05f, 0.4f, "%0.2f");
            ImGui::Text("Shouldn't ban but low values will disconnect.");
            ImGui::EndChild();
        }
    }
    if (ImGui::CollapsingHeader("Gravity changer")) {
        if (ImGui::BeginChild("###gravitychanger", ImVec2(ImGui::GetWindowWidth() * 0.93f, 60.f), true)) {
            ImGui::Checkbox("Enable", &opt::cheat::gravity_on);
            ImGui::SameLine();
            ImGui::SliderFloat("###grav", &opt::cheat::gravity_val, -500.0f, 2000.f, "%0.0f");
            ImGui::Text("Shouldn't ban except negative/zero gravity when in air for too long.");
            ImGui::EndChild();
        }
    }

     if (ImGui::CollapsingHeader("Custom Server")) {
        if (ImGui::BeginChild("###customserver", ImVec2(ImGui::GetWindowWidth() * 0.93f, 60.f), true)) {
            ImGui::Checkbox("Enable", &opt::custom_server_on);
            ImGui::SameLine();
            menu::InputTextSTL("##serverval", &opt::custom_server_val);
            ImGui::Text("You can connect to private servers with this too.");
            ImGui::EndChild();
        }
    }
    ImGui::Checkbox("Block sendpacketraw", &opt::cheat::block_sendpacketraw);

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
            printf("tiles: %d %d %d\n", tilemap->size.x, tilemap->size.y, tilemap->tiles.size());
            auto tile = tilemap->GetTileSafe(5, 24);
            printf("%d %d\n", tile->position_x, tile->position_y);
        }
    }
}