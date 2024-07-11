/// @file rules.c 

#include <Chess/core/rules.h>
#include <stdio.h>

static struct Board board; static struct Piece piece;
static double x,y;
static float scale;
bool is_equality_data(float data_1[8], float data_2[8]){
        for(int i = 0;i < 8;i++){
                if(data_1[i] != data_2[i]){
                        return false;
                }
        }
        return true;
};
bool is_select_pieces(int colour_index,int piece_index)
{

        board_get_info(&board);
        piece_get_info(&piece);
        if(colour_index == WHITE){
                if(is_equality_data(piece.buffer_position_data[WHITE][piece_index], board.buffer_position_data[(int)board.cy][(int)board.cx]) ){
                        return true;
                }
        } else  {
                if(is_equality_data(piece.buffer_position_data[DARK][piece_index], board.buffer_position_data[(int)board.cy][(int)board.cx]) ){
                        return true;
                }
        }

        return false;
};