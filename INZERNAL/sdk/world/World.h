#pragma once
#include <core/utils.h>

class WorldTileMap;

#pragma pack(push, 1)
GTClass World { //TODO: literally load offline worlds with World::LoadFromMem, would be kinda epic
   public:
    void* vtable;
    short version; //our latest known ver is 15
    char pad1[4]; //TODO: find out what this is
    WorldTileMap* TileMap;
    char pad2[50]; //TODO: find out what this is
    void* WorldObjectMap;
    //padding
    //world object map
};
#pragma pack(pop)

constexpr auto objmap = offsetof(World, WorldObjectMap);