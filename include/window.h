/**
 * @file window.h
 * @author Nathan Medros
 * @brief Contains the Window class which acts as the context/global settings manager for the renderer
 * @version 0.1
 * @date 2021-02-06
 * 
 * @copyright Copyright (c) 2021
 *
 */

#ifndef WINDOW_H
#define WINDOW_H

#include "object.h"
#include "camera.h"
#include <SDL2/SDL.h>
#include <vector>
#include "error.h"

/**
 * @brief context, background color, scene manager, misc global settings
 *
 * 
 */

class Window{
public:
    void create();
    void create(int w, int h);
    void create(int w, int h, const char* n);
    void close();

    void clear();
    void clear(float r, float g, float b);
    void clear(float r, float g, float b, float a);
    void update();

    bool shouldClose();
    void setShouldClose(bool state);
    bool getKeyPress(SDL_Scancode key);
    bool getKeyUp(SDL_Scancode key);

    void addToScene(Object *o);
    void setActiveCamera(Camera *cam);

    enum renderMode{RENDER_WIREFRAME, RENDER_SOLID};
    void setRenderMode(renderMode mode);
    renderMode getRenderMode();

    enum projection{PROJECT_ORTHOGRAPHIC, PROJECT_PERSPECTIVE};
    void set4DProjection(projection proj);
    projection get4DProjection();

    void setUseLineStrip(bool value);

private:
    bool useLineStrip = false;
    int width, height;
    const char* name;
    SDL_Window* window;
    SDL_GLContext context;
    bool winShouldClose = false;
    SDL_Event e;
    std::vector<Object*> objects;
    Camera *c;
    bool perspective = false;
    bool renderSolid;
    void createShaders();
    void useShader(bool solid);
    void assignUniformMat4(glm::mat4 val, const char* name);
    void assignUniformBool(bool val, const char* name);
    void assignWireframeSolid();
    void assignUniformVec4(glm::vec4 val, const char* name);
    GLuint solidProgram;
    GLuint wireframeProgram;
    glm::vec2 viewportSize;
};

#endif