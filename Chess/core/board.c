/// @file board.c

#include "Chess/util/util.h"
#include <Chess/core/board.h>

#define WHITE_SQUARE 0.93333334, 0.84705883, 0.7529412,1.0,  \
                    0.93333334, 0.84705883, 0.7529412 ,1.0,  \
                    0.93333334, 0.84705883, 0.7529412, 1.0,  \
                    0.93333334, 0.84705883, 0.7529412, 1.0,  \

#define DARK_SQUARE 0.67058825, 0.47843137, 0.39607844, 1.0, \
                    0.67058825, 0.47843137, 0.39607844, 1.0, \
                    0.67058825, 0.47843137, 0.39607844, 1.0, \
                    0.67058825, 0.47843137, 0.39607844, 1.0, \

#define RANK 8
#define FILE 8

static struct Board self = {
        .index_data = {
            0,1,2,2,3,0
        }
    };
static int SQUARE_TYPE = 0;


// NOTES: UP LEFT -> UP RIGHT -> DOWN RIGHT -> DOWN LEFT (CLOCKWISE ORDER).
static void set_position_data(float buffer_position_data[BOARD_SIZE][POSITIONS_PER_SQUARE], int start, int end, int y, float scale){
    vec2 current_position = {0, 1};
    int i,j;
    for (i = start; i < end; i++) {
            for (j = 0; j < POSITIONS_PER_SQUARE; j++) {
                if ((j & 1) == 1) {
                    buffer_position_data[i][j] = scale*((j <= 3) ? y : y - 1); 
                } else {
                    buffer_position_data[i][j] = scale*((j == 0 ||  j == 6) ? current_position[0] : current_position[1]);
                }
            }
            current_position[0]++;
            current_position[1]++;
        }
        current_position[0] = 0;
        current_position[1] = 1;
};

// NOTES: ODD & ONE = False, EVEN & ONE = True
static void set_colour_data(struct VBO* colour_vertex, float (*buffer_colour_data)[16]){
    for(int i = 0;i < RANK;i++){
        for(int j = 0;j < FILE;j ++){
            if((i + j) & 1){
                vbo_data(colour_vertex[i*RANK+j], buffer_colour_data[0], sizeof(buffer_colour_data[0]));
            }
            else if(!((i+j) & 1)){  
                vbo_data(colour_vertex[i*RANK+j], buffer_colour_data[1], sizeof(buffer_colour_data[1]));
            }
        };
    };
};

/**
 * @brief Initalize, create chess board.
 * 
 * @return struct Board 
 */

struct Board board_init(){
    mat4 proj;
    struct VBO coordinate_vertex;
    struct VBO color_vertex[BOARD_SIZE];
    float buffer_coordinate_data[8] = {
        0,1,
        1,1,
        1,0,
        0,0
    };
    float buffer_color_data[2][16] = {
        { WHITE_SQUARE },
        { DARK_SQUARE  },
    };

    self.shader_vertex = shader_create("../resources/shaders/board.vs", "../resources/shaders/board.fs");
    self.scale = 4 * (float)(2 * window_get().y) / BOARD_SIZE;
    
    for(self.index = 1;self.index <= RANK;self.index++){
        set_position_data(self.buffer_position_data, (self.index-1)*RANK, (self.index)*RANK, self.index, self.scale);
    }

    glm_ortho(0, (float)window_get().x, 0, (float)window_get().y, -1, 1, proj);

    for(self.index = 0;self.index < BOARD_SIZE;self.index++){
        self.buffer_vertex[self.index] = vbo_create(GL_ARRAY_BUFFER, false);
        self.array_vertex[self.index] = vao_create();
        color_vertex[self.index] = vbo_create(GL_ARRAY_BUFFER, false);
    }

    self.index_vertex = vbo_create(GL_ELEMENT_ARRAY_BUFFER, false);

    for(self.index = 0;self.index < BOARD_SIZE;self.index++){
        vbo_data(self.buffer_vertex[self.index], self.buffer_position_data[self.index], sizeof(self.buffer_position_data[self.index]));
    };
    vbo_data(self.index_vertex, (unsigned int*)self.index_data, sizeof(self.index_data));
    set_colour_data(color_vertex, buffer_color_data);

    for(self.index = 0;self.index < BOARD_SIZE;self.index++){
        vao_attrib(self.array_vertex[self.index], self.buffer_vertex[self.index], 0, 2, GL_FLOAT, 0, 0);
        vao_attrib(self.array_vertex[self.index], color_vertex[self.index], 1, 4, GL_FLOAT, 0, 0);
    };

    shader_bind(self.shader_vertex);
    glUniformMatrix4fv(glGetUniformLocation(self.shader_vertex.handle,"proj"),1,false,*proj);
    return self;
};

/**
 * @brief Render, draw board.
 * 
 * @param self 
 */
void board_render(struct Board self){
    glClear(GL_COLOR_BUFFER_BIT);
    shader_bind(self.shader_vertex);
    for(self.index = 0;self.index < BOARD_SIZE;self.index++){
        if(is_possible_moves(self, 0.0, 0.0)){
            SQUARE_TYPE = 1;
        }
        else  
        {
            SQUARE_TYPE = 0;
        };
        glUniform1f(glGetUniformLocation(self.shader_vertex.handle,"square_type"),SQUARE_TYPE);
        vao_bind(self.array_vertex[self.index]);
        vbo_bind(self.index_vertex);
        glDrawElements(GL_TRIANGLES, sizeof(self.index_data) / sizeof(unsigned int), GL_UNSIGNED_INT, 0 );
    };
    
};

/**
 * @brief Destroy, destruct board
 * 
 * @param self 
 */

void board_destroy(struct Board self)
{
    shader_destroy(self.shader_vertex);
    
    vbo_destroy(self.index_vertex);

    for(self.index = 0;self.index < BOARD_SIZE;self.index++){
        vao_destroy(self.array_vertex[self.index]);
        vbo_destroy(self.buffer_vertex[self.index]);
    };
};