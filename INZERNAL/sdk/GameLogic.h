#pragma once
#include <core/utils.h>
#include <sdk/NetAvatar.h>

#pragma pack(push, 1)
GTClass GameLogic {
    char pad[448];
    NetAvatar* local;

   public:
    //TODO: populate gamelogiccomponent

    //this func just gets same member as in struct - in 2.45 that is; position in struct is unureliable so using func
    NetAvatar* GetLocalPlayer() {
        static auto ptr = utils::find_pattern<types::GetLocalPlayer>("CC 48 8B 81 ?? ?? ?? ?? C3 CC", true, 1);
        return ptr(this);
    }
};

#pragma pack(pop)

//constexpr auto offset = offsetof(GameLogic, local);