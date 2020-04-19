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
        void SetUniform3f(const char* name, float v1, float v2, float v3);

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