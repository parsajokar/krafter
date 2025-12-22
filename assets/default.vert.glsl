#version 450 core

layout(location = 0) uniform mat4 u_ViewProjection;

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec2 a_UvCoords;

out vec2 v_UvCoords;

void main()
{
    v_UvCoords = a_UvCoords;
    gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
}
