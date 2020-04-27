#include "glad/glad.h"
#include "Mesh.h"

namespace Rendering
{
    Mesh::Mesh(const std::vector<Rendering::VertexLayout>& vertices, 
                const std::vector<uint>& indices, 
                std::shared_ptr<Rendering::Texture> diffuse,
                std::shared_ptr<Rendering::Texture> specular,
                std::shared_ptr<Rendering::Texture> normal,
                std::shared_ptr<Rendering::Shader> shader,
                Material material)
        : iRenderable(shader, material, glm::vec4(1.0f), true, TEX_DIFFUSE | TEX_SPECULAR | TEX_NORMAL)
    {
        m_Diffuse = diffuse;
        m_Normal = normal;
        m_Specular = specular;
        SetupMesh(vertices, indices);
    }

    Mesh::Mesh(const std::vector<Rendering::VertexLayout>& vertices, 
                const std::vector<uint>& indices, 
                std::shared_ptr<Rendering::Shader> shader,
                Material material) 
        : iRenderable(shader, material, glm::vec4(1.0f), true, 0x00)
    {
        SetupMesh(vertices, indices);
    }

    Mesh::Mesh(const Mesh& mesh) 
    {
        //TODO
        m_Shader = mesh.m_Shader;
        b_HasMaterial = mesh.b_HasMaterial;
        m_Diffuse = mesh.m_Diffuse;
        m_Normal = mesh.m_Normal;
        m_Specular = mesh.m_Specular;
        m_IndicesNumber = mesh.m_IndicesNumber;
        VAO = mesh.VAO;
    }

    Mesh::~Mesh() 
    {
        
    }

    void Mesh::Draw() 
    {
        m_Shader->Bind();
        if(b_HasMaterial)
        {   
            if(m_ActiveTextures.types & TEX_DIFFUSE)
            {
                m_Diffuse->Bind(0);
                m_Shader->SetUniform1i("material.diffuse", 0);
            } else 
            {
                m_Shader->SetUniform3f("material.ambient", m_Material.ambient);
                m_Shader->SetUniform3f("material.diffuse", m_Material.diffuse);
            }

            if(m_ActiveTextures.types & TEX_SPECULAR)
            {
                m_Specular->Bind(1);
                m_Shader->SetUniform1i("material.specular", 1);
            } else 
            {
                m_Shader->SetUniform3f("material.specular", m_Material.specular);
            }

            if(m_ActiveTextures.types & TEX_NORMAL)
            {
                m_Normal->Bind(2);
                m_Shader->SetUniform1i("material.normal", 2);
            }
            
            m_Shader->SetUniform1f("material.opacity", m_Material.opacity); 
            m_Shader->SetUniform1f("material.shininess", m_Material.shininess);  
        }    

        glBindVertexArray(VAO);

        glDrawElements(GL_TRIANGLES, m_IndicesNumber, GL_UNSIGNED_INT, 0);

        glBindVertexArray(0);
        m_Shader->Unbind();
    }

    void Mesh::Draw(const glm::mat4& model)  
    {
        m_Shader->Bind();
        m_Shader->SetUniformMatrix4fv("model", model);
        Draw();
    }

    void Mesh::SetNewShader(std::shared_ptr<Rendering::Shader> shader) 
    {
        m_Shader = shader;
    }


    void Mesh::HasTexture(const bool& hasTexture) 
    {
        b_HasMaterial = hasTexture;
    }

    void Mesh::SetupMesh(const std::vector<Rendering::VertexLayout>& vertices, 
                const std::vector<uint>& indices) 
    {
        uint  VBO, IBO;
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);

        //VERTEX BUFFER

        glGenBuffers(1, &VBO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, 
            sizeof(Rendering::VertexLayout) * vertices.size(), 
            &vertices[0], 
            GL_STATIC_DRAW);

        //INDEX BUFFER

        glGenBuffers(1, &IBO);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, 
            sizeof(uint) * indices.size(), 
            &indices[0], 
            GL_STATIC_DRAW);

        m_IndicesNumber = indices.size();

        //VERTEX ATTRIBUTE

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 
            3, 
            GL_FLOAT, 
            GL_FALSE, 
            sizeof(Rendering::VertexLayout), 
            (void*)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Rendering::VertexLayout), 
        (void*)(offsetof(Rendering::VertexLayout, Rendering::VertexLayout::color)));
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Rendering::VertexLayout), 
        (void*)(offsetof(Rendering::VertexLayout, Rendering::VertexLayout::UVs)));
        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Rendering::VertexLayout), 
        (void*)(offsetof(Rendering::VertexLayout, Rendering::VertexLayout::normals)));
        glEnableVertexAttribArray(4);
        glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Rendering::VertexLayout), 
        (void*)(offsetof(Rendering::VertexLayout, Rendering::VertexLayout::tangent)));
        glEnableVertexAttribArray(5);
        glVertexAttribPointer(5, 3, GL_FLOAT, GL_FALSE, sizeof(Rendering::VertexLayout), 
        (void*)(offsetof(Rendering::VertexLayout, Rendering::VertexLayout::bitangent)));

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }
}

