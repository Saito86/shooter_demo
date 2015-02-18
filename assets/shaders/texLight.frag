//fragment shader
#version 120

uniform sampler2D diffuseMap;
uniform vec4 color;
varying vec2 texcoord;
varying vec3 position;
varying vec3 normal;

uniform vec3 lightPos;

uniform vec3 m_ambient;
uniform vec3 m_diffuse;
uniform vec3 m_specular;
uniform float m_shinines;

uniform vec3 l_ambient;
uniform vec3 l_diffuse;
uniform vec3 l_specular;

void main()
{
	//texture
	vec4 texColor = texture2D(diffuseMap,texcoord);
	
	//ambient light
	vec3 ambient = m_ambient*l_ambient;
	
	//diffuse light
	vec3 surfLight = normalize(lightPos-position);
	vec3 norm = normalize(normal);
	float dcont = max(0.0,dot(norm,surfLight));
	vec3 diffuse = m_diffuse*l_diffuse*dcont;
	
	//specular light
	float dist = length(position-lightPos);
	float att = 1.0/(0.5 + 0.01 * dist + 0.001 * dist*dist);
	vec3 surfView = normalize(-position);
	vec3 reflection = reflect(-surfLight,norm);
	
	float scont = pow(max(0.0,dot(surfView,reflection)),m_shinines);
	vec3 specular = l_specular * m_specular * scont;
	
	gl_FragColor = vec4(texColor.xyz*(ambient+(diffuse+specular)*att),1.0);
	//gl_FragColor = vec4((ambient+diffuse+specular)*att,1.0);
}
//end