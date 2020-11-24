#include <sdk/sdk.h>

GameLogic* sdk::GetGameLogic() {
    static auto address = (GameLogic * (__cdecl*)()) sigs::get(sig::gamelogic);
    return address();
}

uintptr_t* sdk::GetClient() {
    static auto client = (uintptr_t * (__cdecl*)()) sigs::get(sig::enetclient);
    return client();
}

//been this way for over 20 versions, probably will not get updated as its in enetclient.
EnetPeer* sdk::GetPeer() {
    return (EnetPeer*)((uintptr_t)GetClient() + 200);
}
