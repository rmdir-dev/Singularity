#include "Test.h"
#include "Utils/Timer.h"
#include "Utils/Log.h"
#include <iostream>
#include "glm/glm.hpp"
#include "Utils/KeyCodes.h"

//imGUI
#define IMGUI_IMPL_OPENGL_LOADER_GLEW 0
#define IMGUI_IMPL_OPENGL_LOADER_GLAD
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_glfw.h"
#include "ImGui/imgui_impl_opengl3.h"

Test::Test() 
{

}


Test::~Test() 
{
    CORE_INFO("Destroy\n");
    destroy();    
}

void Test::windowInitTest()
{
    Window = std::make_unique<Window::Window>("Test window", 1280, 720);
    Window->SetEventCallback(BIND_EVENT_FCT(Test::onEvent));
    tl = std::make_unique<Layer::TestLayer>();
    ImGUISetup();
}

void Test::mainLoop()
{
    Timer t(__func__);
    tl->OnStart();

    uint frame = 0;
    float timer = 0.0f;

    while(Window->IsWindowClose())
    {
        TPoint startTime = HrClock::now();
        ImGUIRenderBeging();

        Window->ClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        tl->OnRender(Window->GetDeltaTime());
        tl->OnImGUIRender();
        ImGUIRenderEnd();
        Window->onMainLoop();

        TPoint endTime = HrClock::now();
        eTime elaspeTime = endTime - startTime;
        timer += elaspeTime.count();
        frame++;
        if(timer > 1.0f)
        {
            timer = 0.0f;
            CORE_INFO("FPS: ", frame);
            frame = 0;
        }
    }
}

void Test::destroy()
{
    //Delete layers before closing the window
    //Else it won't be able to destroy it's shaders.
    tl.reset();
    Window->CloseWindow();
}

void Test::ImGUISetup() 
{
    const char* glsl_version = "#version 130";
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
    //io.ConfigViewportsNoAutoMerge = true;
    //io.ConfigViewportsNoTaskBarIcon = true;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(Window->GetWindow(), true);
    ImGui_ImplOpenGL3_Init(glsl_version);
}


void Test::ImGUIRenderBeging() 
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    ImGui::Begin("Debug Window");
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
}

void Test::ImGUIRenderEnd() 
{
    ImGui::End();
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    GLFWwindow* backup_current_context = glfwGetCurrentContext();
    ImGui::UpdatePlatformWindows();
    ImGui::RenderPlatformWindowsDefault();
    glfwMakeContextCurrent(backup_current_context);
}

void Test::onEvent(Event::Event& e)
{
	Event::Dispatcher dispatcher(e);
	dispatcher.dispatch<Event::KeyPressed>(BIND_EVENT_FCT(Test::keyPressEvent));
    tl->OnEvent(e);
}

bool Test::keyPressEvent(Event::KeyPressed& e)
{    
    if(e.getKeyCode() == SE_KEY_ESCAPE)
    {
        Window->SetWindowClose(true);
        return true;
    }

	return false;
}