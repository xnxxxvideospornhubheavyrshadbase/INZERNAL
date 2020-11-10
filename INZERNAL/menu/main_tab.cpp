#pragma once
#include <menu/menu.h>
#include <sdk/sdk.h>
void menu::main_tab() {
    ImGui::Text("Menu will be updated in later versions.");
    ImGui::SliderFloat("Punch cooldown", &opt::cheat::punch_cooldown_val, 0.01f, 1.f, "%0.2f");
	
    if (ImGui::Button("SDK test")) {
        auto tilemap = sdk::tilemap();
        printf("tiles: %d\n", tilemap->tiles.size());
       /* if (tilemap)
            printf("%d\n", tilemap->GetTileSafe(5, 24)->foreground);*/
    }
}