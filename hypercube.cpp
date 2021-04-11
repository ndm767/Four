// this draws a perspectively projected tesseract
#include "include/four.h"

vec5 hcubeverts[16]={
    vec5(-1.0f,  1.0f,  1.0f,  1.0f, 1.0f),//0
    vec5(-1.0f, -1.0f,  1.0f,  1.0f, 1.0f),//1
    vec5( 1.0f, -1.0f,  1.0f,  1.0f, 1.0f),//2
    vec5( 1.0f,  1.0f,  1.0f,  1.0f, 1.0f),//3
    vec5( 1.0f, -1.0f, -1.0f,  1.0f, 1.0f),//4
    vec5( 1.0f,  1.0f, -1.0f,  1.0f, 1.0f),//5
    vec5(-1.0f,  1.0f, -1.0f,  1.0f, 1.0f),//6
    vec5(-1.0f, -1.0f, -1.0f,  1.0f, 1.0f),//7
    vec5(-1.0f,  1.0f,  1.0f, -1.0f, 1.0f),//8
    vec5(-1.0f, -1.0f,  1.0f, -1.0f, 1.0f),//9
    vec5( 1.0f, -1.0f,  1.0f, -1.0f, 1.0f),//10
    vec5( 1.0f,  1.0f,  1.0f, -1.0f, 1.0f),//11
    vec5( 1.0f, -1.0f, -1.0f, -1.0f, 1.0f),//12
    vec5( 1.0f,  1.0f, -1.0f, -1.0f, 1.0f),//13
    vec5(-1.0f,  1.0f, -1.0f, -1.0f, 1.0f),//14
    vec5(-1.0f, -1.0f, -1.0f, -1.0f, 1.0f)//15
};
unsigned int hcubeinds[144]={
    //cube 1
    0, 1,
    1, 2,
    2, 3,
    3, 0,
    0, 6,
    6, 5,
    5, 3,
    5, 4,
    4, 2,
    4, 7,
    6, 7,
    7, 1,
    //cube 2
    2, 3,
    3, 5,
    5, 4,
    4, 2,
    2, 10,
    10, 11,
    11, 3,
    10, 12,
    12, 13,
    13, 11,
    13, 5,
    12, 4,
    //cube 3
    8, 0,
    0, 3,
    3, 11,
    11, 8,
    8, 9,
    9, 1,
    1, 0,
    1, 2,
    2, 3,
    2, 10,
    10, 9,
    10, 11,
    //cube 4
    8, 0,
    0, 6,
    6, 14,
    14, 8,
    15, 7,
    7, 1,
    1, 9,
    9, 15,
    8, 9,
    14, 15,
    6, 7,
    1, 0,
    //cube 5
    6, 5,
    5, 13,
    13, 14,
    14, 6,
    7, 4,
    4, 12,
    12, 15,
    15, 7,
    6, 7,
    14, 15,
    13, 12,
    5, 4,
    //cube 6
    8, 11,
    11, 13,
    13, 14,
    14, 8,
    0, 3,
    3, 5,
    5, 6,
    6, 0,
    8, 0,
    11, 3,
    13, 5,
    14, 6
    // the other cubes aren't needed because this is wireframe
};

glm::vec4 hcubeColors[16] = {
    glm::vec4(1.0f, 0.0f, 0.0f, 1.0f),
    glm::vec4(1.0f, 0.0f, 0.0f, 1.0f),
    glm::vec4(1.0f, 0.0f, 0.0f, 1.0f),
    glm::vec4(1.0f, 0.0f, 0.0f, 1.0f),
    glm::vec4(1.0f, 0.0f, 0.0f, 1.0f),
    glm::vec4(1.0f, 0.0f, 0.0f, 1.0f),
    glm::vec4(1.0f, 0.0f, 0.0f, 1.0f),
    glm::vec4(1.0f, 0.0f, 0.0f, 1.0f),
    glm::vec4(0.0f, 1.0f, 0.0f, 1.0f),
    glm::vec4(0.0f, 1.0f, 0.0f, 1.0f),
    glm::vec4(0.0f, 1.0f, 0.0f, 1.0f),
    glm::vec4(0.0f, 1.0f, 0.0f, 1.0f),
    glm::vec4(0.0f, 1.0f, 0.0f, 1.0f),
    glm::vec4(0.0f, 1.0f, 0.0f, 1.0f),
    glm::vec4(0.0f, 1.0f, 0.0f, 1.0f),
    glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)
};

int main(int argc, char *argv[]){
    Window w;
    w.create();

    Camera c;
    c.create();
    w.setActiveCamera(&c);

    Object o;
    o.create(hcubeverts, 16, hcubeinds, 144);
    o.setCustomColor(&hcubeColors[0], 16);
    w.addToScene(&o);

    w.setRenderMode(Window::RENDER_WIREFRAME);
    w.set4DProjection(Window::PROJECT_PERSPECTIVE);

    while(!w.shouldClose()){
        w.clear(0.1f, 0.2f, 0.3f);

        o.rotate(Object::ZW_PLANE, 0.01f);

        w.update();

        if(w.getKeyPress(GLFW_KEY_ESCAPE)){
            w.setShouldClose(true);
        }
        if(w.getKeyPress(GLFW_KEY_SPACE)){
            w.set4DProjection(Window::PROJECT_ORTHOGRAPHIC);
        }
        if(w.getKeyPress(GLFW_KEY_LEFT_CONTROL)){
            w.set4DProjection(Window::PROJECT_PERSPECTIVE);
        }

    }
}