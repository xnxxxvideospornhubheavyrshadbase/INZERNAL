#pragma once
#include <core/utils.h>
#include <sdk/NetAvatar.h>
#include <sdk/Tile.h>

#pragma pack(push, 1)
struct __declspec(align(1)) alignas(1) WorldTileMap {
    class tilemap_t {
       private:
        void* vftable;
        CL_Vec2i size;
        char pad0[8];

       public:
        std::vector<Tile> tiles;
        CL_Vec2i& world_size() {
            return size;
        }
        Tile* GetTileSafe(int col, int row) { //85 d2 78 ? 45 85 c0 78 ? 8b 41 08
            return &tiles[col + row * size.x];
        }
        Tile* GetTileSafe(CL_Vec2i vec) {
            return GetTileSafe(vec.x, vec.y);
        }
    };

#pragma pack(pop)
