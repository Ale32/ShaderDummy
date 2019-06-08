#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 textCoord;

out vec2 v_textCoord;

uniform mat4 u_MVP;

void main()
{
    v_textCoord = textCoord;
    gl_Position = u_MVP * position;
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;
in vec2 v_textCoord;

uniform vec4 u_color;
uniform sampler2D u_texture;


void main()
{
    vec4 texColor = texture(u_texture, v_textCoord);
    color = texColor;
};