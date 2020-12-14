#pragma once
#include <core/globals.h>
#include <core/gt.h>
#include <sdk/sdk.h>
#include <string>

class ProcessTankUpdatePacketHook {
   public:
    static void Execute(types::ProcessTankUpdatePacket orig, GameLogic* logic, GameUpdatePacket* packet) {
        if (logging::enabled) {
            if (logging::console & logging::processtank)
                printf("got raw packet: %d [%s]\n", packet->type, gt::get_type_string(packet->type).c_str());
        }

        if (packet->type == PACKET_CALL_FUNCTION && logging::enabled && logging::console & logging::callfunction) {
            variantlist_t varlist{};
            if (varlist.serialize_from_mem(utils::get_extended(packet))) {
                auto content = varlist.print();
                printf("%s\n", content.c_str());
            }
        }
        orig(logic, packet);
    }
};