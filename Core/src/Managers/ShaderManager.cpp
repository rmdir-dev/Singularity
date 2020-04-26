#include "ShaderManager.h"

namespace Manager
{
    ShaderManager::ShaderManager() 
    {
        std::string vert = "//Shader VERTEX\n\
                            #version 330 core\n\
                            \n\
                            layout (location = 0) in vec3 inPos;\n\
                            \n\
                            void main()\n\
                            {\n\
                                gl_Position = vec4(inPos.x, inPos.y, inPos.z, 1.0);\n\
                            }";

        std::string frag = "//Shader FRAGMENT\n\
                            #version 330 core\n\
                            \n\
                            out vec4 outFragColor;\n\
                            \n\
                            void main() \n\
                            {\n\
                                outFragColor = vec4(1.0);\n\
                            }";
        m_Shaders["Default"] = std::make_shared<Rendering::Shader>(vert, frag);
        m_Shaders["BasicShader"] = std::make_shared<Rendering::Shader>("Assets/BasicShader");
        m_Shaders["BasicTextureD"] = std::make_shared<Rendering::Shader>("Assets/BasicTextureD");
        m_Shaders["BasicTextureDS"] = std::make_shared<Rendering::Shader>("Assets/BasicTextureDS");
        m_Shaders["BasicTextureDSN"] = std::make_shared<Rendering::Shader>("Assets/BasicTextureDSN");
    }

    ShaderManager::~ShaderManager() 
    {
        
    }

    void ShaderManager::addShader(std::string name, std::shared_ptr<Rendering::Shader> shader) 
    {
        //TODO stock shader name in the shader class
        m_Shaders[name] = shader;
    }

    std::shared_ptr<Rendering::Shader> ShaderManager::LoadShader(const char* filePath) 
    {
        std::string name = filePath;
        name = name.substr(name.find('/') + 1, name.length());
        
        std::unordered_map<std::string, std::shared_ptr<Rendering::Shader>>::const_iterator got = m_Shaders.find(filePath);
        if(got == m_Shaders.end())
        {
            m_Shaders[name] = std::make_shared<Rendering::Shader>(filePath);
        }
        return m_Shaders[name];
    }

    std::shared_ptr<Rendering::Shader> ShaderManager::GetBestShader(const ShaderOptions& options) 
    {
        switch (options.flags)
        {
        case TEXDIFF:
            return m_Shaders["BasicTextureD"];
            break;
        case TEXSPEC:
            return m_Shaders["BasicTextureDS"];
            break;
        case TEXNORM:
            return m_Shaders["BasicTextureDSN"];
            break;
            //TODO change light management once the shaders are done.
        case LIGHTPOINT:
            return m_Shaders["BasicShader"];
            break;
        
        default:
            return m_Shaders["Default"];
            break;
        }
        //TODO
        return m_Shaders["Default"];
    }
}

