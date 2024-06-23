#ifdef __cplusplus
extern "C" {
#endif

#ifndef VBO_H
#define VBO_H

#include <Chess/util/util.h>

#include "Chess/gfx/gfx.h"

struct VBO {
    GLuint handle;
    GLint type;
    bool dynamic;
};

struct VBO vbo_create(GLint type, bool dynamic);

void vbo_destroy(struct VBO self);

void vbo_bind(struct VBO self);

void vbo_data(struct VBO self, void *data,  size_t size);

#endif 

#ifdef __cplusplus
}
#endif