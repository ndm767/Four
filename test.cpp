#include "include/four.h"

vec5 tri[3] = {
    vec5(0.0f, 0.0f, -0.1f, 0.0f, 1.0f),
    vec5(1.0f, 0.0f, -0.1f, 0.0f, 1.0f),
    vec5(0.0f, 1.0f, -0.1f, 0.0f, 1.0f)
};

vec5 pcVerts[5] = {
    vec5(0.0f, 0.5f, 0.0f, 0.0f, 1.0f), //0
    vec5(-0.5f, 0.0f, 0.0f, 0.0f, 1.0f), //1
    vec5(0.5f, 0.0f, 0.0f, 0.0f, 1.0f), //2
    vec5(0.0f, 0.0f, -0.5f, 0.0f, 1.0f), //3
    vec5(0.0f, 0.0f, 0.0f, -0.5f, 1.0f) //4
};

unsigned int pcInds[30] = {
    0, 1, 2,
    3, 1, 2,
    3, 0, 1,
    3, 0, 2,
    4, 0, 1,
    4, 0, 2,
    4, 0, 3,
    4, 1, 2,
    4, 1, 3,
    4, 2, 3
};

glm::vec4 triColors[3] = {
    glm::vec4(1.0f, 0.0f, 0.0f, 1.0f),
    glm::vec4(0.0f, 1.0f, 0.0f, 1.0f),
    glm::vec4(0.0f, 0.0f, 1.0f, 1.0f)
};

int main(int argc, char* argv[]){
    Window w;
    w.create();
    //use GL_LINE_STRIP instead of GL_LINES
    w.setUseLineStrip(true);

    Camera c;
    c.create();
    w.setActiveCamera(&c);

    Object o;
    o.create(&pcVerts[0], 5, &pcInds[0], 30);
    //o.setUniformColor(glm::vec4(1.0f, 0.0f, 1.0f, 1.0f));
    w.addToScene(&o);

    Object o2;
    o2.create(&tri[0], 3);
    o2.setCustomColor(&triColors[0], 3);
    w.addToScene(&o2);

    w.setRenderMode(Window::RENDER_WIREFRAME);

    while(!w.shouldClose()){
        w.clear(0.1f, 0.2f, 0.3f);

        o.translate(0.0f, sin(glfwGetTime())/100.0f, 0.0f, 0.0f);

        w.update();

        if(w.getKeyPress(SDL_SCANCODE_ESCAPE)){
            w.setShouldClose(true);
        }
        if(w.getKeyPress(SDL_SCANCODE_W)){
            o.scale(glm::vec4(1.1f, 1.1f, 1.1f, 1.1f));
        }
        if(w.getKeyPress(SDL_SCANCODE_S)){
            o.scale(glm::vec4(0.9f, 0.9f, 0.9f, 0.9f));
        }
        if(w.getKeyPress(SDL_SCANCODE_A)){
            o.rotate(Object::YW_PLANE, -0.1f);
        }
        if(w.getKeyPress(SDL_SCANCODE_D)){
            o.rotate(Object::YW_PLANE, 0.1f);
        }
        if(w.getKeyPress(SDL_SCANCODE_LCTRL)){
            w.setRenderMode(Window::RENDER_WIREFRAME);
        }
        if(w.getKeyPress(SDL_SCANCODE_LSHIFT)){
            w.setRenderMode(Window::RENDER_SOLID);
        }
    }

    w.close();
    return 0;
}