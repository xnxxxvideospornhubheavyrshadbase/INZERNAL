#pragma once
#include <menu/menu.h>
#include <sdk/sdk.h>

void menu::framework_tab() {
    auto& style = ImGui::GetStyle();
    //setup columns and some style
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ style.WindowPadding.x, style.ItemSpacing.y });
    ImGui::Columns(3, nullptr, true);
    float group_w = ImGui::GetCurrentWindow()->Size.x - style.WindowPadding.x * 2;
    ImGui::SetColumnOffset(1, group_w / 3.0f);
    ImGui::SetColumnOffset(2, 2 * group_w / 3.0f);
    ImGui::SetColumnOffset(3, 3 * group_w / 3.0f);

    auto client = sdk::GetClient();
    auto logic = sdk::GetGameLogic();
    auto local = logic->GetLocalPlayer();
    auto world = logic->GetWorld();
    auto tilemap = logic->GetTileMap();
    bool local_div = ImGui::BeginChild("Player", ImVec2(ImGui::GetWindowWidth() / 3.1f, 250.f), true, ImGuiWindowFlags_MenuBar);
    if (local_div && local) {
        ImGui::BeginMenuBar();
        ImGui::Text("Player");
        ImGui::EndMenuBar();

        ImGui::Text("Name: %s", local->name.c_str());
        ImGui::Text("Netid: %d", local->netid);
        ImGui::Text("Address: %llx", local);
        ImGui::Separator();
        ImGui::Text("NetControllerLocal: %llx", local->NetControllerLocal);
        ImGui::Text("AvatarPacketReceiver: %llx", local->AvatarPacketReceiver);
        ImGui::Text("AvatarPacketSender: %llx", local->AvatarPacketSender);
        ImGui::Separator();

        ImGui::Text("Size: %.0f,%.0f", local->size.x, local->size.y);
        auto pos2f = local->GetPos();
        ImGui::Text("Position: %.0f,%.0f", pos2f.x, pos2f.y);

        static float xpos = 0.f, ypos = 0.f;
        ImGui::PushItemWidth(100.f);
        ImGui::InputFloat("X", &xpos, 10.f, 10.f, 0.f);
        ImGui::SameLine();
        ImGui::InputFloat("Y", &ypos, 10.f, 10.f, 0.f);
        ImGui::PopItemWidth();
        if (ImGui::Button("Teleport"))
            local->SetPos(xpos, ypos);
        ImGui::EndChild();
    }
    else if (local_div && !local) {
        ImGui::BeginMenuBar();
        ImGui::Text("Player");
        ImGui::EndMenuBar();
        ImGui::TextDisabled("Not in a world.");
        ImGui::EndChild();
    }

    ImGui::NextColumn();

    bool world_div = ImGui::BeginChild("World", ImVec2(ImGui::GetWindowWidth() / 3.1f, 250.f), true, ImGuiWindowFlags_MenuBar);
    if (world_div && world) {
        ImGui::BeginMenuBar();
        ImGui::Text("World");
        ImGui::EndMenuBar();

        ImGui::Text("Name: %s", world->name.c_str());
        ImGui::Text("Address: %llx", world);
        ImGui::Separator();
        ImGui::Text("WorldRenderer: %llx", logic->GetWorldRenderer());
        ImGui::Text("TileMap: %llx", tilemap);
        auto objmap = logic->GetObjectMap();
        ImGui::Text("WorldObjectMap: %llx", objmap);
        ImGui::Separator();

        static int x = 0, y = 0;
        static Tile* tile = tilemap->GetTileSafe(x, y);

        if (ImGui::CollapsingHeader("Tile information")) {
            ImGui::PushItemWidth(150.f);
            if (ImGui::InputInt("X", &x, 1, 10)) {
                if (x > 99)
                    x = 99;
                else if (x < 0)
                    x = 0;
                tile = tilemap->GetTileSafe(x, y);
            }

            if (ImGui::InputInt("Y", &y, 1, 10)) {
                if (y > 59)
                    y = 59;
                else if (y < 0)
                    y = 0;
                tile = tilemap->GetTileSafe(x, y);
            }
            ImGui::PopItemWidth();
            ImGui::Separator();
            if (tile) {
                ImGui::Text("Foreground: %d", tile->foreground);
                ImGui::Text("Background: %d", tile->background);
                ImGui::Text("Flags: %d", tile->flags);
                ImGui::Text("FG texture pos: %d,%d", (int)(tile->texture_pos % 8), (int)(tile->texture_pos / 8));
                ImGui::Text("BG texture pos: %d,%d", (int)(tile->texture_pos_bg % 8), (int)(tile->texture_pos_bg / 8));
            }
            else
                ImGui::TextColored(ImVec4(231.0f / 255.0f, 76.0f / 255.0f, 60.0f / 255.0f, 1.0f), "Invalid tile");
        }
        if (objmap && ImGui::CollapsingHeader("Dropped items")) {

            ImGui::Columns(4, "dropped"); // 4-ways, with border
            static auto width = ImGui::GetColumnWidth(0);

            ImGui::SetColumnWidth(0, width * 0.65f);
            ImGui::SetColumnWidth(1, width * 1.05f);
            ImGui::SetColumnWidth(2, width * 0.80f);
            
            ImGui::Separator();
            ImGui::Text("OID");
            ImGui::NextColumn();
            ImGui::Text("Item ID");
            ImGui::NextColumn();
            ImGui::Text("Count");
            ImGui::NextColumn();
            ImGui::Text("Position");
            ImGui::NextColumn();
            ImGui::Separator();
            for (auto it = objmap->objects.begin(); it != objmap->objects.end(); ++it) {
                ImGui::Text("%d", it->object_id);
                ImGui::NextColumn();
                ImGui::Text("%d", it->item_id);
                ImGui::NextColumn();
                ImGui::Text("%d", it->amount);
                ImGui::NextColumn();
                ImGui::Text("%.0f,%.0f", it->pos.x, it->pos.y);
                ImGui::NextColumn();
            }
            ImGui::Columns(1);
            ImGui::Separator();
        }
        ImGui::EndChild();
    }
    else if (world_div && !world) {
        ImGui::BeginMenuBar();
        ImGui::Text("World");
        ImGui::EndMenuBar();
        ImGui::TextDisabled("Not in a world.");
        ImGui::EndChild();
    }

    ImGui::NextColumn();

    bool client_div = ImGui::BeginChild("ENetClient", ImVec2(ImGui::GetWindowWidth() / 3.1f, 250.f), true, ImGuiWindowFlags_MenuBar);
    if (client_div && client) {
        ImGui::BeginMenuBar();
        ImGui::Text("ENetClient");
        ImGui::EndMenuBar();

        ImGui::Text("Address: %llx", client);
        ImGui::Separator();
        ImGui::Text("Host: %llx", client->host);
        ImGui::Text("Peer: %llx", client->peer);
        ImGui::Text("Address: %s:%d", client->address.c_str(), client->port);
        ImGui::Text("User: %u", client->user);
        ImGui::Text("Token: %u", client->token);
        ImGui::Separator();
        ImGui::PushItemWidth(150.0f);
        ImGui::InputInt("tracking_tick", &client->tracking_tick);
        ImGui::InputInt("conn_status", &client->conn_status);
        ImGui::InputInt("another_timer", &client->another_timer);
        ImGui::InputInt("connection_timer", &client->connection_timer);
        ImGui::PopItemWidth();
        ImGui::EndChild();
    }
    else if (client_div && !client) {
        ImGui::BeginMenuBar();
        ImGui::Text("ENetClient");
        ImGui::EndMenuBar();
        ImGui::TextDisabled("Not connected.");
        ImGui::EndChild();
    }

    ImGui::Columns(1, nullptr, false);
    ImGui::PopStyleVar();

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
    ImGui::SameLine();
    ImGui::Text("GameLogic: %llx", logic);
}