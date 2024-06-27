#include <Chess/core/piece.h>

//TODO: Render something here.

struct Piece piece_init()
{
    struct Piece self;

    

    return self;
};

void piece_render(struct Piece self)
{
    shader_bind(self.shader_vertex);
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