/// @file vbo.c

#include "Chess/gfx/vbo.h"
#include <stdio.h>

/**
 * @brief Initialize our VBO
 * 
 * @param type 
 * @param dynamic 
 * @return struct VBO 
 */

struct VBO vbo_create(GLint type, bool dynamic)
{
    struct VBO self = {
        .type = type,
        .dynamic = dynamic
    };

    glGenBuffers(1,&self.handle);

    return self;
};

/**
 * @brief Bind our VBO.
 * 
 * @param self 
 */

void vbo_bind(struct VBO self)
{
    glBindBuffer(self.type,self.handle);
};

/**
 * @brief Creates and initializes a buffer object's data store
 * 
 * @param self 
 * @param data 
 * @param size 
 */

void vbo_data(struct VBO self, void *data, size_t size){
    
    vbo_bind(self);

    glBufferData(self.type, size , data, self.dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW );
};

/**
 * @brief Destroy our VBO
 * 
 * @param self 
 */

void vbo_destroy(struct VBO self)
{
    if(self.handle <= 0)
    {
        printf("Warning: Your buffer handle is already destoyed!");
        return;
    };
    glDeleteBuffers(1,&self.handle);
}