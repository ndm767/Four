/**
 * @file object.h
 * @author Nathan Medros
 * @brief Header file with function declarations for renderable objects
 * @version 0.1
 * @date 2021-02-06
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef OBJECT_H
#define OBJECT_H

#include "vec5.h"
#include "mat5.h"
#include <GL/gl3w.h>
#include <vector>

class Object{
public:
    void create(vec5 *verts, int num);
    void create(vec5 *verts, int num, glm::vec4 pos);
    void create(vec5 *verts, int numVerts, unsigned int *Indices, int numIndices);
    void create(vec5 *verts, int numVerts, unsigned int *Indices, int numIndices, glm::vec4 pos);
    void close();

    void render(bool solid, bool perspective);
    void render(bool solid, bool perspective, float scale);

    enum plane{XY_PLANE=0, XZ_PLANE=1, XW_PLANE=2, YZ_PLANE=3, YW_PLANE=4, ZW_PLANE=5};
    void translate(glm::vec4 dist);
    void rotate(plane p, float angle);
    void scale(float scalar);
    void scale(glm::vec4 scalar);

    void customColor(bool val);
    void setCustomColor(glm::vec4 *colorArray, int num);
    void setUniformColor(glm::vec4 color);

    glm::mat4 modelMat; //model matrix for the 3d projection
    mat5 fourModelMat; //4d model matrix
    mat5 scaleMat;
    mat5 transMat;
    mat5 rotMat;
    bool useColor = false;
    glm::vec4 constColor = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
private:
    void __render(std::vector<float> verts, bool solid);
    vec5 position;
    std::vector<vec5> vertices;
    bool useIndexedRendering = false;
    std::vector<unsigned int> indices;
    std::vector<float> colors;
    GLuint VAO, VBO; //Vertex array object, Vertex buffer object
    GLuint CBO; //Color buffer object
    GLuint EBO; //Element buffer object
};

#endif