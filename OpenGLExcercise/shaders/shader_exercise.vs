#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;
out vec3 outColor;
out vec2 texCoord;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 transform;
void main()
{
    //注意乘法要從右向读
    gl_Position = projection * view * model * vec4(aPos,1.0f);//transform * vec4(aPos,1.0f);
    texCoord = vec2(aTexCoord.x,aTexCoord.y);;
    outColor = aColor;
}