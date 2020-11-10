#pragma once
#include <sdk/world/World.h>

#pragma pack(push, 1)
GTClass WorldRenderer {
   public:
    void* vtable;
    World* world;

    //all outdated below for now, dont use any of this for now

    //char pad[64];
    //char steammanager[40];
    //char worldcamera[40];
    //char pad1[24];
    //void* background;
    //char pad1b[8];
    //char newpad[16];
    //void* psystem; //or maybe particlesystem ,i just dont fucking know lol
    //char particlesystem_contents[56];
    //char pad2[104];
    //avatarrenderdata_t avatar_render_data;

    //void force_background(int bg) {
    //    static auto forcebackground = forcebg_t(utils::find_func_start("c7 40 24 00 00 80 3f e9"));
    //    forcebackground(this, bg);
    //}

};
#pragma pack(pop)
