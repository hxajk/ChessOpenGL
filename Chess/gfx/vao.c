#include "Chess/gfx/vao.h"
#include "Chess/gfx/gfx.h"

struct VAO vao_create() {
  struct VAO _vao;
  glCreateVertexArrays(1, &_vao.handle);
  return _vao;
};

void vao_bind(struct VAO self) { glBindVertexArray(self.handle); };

void vao_attrib(struct VAO vao, struct VBO vbo, GLuint index, GLint size,
                GLenum type, GLsizei stride, size_t offset) {
  vao_bind(vao);
  vbo_bind(vbo);

  // Cool jdah !

  switch (type) {
  case GL_FLOAT:
    glVertexAttribPointer(index, size, type, false, stride, (void *)offset);
  case GL_UNSIGNED_INT_2_10_10_10_REV:
    glVertexAttribIPointer(index, size, type, stride, (void *)offset);
  default:
    assert("Only supported type float, and GL_UNSIGNED_INT_2_10_10_10_REV.");
  }

  glEnableVertexAttribArray(index);
};

void vao_destroy(struct VAO self) { glDeleteVertexArrays(1, &self.handle); };