#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#define ASSERT(x) if (!(x)) __debugbreak();
#else
#define ASSERT(x)
#endif

#define GLCall(x)   GLClearError(); \
                    x;\
                    ASSERT(GLLogCall(#x, __FILE__, __LINE__))

static void GLClearError()
{
    while (glGetError() != GL_NO_ERROR);
}

static bool GLLogCall(const char* func, const char* file, uint32_t line)
{
    while (GLenum error = glGetError())
    {
        std::cout << "[OpenGL Error 0x" << std::hex << error << std::dec << "] " << func << " " << file << ':' << line << std::endl;
        return false;
    }
    return true;
}

struct ShaderProgramSource
{
    std::string VertexSource;
    std::string FragmentSource;
};

static ShaderProgramSource ParseShader(const std::string& filepath)
{
    std::ifstream stream(filepath);

    enum class ShaderType{
        NONE = -1,
        VERTEX = 0,
        FRAGMENT = 1
    };

    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;
    while (getline(stream, line))
    {
        if (line.find("#shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
                type = { ShaderType::VERTEX };
            else if (line.find("fragment") != std::string::npos)
                type = { ShaderType::FRAGMENT };
        }
        else
            ss[static_cast<int>(type)] << line << '\n';
    }

    return {ss[static_cast<int>(ShaderType::VERTEX)].str(), ss[static_cast<int>(ShaderType::FRAGMENT)].str()};
}

static unsigned int CompileShader(unsigned int type, const std::string& source)
{
    GLCall(unsigned int id{ glCreateShader(type) });
    const char* src{ source.c_str() };
    GLCall(glShaderSource(id, 1, &src, nullptr));
    GLCall(glCompileShader(id));

    int result;
    GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
    if (result == GL_FALSE)
    {
        int length;
        GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
        char* message{ static_cast<char*>(alloca(length * sizeof(char))) };
        GLCall(glGetShaderInfoLog(id, length, &length, message));
        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader:" << std::endl;
        std::cout << message << std::endl;
        GLCall(glDeleteShader(id));
        return 0;
    }

    return id;
}

static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    GLCall(unsigned int program{ glCreateProgram() });
    GLCall(unsigned int vs{ CompileShader(GL_VERTEX_SHADER, vertexShader) });
    GLCall(unsigned int fs{ CompileShader(GL_FRAGMENT_SHADER, fragmentShader) });

    GLCall(glAttachShader(program, vs));
    GLCall(glAttachShader(program, fs));
    GLCall(glLinkProgram(program));
    GLCall(glValidateProgram(program));

    GLCall(glDeleteShader(vs));
    GLCall(glDeleteShader(fs));

    return program;
}

int main()
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(800, 600, "Hello World", nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    // Sync framerate with monitor refresh rate
    glfwSwapInterval(1);

    if ((glewInit() != GLEW_OK))
        std::cout << "Error on glewInit" << std::endl;

    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "OpenGL Renderer: " << glGetString(GL_RENDERER) << std::endl;

    float positions[]{
        -0.5f, -0.5f, // 0
         0.5f, -0.5f, // 1
         0.5f,  0.5f, // 2
        -0.5f,  0.5f  // 3
    };

    unsigned int indices[]{
        0, 1, 2,
        2, 3, 0
    };

    unsigned int buffer;
    GLCall(glGenBuffers(1, &buffer));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, buffer));
    GLCall(glBufferData(GL_ARRAY_BUFFER, 4 * 2 * sizeof(float), positions, GL_STATIC_DRAW));

    GLCall(glEnableVertexAttribArray(0));
    GLCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), nullptr));

    unsigned int ibo;
    GLCall(glGenBuffers(1, &ibo));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo));
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, 2 * 3 * sizeof(unsigned int), indices, GL_STATIC_DRAW));

    ShaderProgramSource source{ ParseShader("../res/shaders/Basic.shader") };
    unsigned int shader{ CreateShader(source.VertexSource, source.FragmentSource) };
    GLCall(glUseProgram(shader));

    GLCall(int location{ glGetUniformLocation(shader, "u_Color") });
    ASSERT(location != -1);
    GLCall(glUniform4f(location, 0.2f, 0.3f, 0.8f, 1.0f));

    float r{ 0.0f };
    float incr{ 0.01f };

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        GLCall(glClear(GL_COLOR_BUFFER_BIT));

        GLCall(glUniform4f(location, r, 0.3f, 0.8f, 1.0f));
        GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

        if (r > 1.0f || r < 0.0f)
            incr *= -1.0f;
        r += incr;

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    GLCall(glDeleteProgram(shader));

    glfwTerminate();
    return 0;
}