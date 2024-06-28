#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <Chess/gfx/texture.h>
#include "Chess/gfx/gfx.h"

/**
 * @brief Initalize our texture 
 * 
 * @param path 
 * @return struct Texture 
 */

struct Texture texture_create(const char* path)
{
    int width, height, channels, format;
    unsigned char* image;

    stbi_set_flip_vertically_on_load(true); 
    image = stbi_load(path, &width, &height, &channels, STBI_rgb_alpha); 
    assert(image != NULL);

    struct Texture self = {
        .w = width,
        .h = height,
        .channels = channels
    };

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    format = self.channels == 4 ? GL_RGBA : GL_RGB;

    glGenTextures(1,&self.handle);
    glBindTexture(GL_TEXTURE_2D, self.handle);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(image);
    return self;
};

/**
 * @brief Bind our texture
 * 
 * @param self 
 */

void texture_bind(struct Texture self)
{
    glBindTexture(GL_TEXTURE_2D, self.handle);
};

/**
 * @brief Destroy our texture
 * 
 * @param self 
 */

void texture_destroy(struct Texture self)
{
    if(self.handle <= 0)
    {
        printf("Warning: Your texture handle is already destoyed! \n");
        return;
    };
    glDeleteTextures(1,&self.handle);
};