#pragma once
#include <proton/variant2.hpp>


struct __declspec(align(1)) alignas(1) Tile {
   public:
    int unk;
    __int16 foreground;
    __int16 background;
    __int16 flags;
    char position_x;
    char position_y;
    short unk3;
    short texture_pos;
    short texture_pos_bg;
    char pad0[6];
    rect_t collision_rect; //see: Tile::BuildCache and Tile::DoesWorldRectCollide
    void* tile_extra;
    char health_or_damage;
    __int16 unk6;
    int last_tick_punched;
    int unk7;
    int some_tick_2;
    float opacity_maybe;
    char pad[6];
    __int16 backup_flags_maybe;
    char pad1[48]; //to get to 128 as size (see WorldTileMap::Clear)
    void set_tile_foreground(short id) {
        static auto address = detail::get_call<settileforeground_t>("cd e8 ? ? ? ? 41 bf 0f", 1);
        address(this, id);
    }

    void set_text(textmanager_t* manager, const std::string& str, unsigned int background, unsigned int border, CL_Vec2f pos) {
        auto text = manager->add_text(this, str);
        text->position = pos;
        text->set_color(background, border);
    }
    void toggle_flag(short flag) {
        static auto func = flag_generic_t(utils::find_func_start("66 31 51 08"));
        func(this, flag);
    }
    void enable_flag(short flag) {
        static auto func = flag_generic_t(utils::find_func_start("66 09 51 08"));
        func(this, flag);
    }
    void remove_flag(short flag) {
        static auto func = flag_generic_t(utils::find_func_start("66 21 51 08"));
        func(this, flag);
    }
    bool is_collideable(unsigned int uid, world_t* world) {
        static auto func = is_collideable_t(utils::find_func_start("02 74 ? 83 f8 07 74 ? 8b"));
        if (!world || !this)
            return true;
        return func(this, uid, world, true);
    }
    CL_Vec2f get_pos_at_world() {
        return CL_Vec2f{ (float)this->position_x * 32.f, (float)this->position_y * 32.f };
    }
    CL_Vec2i get_pos() {
        return CL_Vec2i{ this->position_x, this->position_y };
    }
};
