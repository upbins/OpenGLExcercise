#version 330 core
out vec4 FragColor;
in vec3 FragPos;
in vec2 texCoord;
in vec2 texCoordLight;//光照贴图纹理坐标
in vec3 Normal;
uniform vec3 cameraPos;
struct Material
{
	vec3 ambient;
	sampler2D diffuse;
	sampler2D specular;
	sampler2D emission;
	float shininess;
};
uniform Material material;

struct LightDirection
{
	vec3 pos;
	vec3 color;
	vec3 dirToLight;
};
uniform LightDirection lightD;

struct Light 
{
	vec3 objectColor;
	vec3 ambientColor;
	vec3 lightPos;
	vec3 lightColor;
	vec3 lightDirection;//平行光测试

};
uniform Light light;

vec3 CalcLightDirectional(LightDirection light,vec3 uNormal,vec3 dirToCamera)
{
	//diffuse max(dot(L,N),0.0f)

	float diffuseIntensity = max(dot(light.dirToLight,uNormal),0.0);
	vec3 diffuseColor = texture(material.diffuse,vec2(texCoordLight.x,texCoordLight.y)).rgb * diffuseIntensity * light.color;
	//specular pow(max(dot(R,Camerapos),0),shininess)
	vec3 R = normalize(reflect(-light.dirToLight,uNormal));
	float specularIntensity = pow(max(dot(R,dirToCamera),0),material.shininess);
	vec3 specularColor = texture(material.specular,vec2(texCoordLight.x,texCoordLight.y)).rgb * specularIntensity * light.color;//
	vec3 result = diffuseColor + specularColor;
	return result;
}
void main()
{   

	//最终结果
	vec3 result = vec3(0.0,0.0,0.0);
	vec3 uNormal = normalize(Normal);
	vec3 dirToCamera = normalize(cameraPos - FragPos);
	result += CalcLightDirectional(lightD,uNormal,dirToCamera);
	FragColor =  vec4(result,1.0f);
	
}