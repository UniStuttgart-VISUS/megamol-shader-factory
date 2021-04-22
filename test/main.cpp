#include <iostream>

#include "msf/compiler.h"
#include "msf/compiler_options.h"

int main() {
    megamol::shaderfactory::compiler_options options({"../test"}, "__AMD__");
    //options.add_definition("__AMD__");

    megamol::shaderfactory::compiler compiler;
    auto content = compiler.preprocess("../test/test.vert.glsl", options);
    std::cout << content;
    return 0;
}
