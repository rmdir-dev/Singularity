#include "TextureManager.h"

namespace Manager
{
    TextureManager::TextureManager() 
    {
        
    }


    TextureManager::~TextureManager() 
    {
        
    }

    std::shared_ptr<Rendering::Texture> TextureManager::LoadTexture(const char* filePath) 
    {
        std::unordered_map<std::string, std::shared_ptr<Rendering::Texture>>::const_iterator got = m_Textures.find(filePath);
        if(got == m_Textures.end())
        {
            m_Textures[filePath] = std::make_shared<Rendering::Texture>(filePath);
        }
        return m_Textures[filePath];
    }
}

