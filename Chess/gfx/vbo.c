#include "Chess/gfx/vbo.h"


struct VBO vbo_create(GLint type, bool dynamic)
{
    struct VBO _vbo = {
        .type = type,
        .dynamic = dynamic
    };

    glGenBuffers(1,&_vbo.handle);

    return _vbo;
};

void vbo_bind(struct VBO self)
{
    glBindBuffer(self.type,self.handle);
};

void vbo_data(struct VBO self, void *data, size_t size){
    
    vbo_bind(self);

    glBufferData(self.type, size , data, self.dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW );
};

void vbo_destroy(struct VBO self)
{
    glDeleteBuffers(1,&self.handle);
}