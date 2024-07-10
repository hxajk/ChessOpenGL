/// @file board.c

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

/**
 * @brief Set the position data object
 * The purpose of this function is to represent position as the square.
 * @param self.buffer_position_data 
 * @param start 
 * @param end 
 * @param y 
 * @param self.scale 
 */
// NOTES: UP LEFT -> UP RIGHT -> DOWN RIGHT -> DOWN LEFT (CLOCKWISE ORDER).
static void set_position_data(float buffer_position_data[RANK][POSITIONS_PER_SQUARE],int y, float scale){
    int j,k;
    static vec2 current_position = {0, 1};
    for(j = 0;j < RANK;j++){
        for(k = 0;k < POSITIONS_PER_SQUARE;k++){
            if ((k & 1) == 1) {
                buffer_position_data[j][k] = scale*((k <= 3) ? y : y - 1); 
            } else {
                buffer_position_data[j][k] = scale*((k == 0 ||  k == 6) ? current_position[0] : current_position[1]);
            }
        }
        current_position[0]++; current_position[1]++;
    }
    current_position[0] = 0; current_position[1] = 1;
}

/**
 * @brief Set the colour data object
 * The purpose of this function is to represent position as the square.
 * @param self.buffer_position_data 
 * @param start 
 * @param end 
 * @param y 
 * @param self.scale 
 */
// NOTES: ODD & ONE = False, EVEN & ONE = True
static void set_colour_data(struct VBO colour_vertex[8][8], float (*buffer_colour_data)[16]){
    for(int i = 0;i < RANK;i++){
        for(int j = 0;j < FILE;j ++){
            if((i + j) & 1){
                vbo_data(colour_vertex[i][j], buffer_colour_data[0], sizeof(buffer_colour_data[0]));
            }
            else if(!((i+j) & 1)){  
                vbo_data(colour_vertex[i][j], buffer_colour_data[1], sizeof(buffer_colour_data[1]));
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
    struct VBO color_vertex[FILE][RANK];
    float buffer_color_data[2][16] = {
        { WHITE_SQUARE },
        { DARK_SQUARE  },
    };

    self.shader_vertex = shader_create("../resources/shaders/board.vs", "../resources/shaders/board.fs");
    self.scale = 4 * (float)(2 * window_get().y) / BOARD_LIMIT;
    int i,j;
    for(i = 0;i < FILE;i++){
            set_position_data(self.buffer_position_data[i], i+1, self.scale);
    }

    glm_ortho(0, (float)window_get().x, 0, (float)window_get().y, -1, 1, proj);

    for(i = 0;i < FILE;i++){
        for(j = 0;j < RANK;j++){
            self.buffer_vertex[i][j] = vbo_create(GL_ARRAY_BUFFER, false);
            self.array_vertex[i][j] = vao_create();
            color_vertex[i][j] = vbo_create(GL_ARRAY_BUFFER, false);
        }
    }
    self.index_vertex = vbo_create(GL_ELEMENT_ARRAY_BUFFER, false);

    for(i = 0;i < FILE;i++){
        for(j = 0;j < RANK;j++){
            vbo_data(self.buffer_vertex[i][j], self.buffer_position_data[i][j], sizeof(self.buffer_position_data[i][j]));
        }
    };
    vbo_data(self.index_vertex, (unsigned int*)self.index_data, sizeof(self.index_data));
    set_colour_data(color_vertex, buffer_color_data);

    for(i = 0;i < FILE;i++){
        for(j = 0;j < RANK;j++){
            vao_attrib(self.array_vertex[i][j], self.buffer_vertex[i][j], 0, 2, GL_FLOAT, 0, 0);
            vao_attrib(self.array_vertex[i][j], color_vertex[i][j], 1, 4, GL_FLOAT, 0, 0);
        }
    };

    printf("%f \n", self.buffer_position_data[0][7][0]);
    printf("%f \n", self.buffer_position_data[0][7][2]);
    printf("%f \n", self.buffer_position_data[0][7][4]);
    printf("%f \n", self.buffer_position_data[0][7][6]);


    shader_bind(self.shader_vertex);
    glUniformMatrix4fv(glGetUniformLocation(self.shader_vertex.handle,"proj"),1,false,*proj);
    return self;
};
static double cx,cy;
void board_get_info(struct Board* board){
    glfwGetCursorPos(window_get().handle, &self.cx, &self.cy);    
    self.cx = glm_max(0,self.cx);
    self.cy = glm_max(0,self.cy);
   
    self.cx = glm_min(504,self.cx);
    self.cy = glm_min(504,self.cy);

    self.cy = fabs(self.cy - 504);

    self.cx = self.cx / self.scale;
    self.cy = self.cy / self.scale;
    
    *board = self;
}

/**
 * @brief Render, draw board.
 * 
 * @param self 
 */
void board_render(struct Board self){
    glClear(GL_COLOR_BUFFER_BIT);
    shader_bind(self.shader_vertex);
    int i,j;
    for(i = 0;i < FILE;i++){
        for(j = 0; j < RANK;j++){
            glUniform1f(glGetUniformLocation(self.shader_vertex.handle,"square_type"),SQUARE_TYPE);
            vao_bind(self.array_vertex[i][j]);
            vbo_bind(self.index_vertex);
            glDrawElements(GL_TRIANGLES, sizeof(self.index_data) / sizeof(unsigned int), GL_UNSIGNED_INT, 0 );
        };
    
    };
}

/**
 * @brief Destroy, destruct board
 * 
 * @param self 
 */

void board_destroy(struct Board self)
{
    shader_destroy(self.shader_vertex);
    int i,j;
    vbo_destroy(self.index_vertex);

    for(i = 0;i < FILE;i++){
        for(j = 0;j < RANK;j++){
            vao_destroy(self.array_vertex[i][j]);
            vbo_destroy(self.buffer_vertex[i][j]);
        }
    };
};