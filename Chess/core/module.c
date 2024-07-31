


#include <Chess/core/module.h>
struct Piece piece;
void highlight_selected_piece(int piece_index, int colour_piece, int value_piece, vec2 inital_position){
        piece_get_info(&piece);
        glUniform1f(glGetUniformLocation(piece.shader_vertex.handle, "square_type"), 
                ( fen_inital_data[piece_index][0] == inital_position[0] && fen_inital_data[piece_index][1] == inital_position[1]) && fen_dynamic_data[piece_index][2] == colour_piece && fen_dynamic_data[piece_index][3] == value_piece ? 1 : 0);
}


void translate_selected_piece(struct Board board, int piece_index, int selected_piece_index , bool isHolded){
        if (isHolded && window_get().mouse.buttons[GLFW_MOUSE_BUTTON_LEFT].down &&
            !is_equality_data(board.buffer_position_data[(int)board.cy][(int)board.cx], 
            board.buffer_position_data[(int)fen_dynamic_data[piece_index][0]][(int)fen_dynamic_data[piece_index][1]])
            ) {
                /*TODO: A more proper handle these pawn, king, ...  */
            fen_dynamic_data[selected_piece_index][0] = board.cy;
            fen_dynamic_data[selected_piece_index][1] = board.cx;
        }

}