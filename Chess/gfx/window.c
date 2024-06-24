#include "Chess/gfx/window.h"
#include <stdio.h>


struct Window window_init(int width, int height, const char* title)
{
    struct Window self = {
        .x = width,
        .y = height,
    };

    #if _DEBUG
    glfwWindowHint(GLFW_CONTEXT_DEBUG, true);
    #endif

    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    self.handle = glfwCreateWindow(self.x, self.y, "Chess", NULL, NULL);

    if(self.handle == NULL)
    {
        printf("error creating window!\n");
        glfwTerminate();
        assert(false);
    };

    glfwMakeContextCurrent(self.handle);

    // TODO: Events call here 

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        printf("error initializing GLAD\n");
        glfwTerminate();
        assert(false);
    }

    glfwSwapInterval(1);

    return self;
};

void window_render(struct Window self)
{
    if(self.handle == NULL)
    {
        printf("Window handle cannot be nullptr\n");
        assert(false);
    };
    glfwSwapBuffers(self.handle);
    glfwPollEvents();
};

void window_destroy(struct Window self)
{
    glfwDestroyWindow(self.handle);
    glfwTerminate();
};