#include "Chess/util/parser.h"

const char* parser_piece(int colour, int piece){
  static char parser_data[20];
  const char* parser_piece_data[6] = {
    "ROOK", "HORSE", "BISHOP", "QUEEN", "KING", "PAWN" 
  };

  const char* parser_colour_data[2] = {
    "WHITE", "DARK"
  };

  memset(parser_data, 0, sizeof(parser_data));

  strcpy(parser_data, parser_colour_data[colour]);
    
  strcat(parser_data, " ");
    
  strcat(parser_data, parser_piece_data[piece]);

  return parser_data;
}


const char* parser_board(int x, int y){
 static char parser_data[2];
 
 parser_data[0] = 'A' + x;  parser_data[1] = '0' + y;
  
  return parser_data;
};