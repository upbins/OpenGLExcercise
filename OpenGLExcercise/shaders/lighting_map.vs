#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 aNormal;
layout (location = 3) in vec2 aTexCoordLight;
out vec3 Normal;
out vec3 FragPos;
out vec2 texCoord;
out vec2 texCoordLight;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
void main()
{
    //注意乘法要從右向读
    gl_Position = projection * view * model * vec4(aPos,1.0f);
    FragPos = vec3(model * vec4(aPos,1.0f));
    Normal = mat3(transpose(inverse(model))) * aNormal;
    texCoord = vec2(aTexCoord.x,aTexCoord.y);
    texCoordLight = vec2(aTexCoordLight.x,aTexCoordLight.y);
}