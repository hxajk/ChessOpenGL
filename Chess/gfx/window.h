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

struct Window window_init(int x, int y, const  char* title);

struct Window window_get();

void window_render(struct Window self);

void window_destroy(struct Window self);
#endif

#ifdef __cplusplus
    }
#endif