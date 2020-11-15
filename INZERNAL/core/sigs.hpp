#pragma once
#include <string>
#include <vector>

namespace sig {
    enum  : int {
        banbypass = 0,
        gamelogic = 1,
        worldtilemap,
        worldrenderer,
        world2screen
    };

    namespace type {
        enum : int {
            direct, //utils::find_pattern
            fstart,   //utils::find_func_start
            call,   //detail::get_call
            dynamic //detail::get
            //leaving out some unused methods (like utils::find_func_end) of getting these for now
        };
    }
   
}

namespace sigs {
    extern std::vector<uintptr_t> database;
    uintptr_t add_pattern(std::string name, std::string pattern, int type, int offset = 0, bool ignore = false);
    void init();
    __forceinline uintptr_t get(int num) {
        return database[num];
    }
} // namespace sigs