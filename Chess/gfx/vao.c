/// @file vao.c

#include "Chess/gfx/vao.h"
#include "Chess/gfx/gfx.h"
#include <stdio.h>


/**
 * @brief 
 * 
 * @return struct VAO 
 */

struct VAO vao_create() {
  struct VAO _vao;
  glCreateVertexArrays(1, &_vao.handle);
  return _vao;
};

/**
 * @brief Bind our VAO.
 * 
 * @param self 
 */

void vao_bind(struct VAO self) 
{ 
  glBindVertexArray(self.handle); 
};

/**
 * @brief Generate an array with generic vertex attribute data.
 * 
 * @param vao 
 * @param vbo 
 * @param index 
 * @param size 
 * @param type 
 * @param stride 
 * @param offset 
 */

void vao_attrib(struct VAO vao, struct VBO vbo, GLuint index, GLint size,
                GLenum type, GLsizei stride, size_t offset) {
  vao_bind(vao);
  vbo_bind(vbo);

  // Cool jdah !

  switch (type) {
  case GL_UNSIGNED_INT_2_10_10_10_REV:
    glVertexAttribIPointer(index, size, type, stride, (void *)offset);
  default:
    glVertexAttribPointer(index, size, type, false, stride, (void *)offset);
  }

  glEnableVertexAttribArray(index);
};

/**
 * @brief Destroy our VAO.
*/ 

void vao_destroy(struct VAO self) { 
  if(self.handle <= 0)
  {
    printf("Warning: Your vao is already destroyed! \n");
    return;
  };
  glDeleteVertexArrays(1, &self.handle); 
  };