#version 330 core 

layout (location = 0) in vec2 pData;


void main(){
    gl_Position = vec4(pData,0,1);
}