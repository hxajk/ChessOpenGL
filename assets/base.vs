#version 330 core 

layout (location = 0) in vec3 pData;
layout (location = 1) in vec3 cData;

out vec3 color;

void main(){
    gl_Position = vec4(pData,1);
    color = cData;
}