#version 450 core

layout(location = 1) uniform sampler2D u_Texture;

layout(location = 0) out vec4 o_Color;

in vec2 v_UvCoords;

void main()
{
    o_Color = texture(u_Texture, v_UvCoords);
}
