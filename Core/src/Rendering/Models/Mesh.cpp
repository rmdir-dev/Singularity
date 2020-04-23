#include "glad/glad.h"
#include "Mesh.h"

namespace Rendering
{
    Mesh::Mesh(const std::vector<Rendering::VertexLayout>& vertices, 
                const std::vector<uint>& indices, 
                std::shared_ptr<Rendering::Texture> textures,
                std::shared_ptr<Rendering::Shader> shader,
                Material material,
                bool hasTexture) 
        : m_Vertices(vertices), m_Indices(indices), m_Textures(textures), m_Shader(shader), m_Material(material), b_HasTexture(hasTexture)
    {
        SetupMesh();
    }

    Mesh::~Mesh() 
    {
        
    }

    void Mesh::Draw() 
    {
        m_Shader->Bind();
        if(b_HasTexture)
        {
            m_Textures->Bind();
        }        

        m_Shader->SetUniform3f("material.ambient", m_Material.ambient);
        m_Shader->SetUniform3f("material.diffuse", m_Material.diffuse);
        m_Shader->SetUniform3f("material.specular", m_Material.specular);
        m_Shader->SetUniform1f("material.shininess", m_Material.shininess);
        //m_Shader->SetUniform1f("material.opacity", m_Material.opacity);

        glBindVertexArray(VAO);

        glDrawElements(GL_TRIANGLES, m_Indices.size(), GL_UNSIGNED_INT, 0);

        glBindVertexArray(0);
        m_Shader->Unbind();
    }

    void Mesh::SetNewShader(std::shared_ptr<Rendering::Shader> shader) 
    {
        m_Shader = shader;
    }


    void Mesh::HasTexture(const bool& hasTexture) 
    {
        b_HasTexture = hasTexture;
    }

    void Mesh::SetupMesh() 
    {
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);

        //VERTEX BUFFER

        glGenBuffers(1, &VBO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, 
            sizeof(Rendering::VertexLayout) * m_Vertices.size(), 
            &m_Vertices[0], 
            GL_STATIC_DRAW);


        //INDEX BUFFER

        glGenBuffers(1, &IBO);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, 
            sizeof(uint) * m_Indices.size(), 
            &m_Indices[0], 
            GL_STATIC_DRAW);

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

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }
}

