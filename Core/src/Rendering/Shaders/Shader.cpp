#include "Shader.h"
#include "glad/glad.h"
#include "Utils/Log.h"
#include "glm/gtc/type_ptr.hpp"


namespace Rendering
{
    Shader::Shader(const char* filePath) 
    {
        auto [vs, fs] = ParseShader(filePath);
        ID = CreateShader(vs, fs);
    }

    Shader::~Shader() 
    {
        glDeleteProgram(ID);
    }

    void Shader::Bind() 
    {
        glUseProgram(ID);
    }

    void Shader::Unbind() 
    {
        glUseProgram(0);
    }

    uint Shader::CompileShader(uint type, const std::string& src) 
    {
        //Create shader of a shader type (Fragment, Vertex, ...) return the ID
        uint id = glCreateShader(type);
        const char* s = src.c_str();

        //Link the shader source code to it's ID.
        glShaderSource(id,      //the ID of the shader we will modify 
                    1,          //How many strings will be pass (in case of an array here it's 1)
                    &s,         //The memory address of the string countaining the source code.
                    nullptr);   //The length of the string if not null terminated, else nullptr or NULL.
        
        //Compile the shader of shader ID;
        glCompileShader(id);

        int result;

        //Return a value as parameter (ref) for a shader object.
        glGetShaderiv(id,           //Shader ID
                GL_COMPILE_STATUS,  //Parameter for the information you want to get.
                &result);           //Where the result of your request should be written.

        if(result == GL_FALSE)
        {
            return 0;   
        }
        return id;
    }

    uint Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader) 
    {
        //Create an empty program and return it's ID
        uint program = glCreateProgram();
        
        //Compile and get the ID of the vertexShader
        uint vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
        //Compile and get the ID of the fragment Shader
        uint fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

        //Attach the Shaders to the program
        glAttachShader(program, vs);
        glAttachShader(program, fs);

        //Link the program
        glLinkProgram(program);

        //validate the program, check that everything is working
        glValidateProgram(program);

        int ret;
        glGetProgramiv(program, GL_VALIDATE_STATUS, &ret);

        if(ret == GL_FALSE)
        {
            CORE_ERROR("Program could not be validate!");
        }
        
        //Delete the "intermediate shader files"
        glDeleteShader(vs);
        glDeleteShader(fs);

        return program;
    }

    std::tuple<std::string, std::string> Shader::ParseShader(const std::string& filePath) 
    {
        //Read the file path
        std::ifstream vsStream(filePath + ".vert");
        std::ifstream fsStream(filePath + ".frag");

        //Get the stream into a string
        std::stringstream ss[2];
        ss[0] << vsStream.rdbuf();
        ss[1] << fsStream.rdbuf();
        
        //Return a tuple containing both shaders strings.
        return { ss[0].str(), ss[1].str() };
    }

    void Shader::SetUniform1i(const char* name, int value) 
    {
        glUniform1i(GetUniformLocation(name), value);
    }

    void Shader::SetUniform3f(const char* name, float v1, float v2, float v3) 
    {
        glUniform3f(GetUniformLocation(name), v1, v2, v3);
    }

    void Shader::SetUniformMatrix4fv(const char* name, const glm::mat4& value) 
    {
        glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
    }

    int Shader::GetUniformLocation(const char* str) 
    {
        if(uniformLocations.find(str) != uniformLocations.end())
        {
            return uniformLocations[str];
        }

        int loc = glGetUniformLocation(ID,      //Program ID
                                       str);    //uniformName
        
        if(loc == -1)
        {
            CORE_WARNING("Uniform '", str, "' does not exist!");
        } else 
        {
            uniformLocations[str] = loc;
        }
        return loc;
    }
}

