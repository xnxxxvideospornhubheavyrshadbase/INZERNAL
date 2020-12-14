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
    uint32_t netid;
    uint32_t unk01;
    EntityComponent* entitycomponent;
    void* unk0;
    byte unk1;
    byte facing_left;
    char unk2[106];
    float unk3;
    uint32_t unk4;
    bool unk5;
    char unk02[15];
    float velocity_x;
    char unk03[8];
    float impulse_x;
    char unk6[24];
    int emotion;
    char unk7[8];
    void* NetControllerLocal; //280
    void* AvatarPacketReceiver;
    void* AvatarPacketSender;
    char unk8[148];
    float gravity;
    char unk9[8];
    float gravity_verify;

    //TODO: somehow differentiate between local and others so you can use SetPos, GetPos for other players too
    //(since they dont use encrypted coords too)

    void SetPos(const CL_Vec2f& n) {
        SetPos(n.x, n.y);
    }
    void SetPos(float x, float y) {
        pos.x = x;
        pos.y = y;
        pos_enc.x = x / 6.5999999;
        pos_enc.y = y / 1.3;
    }
    void SetPosAtTile(int x, int y) {
        SetPos(x * 32 + 8, y * 32);
    }

    //for local only
    CL_Vec2f GetPos() {
        //returning the encrypted one cuz its 100% what the server has
        return CL_Vec2f(pos_enc.x * 6.5999999f, pos_enc.y * 1.3f);
    }
    void SetSize(const CL_Vec2f& n) {
        SetSize(n.x, n.y);
    }
    void SetSize(float x, float y) {
        size.x = x;
        size.y = y;
        size_enc.x = x / 6.5999999;
        size_enc.y = y / 1.3;
    }

    CL_Vec2f GetSize() {
        return size;
    }

    void SetModStatus(bool mod, bool supermod) {
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
constexpr auto offset = offsetof(NetAvatar, NetControllerLocal);

