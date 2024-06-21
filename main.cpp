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


int WIDTH = 1024 / 2;
int HEIGHT = 1024 / 2;

struct HelperFunctions 
{
    std::string LoadShaderFile(const std::string& data){
        
        std::string filepath = "D:/ChessOpenGL/assets/" + data;

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
            -1,-1,
            -1,1,
            1,1,
            1,-1 
        };

        IndexData = {
            0,1,2,
            2,3,0
        };


        glGenBuffers(1,&VertexBuffer);
        glBindBuffer(GL_ARRAY_BUFFER,VertexBuffer);
        glBufferData(GL_ARRAY_BUFFER,VertexData.size() * sizeof(float), VertexData.data(), GL_STATIC_DRAW);



        glGenBuffers(1,&IndexBuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,IndexBuffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER,IndexData.size() * sizeof(GLuint), IndexData.data(), GL_STATIC_DRAW);

        
        glGenVertexArrays(1,&VertexArray);
        glBindVertexArray(VertexArray);

        glVertexAttribPointer(0,2,GL_FLOAT,false,2 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        HelperFunctions _func;

        ShaderID = _func.LoadShader("base.vs", "base.fs");

        glUseProgram(ShaderID);
        glUniform2f(glGetUniformLocation(ShaderID,"resolution"),WIDTH,HEIGHT);

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
    
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow* window = glfwCreateWindow(WIDTH,HEIGHT,"ChessOpenGL", NULL, NULL);

    glfwMakeContextCurrent(window);

     glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int w, int h){
      glViewport(0,0,w,h);
      printf("%d - %d \n", w, h);
    });

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
