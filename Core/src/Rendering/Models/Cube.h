#pragma once

#include "iRenderable.h"

namespace Rendering
{
    class Cube : public iRenderable
    {
        //!!!!!!!!!!!!!!!!!!!!!!!!!!
        //        FUNCTIONS
        //!!!!!!!!!!!!!!!!!!!!!!!!!!
    public:
        Cube(std::shared_ptr<Shader> shader);
        Cube(const Material& material, std::shared_ptr<Shader> shader);
        Cube(const glm::vec4& color, std::shared_ptr<Shader> shader);
        Cube(std::shared_ptr<Rendering::Texture> diffuse, std::shared_ptr<Shader> shader);
        Cube(std::shared_ptr<Rendering::Texture> diffuse, std::shared_ptr<Rendering::Texture> specular, std::shared_ptr<Shader> shader);
        Cube(std::shared_ptr<Rendering::Texture> diffuse, std::shared_ptr<Rendering::Texture> specular, 
        std::shared_ptr<Rendering::Texture> normal, std::shared_ptr<Shader> shader);
        ~Cube();

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
        
    };
}