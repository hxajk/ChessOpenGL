#include "Chess/gfx/gfx.h"
#include <Chess/core/piece.h>

/*
    SECTIONS:
    <data>[0]  ->  White King
    <data>[1]  ->  White Queen
    <data>[2]  ->  White Rook
    <data>[3]  ->  White Bishop
    <data>[4]  ->  White Knight
    <data>[5]  ->  White Pawn
 
    <data>[6]  ->  Black King
    <data>[7]  ->  Black Queen
    <data>[8]  ->  Black Rook
    <data>[9]  ->  Black Bishop
    <data>[10] -> Black Knight
    <data>[11] -> Black Pawn

 */

// TODO: Try to replace <data>[0] with <data>[i], and do the work<3
// c is hell, and strict :(

struct Piece piece_init()
{
    mat4 proj;
    float scale = 72; // fix later on...
    struct VBO coordinate_vertex;
    struct Piece self = {
        .shader_vertex = shader_create("../resources/shaders/base.vs", "../resources/shaders/base.fs"),
        .index_data = {
            0,1,2,2,3,0
        }
    };
    float buffer_position_data[12][16] = {
        {
            4*scale,1*scale,    
            5*scale,1*scale, 
            5*scale,0*scale,    
            4*scale,0*scale,   
        },
        {
            3*scale,1*scale,    
            4*scale,1*scale, 
            4*scale,0*scale,    
            3*scale,0*scale, 
        },
        {},
        {},
        {},
        {},

        {},
        {},
        {},
        {},
        {},
        {},
    };

    float buffer_coordinate_data[8] = {
        0,1,
        1,1,
        1,0,
        0,0
    };
    
    const char* image_paths[] = {
        "../resources/texture/white_king.png",
        "../resources/texture/white_queen.png",
        "../resources/texture/white_rook.png",
        "../resources/texture/white_bishop.png",
        "../resources/texture/white_horse.png",
        "../resources/texture/white_pawn.png",

        "../resources/texture/black_king.png",
        "../resources/texture/black_queen.png",
        "../resources/texture/black_rook.png",
        "../resources/texture/black_bishop.png",
        "../resources/texture/black_horse.png",
        "../resources/texture/black_pawn.png"
    };

    glm_ortho(0, (float)window_get().x, 0, (float)window_get().y, -1, 1, proj);

    for(int i = 0;i < 2;i++){
        self.buffer_vertex[i] = vbo_create(GL_ARRAY_BUFFER, false);
        self.array_vertex[i] = vao_create();
        self.texture_vertex[i] = texture_create(image_paths[i]);  
    }
    coordinate_vertex = vbo_create(GL_ARRAY_BUFFER,false);
    self.index_vertex = vbo_create(GL_ELEMENT_ARRAY_BUFFER, false);


    for(int i = 0;i < 2;i += 1)
    {
        vao_bind(self.array_vertex[i]);
        vbo_data(self.buffer_vertex[i], buffer_position_data[i], sizeof(buffer_position_data[i]));
    };
    vbo_data(coordinate_vertex, buffer_coordinate_data, sizeof(buffer_coordinate_data));
    vbo_data(self.index_vertex, (unsigned int*)self.index_data, sizeof(self.index_data));

    for(int i = 0;i < 2;i += 1)
    {
        vao_attrib(self.array_vertex[i], self.buffer_vertex[i], 0, 2, GL_FLOAT, 0, 0);
        vao_attrib(self.array_vertex[i], coordinate_vertex, 1, 2, GL_FLOAT, 0, 0);
    };
    
    shader_bind(self.shader_vertex);
    glUniformMatrix4fv(glGetUniformLocation(self.shader_vertex.handle,"proj"),1,false,*proj);
    glUniform1i(glGetUniformLocation(self.shader_vertex.handle,"id"),0);

    return self;
};

void piece_render(struct Piece self)
{
    shader_bind(self.shader_vertex);
    for(int i = 0;i < 2;i += 1)
    {
        texture_bind(self.texture_vertex[i]);
        vao_bind(self.array_vertex[i]);
        vbo_bind(self.index_vertex);
        glDrawElements(GL_TRIANGLES,sizeof(self.index_data) / sizeof(unsigned int),GL_UNSIGNED_INT,0);
    };
};

void piece_destroy(struct Piece self)
{
    shader_destroy(self.shader_vertex);
    vbo_destroy(self.index_vertex);
    for(int i = 0;i < 2;i += 1)
    {
        vbo_destroy(self.buffer_vertex[i]);
        vao_destroy(self.array_vertex[i]);
    };
}; 