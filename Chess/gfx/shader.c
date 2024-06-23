#include "Chess/gfx/shader.h"
#include "Chess/gfx/gfx.h"
#include "gfx.h"



static GLint _compile(const char* path, GLenum type)
{
    FILE* f;
    int len;
    char* text;

    f = fopen(path, "r");

    if(f == NULL)
    {
        printf("error loading shader at %s\n", path);
        exit(1);
    };

    fseek(f, 0, SEEK_END);

    len = ftell(f);

    if(len <= 0)
    {
        printf("Length of a file (%d) must not be <= 0", len);
        assert(false);
    };

    fseek(f, 0, SEEK_SET);

    text = calloc(1, len);

    if(text == NULL)
    {
        printf("Text of a file (%s) must not be NULL", text);
        assert(false);
    };

    fread(text, 1, len, f);

    if(strlen(text) <= 0)
    {
        printf("Length Text (%d) must not be <= 0", strlen(text));
        assert(false);
    };

    fclose(f);

    GLuint ShaderType = glCreateShader(type);

    glShaderSource(ShaderType,1,(const char* const*)&text, &len);

    glCompileShader(ShaderType);

    int status;

    glGetShaderiv(ShaderType, GL_COMPILE_STATUS, &status);

    if(status == 0)
    {
        int len;
        glGetShaderiv(ShaderType, 0, &len);

        char* text = calloc(1, len);
        glGetShaderInfoLog(ShaderType, len, NULL , text);

        printf("Error compilling shader at %s:\n %s",path, text);

        assert(false);
    };

    return ShaderType;
};

struct Shader shader_create(const char *vs_path, const char *fs_path)
{
    struct Shader self = {
        .handle = glCreateProgram(),
        .vs_handle = _compile(vs_path, GL_VERTEX_SHADER),
        .fs_handle = _compile(fs_path, GL_FRAGMENT_SHADER)
    };

    glAttachShader(self.handle, self.vs_handle);
    glAttachShader(self.handle, self.fs_handle);


    glLinkProgram(self.handle);

    int linked = 0;

    glGetProgramiv(self.handle, GL_LINK_STATUS, &linked);

    if(linked == 0)
    {
         int len;
        glGetProgramiv(self.handle, 0, &len);

        char* text = calloc(1, len);
        glGetProgramInfoLog(self.handle, len, NULL , text);

        printf("Error linking shader at :\n %s", text);

        assert(false);
    };
    return self;
};

void shader_bind(struct Shader self)
{
    glUseProgram(self.handle);
};