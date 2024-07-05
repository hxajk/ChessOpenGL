/// @file window.c

#include "Chess/gfx/window.h"
#include <GLFW/glfw3.h>
#include <stdio.h>

static struct Window self;

/**
 * @brief Handle mouse call back per time.
 * 
 * @param handle 
 * @param button 
 * @param action 
 * @param mods 
 */

static void mouse_callback(GLFWwindow* handle, int button, int action, int mods)
{
    if(button < 0) 
    {
        return;
    };

    switch (action) 
    {
        case GLFW_PRESS:
            self.mouse.buttons[button].down = true;
            self.mouse.buttons[button].up = false;
            break;
        case GLFW_RELEASE:
            self.mouse.buttons[button].down = false;
            self.mouse.buttons[button].up = true;
            break;
        default:
            break;
    }
    glfwGetCursorPos(self.handle, &self.mouse.x, &self.mouse.y);
};

/**
 * @brief Handle key call back per time.
 * 
 * @param handle 
 * @param key 
 * @param scancode 
 * @param action 
 * @param mods 
 */

static void key_callback(GLFWwindow *handle, int key, int scancode, int action, int mods){
    if (key < 0) {
        return;
    }

    switch (action) {
        case GLFW_PRESS:
            self.keyboard.keys[key].down = true;
            self.keyboard.keys[key].up = false;
            break;
        case GLFW_RELEASE:
            self.keyboard.keys[key].down = false;
            self.keyboard.keys[key].up = true;
            break;
        default:
            break;
    }
};


/**
 * @brief Initalize our window.
 * 
 * @param x 
 * @param y 
 * @param title 
 * @return struct Window 
 */

struct Window window_init(int x, int y, const char* title)
{
    self.x = x; self.y = y;

    #if _DEBUG
    glfwWindowHint(GLFW_CONTEXT_DEBUG, true);
    #endif

    glfwWindowHint(GLFW_RESIZABLE, false);

    self.handle = glfwCreateWindow(self.x, self.y, "Chess", NULL, NULL);

    if(self.handle == NULL)
    {
        printf("error creating window!\n");
        glfwTerminate();
        assert(false);
    };

    glfwMakeContextCurrent(self.handle);

    glfwSetMouseButtonCallback(self.handle, mouse_callback);

    glfwSetKeyCallback(self.handle, key_callback);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        printf("error initializing GLAD\n");
        glfwTerminate();
        assert(false);
    }

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glfwSwapInterval(1);

    return self;
};

/**
 * @brief Get the window handle through a struct.
 * 
 * @return struct Window 
 */

struct Window window_get()
{
    if(self.handle == NULL) {
        printf("error window handle cannot be a nullptr!\n");
        assert(false);
    };
    return self;
};


/**
 * @brief Update the window handle per time.
 * 
 * @param self 
 */

void window_render(struct Window self)
{
    glfwSwapBuffers(self.handle);
    glfwPollEvents();
};

/**
 * @brief Destroy our window.
 * 
 * @param self 
 */

void window_destroy(struct Window self)
{
    glfwDestroyWindow(self.handle);
    glfwTerminate();
};