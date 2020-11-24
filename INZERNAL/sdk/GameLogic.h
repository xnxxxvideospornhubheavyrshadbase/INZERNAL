#pragma once
#include <core/utils.h>
#include <sdk/NetAvatar.h>

class WorldRenderer;
class WorldTileMap;

#pragma pack(push, 1)
GTClass GameLogic {
    char pad[304];
    uintptr_t tilemap; //dont use, see GetTileMap
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
        if (!IsTileMapValid())
            return nullptr; //gt returns 16 if invalid but we should never need null tilemaps, only for ptr check

        return (WorldTileMap*)(tilemap + 16);
    }
    //for some reason gt doesnt directly use this but adds 16 to the value, so if tilemap is null, the real val from GetTileMap is still 16, i.e not null
    bool IsTileMapValid() { 
        return tilemap > 0;
    }
    WorldRenderer* GetWorldRenderer() { 
        return renderer;
    }
   /* WorldCamera* GetWorldCamera() {
    }*/
};

#pragma pack(pop)

constexpr auto offset2 = offsetof(GameLogic, local);