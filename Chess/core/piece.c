/// @file piece.c

#include "Chess/util/util.h"
#include <Chess/core/piece.h>
#include <Chess/util/parser.h>
#include <Chess/core/board.h>
#include <stdio.h>

#define FEN "RNBQKBNR/PPPPPPPP/8/8/8/8/pppppppp/rnbqkbnr"

#define RANK 8
#define FILE 8

static struct Piece self = {
        .index_data = {
            0,1,2,2,3,0
    }
};
static unsigned int SQUARE_TYPE = 0;

struct Board board;
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
static void set_position_data(float buffer_position_data[POSITIONS_PER_PIECE], vec2 vertex_position, int y, float scale){
    int i,j;
    for (j = 0; j < POSITIONS_PER_PIECE; j++){
        if ((j & 1) == 1) {
            buffer_position_data[j] = scale*((j <= 3) ? y : y - 1);
        } else {
            buffer_position_data[j] = scale*((j == 0 || j == 6) ? vertex_position[0] : vertex_position[1]);
        }
    }
};

static bool is_equality_data(float data_1[8], float data_2[8]){
        for(int i = 0;i < 8;i++){
                if(data_1[i] != data_2[i]){
                        return false;
                }
        }
        return true;
};

static void bind_piece(vec2 position, vec2 piece){
        vao_bind(self.array_vertex[(int)position[0]][(int)position[1]]);
        texture_bind(self.texture_vertex[(int)piece[0]][(int)piece[1]]);
        vbo_bind(self.index_vertex);
        glDrawElements(GL_TRIANGLES,sizeof(self.index_data) / sizeof(unsigned int),GL_UNSIGNED_INT,0);
};
vec4 fen_data[32];
int i = 0;
static void bind_fen_data(vec2 position, vec2 piece){
    fen_data[i][0] = position[0]; fen_data[i][1] = position[1];
    fen_data[i][2] = piece[0]; fen_data[i][3] = piece[1];
    printf("[INFO] - %s - %s \n", parser_board(position[0], position[1]) ,parser_piece(piece[0], piece[1]));
    i++;
};
static void load_fen(const char* fen){
    int file = 0;
    int rank = 0;
    for(int i = 0; fen[i] != '\0';i++){
        char c = fen[i];
        if(c == '/'){
            rank = 0;
            file++; 
        } else if(c >= '1' && c <= '8' ) {
            rank += c - '0';
        } else {
            switch (c) {
                case 'P': bind_fen_data((vec2){file,rank}, (vec2){WHITE, PAWN}); break;
                case 'N': bind_fen_data((vec2){file,rank}, (vec2){WHITE, KNIGHT}); break;
                case 'B': bind_fen_data((vec2){file,rank}, (vec2){WHITE, BISHOP}); break;
                case 'R': bind_fen_data((vec2){file,rank}, (vec2){WHITE, ROOK}); break;
                case 'Q': bind_fen_data((vec2){file,rank}, (vec2){WHITE, QUEEN}); break;
                case 'K': bind_fen_data((vec2){file,rank}, (vec2){WHITE, KING}); break;

                case 'p': bind_fen_data((vec2){file,rank}, (vec2){DARK, PAWN}); break;
                case 'n': bind_fen_data((vec2){file,rank}, (vec2){DARK, KNIGHT}); break;
                case 'b': bind_fen_data((vec2){file,rank}, (vec2){DARK, BISHOP}); break;
                case 'r': bind_fen_data((vec2){file,rank}, (vec2){DARK, ROOK}); break;
                case 'q': bind_fen_data((vec2){file,rank}, (vec2){DARK, QUEEN}); break;
                case 'k': bind_fen_data((vec2){file,rank}, (vec2){DARK, KING}); break;
            }
            rank++;
        }
    }
}

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
    int i,j;
    vec2 vertex_position = {0,1};

    for(i = 0;i < FILE;i++){
        vec2 vertex_position = {0, 1};
        for(j = 0;j < RANK;j++){
            set_position_data(self.buffer_position_data[i][j],vertex_position,i+1, self.scale);
            vertex_position[0]++; vertex_position[1]++;
        }
    }

    vertex_position[0] = 0; vertex_position[1] = 1;

    for(i = 0;i < FILE;i++){
        for(j = 0;j < RANK;j++){
            self.buffer_vertex[i][j] = vbo_create(GL_ARRAY_BUFFER, false);
            self.array_vertex[i][j] = vao_create();
        }
    }
    coordinate_vertex = vbo_create(GL_ARRAY_BUFFER, true);
    self.index_vertex = vbo_create(GL_ELEMENT_ARRAY_BUFFER, false);

    for(i = 0;i < 6;i++){
        self.texture_vertex[WHITE][i] = texture_create(image_paths[WHITE][i]);
        self.texture_vertex[DARK][i] = texture_create(image_paths[DARK][i]);
    };

    for(i = 0;i < FILE;i++){
        for(j = 0;j < RANK;j++){
            vbo_data(self.buffer_vertex[i][j], self.buffer_position_data[i][j], sizeof(self.buffer_position_data[i][j]));
        }
    };
    vbo_data(coordinate_vertex, buffer_coordinate_data, sizeof(buffer_coordinate_data));
    vbo_data(self.index_vertex, (unsigned int*)self.index_data, sizeof(self.index_data));

    for(i = 0;i < FILE;i++){
        for(j = 0;j < RANK;j++){
            vao_attrib(self.array_vertex[i][j], self.buffer_vertex[i][j], 0, 2, GL_FLOAT, 0, 0);
            vao_attrib(self.array_vertex[i][j], coordinate_vertex, 1, 2, GL_FLOAT, 0, 0);
        }
    };
    shader_bind(self.shader_vertex);
    glUniformMatrix4fv(glGetUniformLocation(self.shader_vertex.handle,"proj"),1,false,*proj);
    glUniform1i(glGetUniformLocation(self.shader_vertex.handle,"id"),0);

    return self;
};

/**
 * @brief Get piece information by return piece implementation.
 * 
 * @param piece 
 */

void piece_get_info(struct Piece *piece){
    
    *piece = self;
}

/**
 * @brief Render chess piece
 * 
 * @param self 
 */

 bool init = true;
 int piece_saved = 0;
 bool holded = false;
 bool mouse_pressed = false; 
void piece_render(struct Piece self)
{
        shader_bind(self.shader_vertex);
        if(init){
            init = false;
            load_fen(FEN);  
        }   
        board_get_info(&board);

        for(int i = 0;i < 32;i++){
        if( window_get().mouse.buttons[GLFW_MOUSE_BUTTON_LEFT].down && !mouse_pressed  && is_equality_data(board.buffer_position_data[(int)board.cy][(int)board.cx], board.buffer_position_data[(int)fen_data[i][0]][(int)fen_data[i][1]]) ){
            printf("[INFO] - %s \n",parser_piece(fen_data[i][2], fen_data[i][3]));
            holded = true;
            piece_saved = i;
            mouse_pressed = true;
        }
        if(!window_get().mouse.buttons[GLFW_MOUSE_BUTTON_LEFT].down){
            holded = false;
            mouse_pressed = false;
        }        
        if( holded && window_get().mouse.buttons[GLFW_MOUSE_BUTTON_LEFT].down && !is_equality_data(board.buffer_position_data[(int)board.cy][(int)board.cx], board.buffer_position_data[(int)fen_data[i][0]][(int)fen_data[i][1]])){
            fen_data[piece_saved][0] = board.cy;
            fen_data[piece_saved][1] = board.cx;
        }

        printf("%f - %f \n", board.cx, board.cy);
            
        bind_piece((vec2){fen_data[i][0], fen_data[i][1]}, (vec2){fen_data[i][2], fen_data[i][3]});
        }
};

/**
 * @brief Destroy chess piece
 * 
 * @param self 
 */

void piece_destroy(struct Piece self) {
    shader_destroy(self.shader_vertex);
    vbo_destroy(self.index_vertex);
    int i,j;
    for(i = 0;i < FILE;i++){
        for(j = 0;j < RANK;j++){
            vao_destroy(self.array_vertex[i][j]);
            vbo_destroy(self.buffer_vertex[i][j]);
        }
    };
}