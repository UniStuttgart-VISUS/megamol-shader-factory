#version 430

#include "common.h"
#include "common.h"

#ifdef __AMD__
uniform float IsAmd;
#else
uniform float IsNotAmd;
#endif

void main() {
  gl_Position = vec4(1.0);
}
