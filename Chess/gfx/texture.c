#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <Chess/gfx/texture.h>
#include "Chess/gfx/gfx.h"


struct Texture texture_create(const char* image)
{
    struct Texture self;

    int width, height, nrChannels;

    stbi_set_flip_vertically_on_load(true); 
    unsigned char *data = stbi_load(image, &width, &height, &nrChannels, 0); 

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


    glGenTextures(1,&self.handle);
    glBindTexture(GL_TEXTURE_2D, self.handle);

    self.mode = nrChannels == 3 ? GL_RGB : GL_RGBA;

if (data)
{
    glTexImage2D(GL_TEXTURE_2D, 0, self.mode, width, height, 0, self.mode, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
}
else
{
    printf("error loading texture \n");
    assert(false);
}  

    stbi_image_free(data);
    return self;
};

void texture_bind(struct Texture self)
{
    glBindTexture(GL_TEXTURE_2D, self.handle);
};

void texture_destroy(struct Texture self)
{
    glDeleteTextures(1,&self.handle);
};