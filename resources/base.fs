#version 330 core 

out vec4 FragColor;

uniform vec2 resolution; // 1024x1024

#define WHITE vec3(0.941,0.941,0.874)
#define BLACK vec3(0.247,0.345,0.4)

void main(){

    vec2 uv = gl_FragCoord.xy / resolution;

    vec3 result = vec3(0.0f);

    float chessboard = mod(floor(uv.x * 8) + floor(uv.y * 8),2);

    result = mix(BLACK,WHITE, chessboard);

    FragColor = vec4(result,1);
}