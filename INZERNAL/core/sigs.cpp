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
        case sig::type::dynamic: address = detail::resolve<uintptr_t>(pattern.c_str(), offset);
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
    auto bp = add_pattern("ban bypass", "00 3B C1 75 ? 85 C9", sig::type::direct, 3, true);
    if (!bp) //will be invalid if ban bypass already patched, so we are doing this.
        add_pattern("ban bypass", "00 3B C1 90 90 85 C9", sig::type::direct, 3);

    add_pattern("gamelogic", "E8 ? ? ? ? 8b 17 ? 8d", sig::type::dynamic);
    add_pattern("tilemap", "E8 ? ? ? ? 44 8B 87 0C 01 00 00", sig::type::dynamic);
    add_pattern("world renderer", "e8 ? ? ? ? ? ? 6E 01 00", sig::type::dynamic);
    add_pattern("world to screen", "00 e8 ? ? ? ? 49 8b ? ? 41 ? 00 04", sig::type::call, 1);

    size_t invalid = 0;
    for (auto sig : database) {
        if (!sig)
            invalid++;
    }

    if (invalid == 0)
        utils::printc("92", "%zd signatures in db, all valid\n", database.size());
}
