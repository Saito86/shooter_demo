//fragment shader
#version 120

uniform sampler2D diffuseMap;
uniform sampler2D normalMap;
uniform vec4 color;
//varying vec2 texcoord;
//varying vec3 position;
//varying vec3 normal;
//
//uniform vec3 lightPos;
//
//uniform vec3 m_ambient;
//uniform vec3 m_diffuse;
//uniform vec3 m_specular;
//uniform float m_shinines;
//
//uniform vec3 l_ambient;
//uniform vec3 l_diffuse;
//uniform vec3 l_specular;
//
//varying vec3 tangentSurf2Light;
//varying vec3 tangentSurf2View;

void main()
{
	//vec3 lightpos2 = vec3(gl_ModelViewMatrix*vec4(lightPos,1.0));
	////texture
	//vec4 texColor = texture2D(diffuseMap,texcoord);
	//
	////ambient light
	//vec3 ambient = texColor.xyz*l_ambient;
	//
	////diffuse light
	//vec3 surfLight = normalize(tangentSurf2Light);
	//vec3 norm = normalize(texture2D(normalMap,texcoord).xyz*2.0-1.0);
	//float dcont = max(0.0,dot(norm,surfLight));
	//vec3 diffuse = dcont*(texColor.xyz*l_diffuse);
	//
	////specular light
	//float dist = length(position-lightpos2);
	//float att = 1.0/(1.0 + 0.01 * dist + 0.001 * dist*dist);
	//vec3 surfView = normalize(tangentSurf2View);
	//vec3 reflection = reflect(-surfLight,norm);
	//
	//float scont = pow(max(0.0,dot(surfView,reflection)),m_shinines);
	//vec3 specular = scont * l_specular * m_specular;
	//
	////gl_FragColor = vec4((texColor.xyz*(ambient+diffuse+specular)*att),1.0);
	//gl_FragColor = vec4((ambient+diffuse+specular)*att,texColor.a);
	vec3 normal = normalize(texture2D(normalMap,gl_TexCoord[0].st).rgb * 2.0 -1.0);
	vec3 lightpos = normalize(vec3(1.0,1.0,1.5));
	float diffuse = max(dot(normal,lightpos),0.0);
	vec3 color = diffuse * texture2D(diffuseMap,gl_TexCoord[0].st).rgb;
	gl_FragColor = vec4(color,1.0);
}
//end