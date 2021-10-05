#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"

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

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

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

    {

        float positions[]{
                -0.5f, -0.5f, // 0
                0.5f, -0.5f, // 1
                0.5f, 0.5f, // 2
                -0.5f, 0.5f  // 3
        };

        unsigned int indices[]{
                0, 1, 2,
                2, 3, 0
        };

        VertexArray va;
        VertexBuffer vb(positions, 4 * 2 * sizeof(float));

        VertexBufferLayout layout;
        layout.Push<float>(2);
        va.AddBuffer(vb, layout);

        IndexBuffer ib(indices, 2 * 3);

        ShaderProgramSource source{ ParseShader("../res/shaders/Basic.shader") };
        unsigned int shader{ CreateShader(source.VertexSource, source.FragmentSource) };
        GLCall(glUseProgram(shader));

        GLCall(int location{ glGetUniformLocation(shader, "u_Color") });
        ASSERT(location != -1);
        GLCall(glUniform4f(location, 0.2f, 0.3f, 0.8f, 1.0f));

        GLCall(glBindVertexArray(0));
        GLCall(glUseProgram(0));
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
        GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));

        float r{ 0.0f };
        float incr{ 0.01f };

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            GLCall(glClear(GL_COLOR_BUFFER_BIT));

            GLCall(glUseProgram(shader));
            GLCall(glUniform4f(location, r, 0.3f, 0.8f, 1.0f));

            va.Bind();
            ib.Bind();

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

    }

    glfwTerminate();
    return 0;
}