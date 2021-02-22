#include "include/four.h"

vec5 tri[3] = {
    vec5(0.0f, 0.0f, -0.1f, 0.0f, 1.0f),
    vec5(1.0f, 0.0f, -0.1f, 0.0f, 1.0f),
    vec5(0.0f, 1.0f, -0.1f, 0.0f, 1.0f)
};

vec5 pentachoron[30] = {
    //tri 1
    vec5(0.0f, 0.5f, 0.0f, 0.0f, 1.0f), //1
    vec5(-0.5f, 0.0f, 0.0f, 0.0f, 1.0f), //2
    vec5(0.5f, 0.0f, 0.0f, 0.0f, 1.0f), //3
    //z-tri 1(fill out)
    vec5(0.0f, 0.0f, -0.5f, 0.0f, 1.0f), //4
    vec5(-0.5f, 0.0f, 0.0f, 0.0f, 1.0f), //2
    vec5(0.5f, 0.0f, 0.0f, 0.0f, 1.0f), //3
    //z-tri 2
    vec5(0.0f, 0.0f, -0.5f, 0.0f, 1.0f), //4
    vec5(0.0f, 0.5f, 0.0f, 0.0f, 1.0f), //1
    vec5(-0.5f, 0.0f, 0.0f, 0.0f, 1.0f), //2
    //z-tri 3
    vec5(0.0f, 0.0f, -0.5f, 0.0f, 1.0f), //4
    vec5(0.0f, 0.5f, 0.0f, 0.0f, 1.0f), //1
    vec5(0.5f, 0.0f, 0.0f, 0.0f, 1.0f), //3
    //w-tri 12(fill out)
    vec5(0.0f, 0.0f, 0.0f, -0.5f, 1.0f), //5
    vec5(0.0f, 0.5f, 0.0f, 0.0f, 1.0f), //1
    vec5(-0.5f, 0.0f, 0.0f, 0.0f, 1.0f), //2
    //w-tri 13
    vec5(0.0f, 0.0f, 0.0f, -0.5f, 1.0f), //5
    vec5(0.0f, 0.5f, 0.0f, 0.0f, 1.0f), //1
    vec5(0.5f, 0.0f, 0.0f, 0.0f, 1.0f), //3
    //w-tri 14
    vec5(0.0f, 0.0f, 0.0f, -0.5f, 1.0f), //5
    vec5(0.0f, 0.5f, 0.0f, 0.0f, 1.0f), //1
    vec5(0.0f, 0.0f, -0.5f, 0.0f, 1.0f), //4
    //w-tri 23
    vec5(0.0f, 0.0f, 0.0f, -0.5f, 1.0f), //5
    vec5(-0.5f, 0.0f, 0.0f, 0.0f, 1.0f), //2
    vec5(0.5f, 0.0f, 0.0f, 0.0f, 1.0f), //3
    //w-tri 24
    vec5(0.0f, 0.0f, 0.0f, -0.5f, 1.0f), //5
    vec5(-0.5f, 0.0f, 0.0f, 0.0f, 1.0f), //2
    vec5(0.0f, 0.0f, -0.5f, 0.0f, 1.0f), //4
    //w-tri 34
    vec5(0.0f, 0.0f, 0.0f, -0.5f, 1.0f), //5
    vec5(0.5f, 0.0f, 0.0f, 0.0f, 1.0f), //3
    vec5(0.0f, 0.0f, -0.5f, 0.0f, 1.0f) //4
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

    Camera c;
    c.create();
    w.setActiveCamera(&c);

    Object o;
    //o.create(pentachoron, 30);
    o.create(pcVerts, 5, pcInds, 30);
    //o.setCustomColor(&triColors[0], 3);
    //o.setUniformColor(glm::vec4(1.0f, 0.0f, 1.0f, 1.0f));
    w.addToScene(&o);

    Object o2;
    o2.create(tri, 3);
    o2.setCustomColor(&triColors[0], 3);
    w.addToScene(&o2);

    w.setRenderMode(Window::RENDER_WIREFRAME);

    while(!w.shouldClose()){
        w.clear(0.1f, 0.2f, 0.3f);

        o.translate(glm::vec4(0.0f, sin(glfwGetTime())/100.0f, 0.0f, 0.0f));

        w.update();

        if(w.getKeyPress(GLFW_KEY_ESCAPE)){
            w.setShouldClose(true);
        }
        if(w.getKeyPress(GLFW_KEY_W)){
            o.scale(glm::vec4(1.1f, 1.1f, 1.1f, 1.1f));
        }
        if(w.getKeyPress(GLFW_KEY_S)){
            o.scale(glm::vec4(0.9f, 0.9f, 0.9f, 0.9f));
        }
        if(w.getKeyPress(GLFW_KEY_A)){
            o.rotate(Object::YW_PLANE, -0.1f);
        }
        if(w.getKeyPress(GLFW_KEY_D)){
            o.rotate(Object::YW_PLANE, 0.1f);
        }
        if(w.getKeyPress(GLFW_KEY_LEFT_CONTROL)){
            w.setRenderMode(Window::RENDER_WIREFRAME);
        }
        if(w.getKeyPress(GLFW_KEY_LEFT_SHIFT)){
            w.setRenderMode(Window::RENDER_SOLID);
        }
    }

    w.close();
    return 0;
}