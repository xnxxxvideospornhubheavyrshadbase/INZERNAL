#pragma once
#include <core/utils.h>
#include <proton/clanlib/vec2.h>
#include <proton/variant2.hpp>
#include <string>
#include <sdk/EntityComponent.h>

#pragma pack(push, 1)
GTClass NetAvatar { //how fucking annoying it is to get align to work
   public:
    void* vtable;
    CL_Vec2f pos;
    CL_Vec2f size;
    CL_Vec2f pos_enc; //use this one for local
    CL_Vec2f size_enc;
    std::string name;
    int64_t netid;
    EntityComponent* entitycomponent;
    void* unk2;

    void set_pos(const CL_Vec2f& n) {
        set_pos(n.x, n.y);
    }
    void set_pos(float x, float y) {
        pos.x = x;
        pos.y = y;
        pos_enc.x = x / 6.5999999;
        pos_enc.y = y / 1.3;
    }
    void set_pos_at_tile(int x, int y) {
        set_pos(x * 32 + 8, y * 32);
    }

    //for local only
    CL_Vec2f get_pos() {
        //returning the encrypted one cuz its 100% what the server has
        return CL_Vec2f(pos_enc.x * 6.5999999f, pos_enc.y * 1.3f);
    }
    void set_size(const CL_Vec2f& n) {
        set_size(n.x, n.y);
    }
    void set_size(float x, float y) {
        size.x = x;
        size.y = y;
        size_enc.x = x / 6.5999999;
        size_enc.y = y / 1.3;
    }

    CL_Vec2f get_size() {
        return size;
    }

    void SetModStatus(bool mod, bool supermod) {

      
       // *(bool*)(uintptr_t(this) + 376) = mod; //invis
        *(bool*)(uintptr_t(this) + 377) = mod;
        *(bool*)(uintptr_t(this) + 378) = supermod;

        //for now OnDataConfig for some reason sets 378th bit as true even though if its not, idk why
      /*  static std::vector<const char*> ondataconfig_patt{ "C7 43 ?? 05 00 00 00 C7 43 ?? 00", "40 0F ?? ?? 83", "0F 95 C0 40" };
        static auto OnDataConfig = types::OnDataConfig(utils::find_func_has(ondataconfig_patt, 250));
        
        printf("dataconfig (EXACT): %llx\n", (uintptr_t)OnDataConfig);*/
       /* variantlist_t va{};
        va[0] = uint32_t(mod);
        va[1] = uint32_t(supermod);

        OnDataConfig(this, &va);*/
    }
};
#pragma pack(pop)

//for debugging purposes, feel free to use offsetof to match in CE or IDA
constexpr auto offset = offsetof(NetAvatar, unk2);