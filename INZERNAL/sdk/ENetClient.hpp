#pragma once
#include <core/utils.h>
#include <enet/include/enet.h>

#pragma pack(push, 1)
GTClass ENetClient {
   public:
    char unk1[192];
    ENetHost* host;
    ENetPeer* peer;
    int connection_timer;
    int tracking_tick;
    int conn_status;
    int another_timer;
};

#pragma pack(pop)

constexpr auto offset22 = offsetof(ENetClient, connection_timer);