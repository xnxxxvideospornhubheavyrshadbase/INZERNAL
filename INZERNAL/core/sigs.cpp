#pragma once
#include "sigs.hpp"
#include <core/utils.h>

std::vector<uintptr_t> sigs::database{};

uintptr_t sigs::add_pattern(std::string name, std::string pattern, int type, int offset, bool ignore) {
    uintptr_t address = 0;
    switch (type) {
        case sig::type::direct: address = utils::find_pattern(pattern.c_str(), false, offset); break;
        case sig::type::fstart: address = utils::find_func_start(pattern.c_str()) + offset; break;
        case sig::type::call: address = detail::get_call(pattern.c_str(), offset); break;
    }

    if (address == 0 || address <= offset || address >= 0xffffffffffffefff) {
        if (ignore)
            return 0;
        utils::printc("91", "pattern of %s not found!", name.c_str());
        address = 0;
    }

    database.push_back(address);
    return address;
}
void sigs::init() {
   
    auto bp = add_pattern("gt.cpp/patch_banbypass", "00 3B C1 75 ? 85 C9", sig::type::direct, 3, true);
    if (!bp) //will be invalid if ban bypass already patched, so we are doing this.
        add_pattern("gt.cpp/patch_banbypass", "00 3B C1 90 90 85 C9", sig::type::direct, 3);

    add_pattern("sdk.cpp/GetGameLogic", "E8 ? ? ? ? 8b 17 ? 8d 88", sig::type::call);
    add_pattern("WorldCamera.h/WorldToScreen", "00 e8 ? ? ? ? 49 8b ? ? 41 ? 00 04", sig::type::call, 1);
    add_pattern("sdk.cpp/GetClient", "E8 ? ? ? ? 45 ? ? 89 ? ? ? 48 8D ? ? 48", sig::type::call);

    //all hooks.cpp
    add_pattern("hooks.cpp/App::GetVersion", "28 FF 15 ?? ?? ?? ?? FF 15", sig::type::fstart);
    add_pattern("hooks.cpp/BaseApp::SetFPSLimit", "00 00 0F 57 C0 0F 2F C8 72", sig::type::fstart);
    add_pattern("hooks.cpp/LogMsg", "00 28 00 00 45", sig::type::fstart);
    add_pattern("hooks.cpp/NetAvatar::CanMessageT4", "48 8b ce e8 ? ? ? ? 84 c0 74 ? e8", sig::type::call, 3);
    add_pattern("hooks.cpp/CanPunchOrBuildNow", "00 00 83 e9 03 74 ? 83 e9 01 74 ? 83 e9 01", sig::type::fstart);
    add_pattern("hooks.cpp/ObjectMap::HandlePacket", "44 8B ?? ?? 41 83 f8 FF 75 ?? 44", sig::type::fstart);
    add_pattern("hooks.cpp/SendPacketRaw", "00 81 FE 40 42 0F 00", sig::type::fstart);
    add_pattern("hooks.cpp/HandleTouch", "83 B8 ?? ?? ?? ?? 12 75", sig::type::fstart);
    add_pattern("hooks.cpp/WorldCamera_OnUpdate", "89 43 10 0f 2f", sig::type::fstart);
    add_pattern("hooks.cpp/UpdateFromNetAvatar", "32 21 00 00 66 39", sig::type::fstart);
    add_pattern("hooks.cpp/SendPacket", "02 00 00 00 e8 ? ? ? ? 90 48 8d 4c 24 50", sig::type::call, 4);
    add_pattern("hooks.cpp/ProcessTankUpdatePacket", "83 78 04 71 75 ? 49", sig::type::fstart);
    add_pattern("hooks.cpp/CanSeeGhosts", "04 00 00 00 e8 ? ? ? ? 8b c8 e8", sig::type::call, 11);
    add_pattern("hooks.cpp/NetAvatar::Gravity", "B9 CA 27 00 00", sig::type::fstart);
    add_pattern("hooks.cpp/NetHTTP::Update", "05 4D 01 00 00 89 ?? ?? 00", sig::type::fstart);
    add_pattern("hooks.cpp/NetAvatar::ProcessAcceleration", "83 78 04 3c", sig::type::fstart);

    size_t invalid = 0;
    for (auto sig : database) {
        if (!sig)
            invalid++;
    }

    if (invalid == 0)
        utils::printc("92", "%zd signatures in db, all valid\n", database.size());
}
