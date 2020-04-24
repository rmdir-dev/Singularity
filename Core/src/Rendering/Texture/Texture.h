#pragma once

#include "Utils/Type.h"

#define DIFFUSE     0x1; // 0000 0001
#define SPECULAR    0x2; // 0000 0010
#define NORMAL      0x4; // 0000 0100


namespace Rendering
{
    union TextureType
    {
        byte types;
        struct
        {
            byte diffuse    : 1;  // 0x1
            byte specular   : 1;  // 0x2
            byte normal     : 1;  // 0x4
        } texture_types;
    };

    class Texture
    {
    //!!!!!!!!!!!!!!!!!!!!!!!!!!
    //        FUNCTIONS
    //!!!!!!!!!!!!!!!!!!!!!!!!!!
    public:
        Texture(const char* filePath, uint channel = 0, bool sRGB = false);
        ~Texture();

        void Bind();
        void Unbind();

        uint GetTextureID();

    private:

    //!!!!!!!!!!!!!!!!!!!!!!!!!!
    //        VARIABLES
    //!!!!!!!!!!!!!!!!!!!!!!!!!!
    public:
        TextureType types;

    private:
        uint TextureID;
        uint channel;

    };
}