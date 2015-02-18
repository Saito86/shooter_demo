//vertex shader
#version 120

//varying vec2 texcoord;
//varying vec3 position;
//varying vec3 normal;

//uniform vec3 lightPos;

//varying vec3 tangentSurf2Light;
//varying vec3 tangentSurf2View;

void main()
{
	///
	//vec3 lightpos2 = vec3(gl_ModelViewMatrix*vec4(lightPos,1.0));
	//gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
	//texcoord = gl_MultiTexCoord0.xy;
	//position = vec3(gl_ModelViewMatrix * gl_Vertex);
	//normal = gl_NormalMatrix*gl_Normal;
	//
	//vec3 tangent;
	//vec3 v1=cross(gl_Normal,vec3(0.0,0.0,1.0));
	//vec3 v2=cross(gl_Normal,vec3(0.0,1.0,0.0));
	//if(length(v1)>length(v2))
	//	tangent = v1;
	//else
	//	tangent = v2;
	//	
	//vec3 n = normalize(gl_NormalMatrix*gl_Normal);
	//vec3 t = normalize(gl_NormalMatrix*tangent);
	//vec3 b = cross(n,t);
	////mat3 mat = mat3(t.x,t.y,t.z,b.x,b.y,b.z,n.x,n.y,n.z);
	//mat3 mat = mat3(t.x,b.y,n.z,t.x,b.y,n.z,t.x,b.y,n.z);
	//
	//vec3 vc = normalize(lightpos2-position);
	//tangentSurf2Light = mat*vc;
	//
	//vc = normalize(-position);
	//tangentSurf2View = mat*vc;
	///
	gl_TexCoord[0] = gl_MultiTexCoord0;
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
	
}
//end