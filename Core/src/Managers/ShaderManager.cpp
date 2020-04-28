#include "ShaderManager.h"

namespace Manager
{
    ShaderManager::ShaderManager() 
    {
        std::string vert = "//Shader VERTEX\n\
                            #version 330 core\n\
                            \n\
                            layout (location = 0) in vec3 inPos;\n\
                            layout (location = 1) in vec4 inColor;\n\
                            layout (location = 2) in vec2 inUvs;\n\
                            layout (location = 3) in vec3 inNormals;\n\
                            layout (location = 4) in vec3 inTangent;\n\
                            layout (location = 5) in vec3 inBitangent;\n\ 
                            \n\
                            uniform mat4 model;\n\
                            uniform mat4 view;\n\
                            uniform mat4 projection;\n\
                            uniform vec3 vColor;\n\
                            \n\
                            void main()\n\
                            {\n\
                                vec3 fragPosition = vec3(model * vec4(inPos, 1.0));\n\
                                gl_Position = projection * view * vec4(fragPosition, 1.0);\n\
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
        m_Shaders["BasicTextureD"] = std::make_shared<Rendering::Shader>("Assets/TextureTesting/BasicTextureD");
        m_Shaders["BasicTextureDS"] = std::make_shared<Rendering::Shader>("Assets/TextureTesting/BasicTextureDS");
        m_Shaders["BasicTextureDSN"] = std::make_shared<Rendering::Shader>("Assets/TextureTesting/BasicTextureDSN");
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
        name = name.substr(name.find_last_of('/') + 1, name.length());
        
        std::unordered_map<std::string, std::shared_ptr<Rendering::Shader>>::const_iterator got = m_Shaders.find(name);
        if(got == m_Shaders.end())
        {
            m_Shaders[name] = std::make_shared<Rendering::Shader>(filePath);
        }
        return m_Shaders[name];
    }

    std::shared_ptr<Rendering::Shader> ShaderManager::GetBestShader(const byte& options) 
    {
        switch (options)
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

    void ShaderManager::SetView(const glm::mat4& view) 
    {
        for(std::pair<std::string, std::shared_ptr<Rendering::Shader>> element : m_Shaders)
        {
            element.second->Bind();
            element.second->SetUniformMatrix4fv("view", view);
            element.second->Unbind();
        }
    }

    void ShaderManager::SetProjection(const glm::mat4& projection) 
    {
        for(std::pair<std::string, std::shared_ptr<Rendering::Shader>> element : m_Shaders)
        {
            element.second->Bind();
            element.second->SetUniformMatrix4fv("projection", projection);
            element.second->Unbind();
        }
    }
}

