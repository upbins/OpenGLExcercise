#version 330 core
out vec4 FragColor;
in vec3 FragPos;
in vec2 texCoord;
in vec2 texCoordLight;//光照贴图纹理坐标
in vec3 Normal;
struct Material
{
	vec3 ambient;
	sampler2D diffuse;
	sampler2D specular;
	sampler2D emission;
	float shininess;
};
uniform Material material;
// uniform sampler2D texture1;
// uniform sampler2D texture2;
struct Light 
{
	vec3 objectColor;
	vec3 ambientColor;
	//vec3 diffuseColor;
	vec3 lightPos;
	vec3 lightColor;
	vec3 lightDirection;//平行光测试

};
uniform Light light;

struct LightSpot
{
	float cosInnerPhy;
	float cosOutterPhy;
	vec3  spotDirection;
};
uniform LightSpot lightSpot;

//衰减相关
struct Attenuation
{
	float constant;
	float linear;
	float quadratic;
};
uniform Attenuation attenuation;
uniform vec3 cameraPos;
void main()
{   
	//vec4 Texture = mix(texture(texture1, vec2(texCoord.x,texCoord.y)), texture(texture2, vec2(1-texCoord.x,texCoord.y)), 0.2);
	
	// Ambient
    //vec3 ambient = material.ambient * light.ambientColor;
	vec3 ambient = texture(material.diffuse,texCoordLight).rgb * light.ambientColor;

	// Diffuse 
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(light.lightPos - FragPos); //vector point to the light form fragment pos //从fragement指向灯光位置
   	//测试平行光源
	//vec3   lightDir = normalize(-light.lightDirection);
	float diff  = max(dot(lightDir,norm), 0.0);
	//noraml diffuse for vec3 struct
	//vec3 diffuse = material.diffuse * diff * light.lightColor;
	vec3 diffuse = texture(material.diffuse,vec2(texCoordLight.x,texCoordLight.y)).rgb * diff * light.lightColor;
    
	// specular
	vec3 cameraVec = normalize(cameraPos - FragPos);
	vec3 reflectVec = reflect(-lightDir,norm);
	float specularAmount = pow(max(dot(reflectVec,cameraVec),0.0),material.shininess);//镜面烦着的角度
	//noraml specular for vec3 struct
	//vec3 specular = specularAmount * light.lightColor * material.specular ;
	vec3 specular = texture(material.specular,texCoordLight).rgb * specularAmount * light.lightColor;
	//翻转镜面反射贴图测试,盒子中间偏亮,四周偏暗,相反
	//vec3 specular = (vec3(1.0f) - texture(material.specular,texCoordLight).rgb) * specularAmount * light.lightColor;


	// // spotlight (soft edges)
    float theta = dot(normalize(FragPos - light.lightPos), normalize(-lightSpot.spotDirection));
	FragColor = vec4((ambient + diffuse  + specular ) * light.objectColor, 1.0f);
	float spotRatio;
	if (theta > lightSpot.cosInnerPhy)
	{
		//inside
		spotRatio = 1.0f;
	}
	else if (theta > lightSpot.cosOutterPhy)
	{
		float epsilon = lightSpot.cosInnerPhy - lightSpot.cosOutterPhy;
		float intensity = clamp((theta - lightSpot.cosOutterPhy) / epsilon,0.0, 1.0);
		spotRatio = intensity;
		//spotRatio = (theta - light.cosInnerPhy) / (light.cosOutterPhy - light.cosInnerPhy);
	}
	else{
		//outside
		spotRatio = 0.0f;
	}

	//attenuation
	// float distance = length(light.lightPos - FragPos);
	// float attenuationNum = 1.0f / (attenuation.constant + attenuation.linear * distance + attenuation.quadratic*(distance*distance));
	// ambient  *= attenuationNum; 
    // diffuse   *= attenuationNum;
    // specular *= attenuationNum; 
	
	// Emission
	//vec3 emission = vec3(texture(material.emission, texCoordLight));
	//vec4 result = vec4((ambient + diffuse + specular + emission) * light.objectColor, 1.0f);//Texture * vec4((diffuse + ambientColor) * objectColor, 1.0f);

	//最终结果
	// vec4 result = vec4((ambient + diffuse  + specular ) * light.objectColor, 1.0f);
	vec4 result = vec4((ambient + (diffuse  + specular) * spotRatio) * light.objectColor, 1.0f);
	FragColor = result;
	
}