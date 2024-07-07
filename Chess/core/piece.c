/// @file piece.c

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
    for (i = start; i < end; i++) {
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
    self.shader_vertex = shader_create("../resources/shaders/base.vs", "../resources/shaders/base.fs"),
    self.scale = 4 * (float)(2*window_get().y) / 64;

    // Initialize major white pieces
    set_position_data(self.buffer_position_data,0, 8, 1, self.scale);
    // Initialize white pawn pieces
    set_position_data(self.buffer_position_data,8, 16, 2, self.scale);
    // Initialize major black pieces
    set_position_data(self.buffer_position_data,16, 24, 8, self.scale);
    // Initialize black pawn pieces
    set_position_data(self.buffer_position_data,24, 32, 7, self.scale);

    glm_ortho(0, (float)window_get().x, 0, (float)window_get().y, -1, 1, proj);

    for(self.index = 0;self.index < PIECE_LIMITS;self.index++){
        self.buffer_vertex[self.index] = vbo_create(GL_ARRAY_BUFFER, true);
        self.array_vertex[self.index] = vao_create();
    }
    for(self.index = 0;self.index < IMAGES_LIMITS;self.index++){
        self.texture_vertex[self.index] = texture_create(image_paths[self.index]);  
    };

    coordinate_vertex = vbo_create(GL_ARRAY_BUFFER, true);
    self.index_vertex = vbo_create(GL_ELEMENT_ARRAY_BUFFER, false);

    for(self.index = 0;self.index < PIECE_LIMITS;self.index++){
        vbo_data(self.buffer_vertex[self.index], self.buffer_position_data[self.index], sizeof(self.buffer_position_data[self.index]));
    };
    vbo_data(coordinate_vertex, buffer_coordinate_data, sizeof(buffer_coordinate_data));
    vbo_data(self.index_vertex, (unsigned int*)self.index_data, sizeof(self.index_data));

    for(self.index = 0;self.index < PIECE_LIMITS;self.index++){
        vao_attrib(self.array_vertex[self.index], self.buffer_vertex[self.index], 0, 2, GL_FLOAT, 0, 0);
        vao_attrib(self.array_vertex[self.index], coordinate_vertex, 1, 2, GL_FLOAT, 0, 0);
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
        if(is_select_pieces(&self,0.0,0.0)){
            SQUARE_TYPE = 1;
        }
        else{
            SQUARE_TYPE = 0;
        };
        vbo_data(self.buffer_vertex[self.index], self.buffer_position_data[self.index], sizeof(self.buffer_position_data[self.index]));
        glUniform1f(glGetUniformLocation(self.shader_vertex.handle,"square_type"),SQUARE_TYPE);
        if(glm_max(0,self.index) <= 7) {
            // Mayor White pieces
            texture_bind(self.texture_vertex[(self.index < 5) ? self.index : (7 - self.index)]);
        }
        else if(glm_max(8,self.index) <= 15) {
            // Pawn White pieces
            texture_bind(self.texture_vertex[WHITE_PAWN_INDEX]);
        }
        else if(glm_max(16,self.index) <= 23){
            // Mayor Black pieces
            texture_bind(self.texture_vertex[(self.index <= 20) ? self.index - 10 : 23 - self.index + 6]);
        }
        else if(glm_max(24,self.index) <= 32){
            // Pawn Black pieces
            texture_bind(self.texture_vertex[BLACK_PAWN_INDEX]);
        };
        vao_bind(self.array_vertex[self.index]);
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
    for(self.index = 0;self.index < PIECE_LIMITS;self.index++){
        vbo_destroy(self.buffer_vertex[self.index]);
        vao_destroy(self.array_vertex[self.index]);
    };
}; 