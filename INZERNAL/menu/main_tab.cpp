#pragma once
#include <menu/menu.h>
#include <sdk/sdk.h>
void menu::main_tab() {
    ImGui::Text("Menu will be updated in later versions.");
    ImGui::SliderFloat("Punch cooldown", &opt::cheat::punch_cooldown_val, 0.01f, 1.f, "%0.2f");


    ImGui::Text("gamelogic: %llx", sdk::GetGameLogic());
    ImGui::Text("tilemap: %llx", sdk::GetGameLogic()->GetTileMap());
    ImGui::Text("renderer: %llx", sdk::GetGameLogic()->GetWorldRenderer());
    ImGui::Text("enetclient: %llx", sdk::GetClient());

    if (ImGui::Button("SDK test")) {
        auto tilemap = sdk::GetGameLogic()->GetTileMap();

        if (tilemap) {
            printf("tiles: %d\n", tilemap->tiles.size());
            auto tile = tilemap->GetTileSafe(5, 24);
            printf("%d %d\n", tile->position_x, tile->position_y);
        }
    }
}