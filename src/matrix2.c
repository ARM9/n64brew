#include "matrix2.h"

inline void mat2Set(Mat2 *mat, fixed n11, fixed n12, fixed n21, fixed n22){
	mat->n11 = n11; mat->n12 = n12;
	mat->n21 = n21; mat->n22 = n22;
}

inline void mat2Copy(Mat2 *dest, Mat2 *src){
	dest->n11 = src->n11; dest->n12 = src->n12;
	dest->n21 = src->n21; dest->n22 = src->n22;
}

inline void mat2Identity(Mat2 *a){
	a->n11 = 1; a->n12 = 0;
	a->n21 = 0; a->n22 = 1;
}

inline fixed mat2Det(Mat2 *a){
    return fixmul(a->n11, a->n22) - fixmul(a->n12, a->n21);
}

inline void mat2Add(Mat2 *dest, Mat2 *a, Mat2 *b){
	dest->n11 = a->n11 + b->n11; dest->n12 = a->n12 + b->n12;
	dest->n21 = a->n21 + b->n21; dest->n22 = a->n22 + b->n22;
}

inline void mat2Sub(Mat2 *dest, Mat2 *a, Mat2 *b){
	dest->n11 = a->n11 - b->n11; dest->n12 = a->n12 - b->n12;
	dest->n21 = a->n21 - b->n21; dest->n22 = a->n22 - b->n22;
}

inline void mat2Mult(Mat2 *dest, Mat2 *a, Mat2 *b){
	Mat2 t;
	t.n11 = fixmul(a->n11, b->n11) + fixmul(a->n12, b->n21);
	t.n12 = fixmul(a->n11, b->n12) + fixmul(a->n12, b->n22);
	t.n21 = fixmul(a->n21, b->n11) + fixmul(a->n22, b->n21);
	t.n22 = fixmul(a->n21, b->n12) + fixmul(a->n22, b->n22);
    mat2Set(dest, t.n11, t.n12, t.n21, t.n22);
}

inline void mat2Rotate(Mat2 *dest, fixed angle){
    Mat2 t;
    t.n11 = t.n22 = isin(angle+0x2000);
    t.n12 = -(t.n21 = isin(angle));
    mat2Set(dest, t.n11, t.n12, t.n21, t.n22);
}

