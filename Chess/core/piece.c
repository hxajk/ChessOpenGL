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


static struct PieceState self_state = {
    .holded = false,
    .mouse_pressed = false,
    .piece_saved = -1,
    .selected_piece_index = -1
};

static struct Piece self = {
    .index_data = {0, 1, 2, 2, 3, 0}
};
static bool init = true;
static unsigned int SQUARE_TYPE = 0;
struct Board board;

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

void bind_piece(vec2 inital_position, vec2 dynamic_position, vec2 piece);
void update_piece_state_on_mouse_down(int piece_index, struct Board* board);
void update_piece_state_on_mouse_up();

/**
 * @brief Main render for piece.
 * 
 * @param self 
 */

void piece_render(struct Piece self) {
    shader_bind(self.shader_vertex);
    if (init) {
        init = false;
        load_fen_data(FEN);
    }
    board_get_info(&board);
    for (int i = 0; i < 32; i++) {
        update_piece_state_on_mouse_down(i, &board);
        if (self_state.piece_saved != -1) {
            translate_selected_piece(board, i, self_state.piece_saved, self_state.holded);
            highlight_selected_piece(i, fen_dynamic_data[self_state.piece_saved][2],
                                      fen_dynamic_data[self_state.piece_saved][3], 
                                      (vec2){fen_inital_data[self_state.piece_saved][0], fen_inital_data[self_state.piece_saved][1]});
        }
        bind_piece((vec2){fen_inital_data[i][0], fen_inital_data[i][1]}, (vec2){fen_dynamic_data[i][0], fen_dynamic_data[i][1]},
                   (vec2){fen_dynamic_data[i][2], fen_dynamic_data[i][3]});
        update_piece_state_on_mouse_up();
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



/**
 * @brief Come to the end ^ Released -> Reset everthing!
 * 
 */
void update_piece_state_on_mouse_up(){
        if (!window_get().mouse.buttons[GLFW_MOUSE_BUTTON_LEFT].down) {
        self_state.holded = false;
        self_state.mouse_pressed = false;
    }
}

/**
 * @brief Pressed ^ corresponding to the piece position -> saved all the states, otherwise unsaved the piece
 * 
 * @param piece_index 
 * @param board 
 */

void update_piece_state_on_mouse_down(int piece_index, struct Board* board){
        if (window_get().mouse.buttons[GLFW_MOUSE_BUTTON_LEFT].down && !self_state.mouse_pressed &&
        is_equality_data(board->buffer_position_data[(int)board->cy][(int)board->cx],
                         board->buffer_position_data[(int)fen_dynamic_data[piece_index][0]][(int)fen_dynamic_data[piece_index][1]])) {
        self_state.holded = true;
        self_state.piece_saved = piece_index;
        self_state.mouse_pressed = true;
    } else if (window_get().mouse.buttons[GLFW_MOUSE_BUTTON_LEFT].down && !self_state.mouse_pressed &&
               !is_equality_data(board->buffer_position_data[(int)board->cy][(int)board->cx],
                                 board->buffer_position_data[(int)fen_dynamic_data[piece_index][0]][(int)fen_dynamic_data[piece_index][1]])) {
        self_state.piece_saved = -1;
    }
}

/**
 * @brief A better way to handle OpenGL:)
 * 
 * @param inital_position 
 * @param dynamic_position 
 * @param piece 
 */

void bind_piece(vec2 inital_position, vec2 dynamic_position, vec2 piece){
    vao_bind(self.array_vertex[(int)dynamic_position[0]][(int)dynamic_position[1]]);
    texture_bind(self.texture_vertex[(int)piece[0]][(int)piece[1]]);
    vbo_bind(self.index_vertex);
    glDrawElements(GL_TRIANGLES, sizeof(self.index_data) / sizeof(unsigned int), GL_UNSIGNED_INT, 0);
}