#version 140


// in - glVertexAttribPointer in clasa Shader
attribute vec3 position;  
attribute vec2 texCoord;
attribute vec3 normal;

// out catre fragment shader
varying vec2 texCoord0;  
varying vec3 normal0; 
varying vec3 pos0;


// in - Update in clasa Shader
uniform mat4 MVP;  
uniform mat4 Normal;  

void main()
{
	gl_Position = MVP * vec4(position, 1.0);
	texCoord0 = texCoord;
	pos0 = gl_Position.xyz;
	
	// ramane doar componentele x, y, z
	normal0 = (Normal * vec4(normal, 0.0)).xyz;
}
