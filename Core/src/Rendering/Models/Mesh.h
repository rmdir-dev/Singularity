#pragma once

#include "iRenderable.h"

namespace Rendering
{
    class Mesh : public iRenderable
    {
        //!!!!!!!!!!!!!!!!!!!!!!!!!!
        //        FUNCTIONS
        //!!!!!!!!!!!!!!!!!!!!!!!!!!
    public:
        Mesh(const std::vector<Rendering::VertexLayout>& vertices, 
            const std::vector<uint>& indices, 
            std::shared_ptr<Rendering::Texture> diffuse,
            std::shared_ptr<Rendering::Texture> specular,
            std::shared_ptr<Rendering::Texture> normal,
            std::shared_ptr<Rendering::Shader> shader,
            Material material);

        Mesh(const std::vector<Rendering::VertexLayout>& vertices, 
            const std::vector<uint>& indices, 
            std::shared_ptr<Rendering::Shader> shader,
            Material material);
        
        Mesh(const Mesh& mesh);

        ~Mesh();

        void Draw() override;
        void Draw(const glm::mat4& model) override;

        void SetNewShader(std::shared_ptr<Rendering::Shader> shader);

        void HasTexture(const bool& hasTexture = true);

    private:
        void SetupMesh(const std::vector<Rendering::VertexLayout>& vertices, 
                const std::vector<uint>& indices) override;

        //!!!!!!!!!!!!!!!!!!!!!!!!!!
        //        VARIABLES
        //!!!!!!!!!!!!!!!!!!!!!!!!!!
    public:
    private:
        
    };
}
