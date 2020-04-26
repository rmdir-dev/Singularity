#pragma once

#include "Mesh.h"
#include "iRenderable.h"

namespace Rendering
{
    class Quad : public iRenderable
    {
        //!!!!!!!!!!!!!!!!!!!!!!!!!!
        //        FUNCTIONS
        //!!!!!!!!!!!!!!!!!!!!!!!!!!
    public:
        Quad(std::shared_ptr<Shader> m_Shader);
        Quad(const Material& material, std::shared_ptr<Shader> m_Shader);
        Quad(const glm::vec4& color, std::shared_ptr<Shader> m_Shader);
        Quad(std::shared_ptr<Rendering::Texture> diffuse, std::shared_ptr<Shader> m_Shader);
        Quad(std::shared_ptr<Rendering::Texture> diffuse, std::shared_ptr<Rendering::Texture> specular, std::shared_ptr<Shader> m_Shader);
        Quad(std::shared_ptr<Rendering::Texture> diffuse, std::shared_ptr<Rendering::Texture> specular, 
        std::shared_ptr<Rendering::Texture> normal, std::shared_ptr<Shader> m_Shader);
        ~Quad();

        void Draw() override;
        void Draw(const glm::mat4& model) override;

    private:
        void CreateVertices();
        void SetupMesh(const std::vector<Rendering::VertexLayout>& vertices, 
                const std::vector<uint>& indices) override;

        //!!!!!!!!!!!!!!!!!!!!!!!!!!
        //        VARIABLES
        //!!!!!!!!!!!!!!!!!!!!!!!!!!
    public:
    private:
        bool b_HasMaterial;
        
    };
}