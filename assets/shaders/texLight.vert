//vertex shader
#version 120

varying vec2 texcoord;
varying vec3 position;
varying vec3 normal;

void main()
{
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
	texcoord = gl_MultiTexCoord0.xy;
	position = vec3(gl_ModelViewMatrix * gl_Vertex);
	normal = gl_NormalMatrix*gl_Normal;
}
//end