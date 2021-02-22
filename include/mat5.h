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


class mat5{
public:
    vec5 rows[5];
    mat5();
    mat5(glm::vec4 a, glm::vec4 b, glm::vec4 c, glm::vec4 d, glm::vec4 e);
    mat5(vec5 a, vec5 b, vec5 c, vec5 d, vec5 e);

    vec5& operator[](int num){
        return rows[num];
    }
};

inline mat5::mat5(){
    vec5 z = vec5();
    mat5(z, z, z, z, z);
}


inline mat5::mat5(vec5 a, vec5 b, vec5 c, vec5 d, vec5 e){
    rows[0] = a;
    rows[1] = b;
    rows[2] = c;
    rows[3] = d;
    rows[4] = e;
}

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

inline void printMatrix(mat5 mat){
    for(int x = 0; x<5; x++){
        for(int y = 0; y<5; y++){
            printf("| %f |", mat[x][y]);
        }
        printf("\n -------------------------\n");
    }
}

#endif