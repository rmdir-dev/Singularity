#pragma once

#include "Utils/Type.h"

namespace Rendering
{
    class Texture
    {
    //!!!!!!!!!!!!!!!!!!!!!!!!!!
    //        FUNCTIONS
    //!!!!!!!!!!!!!!!!!!!!!!!!!!
    public:
        Texture(const char* filePath, uint channel = 0);
        ~Texture();

        void Bind();
        void Unbind();

        uint GetTextureID();
    private:

    //!!!!!!!!!!!!!!!!!!!!!!!!!!
    //        VARIABLES
    //!!!!!!!!!!!!!!!!!!!!!!!!!!
    public:
    private:
        uint TextureID;
        uint channel;
    };
}