#include "ShaderManager.h"

namespace Manager
{
    ShaderManager::ShaderManager() 
    {
        std::string vert = "//Shader VERTEX\
                            #version 330 core\
                            \
                            layout (location = 0) in vec3 inPos;\
                            \
                            void main()\
                            {\
                                gl_Position = vec4(inPos.x, inPos.y, inPos.z, 1.0);\
                            }";

        std::string frag = "//Shader FRAGMENT\
                            #version 330 core\
                            \
                            out vec4 outFragColor;\
                            \
                            void main() \
                            {\
                                outFragColor = vec4(1.0);\
                            }";
        m_Shaders["Default"] = std::make_shared<Rendering::Shader>(vert, frag);
    }

    ShaderManager::~ShaderManager() 
    {
        
    }

    std::shared_ptr<Rendering::Shader> ShaderManager::LoadShader(const char* filePath) 
    {
        std::unordered_map<std::string, std::shared_ptr<Rendering::Shader>>::const_iterator got = m_Shaders.find(filePath);
        if(got == m_Shaders.end())
        {
            m_Shaders[filePath] = std::make_shared<Rendering::Shader>(filePath);
        }
        return m_Shaders[filePath];
    }

    std::shared_ptr<Rendering::Shader> ShaderManager::GetBestShader(const ShaderOptions& options) 
    {
        //TODO
        return m_Shaders["Default"];
    }
}

