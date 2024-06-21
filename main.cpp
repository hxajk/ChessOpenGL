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

#include <cstdio>
#include <GLFW/glfw3.h>

int main()
{
    
    if(!glfwInit())
        return -1;

    GLFWwindow* window = glfwCreateWindow(1000,1000,"ChessOpenGL", NULL, NULL);

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);


    while(!glfwWindowShouldClose(window))
    {

        glfwPollEvents();
        glfwSwapBuffers(window);
    };
    return 0;
};
