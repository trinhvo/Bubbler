#version 330 core

layout(location = 0) in vec4 vPos;

uniform mat4 MVP;

void main() {
    vec4 pos = vec4(vPos.xy, -vPos.z, vPos.w);
    gl_Position = MVP * pos;
}