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

static void set_position_data(float buffer_position_data[POSITIONS_PER_PIECE], vec2 vertex_position, int y, float scale) {
    for (int j = 0; j < POSITIONS_PER_PIECE; j++) {
        buffer_position_data[j] = scale * ((j & 1) == 1 ? ((j <= 3) ? y : y - 1) : ((j == 0 || j == 6) ? vertex_position[0] : vertex_position[1]));
    }
}

static bool is_equality_data(float data_1[8], float data_2[8]) {
    for (int i = 0; i < 8; i++) {
        if (data_1[i] != data_2[i]) return false;
    }
    return true;
}

vec4 fen_inital_data[32];
vec4 fen_dynamic_data[32];

static void bind_piece(vec2 inital_position, vec2 dynamic_position, vec2 piece) {
    vao_bind(self.array_vertex[(int)dynamic_position[0]][(int)dynamic_position[1]]);
    texture_bind(self.texture_vertex[(int)piece[0]][(int)piece[1]]);
    vbo_bind(self.index_vertex);
    glDrawElements(GL_TRIANGLES, sizeof(self.index_data) / sizeof(unsigned int), GL_UNSIGNED_INT, 0);
}

int index_fen = 0;

static void bind_fen_data(vec2 position, vec2 piece) {
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
                case 'P': bind_fen_data(position, (vec2){WHITE, PAWN}); break;
                case 'N': bind_fen_data(position, (vec2){WHITE, KNIGHT}); break;
                case 'B': bind_fen_data(position, (vec2){WHITE, BISHOP}); break;
                case 'R': bind_fen_data(position, (vec2){WHITE, ROOK}); break;
                case 'Q': bind_fen_data(position, (vec2){WHITE, QUEEN}); break;
                case 'K': bind_fen_data(position, (vec2){WHITE, KING}); break;
                case 'p': bind_fen_data(position, (vec2){DARK, PAWN}); break;
                case 'n': bind_fen_data(position, (vec2){DARK, KNIGHT}); break;
                case 'b': bind_fen_data(position, (vec2){DARK, BISHOP}); break;
                case 'r': bind_fen_data(position, (vec2){DARK, ROOK}); break;
                case 'q': bind_fen_data(position, (vec2){DARK, QUEEN}); break;
                case 'k': bind_fen_data(position, (vec2){DARK, KING}); break;
            }
            rank++;
        }
    }
}

static void highlight_selected_piece(int piece_index, int colour_piece, int value_piece, vec2 inital_position){
        glUniform1f(glGetUniformLocation(self.shader_vertex.handle, "square_type"), 
                ( fen_inital_data[piece_index][0] == inital_position[0] && fen_inital_data[piece_index][1] == inital_position[1]) && fen_dynamic_data[piece_index][2] == colour_piece && fen_dynamic_data[piece_index][3] == value_piece ? 1 : 0);
}

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

bool init = true;
int piece_saved = 0;
bool holded = false;
bool mouse_pressed = false;

void piece_render(struct Piece self) {
    shader_bind(self.shader_vertex);
    if (init) {
        init = false;
        load_fen(FEN);
    }

    board_get_info(&board);

    for (int i = 0; i < 32; i++) {
        if (window_get().mouse.buttons[GLFW_MOUSE_BUTTON_LEFT].down && !mouse_pressed &&
            is_equality_data(board.buffer_position_data[(int)board.cy][(int)board.cx], board.buffer_position_data[(int)fen_dynamic_data[i][0]][(int)fen_dynamic_data[i][1]])) {
            printf("[INFO] - %s \n", parser_piece(fen_dynamic_data[i][2], fen_dynamic_data[i][3]));
            holded = true;
            piece_saved = i;
            mouse_pressed = true;
        }
        if (!window_get().mouse.buttons[GLFW_MOUSE_BUTTON_LEFT].down) {
            holded = false;
            mouse_pressed = false;
        }
        if (holded && window_get().mouse.buttons[GLFW_MOUSE_BUTTON_LEFT].down &&
            !is_equality_data(board.buffer_position_data[(int)board.cy][(int)board.cx], board.buffer_position_data[(int)fen_dynamic_data[i][0]][(int)fen_dynamic_data[i][1]])) {
            fen_dynamic_data[piece_saved][0] = board.cy;
            fen_dynamic_data[piece_saved][1] = board.cx;
        }
        highlight_selected_piece(i, DARK, ROOK, (vec2){7,7});
        highlight_selected_piece(i, WHITE, ROOK, (vec2){0,7});
        printf("%f - %f \n", board.cx, board.cy);
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