#include <iostream>

#include "msf/LineTranslator.h"
#include "msf/ShaderFactory.h"
#include "msf/ShaderFactoryOptions.h"

int main() {
    msf::ShaderFactoryOptions options({"../test"});
    options.addDefinition("__AMD__");

    msf::ShaderFactory factory;
    auto source = factory.preprocess("../test/test.vert.glsl", options);
    std::cout << "============================================================" << std::endl;
    std::cout << source << std::endl;
    std::cout << "============================================================" << std::endl;

    msf::LineTranslator t;
    std::string clean = t.cleanupShader(source);
    std::cout << clean << std::endl;
    std::cout << "============================================================" << std::endl;

    return 0;
}
