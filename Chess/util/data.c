#include <Chess/util/data.h>

static int index_fen = 0;
vec4 fen_inital_data[32];
vec4 fen_dynamic_data[32];
void init_fen_data(float *position, float *piece){
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
void load_fen_data(const char *fen){
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
void set_position_data(float *buffer_position_data, float *vertex_position, int y, float scale){
    for (int j = 0; j < POSITIONS_PER_PIECE; j++) {
        buffer_position_data[j] = scale * ((j & 1) == 1 ? ((j <= 3) ? y : y - 1) : ((j == 0 || j == 6) ? vertex_position[0] : vertex_position[1]));
    }
}
bool is_equality_data(float *data_1, float *data_2) {
    for (int i = 0; i < 8; i++) {
        if (data_1[i] != data_2[i]) return false;
    }
    return true;
}