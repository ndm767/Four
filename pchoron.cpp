#include "include/four.h"

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

int main(int argc, char *argv[]){
    Window w;
    w.create();

    Camera c;
    c.create();
    w.setActiveCamera(&c);

    Object pc;
    pc.create(pcVerts, 5, pcInds, 30);
    pc.setUniformColor(glm::vec4(0.0f, 1.0f, 1.0f, 1.0f));
    w.addToScene(&pc);

    w.setRenderMode(Window::RENDER_WIREFRAME);
    //w.set4DProjection(Window::PROJECT_PERSPECTIVE);

    pc.scale(4.0f);

    while(!w.shouldClose()){
        w.clear(0.1f, 0.2f, 0.3f);
        //pc.rotate(Object::YW_PLANE, 0.01f);
        pc.rotate(Object::XW_PLANE, 0.01f);
        //pc.rotate(Object::ZW_PLANE, 0.02f);

        w.update();

        if(w.getKeyPress(GLFW_KEY_ESCAPE)){
            w.setShouldClose(true);
        }
    }
}