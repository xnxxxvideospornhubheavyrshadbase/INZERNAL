#pragma once
#include <core/utils.h>
#include <sdk/NetAvatar.h>
#include <sdk/world/World.h>

class WorldRenderer;
class WorldTileMap;

#pragma pack(push, 1)
GTClass GameLogic {
    char pad[304];
    World* world;
    WorldRenderer* renderer;
    char pad2[128];
    NetAvatar* local;

   public:
    //TODO: populate gamelogiccomponent

    //this func just gets same member as in struct - in 2.45 that is; position in struct is unureliable so using func
    NetAvatar* GetLocalPlayer() {
        static auto ptr = types::GetLocalPlayer(sigs::get(sig::getlocalplayer));
        return ptr(this);
    }

     //render + tilemap offsets have not changed since 2.996, probably safe to use struct
    WorldTileMap* GetTileMap() {
        if (!world)
            return nullptr; 
        return &world->tilemap; 
    }
    WorldObjectMap* GetObjectMap() {
        if (!world)
            return nullptr;
        return &world->worldobjectmap;
    }
    WorldRenderer* GetWorldRenderer() { 
        return renderer;
    }
    World* GetWorld() {
        return world;
    }
   /* WorldCamera* GetWorldCamera() {
    }*/
};

#pragma pack(pop)

constexpr auto offset2 = offsetof(GameLogic, renderer);