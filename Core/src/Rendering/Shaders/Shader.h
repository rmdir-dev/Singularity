#pragma once

#include "Utils/pch.h"
#include "glm/glm.hpp"

namespace Rendering
{
    class Shader
    {
    //!!!!!!!!!!!!!!!!!!!!!!!!!!
    //      Functions
    //!!!!!!!!!!!!!!!!!!!!!!!!!!
    public:
        Shader(const char* filePath);
        ~Shader();

        void Bind();
        void Unbind();

        uint CompileShader(uint type, const std::string& src);
        uint CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
        std::tuple<std::string, std::string> ParseShader(const std::string& filePath);

    //!!!!!!!!!!!!!!!!!!!!!!!!!!
    //      Uniforms
    //!!!!!!!!!!!!!!!!!!!!!!!!!!  
        //INT
        void SetUniform1i(const char* name, int value);

        //FLOAT
        void SetUniform1f(const char* name, float v1);
        void SetUniform3f(const char* name, float v1, float v2, float v3);
        void SetUniform3f(const char* name, const glm::vec3& values);
        void SetUniform4f(const char* name, float v1, float v2, float v3, float v4);
        void SetUniform4f(const char* name, const glm::vec4& values);

        //MATRIX
        void SetUniformMatrix4fv(const char* name, const glm::mat4& value);

    private:
        int GetUniformLocation(const char* str);

    //!!!!!!!!!!!!!!!!!!!!!!!!!!
    //      Variables
    //!!!!!!!!!!!!!!!!!!!!!!!!!!
    private:
        unsigned int ID;
        std::string filePath;
        std::unordered_map<std::string, int> uniformLocations;
        
    public:
    };
}