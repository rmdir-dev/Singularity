#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"
#include "glad/glad.h"
#include "Utils/Log.h"


namespace Rendering
{
    Texture::Texture(const char* filePath, uint channel, bool sRGB)
        : channel(channel)
    {
        CORE_INFO("Loading texture: ", filePath);
        glGenTextures(1, &TextureID);
        glBindTexture(GL_TEXTURE_2D, TextureID);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        int width, height, nrChannels;
        byte* data = stbi_load(filePath, &width, &height, &nrChannels, 0);

        int internalFormat = nrChannels == 4 ? GL_RGBA : GL_RGB;
		uint format = nrChannels == 4 ? GL_RGBA : GL_RGB;
        if(sRGB)
        {
            int internalFormat = GL_SRGB_ALPHA;
		    uint format = GL_SRGB_ALPHA;
        }
        

        if(data)
        {
            if(nrChannels)
            glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        } else 
        {
            CORE_INFO("Fail to load texture: ", filePath);

            return;
        }
        stbi_image_free(data);
        CORE_INFO("Texture loaded.");
    }

    Texture::~Texture() 
    {
        
    }

    void Texture::Bind() 
    {
        glActiveTexture(GL_TEXTURE0 + channel);
        glBindTexture(GL_TEXTURE_2D, TextureID);
    }

    void Texture::Unbind() 
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    uint Texture::GetTextureID() 
    {
        return TextureID;
    }
}

