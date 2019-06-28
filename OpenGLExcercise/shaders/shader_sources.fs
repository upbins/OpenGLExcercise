#version 330 core
out vec4 FragColor;
in vec3 FragPos;
in vec2 texCoord;
in vec3 Normal;
struct Material
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};
uniform Material material;
uniform sampler2D texture1;
uniform sampler2D texture2;
struct Light 
{
	vec3 objectColor;
	vec3 ambientColor;
	vec3 diffuseColor;
	vec3 lightPos;
	vec3 lightColor;
};
uniform Light light;
uniform vec3 cameraPos;
void main()
{   
	vec4 Texture = mix(texture(texture1, vec2(texCoord.x,texCoord.y)), texture(texture2, vec2(1-texCoord.x,texCoord.y)), 0.2);
	// Ambient
    vec3 ambient = material.ambient * light.ambientColor;
	// Diffuse 
	vec3 lightDir = normalize(light.lightPos - FragPos);
	vec3 diffuse = material.diffuse * max(dot(lightDir,Normal), 0.0) * light.diffuseColor;
	//reflect
	vec3 reflectVec = reflect(-lightDir,Normal);
	vec3 cameraVec = normalize(cameraPos - FragPos);
	float specularAmount = pow(max(dot(reflectVec,cameraVec),0.0),material.shininess);//镜面烦着的角度
	vec3 specular = specularAmount * light.lightColor * material.specular ;
	vec4 result = vec4((ambient + diffuse + specular) * light.objectColor, 1.0f);//Texture * vec4((diffuse + ambientColor) * objectColor, 1.0f);
	FragColor = result;
}