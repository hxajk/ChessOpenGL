/// @file rules.c 

#include <Chess/core/rules.h>

static struct Board board; static struct Piece piece;
static float* piece_clicked_data[2048];
static float  board_clicked_data[2048][8];
static int board_saved = -1; static int piece_saved = -1;
static int  clicked_times = 0;
static int delay_times = 0;
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

bool is_select_pieces(struct Piece self, double xp, double yp)
{
        piece = self;

        glfwGetCursorPos(window_get().handle, &xp, &yp);

        yp = glm_max(0,yp);   
        xp = glm_max(0,xp);

        yp = fabs(yp - 576);
        if(is_equality_data(piece.buffer_position_data[piece.index], board.buffer_position_data[board_saved])){
                piece_saved = piece.index;
        }
        else if(!is_equality_data(piece.buffer_position_data[piece.index], board.buffer_position_data[board_saved])){
                /* printf("EMPTY SQUARE\n"); */
        }

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

        if(glms_aabb_events(board.buffer_position_data[board.index], xp, yp)){
                board_saved = board.index;
        }

        bool is_white_pawn = piece_saved >= 8 && piece_saved <= 15;
        bool is_black_pawn = piece_saved >= 24 && piece_saved <= 32;

        if(is_white_pawn && is_equality_data(piece.buffer_position_data[piece_saved], board.buffer_position_data[board_saved])){
                if(board.index == board_saved + 8 || board.index ==  board_saved + 16){
                        return true;
                }
        }

        if(is_black_pawn && is_equality_data(piece.buffer_position_data[piece_saved], board.buffer_position_data[board_saved])){
                if(board.index == board_saved - 8 || board.index ==  board_saved - 16){
                        return true;
                }
        }

        return false;
};