/// @file window.c

#include "Chess/gfx/window.h"
#include <GLFW/glfw3.h>
#include <stdio.h>

static struct Window self;

/**
 * @brief Handle, and update key related per time.
 * 
 * @param handle 
 * @param key 
 * @param scancode 
 * @param action 
 * @param mods 
 */

static void key_callback(GLFWwindow *handle, int key, int scancode, int action, int mods)
{
    if(key == GLFW_KEY_SPACE)
    {
        glfwSetWindowShouldClose(self.handle, true);
    };
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

    glfwSetKeyCallback(self.handle, key_callback);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        printf("error initializing GLAD\n");
        glfwTerminate();
        assert(false);
    }

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
    if(self.handle == NULL)
    {
        printf("error: window handle cannot be a nullptr!\n");
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