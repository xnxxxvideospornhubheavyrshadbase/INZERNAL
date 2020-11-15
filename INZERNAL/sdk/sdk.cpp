#include <sdk/sdk.h>

GameLogic* sdk::gamelogic() {
    static auto address = (GameLogic * (__cdecl*)())sigs::get(sig::gamelogic);
    return address();
}

WorldTileMap* sdk::tilemap() {
    static auto address = (WorldTileMap * (__cdecl*)())sigs::get(sig::worldtilemap);
    return address();
}

WorldRenderer* sdk::renderer() {
    static auto address = (WorldRenderer * (__cdecl*)())sigs::get(sig::worldrenderer);
    return address();
}

uintptr_t* sdk::enetclient() {
    static auto client = detail::get_call<uintptr_t*(__cdecl*)()>("E8 ? ? ? ? 45 ? ? 89 ? ? ? 48 8D ? ? 48", 0);
    return client();
}

//been this way for over 20 versions, probably will not get updated as its in enetclient.
EnetPeer* sdk::enetpeer() {
    return (EnetPeer*)((uintptr_t)enetclient() + 200);
}
