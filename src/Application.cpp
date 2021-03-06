#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "Renderer.h"
#include "VertexBufferLayout.h"

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
    window = glfwCreateWindow(800, 600, "OpenGL - Learning", nullptr, nullptr);
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
            0.5f,  -0.5f, // 1
            0.5f,  0.5f,  // 2
            -0.5f, 0.5f   // 3
        };

        unsigned int indices[]{0, 1, 2, 2, 3, 0};

        VertexBuffer vb(positions, 4 * 2 * sizeof(float));
        VertexBufferLayout layout;
        layout.Push<float>(2);

        VertexArray va;
        va.AddBuffer(vb, layout);

        IndexBuffer ib(indices, 2 * 3);

        Shader shader("../res/shaders/Basic.shader");
        Renderer renderer;

        float r{0.0f};
        float incr{0.01f};

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            renderer.Clear();
            shader.Bind();
            shader.SetUniform4f("u_Color", r, 0.3f, 0.8f, 1.0f);
            renderer.Draw(va, ib, shader);

            if (r > 1.0f || r < 0.0f)
                incr *= -1.0f;
            r += incr;

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }
    }

    glfwTerminate();
    return 0;
}
