#version 330 core 

out vec4 FragColor;
in vec2 texture_data;
uniform sampler2D id;   
void main()
{
    FragColor = texture2D(id,texture_data);
}