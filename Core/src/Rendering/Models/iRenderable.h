#pragma once

#include "Utils/Type.h"
#include "Utils/pch.h"
#include "glm/glm.hpp"
#include "Rendering/Texture/Texture.h"
#include "Rendering/Shaders/Shader.h"
#include "Rendering/Buffers/VertexLayout.h"
#include "Rendering/Material/Material.h"

namespace Rendering
{    

    class iRenderable
    {
        //!!!!!!!!!!!!!!!!!!!!!!!!!!
        //        FUNCTIONS
        //!!!!!!!!!!!!!!!!!!!!!!!!!!
    public:
        virtual ~iRenderable() {}
        virtual void Draw() = 0;

    protected:
        virtual void SetupMesh(const std::vector<Rendering::VertexLayout>& vertices, 
                const std::vector<uint>& indices) = 0;

        //!!!!!!!!!!!!!!!!!!!!!!!!!!
        //        VARIABLE
        //!!!!!!!!!!!!!!!!!!!!!!!!!!
    public:
    protected:
        uint VAO;
        glm::mat4 m_Model;
        std::shared_ptr<Shader> m_Shader;
        Material m_Material;
        uint m_IndicesNumber;
        glm::vec4 m_Color;
        bool b_HasTexture;
        TextureType activeTextures;
    };
}