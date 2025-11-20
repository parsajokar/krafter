#include "GLFW/glfw3.h"

int main(int argc, char** argv)
{
    glfwInit();
    GLFWwindow* window = glfwCreateWindow(1280, 720, "Krafter", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    glfwSetFramebufferSizeCallback(
        window,
        [](GLFWwindow* window, int width, int height) {
            glViewport(0, 0, width, height);
        }
    );

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        glClear(GL_COLOR_BUFFER_BIT);

        glBegin(GL_TRIANGLES);
        glColor3f(1.0, 0.0, 0.0);
        glVertex2f(-0.5, -0.5);
        glColor3f(0.0, 1.0, 0.0);
        glVertex2f(0.0, 0.5);
        glColor3f(0.0, 0.0, 1.0);
        glVertex2f(0.5, -0.5);
        glEnd();

        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}