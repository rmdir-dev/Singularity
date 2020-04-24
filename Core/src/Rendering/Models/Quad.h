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
        Quad();
        Quad(const glm::vec4& color);
        Quad(const char* diffuse);
        Quad(const char* diffuse, const char* specular);
        Quad(const char* diffuse, const char* specular, const char* normal);
        ~Quad();

        void Draw() override;

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