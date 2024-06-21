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
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <sstream>
#include <fstream>
#include <vector>

struct HelperFunctions 
{
    std::string LoadShaderFile(const std::string& data){
        
        std::string filepath = "D:/LearnCpp/assets/" + data;

        std::fstream file(filepath);  

        std::stringstream ss;
        ss << file.rdbuf();

        return ss.str();
    };

    GLuint LoadShader(const char* VertexShaderName, const char* FragShaderName){
        GLuint ProgramID = glCreateProgram();

        std::string VertexShaderSourceTemp = LoadShaderFile(VertexShaderName);
        std::string FragShaderSourceTemp = LoadShaderFile(FragShaderName);
        
        const char* VertexShaderSource = VertexShaderSourceTemp.c_str();
        const char* FragShaderSource = FragShaderSourceTemp.c_str();

        auto CreateShader = [&](GLuint Mode, const char* ModeSource){
            GLuint ModeShader = glCreateShader(Mode);

            glShaderSource(ModeShader,1,&ModeSource,NULL);

            glCompileShader(ModeShader);

            glAttachShader(ProgramID,ModeShader);
            
            glDeleteShader(ModeShader);
        };

        CreateShader(GL_VERTEX_SHADER, VertexShaderSource);
        CreateShader(GL_FRAGMENT_SHADER, FragShaderSource);

        glLinkProgram(ProgramID);

        return ProgramID;
    };
};

class Triangle 
{
    private:
    GLuint ShaderID;
    GLuint VertexArray;
    GLuint VertexBuffer;
    GLuint IndexBuffer;

    std::vector<float> VertexData;
    std::vector<GLuint> IndexData;
    public:

    Triangle(){

        VertexData = {
            -0.5,0.0,0.0,   0,0,1,
            0.0,0.5,0.0,   0,1,0,
            0.5,0.0,0.0,   1,0,0
        };

        IndexData = {
            0,1,2
        };


        glGenBuffers(1,&VertexBuffer);
        glBindBuffer(GL_ARRAY_BUFFER,VertexBuffer);
        glBufferData(GL_ARRAY_BUFFER,VertexData.size() * sizeof(float), VertexData.data(), GL_STATIC_DRAW);



        glGenBuffers(1,&IndexBuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,IndexBuffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER,IndexData.size() * sizeof(GLuint), IndexData.data(), GL_STATIC_DRAW);

        
        glGenVertexArrays(1,&VertexArray);
        glBindVertexArray(VertexArray);

        glVertexAttribPointer(0,3,GL_FLOAT,false,6 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1,3,GL_FLOAT,false,6 * sizeof(float), (void*)12);
        glEnableVertexAttribArray(1);

        HelperFunctions _func;

        ShaderID = _func.LoadShader("base.vs", "base.fs");

        printf("%d %d %d %d \n", ShaderID, VertexArray, VertexBuffer, IndexBuffer);

        glBindVertexArray(0);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
    };

    void render(){
        glUseProgram(ShaderID);
        glBindVertexArray(VertexArray);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,IndexBuffer);
        glDrawElements(GL_TRIANGLES, IndexData.size(), GL_UNSIGNED_INT, 0);
    };
};


int main()
{
    
    if(!glfwInit())
        return -1;

    GLFWwindow* window = glfwCreateWindow(1000,1000,"ChessOpenGL", NULL, NULL);

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    if(!gladLoadGL())
        return -1;

    Triangle* triangle = new Triangle();
    while(!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(1, 1, 1, 1);

        triangle->render();

        glfwPollEvents();
        glfwSwapBuffers(window);
    };

    delete triangle;
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
};
