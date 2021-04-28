/**
 * @file camera.h
 * @author Nathan Medros
 * @brief Contains the class definition for the Camera class
 * @version 0.1
 * @date 2021-02-06
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef CAMERA_H
#define CAMERA_H

#include "object.h"


/**
 * @brief The Camera class, mostly used as a placeholder right now until custom cameras are implemented.
 * Its just an object with two other matrices
 * I will have to change that once I make them controllable.
 * 
 */
class Camera : public Object{
public:
    void create();
    glm::mat4 viewMat;
    glm::mat4 projMat;
};

#endif