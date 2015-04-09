#ifndef MATRIX2_H
#define MATRIX2_H

#include "numbers.h"

typedef struct Mat2 {
    fixed n11, n12,
          n21, n22;
} Mat2;

void mat2Set(Mat2 *mat, fixed n11, fixed n12, fixed n21, fixed n22);
void mat2Copy(Mat2 *dest, Mat2 *src);
void mat2Identity(Mat2 *a);
fixed mat2Det(Mat2 *a);
void mat2Add(Mat2 *dest, Mat2 *a, Mat2 *b);
void mat2Sub(Mat2 *dest, Mat2 *a, Mat2 *b);
void mat2Mult(Mat2 *dest, Mat2 *a, Mat2 *b);
void mat2Rotate(Mat2 *dest, fixed angle);

#endif //MATRIX2_H
