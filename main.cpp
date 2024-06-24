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

#include "Chess/core/board.h"
#include "Chess/gfx/shader.h"
#include "Chess/gfx/vao.h"
#include "Chess/gfx/vbo.h"

#include <string>
#include <cstdio>
#define INCLUDE_GLFW_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>
/////////////////////////////////////////////////////////////


void run(int width, int height, std::string title);

int main(int argc, char *argv[])
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

    Board board = board_init();


    while (!glfwWindowShouldClose(window)) {

        board_render(board);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

};