/**
 * @file object.cpp
 * @author Nathan Medros
 * @brief Functions to create, modify, and render individual objects
 * @version 0.1
 * @date 2021-02-06
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "object.h"

void Object::create(vec5 *verts, int num){
    create(verts, num, glm::vec4(0.0f, 0.0f, 0.0f, 0.0f));
}

void Object::create(vec5 *verts, int num, glm::vec4 pos){
    position = vec5(pos, 1.0f);
    modelMat = glm::mat4(1.0f);
    fourModelMat = createIdentityMatrix();
    transMat = createIdentityMatrix();
    scaleMat = createIdentityMatrix();
    rotMat = createIdentityMatrix();
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &CBO);
    glGenBuffers(1, &EBO);
    for(int i = 0; i<num; i++){
        vertices.push_back(verts[i]);
    }
}

void Object::create(vec5 *verts, int numVerts, unsigned int *Indices, int numIndices){
    create(verts, numVerts, Indices, numIndices, glm::vec4(0.0f, 0.0f, 0.0f, 0.0f));
}
void Object::create(vec5 *verts, int numVerts, unsigned int *Indices, int numIndices, glm::vec4 pos){
    useIndexedRendering = true;
    position = vec5(pos, 1.0f);
    modelMat = glm::mat4(1.0f);
    fourModelMat = createIdentityMatrix();
    transMat = createIdentityMatrix();
    scaleMat = createIdentityMatrix();
    rotMat = createIdentityMatrix();
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &CBO);
    glGenBuffers(1, &EBO);
    for(int i = 0; i<numVerts; i++){
        vertices.push_back(verts[i]);
    }
    for(int j = 0; j<numIndices; j++){
        indices.push_back(Indices[j]);
    }
}

void Object::render(bool solid, bool perspective){
    std::vector<float> fverts;
    fourModelMat = product(transMat, scaleMat);
    fourModelMat = product(fourModelMat, rotMat);
    for(int i = 0; i<vertices.size(); i++){
        vec5 newVert = vertices[i];
        newVert = product(fourModelMat, newVert);
        float mult = 0.0f;
        if(perspective){
            mult = newVert[3];
        }
        fverts.push_back(newVert[0]/(pow(2, mult)));
        fverts.push_back(newVert[1]/(pow(2, mult)));
        fverts.push_back(newVert[2]/(pow(2, mult)));
    }

    this->__render(fverts, solid);
}
void Object::render(bool solid, bool perspective, float scale){
    std::vector<float> fverts;
    fourModelMat = product(transMat, scaleMat);
    fourModelMat = product(fourModelMat, rotMat);
    for(int i = 0; i<vertices.size(); i++){
        vec5 newVert = vertices[i];
        newVert = product(fourModelMat, newVert);
        float mult = 0.0f;
        if(perspective){
            mult = newVert[3];
        }
        fverts.push_back((newVert[0] * scale)/pow(2, mult));
        fverts.push_back((newVert[1] * scale)/pow(2, mult));
        fverts.push_back((newVert[2] * scale)/pow(2, mult));
    }

    this->__render(fverts, solid);
}

void Object::__render(std::vector<float> verts, bool solid){
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glBufferData(GL_ARRAY_BUFFER, verts.size() * sizeof(float), verts.data(), GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);

    if(useColor){
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, CBO);
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
        glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(float), colors.data(), GL_DYNAMIC_DRAW);
        glEnableVertexAttribArray(1);
    }

    if(useIndexedRendering){
        glBindVertexArray(VAO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(int), indices.data(), GL_DYNAMIC_DRAW);
    }

    glBindVertexArray(VAO);
    if(useIndexedRendering){
        if(solid){
            glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
        }else{
            glDrawElements(GL_LINE_STRIP, indices.size(), GL_UNSIGNED_INT, 0);
        }
    }else{
        if(solid){
            glDrawArrays(GL_TRIANGLES, 0, verts.size()/3);
        }else{
            glDrawArrays(GL_LINE_STRIP, 0, verts.size()/3);
        }
    }
}

void Object::translate(glm::vec4 dist){
    transMat[0][4] += dist[0];
    transMat[1][4] += dist[1];
    transMat[2][4] += dist[2];
    transMat[3][4] += dist[3];
    position[0] += dist[0];
    position[1] += dist[1];
    position[2] += dist[2];
    position[3] += dist[3];
    position[4] = 1;
}
void Object::scale(float scalar){
    this->scale(glm::vec4(scalar, scalar, scalar, scalar));
}
void Object::scale(glm::vec4 scalar){
    for(int i = 0; i<4; i++){
        scaleMat[i][i] *= scalar[i];
    }
}

void Object::rotate(plane p, float angle){
    if(p == XY_PLANE){
        //XY Plane
        mat5 xyRot = createIdentityMatrix();
        xyRot[0][0] = cos(angle);
        xyRot[0][1] = sin(angle);
        xyRot[1][0] = -1.0f * sin(angle);
        xyRot[1][1] = cos(angle);
        rotMat = product(rotMat, xyRot);
    }else if(p == XZ_PLANE){
        //XZ Plane
        mat5 xzRot = createIdentityMatrix();
        xzRot[0][0] = cos(angle);
        xzRot[0][2] = -1.0f * sin(angle);
        xzRot[2][0] = sin(angle);
        xzRot[2][2] = cos(angle);
        rotMat = product(rotMat, xzRot);
    }else if(p == XW_PLANE){
        //XW Plane
        mat5 xwRot = createIdentityMatrix();
        xwRot[0][0] = cos(angle);
        xwRot[0][3] = sin(angle);
        xwRot[3][0] = -1.0f * sin(angle);
        xwRot[3][3] = cos(angle);
        rotMat = product(rotMat, xwRot);
    }else if(p == YZ_PLANE){
        //YZ Plane
        mat5 yzRot = createIdentityMatrix();
        yzRot[1][1] = cos(angle);
        yzRot[1][2] = sin(angle);
        yzRot[2][1] = -1.0f * sin(angle);
        yzRot[2][2] = cos(angle);
        rotMat = product(rotMat, yzRot);
    }else if(p == YW_PLANE){
        //YW Plane
        mat5 ywRot = createIdentityMatrix();
        ywRot[1][1] = cos(angle);
        ywRot[1][3] = -1.0f * sin(angle);
        ywRot[3][1] = sin(angle);
        ywRot[3][3] = cos(angle);
        rotMat = product(rotMat, ywRot);
    }else if(p == ZW_PLANE){
        //ZW Plane
        mat5 zwRot = createIdentityMatrix();
        zwRot[2][2] = cos(angle);
        zwRot[2][3] = -1.0f * sin(angle);
        zwRot[3][2] = sin(angle);
        zwRot[3][3] = cos(angle);
        rotMat = product(rotMat, zwRot);
    }
}

void Object::customColor(bool val){
    useColor = val;
}
void Object::setCustomColor(glm::vec4 *colorArray, int num){
    useColor = true;
    for(int i = 0; i<num; i++){
        for(int j = 0; j<4; j++){
            colors.push_back(colorArray[i][j]);
        }
    }
}

void Object::setUniformColor(glm::vec4 color){
    useColor = false;
    constColor = color;
}