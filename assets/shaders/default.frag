//fragment shader
#version 120

uniform sampler2D diffuseMap;
uniform vec4 color;
varying vec2 texcoord;
varying vec3 position;
varying vec3 normal;

uniform vec3 m_ambient;

void main()
{
	vec4 texColor = texture2D(diffuseMap,texcoord) * color;
	gl_FragColor = texColor;
}
//end