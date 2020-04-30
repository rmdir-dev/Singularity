#include "glad/glad.h"
#include "TestLayer.h"
#include "Utils/pch.h"
#include <iostream>
#include "glm/gtc/matrix_transform.hpp"
#include "Utils/Log.h"
#include "Utils/KeyCodes.h"
#include "ImGui/imgui.h"

namespace Layer
{
    TestLayer::TestLayer() 
    {
        m_ShaderManager = std::make_shared<Manager::ShaderManager>();
        m_ObjMan = Manager::ObjectManager(m_ShaderManager);
        cube.shader = m_ShaderManager->LoadShader("Assets/LightTesting/BasicTextureDS_MultiLight");
        cube2.shader = m_ShaderManager->LoadShader("Assets/LightTesting/BasicTextureDS_MultiLight");
        //nano.shader = m_ShaderManager->LoadShader("Assets/LightTesting/BasicTextureDS_MultiLight");
        m_LightShader = std::make_shared<Rendering::Shader>("Assets/BoxLightShader");


        //CAMERA SETUP
        cameraPos       = glm::vec3(0.0f, 0.15f,  5.0f);
        cameraFront     = glm::vec3(0.0f, 0.0f, -1.0f);
        cameraUp        = glm::vec3(0.0f, 1.0f,  0.0f);
        cameraSpeed = 0.05f;
        sensitivity = 0.1f;
        m_Yaw = -90.0f;
        m_Pitch = 0.0f;

        mvt.input = 0x00;
        sinMov = 0.0f;

        UpdateView(); 

        cube.shader->Bind();       

        cube.model = glm::mat4(1.0f);
        cube2.model = glm::mat4(1.0f);
        cube2.model = glm::translate(cube2.model, glm::vec3(-4.0f, 0.0f, -10.0f));
        //nano.model = glm::mat4(1.0f);
        //nano.model = glm::translate(nano.model, glm::vec3(-4.0f, -1.4f, 0.0f));
        //nano.model = glm::scale(nano.model, glm::vec3(0.2f, 0.2f, 0.2f));     
        projection = glm::perspective(glm::radians(45.0f), 1280.0f / 720.0f, 0.1f, 250.0f);

        cube.shader->SetUniformMatrix4fv("model", cube.model);
        cube.shader->SetUniformMatrix4fv("projection", projection);

        cube.shader->Unbind();

        m_LightShader->Bind();
        m_LightShader->SetUniformMatrix4fv("projection", projection);
        m_LightShader->SetUniform3f("inColor", glm::vec3(1.0f));
        m_LightShader->Unbind();       

        rotation = 0.0f;

        CreateLights();
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
        //m_ObjMan.AddModel("Assets/Nano/nanosuit.obj", nano.shader, &nano.model);

        m_ObjMan.SetProjection(projection);
        m_ObjMan.SetView(view);
    }

    void TestLayer::OnShutDown() 
    {
        
    }

    void TestLayer::OnRender(const float& deltaTime) 
    {
        UpdateMouvement(deltaTime);
        UpdateLights(deltaTime);
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

        m_SLight->Draw();
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
        ImGUILightEditor("Point Light 1", "pointLight[0]", ImGUI_PLight1, m_PLight1);
        ImGUILightEditor("Point Light 2", "pointLight[1]", ImGUI_PLight2, m_PLight2);
        ImGUILightEditor("Point Light 3", "pointLight[2]", ImGUI_PLight3, m_PLight3);
        ImGUILightEditor("Point Light 4", "pointLight[3]", ImGUI_PLight4, m_PLight4);
        ImGUILightEditor("Dir Light", "directionalLight", ImGUI_DLight, m_DLight);    
    }

    void TestLayer::ImGUILightEditor(const char* title, const char* lightShaderName, bool& lightBool, std::shared_ptr<Rendering::PointLight> light) 
    {
        if(ImGui::CollapsingHeader(title))
        {
            if(ImGui::Button(lightBool ? "Light Status : On" : "Light Status : Off"))
            {
                if(lightBool)
                {
                    lightBool = false;
                    light->SetLightSettings(0x00);
                    UpdateStaticLights(lightShaderName, light);
                } else 
                {
                    lightBool = true;
                    light->SetLightSettings(ACTIVATE_LIGHT);
                    UpdateStaticLights(lightShaderName, light);
                }
            }

            if(ImGui::SliderFloat("Position x", &light->m_Position.x, -100.0f, 100.0f))
            {
                UpdateStaticLights(lightShaderName, light);
            }

            if(ImGui::SliderFloat("Position y", &light->m_Position.y, -100.0f, 100.0f))
            {
                UpdateStaticLights(lightShaderName, light);
            }

            if(ImGui::SliderFloat("Position z", &light->m_Position.z, -100.0f, 100.0f))
            {
                UpdateStaticLights(lightShaderName, light);
            }

            float Color[3];
            Color[0] = light->m_Color.r;
            Color[1] = light->m_Color.g;
            Color[2] = light->m_Color.b;
            if(ImGui::ColorEdit3("Color", Color))
            {
                light->m_Color.r = Color[0];
                light->m_Color.g = Color[1];
                light->m_Color.b = Color[2];
                light->SetAmbiant();
                light->SetDiffuse();
                light->SetSpecular();
                UpdateStaticLights(lightShaderName, light);
            }
            if(ImGui::SliderFloat("Ambiant intensity", &light->m_AmbiantIntensity, 0.0f, 1.0f))
            {
                light->SetAmbiant();
                UpdateStaticLights(lightShaderName, light);
            }
            if(ImGui::SliderFloat("Diffuse intensity", &light->m_DiffuseIntensity, 0.0f, 1.0f))
            {
                light->SetDiffuse();
                UpdateStaticLights(lightShaderName, light);
            }
            if(ImGui::SliderFloat("Specular intensity", &light->m_SpecularIntensity, 0.0f, 1.0f))
            {
                light->SetSpecular();
                UpdateStaticLights(lightShaderName, light);
            }
            if(ImGui::SliderFloat("Constant", &light->m_Constant, 0.0f, 1.0f))
            {
                UpdateStaticLights(lightShaderName, light);
            }
            if(ImGui::SliderFloat("Linear", &light->m_Linear, 0.0f, 1.0f))
            {
                UpdateStaticLights(lightShaderName, light);
            }
            if(ImGui::SliderFloat("Quadratic", &light->m_Quadratic, 0.0f, 1.0f))
            {
                UpdateStaticLights(lightShaderName, light);
            }
        }
    }

    void TestLayer::ImGUILightEditor(const char* title, const char* lightShaderName, bool& lightBool, std::shared_ptr<Rendering::DirectionalLight> light) 
    {
        if(ImGui::CollapsingHeader(title))
        {
            if(ImGui::Button(lightBool ? "Light Status : On" : "Light Status : Off"))
            {
                if(lightBool)
                {
                    lightBool = false;
                    light->SetLightSettings(0x00);
                    UpdateStaticLights(lightShaderName, light);
                } else 
                {
                    lightBool = true;
                    light->SetLightSettings(ACTIVATE_LIGHT);
                    UpdateStaticLights(lightShaderName, light);
                }
            }

            if(ImGui::SliderFloat("Direction x", &light->m_Direction.x, -1.0f, 1.0f))
            {
                UpdateStaticLights(lightShaderName, light);
            }

            if(ImGui::SliderFloat("Direction y", &light->m_Direction.y, -1.0f, 1.0f))
            {
                UpdateStaticLights(lightShaderName, light);
            }

            if(ImGui::SliderFloat("Direction z", &light->m_Direction.z, -1.0f, 1.0f))
            {
                UpdateStaticLights(lightShaderName, light);
            }

            float Color[3];
            Color[0] = light->m_Color.r;
            Color[1] = light->m_Color.g;
            Color[2] = light->m_Color.b;
            if(ImGui::ColorEdit3("Color", Color))
            {
                light->m_Color.r = Color[0];
                light->m_Color.g = Color[1];
                light->m_Color.b = Color[2];
                light->SetAmbiant();
                light->SetDiffuse();
                light->SetSpecular();
                UpdateStaticLights(lightShaderName, light);
            }
            if(ImGui::SliderFloat("Ambiant intensity", &light->m_AmbiantIntensity, 0.0f, 1.0f))
            {
                light->SetAmbiant();
                UpdateStaticLights(lightShaderName, light);
            }
            if(ImGui::SliderFloat("Diffuse intensity", &light->m_DiffuseIntensity, 0.0f, 1.0f))
            {
                light->SetDiffuse();
                UpdateStaticLights(lightShaderName, light);
            }
            if(ImGui::SliderFloat("Specular intensity", &light->m_SpecularIntensity, 0.0f, 1.0f))
            {
                light->SetSpecular();
                UpdateStaticLights(lightShaderName, light);
            }
        }
    }

    void TestLayer::CreateLights() 
    {
        cube.shader->Bind();

        //SPOT LIGHT
        m_SLight = std::make_shared<Rendering::SpotLight>();
        m_SLight->SetShader(m_LightShader);
        m_SLight->SetLightSettings(ACTIVATE_LIGHT);
        m_SLight->m_Color = glm::vec3(1.0, 1.0, 1.0);
        m_SLight->SetAmbiant(0.1f);
        m_SLight->SetDiffuse(0.5f);
        m_SLight->SetSpecular(1.0f);
        m_SLight->m_Direction = cameraFront;
        m_SLight->m_Position = cameraPos;
        
        cube.shader->SetUniform3f("spotLight.position",         cameraPos);
        cube.shader->SetUniform3f("spotLight.direction",        cameraFront);
        cube.shader->SetUniform1f("spotLight.cutOff",           m_SLight->m_CutOff);
        cube.shader->SetUniform1f("spotLight.outerCutOff",      m_SLight->m_OuterCutOff);
        cube.shader->SetUniform1f("spotLight.constant",         m_SLight->m_Constant);
        cube.shader->SetUniform1f("spotLight.linear",           m_SLight->m_Linear);
        cube.shader->SetUniform1f("spotLight.quadratic",        m_SLight->m_Quadratic);
        cube.shader->SetUniform3f("spotLight.ambient",          m_SLight->m_Ambiant);
        cube.shader->SetUniform3f("spotLight.diffuse",          m_SLight->m_Diffuse);
        cube.shader->SetUniform3f("spotLight.specular",         m_SLight->m_Specular);        
        cube.shader->SetUniform1i("spotLight.on",               m_SLight->GetOnOrOff());        

        //POINT LIGHT 1
        m_PLight1 = std::make_shared<Rendering::PointLight>(glm::vec3(3.5f, 3.5f, 3.5f));
        m_PLight1->SetShader(m_LightShader);
        m_PLight1->SetLightSettings(ACTIVATE_LIGHT);
        m_PLight1->m_Color = glm::vec3(1.0, 1.0, 1.0);
        m_PLight1->SetAmbiant(0.1f);
        m_PLight1->SetDiffuse(0.5f);
        m_PLight1->SetSpecular(1.0f);

        cube.shader->SetUniform3f("pointLight[0].position",         m_PLight1->m_Position);
        cube.shader->SetUniform1f("pointLight[0].constant",         m_PLight1->m_Constant);
        cube.shader->SetUniform1f("pointLight[0].linear",           m_PLight1->m_Linear);
        cube.shader->SetUniform1f("pointLight[0].quadratic",        m_PLight1->m_Quadratic);
        cube.shader->SetUniform3f("pointLight[0].ambient",          m_PLight1->m_Ambiant);
        cube.shader->SetUniform3f("pointLight[0].diffuse",          m_PLight1->m_Diffuse);
        cube.shader->SetUniform3f("pointLight[0].specular",         m_PLight1->m_Specular);
        cube.shader->SetUniform1i("pointLight[0].on",               m_PLight1->GetOnOrOff());        

        //POINT LIGHT 2
        m_PLight2 = std::make_shared<Rendering::PointLight>(glm::vec3(-2.0f, 0.0f, 1.5f));
        m_PLight2->SetShader(m_LightShader);
        m_PLight2->SetLightSettings(ACTIVATE_LIGHT);
        m_PLight2->m_Color = glm::vec3(1.0, 1.0, 1.0);
        m_PLight2->SetAmbiant(0.1f);
        m_PLight2->SetDiffuse(0.5f);
        m_PLight2->SetSpecular(1.0f);

        cube.shader->SetUniform3f("pointLight[1].position",         m_PLight2->m_Position);
        cube.shader->SetUniform1f("pointLight[1].constant",         m_PLight2->m_Constant);
        cube.shader->SetUniform1f("pointLight[1].linear",           m_PLight2->m_Linear);
        cube.shader->SetUniform1f("pointLight[1].quadratic",        m_PLight2->m_Quadratic);
        cube.shader->SetUniform3f("pointLight[1].ambient",          m_PLight2->m_Ambiant);
        cube.shader->SetUniform3f("pointLight[1].diffuse",          m_PLight2->m_Diffuse);
        cube.shader->SetUniform3f("pointLight[1].specular",         m_PLight2->m_Specular);
        cube.shader->SetUniform1i("pointLight[1].on",               m_PLight2->GetOnOrOff());        

        //POINT LIGHT 3
        m_PLight3 = std::make_shared<Rendering::PointLight>(glm::vec3(-4.0f, 6.0f, -2.5f));
        m_PLight3->SetShader(m_LightShader);
        m_PLight3->SetLightSettings(ACTIVATE_LIGHT);
        m_PLight3->m_Color = glm::vec3(1.0, 1.0, 1.0);
        m_PLight3->SetAmbiant(0.1f);
        m_PLight3->SetDiffuse(0.5f);
        m_PLight3->SetSpecular(1.0f);

        cube.shader->SetUniform3f("pointLight[2].position",         m_PLight3->m_Position);
        cube.shader->SetUniform1f("pointLight[2].constant",         m_PLight3->m_Constant);
        cube.shader->SetUniform1f("pointLight[2].linear",           m_PLight3->m_Linear);
        cube.shader->SetUniform1f("pointLight[2].quadratic",        m_PLight3->m_Quadratic);
        cube.shader->SetUniform3f("pointLight[2].ambient",          m_PLight3->m_Ambiant);
        cube.shader->SetUniform3f("pointLight[2].diffuse",          m_PLight3->m_Diffuse);
        cube.shader->SetUniform3f("pointLight[2].specular",         m_PLight3->m_Specular);
        cube.shader->SetUniform1i("pointLight[2].on",               m_PLight3->GetOnOrOff());       

        //POINT LIGHT 4
        m_PLight4 = std::make_shared<Rendering::PointLight>(glm::vec3(-1.0f, 2.0f, -1.0f));
        m_PLight4->SetShader(m_LightShader);
        m_PLight4->SetLightSettings(ACTIVATE_LIGHT);
        m_PLight4->m_Color = glm::vec3(1.0, 1.0, 1.0);
        m_PLight4->SetAmbiant(0.1f);
        m_PLight4->SetDiffuse(0.5f);
        m_PLight4->SetSpecular(1.0f);

        cube.shader->SetUniform3f("pointLight[3].position",         m_PLight4->m_Position);
        cube.shader->SetUniform1f("pointLight[3].constant",         m_PLight4->m_Constant);
        cube.shader->SetUniform1f("pointLight[3].linear",           m_PLight4->m_Linear);
        cube.shader->SetUniform1f("pointLight[3].quadratic",        m_PLight4->m_Quadratic);
        cube.shader->SetUniform3f("pointLight[3].ambient",          m_PLight4->m_Ambiant);
        cube.shader->SetUniform3f("pointLight[3].diffuse",          m_PLight4->m_Diffuse);
        cube.shader->SetUniform3f("pointLight[3].specular",         m_PLight4->m_Specular);
        cube.shader->SetUniform1i("pointLight[3].on",               m_PLight4->GetOnOrOff());        

        //DIR LIGHT
        m_DLight = std::make_shared<Rendering::DirectionalLight>();
        m_DLight->SetShader(m_LightShader);
        m_DLight->SetLightSettings(ACTIVATE_LIGHT);
        m_DLight->m_Color = glm::vec3(1.0, 1.0, 1.0);
        m_DLight->SetAmbiant(0.1f);
        m_DLight->SetDiffuse(0.5f);
        m_DLight->SetSpecular(1.0f);

        cube.shader->SetUniform3f("directionalLight.direction",         m_DLight->m_Direction);;
        cube.shader->SetUniform3f("directionalLight.ambient",          m_DLight->m_Ambiant);
        cube.shader->SetUniform3f("directionalLight.diffuse",          m_DLight->m_Diffuse);
        cube.shader->SetUniform3f("directionalLight.specular",         m_DLight->m_Specular);
        cube.shader->SetUniform1i("directionalLight.on",               m_DLight->GetOnOrOff());        

        cube.shader->Unbind();
    }

    void TestLayer::UpdateLights(const float& deltaTime) 
    {
        cube.shader->Bind();
        cube.shader->SetUniform3f("spotLight.position",         cameraPos);
        cube.shader->SetUniform3f("spotLight.direction",        cameraFront);
        cube.shader->Unbind();
    } 
    
    void TestLayer::UpdateStaticLights(const String& name, std::shared_ptr<Rendering::DirectionalLight> light) 
    {
        cube.shader->Bind();
        cube.shader->SetUniform3f((name + ".direction").c_str(),        light->m_Direction);
        cube.shader->SetUniform3f((name + ".ambient").c_str(),          light->m_Ambiant);
        cube.shader->SetUniform3f((name + ".diffuse").c_str(),          light->m_Diffuse);
        cube.shader->SetUniform3f((name + ".specular").c_str(),         light->m_Specular);
        cube.shader->SetUniform1i((name + ".on").c_str(),               light->GetOnOrOff());
        cube.shader->Unbind();
    }

    void TestLayer::UpdateStaticLights(const String& name, std::shared_ptr<Rendering::SpotLight> light) 
    {
        cube.shader->Bind();
        cube.shader->SetUniform3f((name + ".position").c_str(),         light->m_Position);
        cube.shader->SetUniform3f((name + ".direction").c_str(),        light->m_Direction);
        cube.shader->SetUniform3f((name + ".ambient").c_str(),          light->m_Ambiant);
        cube.shader->SetUniform3f((name + ".diffuse").c_str(),          light->m_Diffuse);
        cube.shader->SetUniform3f((name + ".specular").c_str(),         light->m_Specular);
        cube.shader->SetUniform1f((name + ".cutOff").c_str(),           light->m_CutOff);
        cube.shader->SetUniform1f((name + ".outerCutOff").c_str(),      light->m_OuterCutOff);
        cube.shader->SetUniform1f((name + ".constant").c_str(),         light->m_Constant);
        cube.shader->SetUniform1f((name + ".linear").c_str(),           light->m_Linear);
        cube.shader->SetUniform1f((name + ".quadratic").c_str(),        light->m_Quadratic);
        cube.shader->SetUniform1i((name + ".on").c_str(),               light->GetOnOrOff());
        cube.shader->Unbind();
    }

    void TestLayer::UpdateStaticLights(const String& name, std::shared_ptr<Rendering::PointLight> light) 
    {
        cube.shader->Bind();
        cube.shader->SetUniform3f((name + ".position").c_str(),         light->m_Position);
        cube.shader->SetUniform3f((name + ".ambient").c_str(),          light->m_Ambiant);
        cube.shader->SetUniform3f((name + ".diffuse").c_str(),          light->m_Diffuse);
        cube.shader->SetUniform3f((name + ".specular").c_str(),         light->m_Specular);
        cube.shader->SetUniform1f((name + ".constant").c_str(),         light->m_Constant);
        cube.shader->SetUniform1f((name + ".linear").c_str(),           light->m_Linear);
        cube.shader->SetUniform1f((name + ".quadratic").c_str(),        light->m_Quadratic);
        cube.shader->SetUniform1i((name + ".on").c_str(),               light->GetOnOrOff());
        cube.shader->Unbind();
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
