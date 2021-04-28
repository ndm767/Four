/**
 * @file vec5.h
 * @author Nathan Medros
 * @brief Class and functions for the vec5 (5d vector) data type.
 * @version 0.1
 * @date 2021-02-06
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef VECFIVE_H
#define VECFIVE_H

#include <glm/gtc/matrix_transform.hpp>
#include <stdio.h>

/**
 * @brief 5d vector class
 * 
 */
class vec5{
public:
    vec5();
    vec5(float a, float b, float c, float d, float e);
    vec5(glm::vec4 a, float b);
    float val[5];
    float& operator[](int num){
        return val[num];
    }
};

/**
 * @brief Construct a new empty vec5 object
 * 
 */
inline vec5::vec5(){
    val[0] = 0.0f;
    val[1] = 0.0f;
    val[2] = 0.0f;
    val[3] = 0.0f;
    val[4] = 0.0f;
}
/**
 * @brief Construct a new vec5 object from 5 floats
 * 
 * @param a 
 * @param b 
 * @param c 
 * @param d 
 * @param e 
 */
inline vec5::vec5(float a, float b, float c, float d, float e){
    val[0] = a;
    val[1] = b;
    val[2] = c;
    val[3] = d;
    val[4] = e;
}
/**
 * @brief Construct a new vec5 object from a glm::vec4 and a float
 * 
 * @param a 
 * @param b 
 */
inline vec5::vec5(glm::vec4 a, float b){
    vec5(a.x, a.y, a.z, a.w, b);
}
/**
 * @brief Dot product of two 5d vectors
 * 
 * @param a first vector
 * @param b second vector
 * @return float 
 */
inline float dot(vec5 a, vec5 b){
    float ret = 0.0f;
    ret += a[0] * b[0];
    ret += a[1] * b[1];
    ret += a[2] * b[2];
    ret += a[3] * b[3];
    ret += a[4] * b[4];
    return ret;
}
/**
 * @brief Prints vector for debugging purposes
 *
 * @param a vector to be printed.
 */
inline void printVec(vec5 a){
    printf("[%f, %f, %f, %f, %f]\n", a[0], a[1], a[2], a[3], a[4]);
}

#endif