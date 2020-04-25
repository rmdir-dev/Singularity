#pragma once

#include "Utils/pch.h"
#include "Rendering/Texture/Texture.h"

namespace Manager
{
    class TextureManager
    {
        //!!!!!!!!!!!!!!!!!!!!!!!!!!
        //        FUNCTIONS
        //!!!!!!!!!!!!!!!!!!!!!!!!!!
    public:
        TextureManager();
        ~TextureManager();

        std::shared_ptr<Rendering::Texture> LoadTexture(const char* filePath);

    protected:
    
        //!!!!!!!!!!!!!!!!!!!!!!!!!!
        //        VARIABLE
        //!!!!!!!!!!!!!!!!!!!!!!!!!!
    public:
    protected:
        std::unordered_map<std::string, std::shared_ptr<Rendering::Texture>> m_Textures;
    };
}