//light

uniform sampler2D diffuseMap;

varying vec3 N;
varying vec3 v;
varying vec2 texcoord;

uniform vec3 m_ambient;

void main(void)
{
	vec4 finalColor = vec4(0.0,0.0,0.0,1.0);
	vec4 texColor = texture2D(diffuseMap,texcoord);
	vec3 halfVector;
	vec3 n;
	
	for(int i=0;i<2;i++)
	{
		vec3 L = normalize(gl_LightSource[i].position.xyz - v);
		vec3 E = normalize(-v);
		vec3 R = normalize(-reflect(L,N));
		halfVector = gl_LightSource[i].halfVector.xyz;
		n = normalize(N);
		float dist = length(L);
		
		vec4 lAmb = gl_FrontLightProduct[i].ambient;
		
		float ndotL = max(dot(N,L),0.0);
		
		vec4 lDiff = gl_FrontLightProduct[i].diffuse * ndotL;
		lDiff = clamp(lDiff,0.0,1.0);
		
		if(ndotL > 0.0)
		{
			float att = 1.0/(gl_LightSource[i].constantAttenuation + gl_LightSource[i].linearAttenuation*dist + gl_LightSource[i].quadraticAttenuation * dist * dist); 
			
			finalColor += att * (lDiff*ndotL + lAmb);
			
			
			vec3 hakfV = normalize(halfVector);
			float NdotHV = max(dot(n,hakfV),0.0);
			
			
			finalColor += att * gl_FrontMaterial.specular * gl_LightSource[i].specular * pow(NdotHV,gl_FrontMaterial.shininess);
		}
	}
	
	//gl_FragColor = (gl_FrontLightModelProduct.sceneColor + finalColor) * texColor;
	gl_FragColor =  finalColor * texColor;
}

//end