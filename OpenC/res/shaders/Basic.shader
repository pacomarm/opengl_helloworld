#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;

out vec2 v_TexCoord;
uniform mat4 u_MVP; // creation of the 4x4 matrix, Model View Projection (MVP)

void main()
{
	gl_Position = u_MVP * position; // now each vertex position is computed as 
	v_TexCoord = texCoord;			// the product of the MVP matrix and the 4-d position vector
};									

// ------

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_TexCoord;
uniform vec4 u_Color;
uniform sampler2D u_Texture;

void main()
{
	vec4 texColor = texture(u_Texture, v_TexCoord);
	color = texColor; // removed the color flickering animation
};