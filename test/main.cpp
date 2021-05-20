#include <iostream>

#define MSF_OPENGL_INCLUDE_GLAD
#include "msf/ShaderFactory.h"
#include "msf/ShaderFactoryOptionsOpenGL.h"

int main() {
    msf::ShaderFactoryOptionsOpenGL options({"../test"}, "__AMD__");
    // options.addDefinition("__AMD__");

    msf::ShaderFactory factory;
    auto content = factory.preprocess("../test/test.vert.glsl", options);
    std::cout << content << std::endl;

    return 0;
}
