#pragma once


#include "shaderc/shaderc.h"

//#include "glslang/Public/ShaderLang.h"

namespace megamol {
namespace shaderfactory {

class shaderfactory {
public:
    shaderfactory(shaderfactory const&) = delete;
    shaderfactory& operator=(shaderfactory const&) = delete;
    shaderfactory(shaderfactory&&) = delete;
    shaderfactory& operator=(shaderfactory&&) = delete;

    // https://codereview.stackexchange.com/questions/173929/modern-c-singleton-template
    static auto& instance() {
        static shaderfactory factory;
        return factory;
    }

private:
    shaderfactory() {
        //glslang::InitializeProcess();
    }

    ~shaderfactory() {
        // glslang::FinalizeProcess();
    }
};

} // end namespace shaderfactory
} // end namespace megamol
