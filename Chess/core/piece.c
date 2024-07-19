/// @file piece.c

#include "Chess/gfx/gfx.h"
#include "Chess/util/util.h"
#include <Chess/core/piece.h>
#include <Chess/util/parser.h>
#include <Chess/core/board.h>
#include <stdio.h>

#define FEN "RNBQKBNR/PPPPPPPP/8/8/8/8/pppppppp/rnbqkbnr"
#define RANK 8
#define FILE 8

static struct Piece self = {
    .index_data = {0, 1, 2, 2, 3, 0}
};
static unsigned int SQUARE_TYPE = 0;

struct Board board;

vec4 fen_inital_data[32];
vec4 fen_dynamic_data[32];

/**
 * @brief Bind piece together.
 * 
 * @param inital_position 
 * @param dynamic_position 
 * @param piece 
 */

static void bind_piece(vec2 inital_position, vec2 dynamic_position, vec2 piece) {
    vao_bind(self.array_vertex[(int)dynamic_position[0]][(int)dynamic_position[1]]);
    texture_bind(self.texture_vertex[(int)piece[0]][(int)piece[1]]);
    vbo_bind(self.index_vertex);
    glDrawElements(GL_TRIANGLES, sizeof(self.index_data) / sizeof(unsigned int), GL_UNSIGNED_INT, 0);
}


/**
 * @brief Initalize fen data together.
 * 
 * @param position 
 * @param piece 
 */
static int index_fen = 0;
static void init_fen_data(vec2 position, vec2 piece) {
    fen_inital_data[index_fen][1] = position[1];  
    fen_inital_data[index_fen][0] = position[0];  
    fen_dynamic_data[index_fen][0] = position[0]; 
    fen_dynamic_data[index_fen][1] = position[1];
    fen_inital_data[index_fen][2] = piece[0]; 
    fen_inital_data[index_fen][3] = piece[1]; 
    fen_dynamic_data[index_fen][2] = piece[0]; 
    fen_dynamic_data[index_fen][3] = piece[1];
    printf("[INFO] - %s - %s \n", parser_board(position[0], position[1]), parser_piece(piece[0], piece[1]));
    index_fen++;
}

/**
 * @brief Load fen data
 * 
 * @param fen 
 */

static void load_fen(const char* fen) {
    int file = 0, rank = 0;
    for (int i = 0; fen[i] != '\0'; i++) {
        char c = fen[i];
        if (c == '/') {
            rank = 0;
            file++;
        } else if (c >= '1' && c <= '8') {
            rank += c - '0';
        } else {
            vec2 position = {file, rank};
            switch (c) {
                case 'P': init_fen_data(position, (vec2){WHITE, PAWN}); break;
                case 'N': init_fen_data(position, (vec2){WHITE, KNIGHT}); break;
                case 'B': init_fen_data(position, (vec2){WHITE, BISHOP}); break;
                case 'R': init_fen_data(position, (vec2){WHITE, ROOK}); break;
                case 'Q': init_fen_data(position, (vec2){WHITE, QUEEN}); break;
                case 'K': init_fen_data(position, (vec2){WHITE, KING}); break;
                case 'p': init_fen_data(position, (vec2){DARK, PAWN}); break;
                case 'n': init_fen_data(position, (vec2){DARK, KNIGHT}); break;
                case 'b': init_fen_data(position, (vec2){DARK, BISHOP}); break;
                case 'r': init_fen_data(position, (vec2){DARK, ROOK}); break;
                case 'q': init_fen_data(position, (vec2){DARK, QUEEN}); break;
                case 'k': init_fen_data(position, (vec2){DARK, KING}); break;
            }
            rank++;
        }
    }
}

/**
 * @brief Main initalize for piece
 * 
 * @return struct Piece 
 */

struct Piece piece_init() {
    mat4 proj;
    struct VBO coordinate_vertex;
    float buffer_coordinate_data[8] = {0, 1, 1, 1, 1, 0, 0, 0};
    const char* image_paths[2][6] = {
        {"../resources/texture/white_rook.png", "../resources/texture/white_horse.png", "../resources/texture/white_bishop.png", "../resources/texture/white_queen.png", "../resources/texture/white_king.png", "../resources/texture/white_pawn.png"},
        {"../resources/texture/black_rook.png", "../resources/texture/black_horse.png", "../resources/texture/black_bishop.png", "../resources/texture/black_queen.png", "../resources/texture/black_king.png", "../resources/texture/black_pawn.png"}
    };

    self.shader_vertex = shader_create("../resources/shaders/base.vs", "../resources/shaders/base.fs");
    self.scale = 4 * (float)(2 * window_get().y) / 64;
    glm_ortho(0, (float)window_get().x, 0, (float)window_get().y, -1, 1, proj);

    for (int i = 0; i < FILE; i++) {
        vec2 vertex_position = {0, 1};
        for (int j = 0; j < RANK; j++) {
            set_position_data(self.buffer_position_data[i][j], vertex_position, i + 1, self.scale);
            vertex_position[0]++;
            vertex_position[1]++;
        }
    }

    for (int i = 0; i < FILE; i++) {
        for (int j = 0; j < RANK; j++) {
            self.buffer_vertex[i][j] = vbo_create(GL_ARRAY_BUFFER, false);
            self.array_vertex[i][j] = vao_create();
        }
    }
    coordinate_vertex = vbo_create(GL_ARRAY_BUFFER, true);
    self.index_vertex = vbo_create(GL_ELEMENT_ARRAY_BUFFER, false);

    for (int i = 0; i < 6; i++) {
        self.texture_vertex[WHITE][i] = texture_create(image_paths[WHITE][i]);
        self.texture_vertex[DARK][i] = texture_create(image_paths[DARK][i]);
    }

    for (int i = 0; i < FILE; i++) {
        for (int j = 0; j < RANK; j++) {
            vbo_data(self.buffer_vertex[i][j], self.buffer_position_data[i][j], sizeof(self.buffer_position_data[i][j]));
        }
    }
    vbo_data(coordinate_vertex, buffer_coordinate_data, sizeof(buffer_coordinate_data));
    vbo_data(self.index_vertex, (unsigned int*)self.index_data, sizeof(self.index_data));

    for (int i = 0; i < FILE; i++) {
        for (int j = 0; j < RANK; j++) {
            vao_attrib(self.array_vertex[i][j], self.buffer_vertex[i][j], 0, 2, GL_FLOAT, 0, 0);
            vao_attrib(self.array_vertex[i][j], coordinate_vertex, 1, 2, GL_FLOAT, 0, 0);
        }
    }

    shader_bind(self.shader_vertex);
    glUniformMatrix4fv(glGetUniformLocation(self.shader_vertex.handle, "proj"), 1, false, *proj);
    glUniform1i(glGetUniformLocation(self.shader_vertex.handle, "id"), 0);

    return self;
}

void piece_get_info(struct Piece *piece) {
    *piece = self;
}

/**
 * @brief  The name speaks for itself.
 * 
 * @param piece_index 
 * @param colour_piece 
 * @param value_piece 
 * @param inital_position 
 */
static void highlight_selected_piece(int piece_index, int colour_piece, int value_piece, vec2 inital_position){
        glUniform1f(glGetUniformLocation(self.shader_vertex.handle, "square_type"), 
                ( fen_inital_data[piece_index][0] == inital_position[0] && fen_inital_data[piece_index][1] == inital_position[1]) && fen_dynamic_data[piece_index][2] == colour_piece && fen_dynamic_data[piece_index][3] == value_piece ? 1 : 0);
}

/**
 * @brief The name speaks for itself
 * 
 * @param board 
 * @param piece_index 
 * @param isHolded 
 */

static void translate_selected_piece(struct Board board, int piece_index, int selected_piece_index , bool isHolded){
        if (isHolded && window_get().mouse.buttons[GLFW_MOUSE_BUTTON_LEFT].down &&
            !is_equality_data(board.buffer_position_data[(int)board.cy][(int)board.cx], 
            board.buffer_position_data[(int)fen_dynamic_data[piece_index][0]][(int)fen_dynamic_data[piece_index][1]])
            ) {
                /*TODO: A more proper handle these pawn, king, ...  */
            fen_dynamic_data[selected_piece_index][0] = board.cy;
            fen_dynamic_data[selected_piece_index][1] = board.cx;
        }

}
static bool init = true;
static int piece_saved = ~1;
static bool holded = false;
static bool mouse_pressed = false;
/**
 * @brief Main render for piece.
 * 
 * @param self 
 */

void piece_render(struct Piece self) {
    shader_bind(self.shader_vertex);
    if (init) {
        init = false;
        load_fen(FEN);
    }
    board_get_info(&board);
    for (int i = 0; i < 32; i++) {
        if (window_get().mouse.buttons[GLFW_MOUSE_BUTTON_LEFT].down && !mouse_pressed &&
            is_equality_data(board.buffer_position_data[(int)board.cy][(int)board.cx],
            board.buffer_position_data[(int)fen_dynamic_data[i][0]][(int)fen_dynamic_data[i][1]])
            ) {
            printf("[INFO] - %s \n", parser_piece(fen_dynamic_data[i][2], fen_dynamic_data[i][3]));
            holded = true;
            piece_saved = i;
            mouse_pressed = true;
        }  else if (window_get().mouse.buttons[GLFW_MOUSE_BUTTON_LEFT].down && !mouse_pressed &&
            !is_equality_data(board.buffer_position_data[(int)board.cy][(int)board.cx],
            board.buffer_position_data[(int)fen_dynamic_data[i][0]][(int)fen_dynamic_data[i][1]])
            ) {
            piece_saved = ~1;
        }
        if (!window_get().mouse.buttons[GLFW_MOUSE_BUTTON_LEFT].down) {
            holded = false;
            mouse_pressed = false;
        }

        translate_selected_piece(board, i, piece_saved , holded);
        highlight_selected_piece(i, fen_dynamic_data[piece_saved][2], fen_dynamic_data[piece_saved][3], (vec2){fen_inital_data[piece_saved][0],fen_inital_data[piece_saved][1]});
        bind_piece((vec2){fen_inital_data[i][0], fen_inital_data[i][1]}, (vec2){fen_dynamic_data[i][0], fen_dynamic_data[i][1]}, (vec2){fen_dynamic_data[i][2], fen_dynamic_data[i][3]});
    }
}

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