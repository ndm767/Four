/**
 * @file mat5.h
 * @author Nathan Medros
 * @brief Class and functions for the mat5 (5d matrix) data type
 * @version 0.1
 * @date 2021-02-06
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef MATFIVE_H
#define MATFIVE_H

#include "vec5.h"
#include <stdio.h>

/**
 * @brief 5d matrix class
 * 
 */
class mat5{
public:
    vec5 rows[5];
    mat5();
    mat5(glm::vec4 a, glm::vec4 b, glm::vec4 c, glm::vec4 d, glm::vec4 e);
    mat5(vec5 a, vec5 b, vec5 c, vec5 d, vec5 e);
    /**
     * @brief allows access to the rows of the matrix as if it was an array
     * 
     * @param num 
     * @return vec5& 
     */
    vec5& operator[](int num){
        return rows[num];
    }
};
/**
 * @brief Construct a new empty mat5 object
 * 
 */
inline mat5::mat5(){
    vec5 z = vec5();
    mat5(z, z, z, z, z);
}

/**
 * @brief Construct a new mat5 object from 5 vectors
 *
 * @param a first row
 * @param b second row
 * @param c third row
 * @param d fourth row
 * @param e fifth row
 */
inline mat5::mat5(vec5 a, vec5 b, vec5 c, vec5 d, vec5 e){
    rows[0] = a;
    rows[1] = b;
    rows[2] = c;
    rows[3] = d;
    rows[4] = e;
}

/**
 * @brief Create a 5d identity matrix (matrix with all 0's except for 1's on the diagonal)
 * 
 * @return mat5 
 */
inline mat5 createIdentityMatrix(){
    //matrix with all zeroes
    mat5 ret = mat5();
    //make the diagonals 1
    ret[0][0] = 1.0f;
    ret[1][1] = 1.0f;
    ret[2][2] = 1.0f;
    ret[3][3] = 1.0f;
    ret[4][4] = 1.0f;
    return ret;
}

/**
 * @brief Gives the product of two 5d matrices
 *
 * @param a the first matrix to be multiplied
 * @param b the second matrix to be multiplied
 * @return mat5 
 */
inline mat5 product(mat5 a, mat5 b){
    /*
    in 2x2:
    [a b] [1 2] = (ab * 13) (ab * 24)
    [c d] [3 4] = (cd * 13) (cd * 24)
    */
   //step 1, convert a from col-major to row major
   //step 2, dot products
   //step 3 assemble
   mat5 ret = mat5();
   mat5 transMat = mat5();
   for(int x= 0; x<5; x++){
       for(int y = 0; y<5; y++){
           transMat[x][y] = b[y][x];
       }
   }
   for(int i = 0; i<5; i++){
       for(int j = 0; j<5; j++){
           ret[i][j] = dot(a[i], transMat[j]);
       }
   }

   return ret;
}

/**
 * @brief Gives the product of a 5d matrix and 5d vector
 *
 * @param a the matrix to be multiplied
 * @param b the vector to be multiplied
 * @return vec5 
 */

inline vec5 product(mat5 a, vec5 b){
    vec5 ret = vec5();

    for(int x = 0; x<5; x++){
        ret[x] += a[x][0]*b[0];
        ret[x] += a[x][1]*b[1];
        ret[x] += a[x][2]*b[2];
        ret[x] += a[x][3]*b[3];
        ret[x] += a[x][4]*b[4];
    }

    return ret;
}

/**
 * @brief prints a mat5 for debugging purposes
 *
 * @param mat the matrix to be printed
 */
inline void printMatrix(mat5 mat){
    for(int x = 0; x<5; x++){
        for(int y = 0; y<5; y++){
            printf("| %f |", mat[x][y]);
        }
        printf("\n -------------------------\n");
    }
}

#endif