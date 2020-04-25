#pragma once

#include "Utils/Type.h"
#include "Utils/pch.h"
#include "glm/glm.hpp"
#include "Rendering/Texture/Texture.h"
#include "Rendering/Shaders/Shader.h"
#include "Rendering/Buffers/VertexLayout.h"
#include "Rendering/Material/Material.h"
#include "Managers/ShaderManager.h"
#include "Managers/TextureManager.h"

namespace Rendering
{    

    class iRenderable
    {
        //!!!!!!!!!!!!!!!!!!!!!!!!!!
        //        FUNCTIONS
        //!!!!!!!!!!!!!!!!!!!!!!!!!!
    public:
        iRenderable() {}
        iRenderable(Manager::TextureManager& texMan, Manager::ShaderManager& shadMan) 
            : m_TexMan(std::make_unique<Manager::TextureManager>(texMan)), m_ShadMan(std::make_unique<Manager::ShaderManager>(shadMan))
        {}
        virtual ~iRenderable() {}
        virtual void Draw() = 0;
        virtual void Draw(const glm::mat4& model) = 0;

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
        std::unique_ptr<Manager::TextureManager> m_TexMan;
        std::unique_ptr<Manager::ShaderManager> m_ShadMan;
    };
}