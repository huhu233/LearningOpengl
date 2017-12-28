#version 440 core

in vec3 fragPosition;
in vec2 texcoord;
in vec3 normal;
struct Material
{
	sampler2D diffuse;
	vec3 specular;
	float shininess;

};

uniform Material material;

struct Light
{
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};
uniform Light light;

uniform vec3 viewSource;
out vec4 color;

void main()
{
	vec3 nor = normalize(normal);
//set ambient
//	vec3 ambient = light.ambient * vec3(texture(material.diffuse, texcoord));
	vec3 ambient = vec3(texture(material.diffuse, texcoord));
//set diffuse
	vec3 lightDir = normalize(light.position - fragPosition);
	float diff = max( dot(nor, lightDir), 0.0);
//	vec3 diffuse = diff * light.diffuse * vec3(texture(material.diffuse, texcoord));
	vec3 diffuse = vec3(texture(material.diffuse, texcoord));

//calculate specular;	
//	float specularStrength = 0.5;
	vec3 viewDir = normalize(viewSource - fragPosition);
	vec3 reflectDir = reflect(-lightDir, nor);
	float ref = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);
	vec3 tmp = vec3(texture(material.diffuse, texcoord));
//	vec3 specular = ref * light.specular * tmp;
	vec3 specular = 1.0 * tmp;
	color = vec4(ambient + diffuse + specular, 1.0f);
}