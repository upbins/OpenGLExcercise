#pragma once
#include <glad/glad.h>// 包含glad来获取所有的必须OpenGL头文件
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
private:
	//程序ID
	unsigned int ID;
    void checkCompileErrors(unsigned int shader, std::string type);
public:
    Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
    ~Shader();
    enum Slot 
    {
        DIFFUSE,
        SPECULAR,
        EMISSION,
    };
    // 使用/激活程序
    void use();
    // utility uniform functions
    // ------------------------------------------------------------------------
    void setBool(const std::string &name, bool value);
    // ------------------------------------------------------------------------
    void setInt(const std::string &name, int value);
    // ------------------------------------------------------------------------
    void setFloat(const std::string &name, float value);
    // ------------------------------------------------------------------------
    void setVec2(const std::string &name, const glm::vec2 &value); 
        // ------------------------------------------------------------------------
    void setVec2(const std::string &name, float x, float y);
    // ------------------------------------------------------------------------
    void setVec3(const std::string &name, const glm::vec3 &value);
    // ------------------------------------------------------------------------
    void setVec3(const std::string &name, float x, float y, float z);
    // ------------------------------------------------------------------------
    void setVec4(const std::string &name, const glm::vec4 &value);
    // ------------------------------------------------------------------------
    void setVec4(const std::string &name, float x, float y, float z, float w);
    // ------------------------------------------------------------------------
    void setMat2(const std::string &name, const glm::mat2 &mat);
    // ------------------------------------------------------------------------
    void setMat3(const std::string &name, const glm::mat3 &mat);
    // ------------------------------------------------------------------------
    void setMat4(const std::string &name, const glm::mat4 &mat);
};
