#ifdef __cplusplus
extern "C" {
#endif
#include <Chess/util/util.h>
#include <Chess/gfx/gfx.h>

#ifndef TEXTURE_H 
#define TEXTURE_H 

struct Texture {
    GLuint handle;
    GLint mode;
};

struct Texture texture_create(const char* image);

void texture_bind(struct Texture self);

void texture_destroy(struct Texture self);

#endif

#ifdef __cplusplus
}
#endif