#include <iostream>

#include "compiler.h"
#include "compiler_options.h"

int main() {
    megamol::shaderfactory::compiler_options options;
    options.add_definition("__AMD__");
    options.set_include_paths({"..\\test\\"});

    megamol::shaderfactory::compiler compiler;
    auto content = compiler.preprocess("..\\test\\test.vert.glsl", options);
    std::cout << content;
    return 0;
}