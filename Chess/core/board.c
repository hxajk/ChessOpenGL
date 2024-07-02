/// @file board.c

#include <Chess/core/board.h>

#define BOARD_SIZE 64
#define POSITIONS_PER_SQUARE 8

#define WHITE_SQUARE 0.93333334, 0.84705883, 0.7529412, 1.0,\
                    0.93333334, 0.84705883, 0.7529412 , 1.0,\
                    0.93333334, 0.84705883, 0.7529412, 1.0,\
                    0.93333334, 0.84705883, 0.7529412, 1.0,\

#define DARK_SQUARE 0.67058825, 0.47843137, 0.39607844, 1.0,\
                    0.67058825, 0.47843137, 0.39607844, 1.0,\
                    0.67058825, 0.47843137, 0.39607844, 1.0,\
                    0.67058825, 0.47843137, 0.39607844, 1.0,\

static void set_position_data(float buffer_position_data[BOARD_SIZE][POSITIONS_PER_SQUARE], int start, int end, int y, float scale){
    vec2 current_position = {0, 1};
    int i,j;
    for (i = start; i < end; i++) {
            for (j = 0; j < POSITIONS_PER_SQUARE; j++) {
                if ((j & 1) == 1) {
                    buffer_position_data[i][j] = scale * ((j <= 3) ? y : y - 1); // If y <= 3, draw UP right, else draw UP down
                } else {
                    buffer_position_data[i][j] = scale * ((j == 0 || j == 6) ? current_position[0] : current_position[1]);
                }
            }
            current_position[0]++;
            current_position[1]++;
        }
        current_position[0] = 0;
        current_position[1] = 1;
};

/**
 * @brief Initalize, create chess board.
 * 
 * @return struct Board 
 */

struct Board board_init(){
    float buffer_position_data[64][8] = {{0}};
    float buffer_coordinate_data[8] = {
        0,1,
        1,1,
        1,0,
        0,0
    };
    float buffer_color_data[2][16] = {
        {
           WHITE_SQUARE
        },
        {
           DARK_SQUARE
        },
    };
    float scale;
    mat4 proj;
    scale = 4 * (float)(2 * window_get().y) / 64;
    struct VBO coordinate_vertex;
    struct VBO color_vertex[64];
    struct Board self = {
        .shader_vertex = shader_create("../resources/shaders/board.vs", "../resources/shaders/board.fs"),
        .index_data = {
            0,1,2,2,3,0
        },
    };

    // Rank 1
    set_position_data(buffer_position_data,0,  8,    1, scale);
    // Rank 2
    set_position_data(buffer_position_data,8,  16,   2, scale);
    // Rank 3
    set_position_data(buffer_position_data,16, 24,   3, scale);
    // Rank 4
    set_position_data(buffer_position_data,24, 32,   4, scale);
    // Rank 5
    set_position_data(buffer_position_data,32, 40,   5, scale);
    // Rank 6
    set_position_data(buffer_position_data,40, 48,   6, scale);
    // Rank 7
    set_position_data(buffer_position_data,48, 56,   7, scale);
    // Rank 8
    set_position_data(buffer_position_data,56, 64,   8, scale);

    glm_ortho(0, (float)window_get().x, 0, (float)window_get().y, -1, 1, proj);

    for(int i = 0;i < BOARD_SIZE;i++){
        self.buffer_vertex[i] = vbo_create(GL_ARRAY_BUFFER, false);
        self.array_vertex[i] = vao_create();
        color_vertex[i] = vbo_create(GL_ARRAY_BUFFER, false);
    }

    self.index_vertex = vbo_create(GL_ELEMENT_ARRAY_BUFFER, false);

    for(int i = 0;i < BOARD_SIZE;i += 1)
    {
        vao_bind(self.array_vertex[i]);
        vbo_data(self.buffer_vertex[i], buffer_position_data[i], sizeof(buffer_position_data[i]));
    };
    
    for(int i = 0;i < 8;i += 1)
    {
        for(int j = 0;j < 8;j += 1)
        {
            if((i + j) & 1)
                vbo_data(color_vertex[i*8+j], buffer_color_data[0], sizeof(buffer_color_data[0]));
            else  
                vbo_data(color_vertex[i*8+j], buffer_color_data[1], sizeof(buffer_color_data[1]));
        };
    };
    

    vbo_data(self.index_vertex, (unsigned int*)self.index_data, sizeof(self.index_data));

    for(int i = 0;i < BOARD_SIZE;i += 1)
    {
        vao_attrib(self.array_vertex[i], self.buffer_vertex[i], 0, 2, GL_FLOAT, 0, 0);
        vao_attrib(self.array_vertex[i], color_vertex[i], 1, 4, GL_FLOAT, 0, 0);
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
    for(int i = 0;i < BOARD_SIZE;i += 1)
    {
        vao_bind(self.array_vertex[i]);
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

    for(int i = 0;i < BOARD_SIZE;i += 1)
    {
        vao_destroy(self.array_vertex[i]);
        vbo_destroy(self.buffer_vertex[i]);
    };
};