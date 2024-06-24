#ifdef __cplusplus
extern "C" {
#endif
#include <Chess/gfx/gfx.h>
#include <Chess/util/util.h>
#ifndef WINDOW_H
#define WINDOW_H



struct Window {
    GLFWwindow* handle;
    float x,y;
};

struct Window window_init(int width, int height, const  char* title);

void window_render(struct Window self);

void window_destroy(struct Window self);

#endif

#ifdef __cplusplus
    }
#endif