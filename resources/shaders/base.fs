#version 330 core 

out vec4 FragColor;
in vec2 texture_data;
uniform sampler2D id;   
uniform float square_type;
void main()
{
    vec4 tex_color = texture2D(id,texture_data);
    FragColor = tex_color;
    if(square_type == 1){
        FragColor += vec4(0.353,0.388,0.612, 0.15); //rgb(119, 118, 179)
    }
}