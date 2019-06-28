#version 330 core
out vec4 FragColor;
in vec3 outColor;// 从顶点着色器传来的输入变量（名称相同、类型相同）
in vec2 texCoord;
uniform sampler2D outTexture;
uniform sampler2D outTexture2;
uniform float mixThird;
void main()
{   
    FragColor = mix(texture(outTexture, vec2(texCoord.x,texCoord.y)), texture(outTexture2, vec2(1-texCoord.x,texCoord.y)) * vec4(outColor,1.0f), mixThird);//texture(outTexture,texCoord)*vec4(outColor,1.0f);/ //* vec4(outColor,1.0);
  
}