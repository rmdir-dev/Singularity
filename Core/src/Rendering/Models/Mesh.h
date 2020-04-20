#pragma once

#include "Utils/pch.h"
#include "Rendering/Buffers/VertexLayout.h"
#include "Rendering/Texture/Texture.h"
#include "Rendering/Shaders/Shader.h"

namespace Rendering
{
    class Mesh
    {
        //!!!!!!!!!!!!!!!!!!!!!!!!!!
        //        FUNCTIONS
        //!!!!!!!!!!!!!!!!!!!!!!!!!!
    public:
        Mesh(const std::vector<Rendering::VertexLayout>& vertices, 
            const std::vector<uint>& indices, 
            std::shared_ptr<Rendering::Texture> textures,
            std::shared_ptr<Rendering::Shader> shader);
        ~Mesh();

        void Draw();

        void SetNewShader(std::shared_ptr<Rendering::Shader> shader);

    private:
        void SetupMesh();

        //!!!!!!!!!!!!!!!!!!!!!!!!!!
        //        VARIABLES
        //!!!!!!!!!!!!!!!!!!!!!!!!!!
    public:
    private:
        uint VAO,VBO, IBO;

        //TODO is this usefull? if not do not keep this in memory!
        std::vector<Rendering::VertexLayout> m_Vertices;
        std::vector<uint> m_Indices;
        std::shared_ptr<Rendering::Texture> m_Textures;
        std::shared_ptr<Rendering::Shader> m_Shader;
    };
}
