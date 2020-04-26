#pragma once

#include "Utils/pch.h"
#include "Rendering/Shaders/Shader.h"

#define LIGHTDIR    0x01
#define LIGHTPOINT  0x02
#define LIGHTSPOT   0x04
#define TEXDIFF     0x08
#define TEXSPEC     0x10
#define TEXNORM     0x20

namespace Manager
{
    union ShaderOptions
    {
        short flags;
        struct options
        {
            short LightDirectional  : 1;    // 0000 0001
            short LightPoint        : 1;    // 0000 0010
            short LightSpot         : 1;    // 0000 0100
            short TexDiffuse        : 1;    // 0000 1000
            short TexSpecular       : 1;    // 0001 0000
            short TexNormal         : 1;    // 0010 0000
        };
    };

    class ShaderManager
    {
        //!!!!!!!!!!!!!!!!!!!!!!!!!!
        //        FUNCTIONS
        //!!!!!!!!!!!!!!!!!!!!!!!!!!
    public:
        ShaderManager();
        ~ShaderManager();

        /*
        */
        void addShader(std::string name, std::shared_ptr<Rendering::Shader> shader);
        
        /*
        */
        std::shared_ptr<Rendering::Shader> LoadShader(const char* filePath);
        
        /*
        */
        std::shared_ptr<Rendering::Shader> GetBestShader(const ShaderOptions& options);

    private:
    
        //!!!!!!!!!!!!!!!!!!!!!!!!!!
        //        VARIABLE
        //!!!!!!!!!!!!!!!!!!!!!!!!!!
    public:
    private:
        std::unordered_map<std::string, std::shared_ptr<Rendering::Shader>> m_Shaders;
    };
}