#pragma once
//include everything here so no need to include them individually in other files
#include <sdk/GameLogic.h>
#include <sdk/GameUpdatePacket.h>
#include <sdk/NetAvatar.h>
#include <sdk/AvatarRenderData.h>
#include <sdk/WorldTileMap.h>

class EnetPeer;
namespace sdk {
	GameLogic* gamelogic();
    WorldTileMap* tilemap();
	uintptr_t* enetclient(); //TODO: class for enetclient
    EnetPeer* enetpeer();

}