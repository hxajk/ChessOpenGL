#include "Chess/gfx/gfx.h"
#include <Chess/core/piece.h>

//TODO: Render something here.

struct Piece piece_init()
{
    struct Piece self = {
        .array_vertex = vao_create(),
        .buffer_vertex = vbo_create(GL_ARRAY_BUFFER, false),
        .index_vertex = vbo_create(GL_ELEMENT_ARRAY_BUFFER, false),
        .shader_vertex = shader_create("../resources/shaders/base.vs", "../resources/shaders/base.fs"),
        .texture_vertex = texture_create("../resources/texture/chess_pieces.png"),
        .buffer_data = {
            0,384,
            512,384,
            512,128,
            0,128,
        },
        .index_data = {
            0,1,2,2,3,0
        },
    };

    /* assert(self.array_vertex.handle > 0 || self.buffer_vertex.handle > 0 || self.index_vertex.handle > 0 || self.shader_vertex.handle > 0 || self.texture_vertex.handle > 0); */

    vbo_bind(self.buffer_vertex);
    vbo_data(self.buffer_vertex, (float*)self.buffer_data, sizeof(self.buffer_data));

    vbo_bind(self.index_vertex);
    vbo_data(self.index_vertex, (unsigned int*)self.index_data, sizeof(self.index_data));

    vao_bind(self.array_vertex);
    vao_attrib(self.array_vertex, self.buffer_vertex, 0, 2, GL_FLOAT, 4 * sizeof(float), 0);
    vao_attrib(self.array_vertex, self.buffer_vertex, 1, 2, GL_FLOAT, 4 * sizeof(float), 0);

    shader_bind(self.shader_vertex);
    glUniform1i(glGetUniformLocation(self.shader_vertex.handle,"id"),0);

    return self;
};

void piece_render(struct Piece self)
{
    shader_bind(self.shader_vertex);
    texture_bind(self.texture_vertex);
    vao_bind(self.array_vertex);
    vbo_bind(self.index_vertex);
    vbo_bind(self.buffer_vertex);
};

void piece_destroy(struct Piece self)
{
    shader_destroy(self.shader_vertex);
    vao_destroy(self.array_vertex);
    vbo_destroy(self.buffer_vertex);
    vbo_destroy(self.index_vertex);
};