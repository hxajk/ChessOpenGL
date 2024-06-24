#ifdef __cplusplus
extern "C" {
#endif

#ifndef VAO_H
#define VAO_H 

#include "Chess/gfx/gfx.h"
#include "Chess/gfx/vbo.h"
#include <Chess/util/util.h>

struct VAO {
    GLuint handle;
};

struct VAO vao_create();


void vao_bind(struct VAO self);
void vao_destroy(struct VAO self); 

void vao_attrib(struct VAO self, struct VBO vbo, GLuint index, GLint size, GLenum type, GLsizei stride, size_t offset);

#endif 

#ifdef __cplusplus
}
#endif