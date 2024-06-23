/*

   ____ _                      ___                    ____ _     
  / ___| |__   ___  ___ ___   / _ \ _ __   ___ _ __  / ___| |    
 | |   | '_ \ / _ \/ __/ __| | | | | '_ \ / _ \ '_ \| |  _| |    
 | |___| | | |  __/\__ \__ \ | |_| | |_) |  __/ | | | |_| | |___ 
  \____|_| |_|\___||___/___/  \___/| .__/ \___|_| |_|\____|_____|
                                   |_|                           

-- Author: hxajk (hxajkzzz@gmail.com).
-- Update: 2024-06-20 15:12:00 
*/

///////////////////////////////////////////////////////////////

#include "Chess/gfx/shader.h"
#include "Chess/gfx/vao.h"
#include "Chess/gfx/vbo.h"

#include <string>
#include <cstdio>
#include <vector>
#define INCLUDE_GLFW_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>
/////////////////////////////////////////////////////////////


void run(int width, int height, std::string title);

int main()
{
    run(1024 / 2,1024 / 2,"Chess");
};

void run(int width, int height, std::string title)
{
    if(!glfwInit()){
        return;
    }

    #if _DEBUG
    glfwWindowHint(GLFW_CONTEXT_DEBUG, true);
    #endif

    GLFWwindow* window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);

    if(!window)
    {
        glfwTerminate();
        return;
    };

    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);

    glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int w, int h){
        glViewport(0, 0, w, h);
    });

    glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods){
        if(key == GLFW_KEY_SPACE)  glfwSetWindowShouldClose(window, GLFW_TRUE); 
    });

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        return;
    };

    Shader shader = shader_create("D:/ChessOpenGL/resources/base.vs", "D:/ChessOpenGL/resources/base.fs");

    std::vector<float> v = {
        1,1,
        1,-1,
        -1,-1,
        -1,1
    };
    std::vector<GLuint> i = {
        0,1,2,
        2,3,0,
    };
    
   struct VBO vbo = vbo_create(GL_ARRAY_BUFFER, false);

   struct VBO ibo = vbo_create(GL_ELEMENT_ARRAY_BUFFER, false);

   vbo_bind(vbo);

   vbo_bind(ibo);

   vbo_data(vbo, v.data(), v.size() * sizeof(float));

   vbo_data(ibo, i.data(), i.size() * 4);

    VAO vao = vao_create();

    vao_bind(vao);

    vao_attrib(vao, vbo, 0, 2, GL_FLOAT, 2 * sizeof(float), 0);

    shader_bind(shader);

    glUniform2f(glGetUniformLocation(shader.handle, "resolution"), width, height);

    while (!glfwWindowShouldClose(window)) {

        shader_bind(shader);
        vbo_bind(vbo);
        vbo_bind(ibo);
        vao_bind(vao);
        glDrawElements(GL_TRIANGLES,i.size(),GL_UNSIGNED_INT,0);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

};