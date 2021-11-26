#ifndef OPENGL_LEARNING_SHADER_H
#define OPENGL_LEARNING_SHADER_H

#include "pch.h"

struct ShaderProgramSource
{
    std::string VertexSource;
    std::string FragmentSource;
};

class Shader
{
public:
    Shader(const std::string& filepath);
    ~Shader();

    void Bind() const;
    void Unbind() const;

    void SetUniform4f(const std::string& name, float v0, float v1, float v2,
                      float v3);

private:
    int GetUniformLocation(const std::string& name);
    ShaderProgramSource ParseShader(const std::string& filepath);
    unsigned int CreateShader(const std::string& vertexShader,
                              const std::string& fragmentShader);
    static unsigned int CompileShader(unsigned int type,
                                      const std::string& source);

    unsigned int m_RendererID;
    std::string m_Filepath;
    std::unordered_map<std::string, int> m_UniformLocationCache;
};

#endif // OPENGL_LEARNING_SHADER_H
