/*
main window generator
*/

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <cmath>
#include <ctime>
#include <cstdlib>
using namespace std;

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;

struct Engine {
    GLFWwindow* window;
    const float SCALE = 1, RATIO = 0.75;
    int WIDTH, HEIGHT;

    Engine() {
        WIDTH = 800 * SCALE;
        HEIGHT = WIDTH * RATIO;

        if (!glfwInit()) {
            cerr << "--- ERR167 ---\n Engine initialization failed\n";
            exit(EXIT_FAILURE);
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        window = glfwCreateWindow(WIDTH, HEIGHT, "Quasistar's Atom Simulation", nullptr, nullptr);
        if (!window) {
            cerr << "--- ERR267 ---\n Window could not be constructed\n";
            glfwTerminate();
            exit(EXIT_FAILURE);
        }

        glfwMakeContextCurrent(window);

        if (glewInit() != GLEW_OK) {
            cerr << "--- ERR367 ---\n GLEW initialization failed\n";
            exit(EXIT_FAILURE);
        }

        glViewport(0, 0, WIDTH, HEIGHT);
        glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
    }

    void run() {
        while (!glfwWindowShouldClose(window)) {
            if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
                glfwSetWindowShouldClose(window, true);

            glClear(GL_COLOR_BUFFER_BIT);

            glfwSwapBuffers(window);
            glfwPollEvents();
        }
    }

    ~Engine() {
        glfwDestroyWindow(window);
        glfwTerminate();
    }
};

int main() {
    Engine engine;
    engine.run();
    return 0;
}