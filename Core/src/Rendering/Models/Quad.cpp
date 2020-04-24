#include "Quad.h"
#include "glad/glad.h"

namespace Rendering
{
    Quad::Quad() 
    {
        m_Color = glm::vec4(1.0f);
        b_HasTexture = false;
        activeTextures.types = 0x00;
        CreateVertices();
    }

    Quad::Quad(const char* diffuse, const char* specular, const char* normal) 
    {
        b_HasTexture = true;
        activeTextures.types = DIFFUSE | SPECULAR | NORMAL;
        CreateVertices();
    }

    Quad::Quad(const char* diffuse, const char* specular) 
    {
        b_HasTexture = true;
        activeTextures.types = DIFFUSE | SPECULAR;
        CreateVertices();
    }

    Quad::Quad(const char* diffuse) 
    {
        b_HasTexture = true;
        activeTextures.types = DIFFUSE;
        CreateVertices();
    }

    Quad::Quad(const glm::vec4& color) 
    {
        m_Color = color;
        b_HasTexture = false;
        activeTextures.types = 0x00;
        CreateVertices();
    }

    Quad::~Quad() 
    {
        
    }

    void Quad::Draw() 
    {
        m_Shader->Bind();
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);
        m_Shader->Unbind();
    }

    void Quad::CreateVertices() 
    {
        std::vector<Rendering::VertexLayout> vertices;
        vertices.resize(6);

        //Vertex 1
        vertices[0].position = glm::vec3(-1.0f,  1.0f, 0.0f);
        vertices[0].UVs = glm::vec2(0.0f, 1.0f);
        vertices[0].normals = glm::vec3(0.0f, 0.0f, 1.0f);
        vertices[0].color = m_Color;
        //Vertex 2
        vertices[1].position = glm::vec3(-1.0f, -1.0f, 0.0f);
        vertices[1].UVs = glm::vec2(0.0f, 0.0f);
        vertices[1].normals = glm::vec3(0.0f, 0.0f, 1.0f);
        vertices[1].color = m_Color;
        //Vertex 3
        vertices[2].position = glm::vec3( 1.0f, -1.0f, 0.0f);
        vertices[2].UVs = glm::vec2(1.0f, 0.0f);
        vertices[2].normals = glm::vec3(0.0f, 0.0f, 1.0f);
        vertices[2].color = m_Color;

        //Vertex 4
        vertices[3].position = glm::vec3(-1.0f,  1.0f, 0.0f);
        vertices[3].UVs = glm::vec2(0.0f, 1.0f);
        vertices[3].normals = glm::vec3(0.0f, 0.0f, 1.0f);
        vertices[3].color = m_Color;
        //Vertex 5
        vertices[4].position = glm::vec3( 1.0f, -1.0f, 0.0f);
        vertices[4].UVs = glm::vec2(1.0f, 0.0f);
        vertices[4].normals = glm::vec3(0.0f, 0.0f, 1.0f);
        vertices[4].color = m_Color;
        //Vertex 6
        vertices[5].position = glm::vec3( 1.0f,  1.0f, 0.0f);
        vertices[5].UVs = glm::vec2(1.0f, 1.0f);
        vertices[5].normals = glm::vec3(0.0f, 0.0f, 1.0f);
        vertices[5].color = m_Color;

        //TRIANGLE 1
        glm::vec3 e1 = vertices[1].position - vertices[0].position;
        glm::vec3 e2 = vertices[2].position - vertices[0].position;
        glm::vec2 d1 = vertices[1].UVs - vertices[0].UVs;
        glm::vec2 d2 = vertices[2].UVs - vertices[0].UVs;

        float f = 1.0f / (d1.x * d2.y - d2.x * d1.y);

        glm::vec3 tan, bitan;

        tan.x = f * (d2.y * e1.x - d1.y * e2.x);
        tan.y = f * (d2.y * e1.y - d1.y * e2.y);
        tan.z = f * (d2.y * e1.z - d1.y * e2.z);
        tan = glm::normalize(tan);

        bitan.x = f * (-d2.y * e1.x + d1.y * e2.x);
        bitan.y = f * (-d2.y * e1.y + d1.y * e2.y);
        bitan.z = f * (-d2.y * e1.z + d1.y * e2.z);
        bitan = glm::normalize(bitan);

        vertices[0].tangent = tan;
        vertices[0].bitangent = bitan;
        vertices[1].tangent = tan;
        vertices[1].bitangent = bitan;
        vertices[2].tangent = tan;
        vertices[2].bitangent = bitan;

        //TRIANGLE 2
        e1 = vertices[4].position - vertices[3].position;
        e2 = vertices[5].position - vertices[3].position;
        d1 = vertices[4].UVs - vertices[3].UVs;
        d2 = vertices[5].UVs - vertices[3].UVs;

        f = 1.0f / (d1.x * d2.y - d2.x * d1.y);

        tan.x = f * (d2.y * e1.x - d1.y * e2.x);
        tan.y = f * (d2.y * e1.y - d1.y * e2.y);
        tan.z = f * (d2.y * e1.z - d1.y * e2.z);
        tan = glm::normalize(tan);

        bitan.x = f * (-d2.y * e1.x + d1.y * e2.x);
        bitan.y = f * (-d2.y * e1.y + d1.y * e2.y);
        bitan.z = f * (-d2.y * e1.z + d1.y * e2.z);
        bitan = glm::normalize(bitan);

        vertices[3].tangent = tan;
        vertices[3].bitangent = bitan;
        vertices[4].tangent = tan;
        vertices[4].bitangent = bitan;
        vertices[5].tangent = tan;
        vertices[5].bitangent = bitan;

        std::vector<uint> indices;
        indices.resize(6);
        indices[0] = 0;
        indices[1] = 1;
        indices[2] = 2;
        indices[3] = 0;
        indices[4] = 2;
        indices[5] = 3;

        SetupMesh(vertices, indices);
    }

    void Quad::SetupMesh(const std::vector<Rendering::VertexLayout>& vertices, 
                const std::vector<uint>& indices) 
    {
        uint  VBO;
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
        //NOT ACTIVE !!! => For normals

        //VERTEX ATTRIBUTE

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0,                //location index
            3,                                  //Number of variables
            GL_FLOAT,                           //Type of variable
            GL_FALSE,                           //Normalize
            sizeof(Rendering::VertexLayout),    //Size of the buffer 
            (void*)0);                          //offset (here 0)
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