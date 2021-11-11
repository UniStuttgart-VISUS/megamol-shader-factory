#include <iostream>

#include "msf/ShaderFactory.h"
#include "msf/ShaderFactoryOptions.h"

int main() {
    msf::ShaderFactoryOptions options({"../test"});
    options.addDefinition("__AMD__");

    msf::ShaderFactory factory;
    auto content = factory.preprocess("../test/test.vert.glsl", options);
    std::cout << content << std::endl;

    return 0;
}
