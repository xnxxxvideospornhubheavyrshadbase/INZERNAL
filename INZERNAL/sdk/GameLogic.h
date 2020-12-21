#pragma once
#include <core/utils.h>
#include <sdk/world/World.h>
#include <core/sigs.hpp>
#include <core/globals.h>

class WorldRenderer;
class WorldTileMap;
class NetAvatar;

#pragma pack(push, 1)
GTClass GameLogic {
    char pad[264];
    World* world;
    WorldRenderer* renderer;
    char pad2[128];
    NetAvatar* local;

   public:
    //TODO: populate gamelogiccomponent

    NetAvatar* GetLocalPlayer() {
        return local;
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
