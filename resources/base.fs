#version 330 core 

out vec4 FragColor;
in vec2 tex;
uniform sampler2D id;   
void main()
{
    FragColor = texture2D(id,tex);
}