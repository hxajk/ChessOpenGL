/// @file rules.c 

#include <Chess/core/rules.h>
#include <stdio.h>

static struct Board board; static struct Piece piece;
static int board_saved = -1; static int piece_saved = -1;
static float* piece_position_data[32][8]; 
static bool holded = false;
static int x_saved = -1,y_saved = -1;
static int SCALE = BOARD_SIZE / 8;
typedef struct IsPieceIndex{
        bool is_white_pawn;
        bool is_black_pawn;

        bool is_white_knight;
        bool is_black_knight;

        bool is_white_bishop;
        bool is_black_bishop;

        bool is_white_king;
        bool is_black_king;

        bool is_white_queen;
        bool is_black_queen;

        bool is_white_rook;
        bool is_black_rook;
} IsPieceIndex;

bool is_clicked_piece(){
        struct Window window = window_get();
        if(window.mouse.buttons[GLFW_MOUSE_BUTTON_LEFT].down){
                return true;
        }
        else if(window.mouse.buttons[GLFW_MOUSE_BUTTON_RIGHT].down){
                return false;
        } else {
                return false;
        }
};

bool is_equality_data(float x_data[8],float y_data[8]){
        if(
                x_data[0] == y_data[0] &&
                x_data[1] == y_data[1] &&
                x_data[2] == y_data[2] &&
                x_data[3] == y_data[3]  
          ){
                return true;
          }
          return false;
};

void initalize_copy_data(float copy_data[32][8]){
        for(int i = 0;i < 32;i++){
                for(int j = 0;j < 8;j++){
                        piece_position_data[i][j] = malloc(1 * sizeof(float));
                        *piece_position_data[i][j] = copy_data[i][j];
                }
        }

        printf("%f \n", *piece_position_data[31][0]);
};

bool is_select_pieces(struct Piece* self, double xp, double yp)
{
        piece = *self;

        glfwGetCursorPos(window_get().handle, &xp, &yp);

        yp = glm_max(0,yp);   
        xp = glm_max(0,xp);

        yp = fabs(yp - 576);
        if(is_equality_data(piece.buffer_position_data[piece.index], board.buffer_position_data[board_saved])){
                piece_saved = piece.index;
                holded = true;
        }
        else if(!is_equality_data(piece.buffer_position_data[piece.index], board.buffer_position_data[board_saved])){
                /* printf("EMPTY SQUARE\n"); */
        }

        if(holded){
                bool is_clicked_events = window_get().mouse.buttons[GLFW_MOUSE_BUTTON_LEFT].down;
                if(is_clicked_events){
                        *piece_position_data[piece_saved][0] = (x_saved - 0) * SCALE;
                        *piece_position_data[piece_saved][1] = (y_saved + 1) * SCALE;

                        *piece_position_data[piece_saved][2] = (x_saved + 1) * SCALE;
                        *piece_position_data[piece_saved][3] = (y_saved + 1) * SCALE;

                        *piece_position_data[piece_saved][4] = (x_saved + 1) * SCALE;
                        *piece_position_data[piece_saved][5] = (y_saved + 0) * SCALE;

                        *piece_position_data[piece_saved][6] = (x_saved - 0) * SCALE;
                        *piece_position_data[piece_saved][7] = (y_saved + 0) * SCALE;
                }
                else if(!is_clicked_events){
                        holded = false;
                };
        }
        if (piece_saved != -1 && !holded) {

        for(int i = 0;i < 8;i++){
                self->buffer_position_data[piece_saved][i] = *piece_position_data[piece_saved][i];
                }        
        }
        printf("%f \n", self->buffer_position_data[9][0]);

        if(piece_saved == piece.index && is_equality_data(piece.buffer_position_data[piece.index], board.buffer_position_data[board_saved])){
                return true;
        } else {
                return false;
        }
};

bool is_possible_moves(struct Board self, double xp, double yp)
{
         glfwGetCursorPos(window_get().handle, &xp, &yp);

        yp = glm_max(0,yp);   
        xp = glm_max(0,xp);

        yp = fabs(yp - 576);

        board = self;
        bool is_clicked_events = window_get().mouse.buttons[GLFW_MOUSE_BUTTON_LEFT].down;
        if(is_clicked_events &&  glms_aabb_events(board.buffer_position_data[board.index], xp, yp)){
                board_saved = board.index;
                x_saved = xp / 72;
                y_saved = yp / 72;
        }

        IsPieceIndex is_piece;

        is_piece.is_white_pawn = piece_saved >= 8 && piece_saved <= 15;
        is_piece.is_black_pawn = piece_saved >= 24 && piece_saved <= 31;

        is_piece.is_white_knight = piece_saved == 1 || piece_saved == 6;
        is_piece.is_black_knight = piece_saved == 17 || piece_saved == 22;

        is_piece.is_white_bishop = piece_saved == 2 || piece_saved == 5;
        is_piece.is_black_bishop = piece_saved == 18 || piece_saved == 21;

        is_piece.is_white_king = piece_saved == 4; 
        is_piece.is_black_king = piece_saved == 20;

        is_piece.is_white_queen = piece_saved == 3;
        is_piece.is_black_queen = piece_saved == 19;

        is_piece.is_white_rook = piece_saved == 0 || piece_saved == 7;
        is_piece.is_black_rook = piece_saved == 16 || piece_saved == 24;

        /* if(is_piece.is_white_pawn && is_equality_data(piece.buffer_position_data[piece_saved], board.buffer_position_data[board_saved])){
                if(board.index == board_saved + 8 || board.index ==  board_saved + 16){
                        return true;
                }
                printf("%s \n", "WHITE_PAWN");
        } 
        else if(is_piece.is_black_pawn && is_equality_data(piece.buffer_position_data[piece_saved], board.buffer_position_data[board_saved])){
                if(board.index == board_saved - 8 || board.index ==  board_saved - 16){
                        return true;
                }
                printf("%s \n", "BLACK_PAWN");
        }

        else if(is_piece.is_white_knight && is_equality_data(piece.buffer_position_data[piece_saved], board.buffer_position_data[board_saved])){
                printf("%s \n", "WHITE_KNIGHT");
        }
        else if(is_piece.is_black_knight && is_equality_data(piece.buffer_position_data[piece_saved], board.buffer_position_data[board_saved])){
                printf("%s \n", "BLACK_KNIGHT");
        }

        else if(is_piece.is_white_bishop && is_equality_data(piece.buffer_position_data[piece_saved], board.buffer_position_data[board_saved])){
                printf("%s \n", "WHITE_BISHOP");
        }
        else if(is_piece.is_black_bishop && is_equality_data(piece.buffer_position_data[piece_saved], board.buffer_position_data[board_saved])){
                printf("%s \n", "BLACK_BISHOP");
        }

        else if(is_piece.is_white_king && is_equality_data(piece.buffer_position_data[piece_saved], board.buffer_position_data[board_saved])){
                printf("%s \n", "WHITE_KING");
        }
        else if(is_piece.is_black_king && is_equality_data(piece.buffer_position_data[piece_saved], board.buffer_position_data[board_saved])){
                printf("%s \n", "BLACK_KING");
        }

        else if(is_piece.is_white_queen && is_equality_data(piece.buffer_position_data[piece_saved], board.buffer_position_data[board_saved])){
                printf("%s \n", "WHITE_QUEEN");
        }
        else if(is_piece.is_black_queen && is_equality_data(piece.buffer_position_data[piece_saved], board.buffer_position_data[board_saved])){
                printf("%s \n", "BLACK_QUEEN");
        }

        else if(is_piece.is_white_rook && is_equality_data(piece.buffer_position_data[piece_saved], board.buffer_position_data[board_saved])){
                printf("%s \n", "WHITE_ROOK");
        }
        else if(is_piece.is_black_rook && is_equality_data(piece.buffer_position_data[piece_saved], board.buffer_position_data[board_saved])){
                printf("%s \n", "BLACK_ROOK");
        } */

        return false;
};