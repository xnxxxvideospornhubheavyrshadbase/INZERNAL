#pragma once
#include <core/utils.h>
#include <sdk/NetAvatar.h>

class WorldRenderer;
class WorldTileMap;

#pragma pack(push, 1)
GTClass GameLogic {
    char pad[304];
    uintptr_t tilemap; //for some reason gt doesnt direclty use this
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

     //these have not changed since 2.996, probably safe to use struct offset
    WorldTileMap* GetTileMap() {
        return (WorldTileMap*)(tilemap + 16);
    }
    WorldRenderer* GetWorldRenderer() { 
        return renderer;
    }
   /* WorldCamera* GetWorldCamera() {
    }*/
};

#pragma pack(pop)

constexpr auto offset2 = offsetof(GameLogic, local);