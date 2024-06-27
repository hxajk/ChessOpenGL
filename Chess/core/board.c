/// @file board.c

#include <Chess/core/board.h>
/**
 * @brief Initalize, create chess board.
 * 
 * @return struct Board 
 */

struct Board board_init(){
    mat4 proj;
    struct Board self = {
        .shader_vertex = shader_create("../resources/shaders/base.vs", "../resources/shaders/board.fs"),

        .buffer_data = {
            0,0,  
            0,512,  
            512,512,   
            512,0,
        },

        .index_data = {
            0,1,2,2,3,0
        },
    };

    glm_ortho(0, (float)window_get().x, 0, (float)window_get().y, -1, 1, proj);

    self.buffer_vertex = vbo_create(GL_ARRAY_BUFFER, false);
    self.array_vertex = vao_create();
    self.index_vertex = vbo_create(GL_ELEMENT_ARRAY_BUFFER, false);

    vbo_bind(self.buffer_vertex);
    vbo_bind(self.index_vertex);

    vbo_data(self.buffer_vertex, (float*)self.buffer_data , sizeof(self.buffer_data) );
    vbo_data(self.index_vertex, (unsigned int*)self.index_data , sizeof(self.index_data) ) ;

    vao_bind(self.array_vertex);
    vao_attrib(self.array_vertex, self.buffer_vertex, 0, 2, GL_FLOAT, 2 * sizeof(float), 0);

    shader_bind(self.shader_vertex);

    glUniformMatrix4fv(glGetUniformLocation(self.shader_vertex.handle,"proj"),1,false,*proj);

    glUniform2f(glGetUniformLocation(self.shader_vertex.handle,"resolution"),(float)window_get().x,(float)window_get().y);

    return self;
};

/**
 * @brief Render, draw board.
 * 
 * @param self 
 */

void board_render(struct Board self){
    shader_bind(self.shader_vertex);
    vao_bind(self.array_vertex);
    vbo_bind(self.index_vertex);
    glDrawElements(GL_TRIANGLES, sizeof(self.index_data) / sizeof(unsigned int), GL_UNSIGNED_INT, 0 );
};

/**
 * @brief Destroy, destruct board
 * 
 * @param self 
 */

void board_destroy(struct Board self)
{
    shader_destroy(self.shader_vertex);
    vao_destroy(self.array_vertex);
    vbo_destroy(self.buffer_vertex);
    vbo_destroy(self.index_vertex);
};