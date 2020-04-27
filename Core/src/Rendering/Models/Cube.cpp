#include "Cube.h"
#include "glad/glad.h"

namespace Rendering
{
    Cube::Cube(std::shared_ptr<Shader> shader)
        : iRenderable(shader, BaseMaterial, glm::vec4(1.0), false, 0x00)
    {
        CreateVertices();
    }

    Cube::Cube(std::shared_ptr<Rendering::Texture> diffuse, std::shared_ptr<Rendering::Texture> specular, 
            std::shared_ptr<Rendering::Texture> normal, std::shared_ptr<Shader> shader)
        : iRenderable(shader, BaseMaterial, glm::vec4(1.0), true, TEX_DIFFUSE | TEX_SPECULAR | TEX_NORMAL)
    {
        m_Diffuse = diffuse;
        m_Specular = specular;
        m_Normal = normal;
        CreateVertices();
    }

    Cube::Cube(std::shared_ptr<Rendering::Texture> diffuse, std::shared_ptr<Rendering::Texture> specular, std::shared_ptr<Shader> shader) 
        : iRenderable(shader, BaseMaterial, glm::vec4(1.0), true, TEX_DIFFUSE | TEX_SPECULAR)
    {
        m_Diffuse = diffuse;
        m_Specular = specular;
        CreateVertices();
    }

    Cube::Cube(std::shared_ptr<Rendering::Texture> diffuse, std::shared_ptr<Shader> shader)
        : iRenderable(shader, BaseMaterial, glm::vec4(1.0), true, TEX_DIFFUSE)
    {
        m_Diffuse = diffuse;
        CreateVertices();
    }

    Cube::Cube(const glm::vec4& color, std::shared_ptr<Shader> shader)
        : iRenderable(shader, BaseMaterial, color, true, 0x00)
    {
        CreateVertices();
    }

    Cube::Cube(const Material& material, std::shared_ptr<Shader> shader)
        : iRenderable(shader, material, glm::vec4(1.0), true, 0x00)
    {
        CreateVertices();
    }

    Cube::~Cube() 
    {
        
    }


    void Cube::Draw() 
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
            
            //m_Shader->SetUniform1f("material.opacity", m_Material.opacity); 
            m_Shader->SetUniform1f("material.shininess", m_Material.shininess);  
        }

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);
        m_Shader->Unbind();
    }

    void Cube::Draw(const glm::mat4& model) 
    {
        m_Shader->Bind();
        m_Shader->SetUniformMatrix4fv("model", model);
        Draw();
    }

    void Cube::CreateVertices() 
    {
        std::vector<Rendering::VertexLayout> vertices;
        vertices.resize(36);

        //---------------------------------------------------------
        //FRONT FACE
        //---------------------------------------------------------
        //Vertex 1
        vertices[0].position = glm::vec3(-1.0f,  1.0f, 1.0f);
        vertices[0].UVs = glm::vec2(0.0f, 1.0f);
        vertices[0].normals = glm::vec3(0.0f, 0.0f, 1.0f);
        vertices[0].color = m_Color;
        //Vertex 2
        vertices[1].position = glm::vec3(-1.0f, -1.0f, 1.0f);
        vertices[1].UVs = glm::vec2(0.0f, 0.0f);
        vertices[1].normals = glm::vec3(0.0f, 0.0f, 1.0f);
        vertices[1].color = m_Color;
        //Vertex 3
        vertices[2].position = glm::vec3( 1.0f, -1.0f, 1.0f);
        vertices[2].UVs = glm::vec2(1.0f, 0.0f);
        vertices[2].normals = glm::vec3(0.0f, 0.0f, 1.0f);
        vertices[2].color = m_Color;

        //Vertex 4
        vertices[3].position = glm::vec3(-1.0f,  1.0f, 1.0f);
        vertices[3].UVs = glm::vec2(0.0f, 1.0f);
        vertices[3].normals = glm::vec3(0.0f, 0.0f, 1.0f);
        vertices[3].color = m_Color;
        //Vertex 5
        vertices[4].position = glm::vec3( 1.0f, -1.0f, 1.0f);
        vertices[4].UVs = glm::vec2(1.0f, 0.0f);
        vertices[4].normals = glm::vec3(0.0f, 0.0f, 1.0f);
        vertices[4].color = m_Color;
        //Vertex 6
        vertices[5].position = glm::vec3( 1.0f,  1.0f, 1.0f);
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

        //---------------------------------------------------------
        //BACK FACE
        //---------------------------------------------------------
        //Vertex 1
        vertices[6].position = glm::vec3(-1.0f,  1.0f, -1.0f);
        vertices[6].UVs = glm::vec2(0.0f, 1.0f);
        vertices[6].normals = glm::vec3(0.0f, 0.0f, -1.0f);
        vertices[6].color = m_Color;
        //Vertex 2
        vertices[7].position = glm::vec3(-1.0f, -1.0f, -1.0f);
        vertices[7].UVs = glm::vec2(0.0f, 0.0f);
        vertices[7].normals = glm::vec3(0.0f, 0.0f, -1.0f);
        vertices[7].color = m_Color;
        //Vertex 3
        vertices[8].position = glm::vec3( 1.0f, -1.0f, -1.0f);
        vertices[8].UVs = glm::vec2(1.0f, 0.0f);
        vertices[8].normals = glm::vec3(0.0f, 0.0f, -1.0f);
        vertices[8].color = m_Color;

        //Vertex 4
        vertices[9].position = glm::vec3(-1.0f,  1.0f, -1.0f);
        vertices[9].UVs = glm::vec2(0.0f, 1.0f);
        vertices[9].normals = glm::vec3(0.0f, 0.0f, -1.0f);
        vertices[9].color = m_Color;
        //Vertex 5
        vertices[10].position = glm::vec3( 1.0f, -1.0f, -1.0f);
        vertices[10].UVs = glm::vec2(1.0f, 0.0f);
        vertices[10].normals = glm::vec3(0.0f, 0.0f, -1.0f);
        vertices[10].color = m_Color;
        //Vertex 6
        vertices[11].position = glm::vec3( 1.0f,  1.0f, -1.0f);
        vertices[11].UVs = glm::vec2(1.0f, 1.0f);
        vertices[11].normals = glm::vec3(0.0f, 0.0f, -1.0f);
        vertices[11].color = m_Color;

        //TRIANGLE 1
        e1 = vertices[7].position - vertices[6].position;
        e2 = vertices[8].position - vertices[6].position;
        d1 = vertices[7].UVs - vertices[6].UVs;
        d2 = vertices[8].UVs - vertices[6].UVs;

        f = 1.0f / (d1.x * d2.y - d2.x * d1.y);

        tan.x = f * (d2.y * e1.x - d1.y * e2.x);
        tan.y = f * (d2.y * e1.y - d1.y * e2.y);
        tan.z = f * (d2.y * e1.z - d1.y * e2.z);
        tan = glm::normalize(tan);

        bitan.x = f * (-d2.y * e1.x + d1.y * e2.x);
        bitan.y = f * (-d2.y * e1.y + d1.y * e2.y);
        bitan.z = f * (-d2.y * e1.z + d1.y * e2.z);
        bitan = glm::normalize(bitan);

        vertices[6].tangent = tan;
        vertices[6].bitangent = bitan;
        vertices[7].tangent = tan;
        vertices[7].bitangent = bitan;
        vertices[8].tangent = tan;
        vertices[8].bitangent = bitan;

        //TRIANGLE 2
        e1 = vertices[10].position - vertices[9].position;
        e2 = vertices[11].position - vertices[9].position;
        d1 = vertices[10].UVs - vertices[9].UVs;
        d2 = vertices[11].UVs - vertices[9].UVs;

        f = 1.0f / (d1.x * d2.y - d2.x * d1.y);

        tan.x = f * (d2.y * e1.x - d1.y * e2.x);
        tan.y = f * (d2.y * e1.y - d1.y * e2.y);
        tan.z = f * (d2.y * e1.z - d1.y * e2.z);
        tan = glm::normalize(tan);

        bitan.x = f * (-d2.y * e1.x + d1.y * e2.x);
        bitan.y = f * (-d2.y * e1.y + d1.y * e2.y);
        bitan.z = f * (-d2.y * e1.z + d1.y * e2.z);
        bitan = glm::normalize(bitan);

        vertices[9].tangent = tan;
        vertices[9].bitangent = bitan;
        vertices[10].tangent = tan;
        vertices[10].bitangent = bitan;
        vertices[11].tangent = tan;
        vertices[11].bitangent = bitan;

        //---------------------------------------------------------
        //TOP FACE
        //---------------------------------------------------------
        //Vertex 1
        vertices[12].position = glm::vec3( 1.0f,  1.0f, 1.0f);
        vertices[12].UVs = glm::vec2(0.0f, 0.0f);
        vertices[12].normals = glm::vec3(0.0f, 1.0f, 0.0f);
        vertices[12].color = m_Color;
        //Vertex 2
        vertices[13].position = glm::vec3(-1.0f,  1.0f, 1.0f);
        vertices[13].UVs = glm::vec2(1.0f, 0.0f);
        vertices[13].normals = glm::vec3(0.0f, 1.0f, 0.0f);
        vertices[13].color = m_Color;
        //Vertex 3
        vertices[14].position = glm::vec3(-1.0f, 1.0f, -1.0f);
        vertices[14].UVs = glm::vec2(1.0f, 1.0f);
        vertices[14].normals = glm::vec3(0.0f, 1.0f, 0.0f);
        vertices[14].color = m_Color;

        //Vertex 4
        vertices[15].position = glm::vec3(1.0f,  1.0f, 1.0f);
        vertices[15].UVs = glm::vec2(0.0f, 0.0f);
        vertices[15].normals = glm::vec3(0.0f, 1.0f, 0.0f);
        vertices[15].color = m_Color;
        //Vertex 5
        vertices[16].position = glm::vec3( 1.0f, 1.0f, -1.0f);
        vertices[16].UVs = glm::vec2(0.0f, 1.0f);
        vertices[16].normals = glm::vec3(0.0f, 1.0f, 0.0f);
        vertices[16].color = m_Color;
        //Vertex 6
        vertices[17].position = glm::vec3(-1.0f,  1.0f, -1.0f);
        vertices[17].UVs = glm::vec2(1.0f, 1.0f);
        vertices[17].normals = glm::vec3(0.0f, 1.0f, 0.0f);
        vertices[17].color = m_Color;

        //TRIANGLE 1
        e1 = vertices[13].position - vertices[12].position;
        e2 = vertices[14].position - vertices[12].position;
        d1 = vertices[13].UVs - vertices[12].UVs;
        d2 = vertices[14].UVs - vertices[12].UVs;

        f = 1.0f / (d1.x * d2.y - d2.x * d1.y);

        tan.x = f * (d2.y * e1.x - d1.y * e2.x);
        tan.y = f * (d2.y * e1.y - d1.y * e2.y);
        tan.z = f * (d2.y * e1.z - d1.y * e2.z);
        tan = glm::normalize(tan);

        bitan.x = f * (-d2.y * e1.x + d1.y * e2.x);
        bitan.y = f * (-d2.y * e1.y + d1.y * e2.y);
        bitan.z = f * (-d2.y * e1.z + d1.y * e2.z);
        bitan = glm::normalize(bitan);

        vertices[12].tangent = tan;
        vertices[12].bitangent = bitan;
        vertices[13].tangent = tan;
        vertices[13].bitangent = bitan;
        vertices[14].tangent = tan;
        vertices[14].bitangent = bitan;

        //TRIANGLE 2
        e1 = vertices[16].position - vertices[15].position;
        e2 = vertices[17].position - vertices[15].position;
        d1 = vertices[16].UVs - vertices[15].UVs;
        d2 = vertices[17].UVs - vertices[15].UVs;

        f = 1.0f / (d1.x * d2.y - d2.x * d1.y);

        tan.x = f * (d2.y * e1.x - d1.y * e2.x);
        tan.y = f * (d2.y * e1.y - d1.y * e2.y);
        tan.z = f * (d2.y * e1.z - d1.y * e2.z);
        tan = glm::normalize(tan);

        bitan.x = f * (-d2.y * e1.x + d1.y * e2.x);
        bitan.y = f * (-d2.y * e1.y + d1.y * e2.y);
        bitan.z = f * (-d2.y * e1.z + d1.y * e2.z);
        bitan = glm::normalize(bitan);

        vertices[15].tangent = tan;
        vertices[15].bitangent = bitan;
        vertices[16].tangent = tan;
        vertices[16].bitangent = bitan;
        vertices[17].tangent = tan;
        vertices[17].bitangent = bitan;

        //---------------------------------------------------------
        //BOTTOM FACE
        //---------------------------------------------------------
        //Vertex 1
        vertices[18].position = glm::vec3( 1.0f,  -1.0f, 1.0f);
        vertices[18].UVs = glm::vec2(0.0f, 0.0f);
        vertices[18].normals = glm::vec3(0.0f, -1.0f, 0.0f);
        vertices[18].color = m_Color;
        //Vertex 2
        vertices[19].position = glm::vec3(-1.0f,  -1.0f, 1.0f);
        vertices[19].UVs = glm::vec2(1.0f, 0.0f);
        vertices[19].normals = glm::vec3(0.0f, -1.0f, 0.0f);
        vertices[19].color = m_Color;
        //Vertex 3
        vertices[20].position = glm::vec3(-1.0f, -1.0f, -1.0f);
        vertices[20].UVs = glm::vec2(1.0f, 1.0f);
        vertices[20].normals = glm::vec3(0.0f, -1.0f, 0.0f);
        vertices[20].color = m_Color;

        //Vertex 4
        vertices[21].position = glm::vec3(1.0f,  -1.0f, 1.0f);
        vertices[21].UVs = glm::vec2(0.0f, 0.0f);
        vertices[21].normals = glm::vec3(0.0f, -1.0f, 0.0f);
        vertices[21].color = m_Color;
        //Vertex 5
        vertices[22].position = glm::vec3( 1.0f, -1.0f, -1.0f);
        vertices[22].UVs = glm::vec2(0.0f, 1.0f);
        vertices[22].normals = glm::vec3(0.0f, -1.0f, 0.0f);
        vertices[22].color = m_Color;
        //Vertex 6
        vertices[23].position = glm::vec3(-1.0f, -1.0f, -1.0f);
        vertices[23].UVs = glm::vec2(1.0f, 1.0f);
        vertices[23].normals = glm::vec3(0.0f, -1.0f, 0.0f);
        vertices[23].color = m_Color;

        //TRIANGLE 1
        e1 = vertices[19].position - vertices[18].position;
        e2 = vertices[20].position - vertices[18].position;
        d1 = vertices[19].UVs - vertices[18].UVs;
        d2 = vertices[20].UVs - vertices[18].UVs;

        f = 1.0f / (d1.x * d2.y - d2.x * d1.y);

        tan.x = f * (d2.y * e1.x - d1.y * e2.x);
        tan.y = f * (d2.y * e1.y - d1.y * e2.y);
        tan.z = f * (d2.y * e1.z - d1.y * e2.z);
        tan = glm::normalize(tan);

        bitan.x = f * (-d2.y * e1.x + d1.y * e2.x);
        bitan.y = f * (-d2.y * e1.y + d1.y * e2.y);
        bitan.z = f * (-d2.y * e1.z + d1.y * e2.z);
        bitan = glm::normalize(bitan);

        vertices[18].tangent = tan;
        vertices[18].bitangent = bitan;
        vertices[19].tangent = tan;
        vertices[19].bitangent = bitan;
        vertices[20].tangent = tan;
        vertices[20].bitangent = bitan;

        //TRIANGLE 2
        e1 = vertices[22].position - vertices[21].position;
        e2 = vertices[23].position - vertices[21].position;
        d1 = vertices[22].UVs - vertices[21].UVs;
        d2 = vertices[23].UVs - vertices[21].UVs;

        f = 1.0f / (d1.x * d2.y - d2.x * d1.y);

        tan.x = f * (d2.y * e1.x - d1.y * e2.x);
        tan.y = f * (d2.y * e1.y - d1.y * e2.y);
        tan.z = f * (d2.y * e1.z - d1.y * e2.z);
        tan = glm::normalize(tan);

        bitan.x = f * (-d2.y * e1.x + d1.y * e2.x);
        bitan.y = f * (-d2.y * e1.y + d1.y * e2.y);
        bitan.z = f * (-d2.y * e1.z + d1.y * e2.z);
        bitan = glm::normalize(bitan);

        vertices[21].tangent = tan;
        vertices[21].bitangent = bitan;
        vertices[22].tangent = tan;
        vertices[22].bitangent = bitan;
        vertices[23].tangent = tan;
        vertices[23].bitangent = bitan;

        //---------------------------------------------------------
        //RIGHT FACE
        //---------------------------------------------------------
        //Vertex 1
        vertices[24].position = glm::vec3( 1.0f,  -1.0f, 1.0f);
        vertices[24].UVs = glm::vec2(0.0f, 0.0f);
        vertices[24].normals = glm::vec3(1.0f, 0.0f, 0.0f);
        vertices[24].color = m_Color;
        //Vertex 2
        vertices[25].position = glm::vec3(1.0f,  1.0f, 1.0f);
        vertices[25].UVs = glm::vec2(1.0f, 0.0f);
        vertices[25].normals = glm::vec3(1.0f, 0.0f, 0.0f);
        vertices[25].color = m_Color;
        //Vertex 3
        vertices[26].position = glm::vec3( 1.0f, 1.0f, -1.0f);
        vertices[26].UVs = glm::vec2(1.0f, 1.0f);
        vertices[26].normals = glm::vec3(1.0f, 0.0f, 0.0f);
        vertices[26].color = m_Color;

        //Vertex 4
        vertices[27].position = glm::vec3(1.0f,  -1.0f, 1.0f);
        vertices[27].UVs = glm::vec2(0.0f, 0.0f);
        vertices[27].normals = glm::vec3(1.0f, 0.0f, 0.0f);
        vertices[27].color = m_Color;
        //Vertex 5
        vertices[28].position = glm::vec3( 1.0f, -1.0f, -1.0f);
        vertices[28].UVs = glm::vec2(0.0f, 1.0f);
        vertices[28].normals = glm::vec3(1.0f, 0.0f, 0.0f);
        vertices[28].color = m_Color;
        //Vertex 6
        vertices[29].position = glm::vec3(1.0f, 1.0f, -1.0f);
        vertices[29].UVs = glm::vec2(1.0f, 1.0f);
        vertices[29].normals = glm::vec3(1.0f, 0.0f, 0.0f);
        vertices[29].color = m_Color;

        //TRIANGLE 1
        e1 = vertices[25].position - vertices[24].position;
        e2 = vertices[26].position - vertices[24].position;
        d1 = vertices[25].UVs - vertices[24].UVs;
        d2 = vertices[26].UVs - vertices[24].UVs;

        f = 1.0f / (d1.x * d2.y - d2.x * d1.y);

        tan.x = f * (d2.y * e1.x - d1.y * e2.x);
        tan.y = f * (d2.y * e1.y - d1.y * e2.y);
        tan.z = f * (d2.y * e1.z - d1.y * e2.z);
        tan = glm::normalize(tan);

        bitan.x = f * (-d2.y * e1.x + d1.y * e2.x);
        bitan.y = f * (-d2.y * e1.y + d1.y * e2.y);
        bitan.z = f * (-d2.y * e1.z + d1.y * e2.z);
        bitan = glm::normalize(bitan);

        vertices[24].tangent = tan;
        vertices[24].bitangent = bitan;
        vertices[25].tangent = tan;
        vertices[25].bitangent = bitan;
        vertices[26].tangent = tan;
        vertices[26].bitangent = bitan;

        //TRIANGLE 2
        e1 = vertices[28].position - vertices[27].position;
        e2 = vertices[29].position - vertices[27].position;
        d1 = vertices[28].UVs - vertices[27].UVs;
        d2 = vertices[29].UVs - vertices[27].UVs;

        f = 1.0f / (d1.x * d2.y - d2.x * d1.y);

        tan.x = f * (d2.y * e1.x - d1.y * e2.x);
        tan.y = f * (d2.y * e1.y - d1.y * e2.y);
        tan.z = f * (d2.y * e1.z - d1.y * e2.z);
        tan = glm::normalize(tan);

        bitan.x = f * (-d2.y * e1.x + d1.y * e2.x);
        bitan.y = f * (-d2.y * e1.y + d1.y * e2.y);
        bitan.z = f * (-d2.y * e1.z + d1.y * e2.z);
        bitan = glm::normalize(bitan);

        vertices[27].tangent = tan;
        vertices[27].bitangent = bitan;
        vertices[28].tangent = tan;
        vertices[28].bitangent = bitan;
        vertices[29].tangent = tan;
        vertices[29].bitangent = bitan;

        //---------------------------------------------------------
        //LEFT FACE
        //---------------------------------------------------------
        //Vertex 1
        vertices[30].position = glm::vec3(-1.0f,  -1.0f, 1.0f);
        vertices[30].UVs = glm::vec2(0.0f, 0.0f);
        vertices[30].normals = glm::vec3(-1.0f, 0.0f, 0.0f);
        vertices[30].color = m_Color;
        //Vertex 2
        vertices[31].position = glm::vec3(-1.0f,  1.0f, 1.0f);
        vertices[31].UVs = glm::vec2(1.0f, 0.0f);
        vertices[31].normals = glm::vec3(-1.0f, 0.0f, 0.0f);
        vertices[31].color = m_Color;
        //Vertex 3
        vertices[32].position = glm::vec3(-1.0f, 1.0f, -1.0f);
        vertices[32].UVs = glm::vec2(1.0f, 1.0f);
        vertices[32].normals = glm::vec3(-1.0f, 0.0f, 0.0f);
        vertices[32].color = m_Color;

        //Vertex 4
        vertices[33].position = glm::vec3(-1.0f,  -1.0f, 1.0f);
        vertices[33].UVs = glm::vec2(0.0f, 0.0f);
        vertices[33].normals = glm::vec3(-1.0f, 0.0f, 0.0f);
        vertices[33].color = m_Color;
        //Vertex 5
        vertices[34].position = glm::vec3(-1.0f, -1.0f, -1.0f);
        vertices[34].UVs = glm::vec2(0.0f, 1.0f);
        vertices[34].normals = glm::vec3(-1.0f, 0.0f, 0.0f);
        vertices[34].color = m_Color;
        //Vertex 6
        vertices[35].position = glm::vec3(-1.0f, 1.0f, -1.0f);
        vertices[35].UVs = glm::vec2(1.0f, 1.0f);
        vertices[35].normals = glm::vec3(-1.0f, 0.0f, 0.0f);
        vertices[35].color = m_Color;

        //TRIANGLE 1
        e1 = vertices[31].position - vertices[30].position;
        e2 = vertices[32].position - vertices[30].position;
        d1 = vertices[31].UVs - vertices[30].UVs;
        d2 = vertices[32].UVs - vertices[30].UVs;

        f = 1.0f / (d1.x * d2.y - d2.x * d1.y);

        tan.x = f * (d2.y * e1.x - d1.y * e2.x);
        tan.y = f * (d2.y * e1.y - d1.y * e2.y);
        tan.z = f * (d2.y * e1.z - d1.y * e2.z);
        tan = glm::normalize(tan);

        bitan.x = f * (-d2.y * e1.x + d1.y * e2.x);
        bitan.y = f * (-d2.y * e1.y + d1.y * e2.y);
        bitan.z = f * (-d2.y * e1.z + d1.y * e2.z);
        bitan = glm::normalize(bitan);

        vertices[30].tangent = tan;
        vertices[30].bitangent = bitan;
        vertices[31].tangent = tan;
        vertices[31].bitangent = bitan;
        vertices[32].tangent = tan;
        vertices[32].bitangent = bitan;

        //TRIANGLE 2
        e1 = vertices[34].position - vertices[33].position;
        e2 = vertices[35].position - vertices[33].position;
        d1 = vertices[34].UVs - vertices[33].UVs;
        d2 = vertices[35].UVs - vertices[33].UVs;

        f = 1.0f / (d1.x * d2.y - d2.x * d1.y);

        tan.x = f * (d2.y * e1.x - d1.y * e2.x);
        tan.y = f * (d2.y * e1.y - d1.y * e2.y);
        tan.z = f * (d2.y * e1.z - d1.y * e2.z);
        tan = glm::normalize(tan);

        bitan.x = f * (-d2.y * e1.x + d1.y * e2.x);
        bitan.y = f * (-d2.y * e1.y + d1.y * e2.y);
        bitan.z = f * (-d2.y * e1.z + d1.y * e2.z);
        bitan = glm::normalize(bitan);

        vertices[33].tangent = tan;
        vertices[33].bitangent = bitan;
        vertices[34].tangent = tan;
        vertices[34].bitangent = bitan;
        vertices[35].tangent = tan;
        vertices[35].bitangent = bitan;

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

    void Cube::SetupMesh(const std::vector<Rendering::VertexLayout>& vertices, 
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