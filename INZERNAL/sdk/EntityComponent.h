#pragma once
#include <core/utils.h>

#include <sdk/world/Tile.h>

#pragma pack(push, 1)
GTClass EntityComponent {
   public:
    int test;
    //currently not possible to make anything for this since this needs such a big chunk of (full) proton and needs boost
};
#pragma pack(pop)

//constexpr auto offset = offsetof(EntityComponent, parent);