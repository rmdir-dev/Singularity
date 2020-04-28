#include "glad/glad.h"
#include "TestLayer.h"
#include "Utils/pch.h"
#include <iostream>
#include "glm/gtc/matrix_transform.hpp"
#include "Utils/Log.h"
#include "Utils/KeyCodes.h"

namespace Layer
{
    TestLayer::TestLayer() 
    {
        m_ShaderManager = std::make_shared<Manager::ShaderManager>();
        m_ObjMan = Manager::ObjectManager(m_ShaderManager);
        cube.shader = m_ShaderManager->LoadShader("Assets/LightTesting/BasicTextureDS_Point");
        cube2.shader = m_ShaderManager->LoadShader("Assets/LightTesting/BasicTextureDS_Point");
        m_LightShader = std::make_shared<Rendering::Shader>("Assets/BoxLightShader");
        m_PLight = std::make_shared<Rendering::PointLight>(glm::vec3(2.0f));
        m_PLight->SetShader(m_LightShader);
        m_PLight->SetLightSettings(ACTIVATE_LIGHT | VISIBLE_LIGHT_BOX);
        m_PLight->m_Color = glm::vec3(1.0, 1.0, 1.0);
        m_PLight->m_Ambiant = glm::vec3(0.2f)    * m_PLight->m_Color;
        m_PLight->m_Diffuse = glm::vec3(0.5f)    * m_PLight->m_Color;
        m_PLight->m_Specular = glm::vec3(1.0f)   * m_PLight->m_Color;

        //CAMERA SETUP
        cameraPos       = glm::vec3(0.0f, 0.15f,  5.0f);
        cameraFront     = glm::vec3(0.0f, 0.0f, -1.0f);
        cameraUp        = glm::vec3(0.0f, 1.0f,  0.0f);
        cameraSpeed = 0.05f;
        sensitivity = 0.1f;
        m_Yaw = -84.0f;
        m_Pitch = 0.0f;

        mvt.input = 0x00;
        sinMov = 0.0f;

        UpdateView(); 

        cube.shader->Bind();       

        cube.model = glm::mat4(1.0f);
        cube2.model = glm::mat4(1.0f);
        cube2.model = glm::translate(cube2.model, glm::vec3(-4.0f, 0.0f, 0.0f));
        //model = glm::translate(model, glm::vec3(0.0f, -1.4f, 0.0f)); // translate it down so it's at the center of the scene
        //model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));	// it's a bit too big for our scene, so scale it down      
        projection = glm::perspective(glm::radians(45.0f), 1280.0f / 720.0f, 0.1f, 250.0f);

        cube.shader->SetUniformMatrix4fv("model", cube.model);
        cube.shader->SetUniformMatrix4fv("projection", projection);

        cube.shader->Unbind();

        m_LightShader->Bind();
        m_LightShader->SetUniformMatrix4fv("projection", projection);
        m_LightShader->SetUniform3f("inColor", glm::vec3(1.0f));
        m_LightShader->Unbind();       

        rotation = 0.0f;
    }


    TestLayer::~TestLayer() 
    {
        
    }

    void TestLayer::OnStart() 
    {
        //m_Mesh = std::make_unique<Rendering::Mesh>(m_Vertices, m_Indices, m_Texture, cube.shader);
        //m_Model = std::make_unique<Rendering::Model>("Assets/Nano/nanosuit.obj", cube.shader);
        //m_ObjMan.AddModel("Assets/Nano/nanosuit.obj", cube.shader, &model);
        Material material = 
        {
            glm::vec4(0.5),
            glm::vec4(0.5),
            glm::vec4(1.0),
            1.0f,
            16
        };
        m_ObjMan.AddCube("Assets/container2.png", "Assets/container2_specular.png", &cube.model, cube.shader);
        m_ObjMan.AddCube("Assets/container2.png", "Assets/container2_specular.png", &cube2.model, cube2.shader);

        cube.shader->Bind();
        //cube.shader->SetUniform3f("diffuseLight.position", m_PLight->m_Position);
        cube.shader->SetUniform3f("pointLight.position", m_PLight->m_Position);
        cube.shader->SetUniform1f("pointLight.constant", m_PLight->m_Constant);
        cube.shader->SetUniform1f("pointLight.linear", m_PLight->m_Linear);
        cube.shader->SetUniform1f("pointLight.quadratic", m_PLight->m_Quadratic);
        cube.shader->SetUniform3f("pointLight.color", m_PLight->m_Color);
        cube.shader->SetUniform3f("pointLight.ambient", m_PLight->m_Ambiant);
        cube.shader->SetUniform3f("pointLight.diffuse", m_PLight->m_Diffuse);
        cube.shader->SetUniform3f("pointLight.specular", m_PLight->m_Specular);
        //cube.shader->SetUniform1f("diffuseLight.intensity", m_Light->m_Intensity);
        cube.shader->Unbind();

        m_ObjMan.SetProjection(projection);
        m_ObjMan.SetView(view);
    }

    void TestLayer::OnShutDown() 
    {
        
    }

    void TestLayer::OnRender(const float& deltaTime) 
    {
        UpdateMouvement(deltaTime);
        cube.shader->Bind();
        //Light translation
        //sinMov += 0.001f;
        //m_Light->Translate(glm::vec3(0.0f, (sin(sinMov) * 5.0f)* deltaTime, 0.0f));
        //cube.shader->SetUniform3f("diffuseLight.position", m_Light->m_Position);
        if(sinMov == 400.0f)
        {
            CORE_INFO((float) (sin(sinMov)));
            sinMov = 0.0f;
        }

        //TRANSLATION        
        //model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
        //ROTATION
        cube.model = glm::rotate(cube.model, (0.5f * deltaTime) * glm::radians(50.0f), glm::vec3(1.0f, 1.0f, 0.0f));
        cube2.model = glm::rotate(cube2.model, (0.5f * deltaTime) * glm::radians(50.0f), glm::vec3(1.0f, 1.0f, 0.0f));
        //cube.shader->SetUniformMatrix4fv("model", model);
        //m_Model->Draw();
        //cube.shader->Unbind();
        //PROJECTION AND VIEW NOT SETS !!!!
        m_ObjMan.Render();

        m_PLight->Draw();
    }

    void TestLayer::UpdateView() 
    {
        cube.shader->Bind();
        view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        cube.shader->SetUniformMatrix4fv("view", view);
        cube.shader->SetUniform3f("cameraPos", cameraPos);
        cube.shader->Unbind();

        m_LightShader->Bind();
        m_LightShader->SetUniformMatrix4fv("view", view);
        m_LightShader->Unbind();

        m_ObjMan.SetView(view);
    }

    void TestLayer::UpdateMouvement(const float& deltaTime) 
    {
        cameraSpeed = 2.5f * deltaTime;
        if(mvt.bits.w)
        {
            cameraPos += cameraSpeed * cameraFront;
        }
        if(mvt.bits.s)
        {
            cameraPos -= cameraSpeed * cameraFront;
        }
        if(mvt.bits.a)
        {
            cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
        }
        if(mvt.bits.d)
        {
            cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
        }
        if(mvt.bits.q)
        {
            cameraPos -= cameraSpeed * cameraUp;
        }
        if(mvt.bits.e)
        {
            cameraPos += cameraSpeed * cameraUp;
        }
        UpdateView();
    }

    void TestLayer::OnEvent(Event::Event& e) 
    {
        Event::Dispatcher dispatcher(e);
	    dispatcher.dispatch<Event::KeyPressed>(BIND_EVENT_FCT(TestLayer::KeyPressEvent));
	    dispatcher.dispatch<Event::KeyReleased>(BIND_EVENT_FCT(TestLayer::KeyReleasedEvent));
	    dispatcher.dispatch<Event::MouseMoved>(BIND_EVENT_FCT(TestLayer::MouseMovedEvent));
	    dispatcher.dispatch<Event::WindowResize>(BIND_EVENT_FCT(TestLayer::WindowResizeEvent));
    }

    void TestLayer::OnImGUIRender() 
    {
        
    }
    
    bool TestLayer::KeyPressEvent(Event::KeyPressed& e) 
    {
        switch (e.getKeyCode())
        {
        case SE_KEY_W:
            mvt.bits.w = 1;
            break;
        
        case SE_KEY_S:
            mvt.bits.s = 1;
            break;

        case SE_KEY_A:
            mvt.bits.a = 1;
            break;

        case SE_KEY_D:
            mvt.bits.d = 1;
            break;

        case SE_KEY_Q:
            mvt.bits.q = 1;
            break;

        case SE_KEY_E:
            mvt.bits.e = 1;
            break;

        default:
            break;
        }
        return true;
    }

    bool TestLayer::KeyReleasedEvent(Event::KeyReleased& e) 
    {
        switch (e.getKeyCode())
        {
        case SE_KEY_W:
            mvt.bits.w = 0;
            break;
        
        case SE_KEY_S:
            mvt.bits.s = 0;
            break;

        case SE_KEY_A:
            mvt.bits.a = 0;
            break;

        case SE_KEY_D:
            mvt.bits.d = 0;
            break;

        case SE_KEY_Q:
            mvt.bits.q = 0;
            break;

        case SE_KEY_E:
            mvt.bits.e = 0;
            break;

        default:
            break;
        }
        return true;
    }

    bool TestLayer::MouseMovedEvent(Event::MouseMoved& e) 
    {
        m_Yaw += e.GetMousePosition().x * sensitivity;
        m_Pitch -= e.GetMousePosition().y * sensitivity;

        if(m_Pitch > 89.0f)
            m_Pitch =  89.0f;
        if(m_Pitch < -89.0f)
            m_Pitch = -89.0f;

        glm::vec3 direction;
        direction.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
        direction.y = sin(glm::radians(m_Pitch));
        direction.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
        cameraFront = glm::normalize(direction);

        return true;
    }

    bool TestLayer::WindowResizeEvent(Event::WindowResize& e) 
    {
        WindowSize size = e.GetWindowSize();
        cube.shader->Bind();
        projection = glm::perspective(glm::radians(45.0f), size.width / size.height, 0.1f, 250.0f);
        cube.shader->SetUniformMatrix4fv("projection", projection);
        cube.shader->Unbind();

        m_LightShader->Bind();
        m_LightShader->SetUniformMatrix4fv("projection", projection);
        m_LightShader->Unbind();

        m_ObjMan.SetProjection(projection);

        return true;
    }
}
