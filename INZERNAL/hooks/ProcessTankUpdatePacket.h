#pragma once
#include <core/globals.h>
#include <core/gt.h>
#include <sdk/sdk.h>
#include <string>

class ProcessTankUpdatePacketHook {
   public:
    static void Execute(types::ProcessTankUpdatePacket orig, GameLogic* logic, GameUpdatePacket* packet) {
        printf("got raw packet with type: %d\n", packet->type);
        orig(logic, packet);
    }
};