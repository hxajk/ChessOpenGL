#include "Chess/gfx/gfx.h"
#include <Chess/core/piece.h>

#define PIECE_LIMITS 32
#define IMAGES_LIMITS 12
#define WHITE_PAWN_INDEX 5
#define BLACK_PAWN_INDEX 11

/*
    SECTIONS:
   
    <data>[0]  ->  White Rook
    <data>[1]  ->  White Knight
    <data>[2]  ->  White Bishop
    <data>[3]  ->  White King
    <data>[4]  ->  White Queen
    <data>[2..1..0]
    <data>[5] (8 times)  ->  White Pawn
 
    <data>[6]  ->   Black Rook
    <data>[7]  ->   Black Knight
    <data>[8]  ->   Black Bishop
    <data>[9]  ->   Black King
    <data>[10] ->   Black Queen
    <data>[8..7..6]
    <data>[11] (8 times)  ->  Black Pawn
 */


/**
 * @brief Initalize piece, create chess pieces
 * 
 * @return struct Piece 
 */

struct Piece piece_init()
{
    mat4 proj;
    float scale = 4 * (float)(window_get().y + window_get().y) / 64; // just 4*a, where a is the side of the the board.
    struct VBO coordinate_vertex;
    struct Piece self = {
        .shader_vertex = shader_create("../resources/shaders/base.vs", "../resources/shaders/base.fs"),
        .index_data = {
            0,1,2,2,3,0
        }
    };
    float buffer_position_data[32][8] = {{0}};
    vec2 point = {0,1}; 
    for(int i = 0;i < 8;i += 1)
    {
        // Mayor white pieces
        for(int j = 0;j < 8;j += 1)
        {
            if((j & 1) == 1)
                buffer_position_data[i][j] = scale*(j <= 3 ? 1 : 0);
            else
                buffer_position_data[i][j] = scale*(j == 0 || j == 6 ? point[0] : point[1]);
        };
        point[0]++; point[1]++;
    };
    point[0] = 0; point[1] = 1;
    for(int i = 8;i < 16;i += 1)
    {
        // White pawn pieces
        for(int j = 0;j < 8;j += 1)
        {
            if((j & 1) == 1)
                buffer_position_data[i][j] = scale*(j <= 3 ? 2 : 1);
            else
                buffer_position_data[i][j] = scale*(j == 0 || j == 6 ? point[0] : point[1]); 
        };      
        point[0]++; point[1]++;
    };
    point[0] = 0; point[1] = 1;
    for(int i = 16;i < 24;i += 1)
    {
        // Mayor black pieces
        for(int j = 0;j < 8;j += 1)
        {
            if((j&1) == 1)
                buffer_position_data[i][j] = scale*(j <= 3 ? 8 : 7);
            else
                buffer_position_data[i][j] = scale*(j == 0 || j == 6 ? point[0] : point[1]); 
        };      
        point[0]++; point[1]++;
    };
    point[0] = 0; point[1] = 1;
    for(int i = 24;i < 33;i += 1)
    {
        // Black pawn pieces
        for(int j = 0;j < 8;j += 1)
        {
            if((j&1) == 1)
                buffer_position_data[i][j] = scale*(j <= 3 ? 7 : 6);
            else
                buffer_position_data[i][j] = scale*(j == 0 || j == 6 ? point[0] : point[1]); 
        };      
        point[0]++; point[1]++;
    };

    float buffer_coordinate_data[8] = {
        0,1,
        1,1,
        1,0,
        0,0
    };
    
    const char* image_paths[] = {
        
        "../resources/texture/white_rook.png",
        "../resources/texture/white_horse.png",
        "../resources/texture/white_bishop.png",
        "../resources/texture/white_queen.png",
        "../resources/texture/white_king.png",
        "../resources/texture/white_pawn.png",

        "../resources/texture/black_rook.png",
        "../resources/texture/black_horse.png",
        "../resources/texture/black_bishop.png",
        "../resources/texture/black_queen.png",
        "../resources/texture/black_king.png",
        "../resources/texture/black_pawn.png",
    };

    glm_ortho(0, (float)window_get().x, 0, (float)window_get().y, -1, 1, proj);

    for(int i = 0;i < PIECE_LIMITS;i++){
        self.buffer_vertex[i] = vbo_create(GL_ARRAY_BUFFER, false);
        self.array_vertex[i] = vao_create();
    }
    for(int i = 0;i < IMAGES_LIMITS;i++){
        self.texture_vertex[i] = texture_create(image_paths[i]);  
    };

    coordinate_vertex = vbo_create(GL_ARRAY_BUFFER,false);
    self.index_vertex = vbo_create(GL_ELEMENT_ARRAY_BUFFER, false);

    for(int i = 0;i < PIECE_LIMITS;i += 1)
    {
        vao_bind(self.array_vertex[i]);
        vbo_data(self.buffer_vertex[i], buffer_position_data[i], sizeof(buffer_position_data[i]));
    };
    vbo_data(coordinate_vertex, buffer_coordinate_data, sizeof(buffer_coordinate_data));
    vbo_data(self.index_vertex, (unsigned int*)self.index_data, sizeof(self.index_data));

    for(int i = 0;i < PIECE_LIMITS;i += 1)
    {
        vao_attrib(self.array_vertex[i], self.buffer_vertex[i], 0, 2, GL_FLOAT, 0, 0);
        vao_attrib(self.array_vertex[i], coordinate_vertex, 1, 2, GL_FLOAT, 0, 0);
    };
    
    shader_bind(self.shader_vertex);
    glUniformMatrix4fv(glGetUniformLocation(self.shader_vertex.handle,"proj"),1,false,*proj);
    glUniform1i(glGetUniformLocation(self.shader_vertex.handle,"id"),0);

    return self;
};

/**
 * @brief Render chess piece
 * 
 * @param self 
 */

void piece_render(struct Piece self)
{
    shader_bind(self.shader_vertex);
    for(int i = 0;i < PIECE_LIMITS;i += 1)
    {
        if(glm_max(0,i) <= 7) {
            // Mayor White pieces
            texture_bind(self.texture_vertex[(i < 5) ? i : (7 - i)]);
        }
        else if(glm_max(8,i) <= 15) {
            // Pawn White pieces
            texture_bind(self.texture_vertex[WHITE_PAWN_INDEX]);
        }
        else if(glm_max(16,i) <= 23){
            // Mayor Black pieces
            texture_bind(self.texture_vertex[(i <= 20) ? i - 10 : 23 - i + 6]);
        }
        else if(glm_max(24,i) <= 32){
            // Pawn Black pieces
            texture_bind(self.texture_vertex[BLACK_PAWN_INDEX]);
        };
        vao_bind(self.array_vertex[i]);
        vbo_bind(self.index_vertex);
        glDrawElements(GL_TRIANGLES,sizeof(self.index_data) / sizeof(unsigned int),GL_UNSIGNED_INT,0);
    };
};

/**
 * @brief Destroy chess piece
 * 
 * @param self 
 */

void piece_destroy(struct Piece self)
{
    shader_destroy(self.shader_vertex);
    vbo_destroy(self.index_vertex);
    for(int i = 0;i < PIECE_LIMITS;i += 1)
    {
        vbo_destroy(self.buffer_vertex[i]);
        vao_destroy(self.array_vertex[i]);
    };
}; 