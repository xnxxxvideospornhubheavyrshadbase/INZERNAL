#include <sdk/sdk.h>

GameLogic* sdk::gamelogic() {
    static auto address = (GameLogic * (__cdecl*)()) sigs::get(sig::gamelogic);
    return address();
}

uintptr_t* sdk::enetclient() {
    static auto client = (uintptr_t * (__cdecl*)()) sigs::get(sig::enetclient);
    return client();
}

//been this way for over 20 versions, probably will not get updated as its in enetclient.
EnetPeer* sdk::enetpeer() {
    return (EnetPeer*)((uintptr_t)enetclient() + 200);
}
