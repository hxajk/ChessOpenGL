/// @file piece.c

#include "Chess/util/util.h"
#include <Chess/core/piece.h>

static struct Piece self = {
        .index_data = {
            0,1,2,2,3,0
    }
};
static unsigned int SQUARE_TYPE = 0;

/**
 * @brief Set the position data object
 * The purpose of this function is to represent position as the square.
 * @param self.buffer_position_data 
 * @param start 
 * @param end 
 * @param y 
 * @param self.scale 
 */
// NOTES: UP LEFT -> UP RIGHT -> DOWN RIGHT -> DOWN LEFT (CLOCKWISE ORDER).
static void set_position_data(float buffer_position_data[PIECE_LIMITS][POSITIONS_PER_PIECE], int start, int end, int y, float scale){
    vec2 current_position = {0, 1};
    int i,j;
    for (i = start; i <= end; i++) {
            for (j = 0; j < POSITIONS_PER_PIECE; j++){
                if ((j & 1) == 1) {
                    buffer_position_data[i][j] = scale*((j <= 3) ? y : y - 1);
                } else {
                    buffer_position_data[i][j] = scale*((j == 0 || j == 6) ? current_position[0] : current_position[1]);
                }
            }
            current_position[0]++;
            current_position[1]++;
        }
        current_position[0] = 0;
        current_position[1] = 1;
};

/**
 * @brief Initalize piece, create chess pieces
 * 
 * @return struct Piece 
 */

struct Piece piece_init()
{
    mat4 proj;
    struct VBO coordinate_vertex;
    float buffer_coordinate_data[8] = {
        0,1,
        1,1,
        1,0,
        0,0
    };
    const char* image_paths[2][6] = {
        {
            "../resources/texture/white_rook.png",
            "../resources/texture/white_horse.png",
            "../resources/texture/white_bishop.png",
            "../resources/texture/white_queen.png",
            "../resources/texture/white_king.png",
            "../resources/texture/white_pawn.png",
        },

        {
            "../resources/texture/black_rook.png",
            "../resources/texture/black_horse.png",
            "../resources/texture/black_bishop.png",
            "../resources/texture/black_queen.png",
            "../resources/texture/black_king.png",
            "../resources/texture/black_pawn.png",
        }

    };
    self.shader_vertex = shader_create("../resources/shaders/base.vs", "../resources/shaders/base.fs"),
    self.scale = 4 * (float)(2*window_get().y) / 64;
    glm_ortho(0, (float)window_get().x, 0, (float)window_get().y, -1, 1, proj);

    set_position_data(self.buffer_position_data[WHITE],0, 7, 1, self.scale);
    set_position_data(self.buffer_position_data[WHITE],8, 15, 2, self.scale);
    set_position_data(self.buffer_position_data[DARK],0, 7, 8, self.scale);
    set_position_data(self.buffer_position_data[DARK],8, 15, 7, self.scale);

    int i;
    for(i = 0;i < PIECE_LIMITS;i++){
        self.buffer_vertex[WHITE][i] = vbo_create(GL_ARRAY_BUFFER, true);
        self.array_vertex[WHITE][i] = vao_create();
        self.buffer_vertex[DARK][i] = vbo_create(GL_ARRAY_BUFFER, true);
        self.array_vertex[DARK][i] = vao_create();
    }
    coordinate_vertex = vbo_create(GL_ARRAY_BUFFER, true);
    self.index_vertex = vbo_create(GL_ELEMENT_ARRAY_BUFFER, false);

    for(i = 0;i < 6;i++){
        self.texture_vertex[WHITE][i] = texture_create(image_paths[WHITE][i]);
        self.texture_vertex[DARK][i] = texture_create(image_paths[DARK][i]);
    };
    for(i = 0;i < PIECE_LIMITS;i++){
        vbo_data(self.buffer_vertex[WHITE][i], self.buffer_position_data[WHITE][i], sizeof(self.buffer_position_data[WHITE][i]));
        vbo_data(self.buffer_vertex[DARK][i], self.buffer_position_data[DARK][i], sizeof(self.buffer_position_data[DARK][i]));
    };
    vbo_data(coordinate_vertex, buffer_coordinate_data, sizeof(buffer_coordinate_data));
    vbo_data(self.index_vertex, self.index_data, sizeof(self.index_data));

    for(i = 0;i < PIECE_LIMITS;i++){
        vao_attrib(self.array_vertex[WHITE][i], self.buffer_vertex[WHITE][i], 0, 2, GL_FLOAT, 0, 0);
        vao_attrib(self.array_vertex[WHITE][i], coordinate_vertex, 1, 2, GL_FLOAT, 0, 0);
        vao_attrib(self.array_vertex[DARK][i], self.buffer_vertex[DARK][i], 0, 2, GL_FLOAT, 0, 0);
        vao_attrib(self.array_vertex[DARK][i], coordinate_vertex, 1, 2, GL_FLOAT, 0, 0);
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
        for(self.index = 0;self.index < PIECE_LIMITS;self.index++){
            glUniform1f(glGetUniformLocation(self.shader_vertex.handle,"square_type"),SQUARE_TYPE);

            vbo_data(self.buffer_vertex[WHITE][self.index], self.buffer_position_data[WHITE][self.index], sizeof(self.buffer_position_data[WHITE][self.index]));
            texture_bind(self.texture_vertex[0][0]);
            vao_bind(self.array_vertex[WHITE][self.index]);
            vbo_bind(self.index_vertex);
            glDrawElements(GL_TRIANGLES,sizeof(self.index_data) / sizeof(unsigned int),GL_UNSIGNED_INT,0);

            vbo_data(self.buffer_vertex[DARK][self.index], self.buffer_position_data[DARK][self.index], sizeof(self.buffer_position_data[DARK][self.index]));
            texture_bind(self.texture_vertex[DARK][0]);
            vao_bind(self.array_vertex[DARK][self.index]);
            vbo_bind(self.index_vertex);
            glDrawElements(GL_TRIANGLES,sizeof(self.index_data) / sizeof(unsigned int),GL_UNSIGNED_INT,0);
        };
};

/**
 * @brief Destroy chess piece
 * 
 * @param self 
 */

void piece_destroy(struct Piece self) {
    shader_destroy(self.shader_vertex);
    vbo_destroy(self.index_vertex);
    for (self.index = 0; self.index < PIECE_LIMITS; self.index++) {
        vbo_destroy(self.buffer_vertex[WHITE][self.index]);
        vao_destroy(self.array_vertex[WHITE][self.index]);
        vbo_destroy(self.buffer_vertex[DARK][self.index]);
        vao_destroy(self.array_vertex[DARK][self.index]);
    }
}