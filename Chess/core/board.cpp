#include <Chess/core/board.h>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtc/type_ptr.hpp>

struct Board board_init(){
    glm::mat4 proj;
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

    proj = glm::ortho<float>(0,512,0,512);


    self.buffer_vertex = vbo_create(GL_ARRAY_BUFFER, false);
    self.array_vertex = vao_create();
    self.index_vertex = vbo_create(GL_ELEMENT_ARRAY_BUFFER, false);

    vbo_bind(self.buffer_vertex);
    vbo_bind(self.index_vertex);

    vbo_data(self.buffer_vertex, self.buffer_data.data(), self.buffer_data.size() * sizeof(float) );
    vbo_data(self.index_vertex, self.index_data.data(), self.index_data.size() * sizeof(GLuint));

    vao_bind(self.array_vertex);
    vao_attrib(self.array_vertex, self.buffer_vertex, 0, 2, GL_FLOAT, 2 * sizeof(float), 0);

    shader_bind(self.shader_vertex);

    glUniformMatrix4fv(glGetUniformLocation(self.shader_vertex.handle,"proj"),1,false,glm::value_ptr(proj));

    glUniform2f(glGetUniformLocation(self.shader_vertex.handle,"resolution"),(float)window_get().x,(float)window_get().y);

    return self;
};

void board_render(struct Board self){
    shader_bind(self.shader_vertex);
    vao_bind(self.array_vertex);
    vbo_bind(self.index_vertex);
    glDrawElements(GL_TRIANGLES, self.index_data.size(), GL_UNSIGNED_INT, 0 );
};

