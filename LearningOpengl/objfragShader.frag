#version 440 core

in vec3 fragPosition;
in vec3 normal;

uniform vec3 objColor;
uniform vec3 lightColor;
uniform vec3 lightSource;
uniform vec3 viewSource;
uniform int bline;

out vec4 color;

void main()
{

	vec3 ambient = 0.1f * lightColor;
	vec3 lightDir = normalize(lightSource - fragPosition);
	vec3 nor = normalize(normal);

	float lightDistance = length(lightSource - fragPosition);
	float constantAttenuation = 1.0;	//衰减因子
	float lineAttenuation = 1.0;
	float quadraticAttenuation = 0.5;
	float Attenuation;

//diffu
	float diff = max( dot(nor, lightDir), 0.0);

//calculate specular;

	float ref;
	if(bline == 1)
	{
		vec3 viewDir = normalize(viewSource - fragPosition);
		vec3 halfDir = normalize(viewSource + normalize(lightDir));
		if(diff == 0.0) ref = 0.0;						//如果没有光照，反射光也不必计算				
		else ref = pow(max(dot(nor, halfDir), 0.0f), 32);
	}
	else
	{
		vec3 viewDir = normalize(viewSource - fragPosition);
		vec3 reflectDir = reflect(-lightDir, nor);
		ref = pow(max(dot(viewDir, reflectDir), 0.0f), 32);		
	}

	Attenuation = 1.0 / (constantAttenuation + lineAttenuation * lightDistance + quadraticAttenuation * lightDistance * lightDistance);
//	Attenuation = 1.0;
	vec3 diffuse = Attenuation * diff * lightColor;
	vec3 specular = Attenuation * ref * lightColor;

	color = vec4( (ambient + diffuse + specular) * objColor, 1.0f);	//在此处高光不参加颜色的调制，直接叠加
}