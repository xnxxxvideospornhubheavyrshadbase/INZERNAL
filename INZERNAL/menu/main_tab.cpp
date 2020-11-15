#pragma once
#include <menu/menu.h>
#include <sdk/sdk.h>
void menu::main_tab() {
    ImGui::Text("Menu will be updated in later versions.");
    ImGui::SliderFloat("Punch cooldown", &opt::cheat::punch_cooldown_val, 0.01f, 1.f, "%0.2f");

    //TODO: add rest of signatures


    ImGui::Text("gamelogic: %llx", sdk::gamelogic());
    ImGui::Text("tilemap: %llx", sdk::gamelogic()->GetTileMap());
    ImGui::Text("renderer: %llx", sdk::gamelogic()->GetWorldRenderer());
    ImGui::Text("enetclient: %llx", sdk::enetclient());

    if (ImGui::Button("SDK test")) {
        auto tilemap = sdk::gamelogic()->GetTileMap();

        if (tilemap) {
            printf("tiles: %d\n", tilemap->tiles.size());
            auto tile = tilemap->GetTileSafe(5, 24);
            printf("%d %d\n", tile->position_x, tile->position_y);
        }
    }
}