#include <iostream>

#include "msf/ShaderFactory.h"
#include "msf/ShaderFactoryOptions.h"

int main() {
    msf::ShaderFactoryOptions options({"../test"}, "__AMD__");
    // options.add_definition("__AMD__");

    msf::ShaderFactory factory;
    auto content = factory.preprocess("../test/test.vert.glsl", options);
    std::cout << content;
    return 0;
}
