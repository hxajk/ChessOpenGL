#ifdef __cplusplus
extern "C" {
#endif
#ifndef SHADER_H
#define SHADER_H

#include "Chess/gfx/gfx.h"
#include <Chess/util/util.h>

struct Shader {
    GLuint handle, vs_handle, fs_handle;
};

struct Shader shader_create(const char *vs_path, const char *fs_path);

void shader_bind(struct Shader self);

#endif

#ifdef __cplusplus
}
#endif