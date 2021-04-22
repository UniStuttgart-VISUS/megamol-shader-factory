/*
 * compiler_options.h
 *
 * Copyright (C) 2020-2021 by Universitaet Stuttgart (VISUS). Alle Rechte vorbehalten.
 */
#pragma once

#include <filesystem>
#include <vector>

#include "glslang/Public/ShaderLang.h"

#include "msf/includer.h"

namespace megamol::shaderfactory {

/*
 * default resource limits for glslang compiler
 * Adapted from: https://github.com/google/shaderc/blob/main/libshaderc_util/src/resources.cc
 * License: Apache 2.0
 */
const TBuiltInResource default_resource_limits = {
    /*.maxLights = */ 8,        // From OpenGL 3.0 table 6.46.
    /*.maxClipPlanes = */ 6,    // From OpenGL 3.0 table 6.46.
    /*.maxTextureUnits = */ 2,  // From OpenGL 3.0 table 6.50.
    /*.maxTextureCoords = */ 8, // From OpenGL 3.0 table 6.50.
    /*.maxVertexAttribs = */ 16,
    /*.maxVertexUniformComponents = */ 1024,
    /*.maxVaryingFloats = */ 60, // From OpenGLES 3.1 table 6.44.
    /*.maxVertexTextureImageUnits = */ 16,
    /*.maxCombinedTextureImageUnits = */ 80,
    /*.maxTextureImageUnits = */ 16,
    /*.maxFragmentUniformComponents = */ 1024,

    /*.maxDrawBuffers = */ 8,

    /*.maxVertexUniformVectors = */ 256,
    /*.maxVaryingVectors = */ 15,
    /*.maxFragmentUniformVectors = */ 256,
    /*.maxVertexOutputVectors = */ 16,  // maxVertexOutputComponents / 4
    /*.maxFragmentInputVectors = */ 32, // maxFragmentInputComponents / 4
    /*.minProgramTexelOffset = */ -8,
    /*.maxProgramTexelOffset = */ 7,
    /*.maxClipDistances = */ 8,
    /*.maxComputeWorkGroupCountX = */ 65535,
    /*.maxComputeWorkGroupCountY = */ 65535,
    /*.maxComputeWorkGroupCountZ = */ 65535,
    /*.maxComputeWorkGroupSizeX = */ 1024,
    /*.maxComputeWorkGroupSizeY = */ 1024,
    /*.maxComputeWorkGroupSizeZ = */ 64,
    /*.maxComputeUniformComponents = */ 1024,
    /*.maxComputeTextureImageUnits = */ 16,
    /*.maxComputeImageUniforms = */ 8,
    /*.maxComputeAtomicCounters = */ 8,
    /*.maxComputeAtomicCounterBuffers = */ 8,
    /*.maxVaryingComponents = */ 60,
    /*.maxVertexOutputComponents = */ 64,
    /*.maxGeometryInputComponents = */ 64,
    /*.maxGeometryOutputComponents = */ 128,
    /*.maxFragmentInputComponents = */ 128,
    /*.maxImageUnits = */ 8,
    /*.maxCombinedImageUnitsAndFragmentOutputs = */ 8, // ?
    /*.maxCombinedShaderOutputResources = */ 8,
    /*.maxImageSamples = */ 0,
    /*.maxVertexImageUniforms = */ 0,
    /*.maxTessControlImageUniforms = */ 0,
    /*.maxTessEvaluationImageUniforms = */ 0,
    /*.maxGeometryImageUniforms = */ 0,
    /*.maxFragmentImageUniforms = */ 8,
    /*.maxCombinedImageUniforms = */ 8,
    /*.maxGeometryTextureImageUnits = */ 16,
    /*.maxGeometryOutputVertices = */ 256,
    /*.maxGeometryTotalOutputComponents = */ 1024,
    /*.maxGeometryUniformComponents = */ 1024,
    /*.maxGeometryVaryingComponents = */ 60, // Does not seem to be defined
                                             // anywhere, set equal to
                                             // maxVaryingComponents.
    /*.maxTessControlInputComponents = */ 128,
    /*.maxTessControlOutputComponents = */ 128,
    /*.maxTessControlTextureImageUnits = */ 16,
    /*.maxTessControlUniformComponents = */ 1024,
    /*.maxTessControlTotalOutputComponents = */ 4096,
    /*.maxTessEvaluationInputComponents = */ 128,
    /*.maxTessEvaluationOutputComponents = */ 128,
    /*.maxTessEvaluationTextureImageUnits = */ 16,
    /*.maxTessEvaluationUniformComponents = */ 1024,
    /*.maxTessPatchComponents = */ 120,
    /*.maxPatchVertices = */ 32,
    /*.maxTessGenLevel = */ 64,
    /*.maxViewports = */ 16,
    /*.maxVertexAtomicCounters = */ 0,
    /*.maxTessControlAtomicCounters = */ 0,
    /*.maxTessEvaluationAtomicCounters = */ 0,
    /*.maxGeometryAtomicCounters = */ 0,
    /*.maxFragmentAtomicCounters = */ 8,
    /*.maxCombinedAtomicCounters = */ 8,
    /*.maxAtomicCounterBindings = */ 1,
    /*.maxVertexAtomicCounterBuffers = */ 0,

    /*.maxTessControlAtomicCounterBuffers = */ 0,
    /*.maxTessEvaluationAtomicCounterBuffers = */ 0,
    /*.maxGeometryAtomicCounterBuffers = */ 0,

    /*.maxFragmentAtomicCounterBuffers = */ 1,
    /*.maxCombinedAtomicCounterBuffers = */ 1,
    /*.maxAtomicCounterBufferSize = */ 32,
    /*.maxTransformFeedbackBuffers = */ 4,
    /*.maxTransformFeedbackInterleavedComponents = */ 64,
    /*.maxCullDistances = */ 8,
    /*.maxCombinedClipAndCullDistances = */ 8,
    /*.maxSamples = */ 4,
    /* .maxMeshOutputVerticesNV = */ 256,
    /* .maxMeshOutputPrimitivesNV = */ 512,
    /* .maxMeshWorkGroupSizeX_NV = */ 32,
    /* .maxMeshWorkGroupSizeY_NV = */ 1,
    /* .maxMeshWorkGroupSizeZ_NV = */ 1,
    /* .maxTaskWorkGroupSizeX_NV = */ 32,
    /* .maxTaskWorkGroupSizeY_NV = */ 1,
    /* .maxTaskWorkGroupSizeZ_NV = */ 1,
    /* .maxMeshViewCountNV = */ 4,
    /* .maxDualSourceDrawBuffersEXT = */ 1,

    /*.limits = */
    {
        /*.nonInductiveForLoops = */ 1,
        /*.whileLoops = */ 1,
        /*.doWhileLoops = */ 1,
        /*.generalUniformIndexing = */ 1,
        /*.generalAttributeMatrixVectorIndexing = */ 1,
        /*.generalVaryingIndexing = */ 1,
        /*.generalSamplerIndexing = */ 1,
        /*.generalVariableIndexing = */ 1,
        /*.generalConstantMatrixVectorIndexing = */ 1,
    }};


struct macro {
    macro(std::string const& name) : name_(name) {}

    macro(std::string const& name, std::string val) : name_(name), val_(val) {}

    std::string name_;
    std::string val_;
};


/**
 * Utility for defining shaderc compiler options.
 */
class compiler_options {
public:
    compiler_options(std::vector<std::filesystem::path> const& paths)
            : includer_(includer(paths)), resource_limits_(default_resource_limits), paths_(paths) {
        add_vendor_definition();
    }

    compiler_options(std::vector<std::filesystem::path> const& paths, std::string const& vendor)
            : includer_(includer(paths)), resource_limits_(default_resource_limits), paths_(paths) {
        add_definition(vendor);
    }

    void add_definition(std::string const& name) {
        macros_.emplace_back(name);
    }

    void add_definition(std::string const& name, std::string const& value) {
        macros_.emplace_back(name, value);
    }

    /**
     * Set include paths. Overrides previously set paths.
     */
    void set_include_paths(std::vector<std::filesystem::path> const& paths) {
        includer_ = includer(paths);
        paths_ = paths;
    }

    std::vector<std::filesystem::path> const& get_shader_paths() const {
        return paths_;
    }

    std::string get_preamble() const {
        std::string preamble;
        preamble += "#extension GL_GOOGLE_include_directive : enable\n";
        for (auto const& macro : macros_) {
            if (!macro.name_.empty()) {
                preamble += "#define " + macro.name_;
                if (!macro.val_.empty()) {
                    preamble += " " + macro.val_;
                }
                preamble += "\n";
            }
        }
        return preamble;
    }

    TBuiltInResource const* get_resource_limits() const {
        return &resource_limits_;
    }

    includer get_includer() const {
        return includer_;
    }

private:
    void add_vendor_definition();

    includer includer_;

    TBuiltInResource resource_limits_;

    std::vector<macro> macros_;

    std::vector<std::filesystem::path> paths_;
}; // end class compiler_options


} // end namespace megamol::shaderfactory
