//
//  matrix.h
//  RayTracing
//
//  Created by Ming Yao on 15/10/26.
//

#ifndef MATRIX_H
#define MATRIX_H
#include "../util.h"
#include <cstring>
#include <cassert>

namespace MyMath {
    // a template matrix class
    // row first, column second
    template <typename T>
    class Matrix {
    public:
        // data fields
        T **data;
        int length[2];
        // length[0] - row length
        // length[1] - column length
    public:
        Matrix(int w=100, int h=100) : length{w,h} {
            allocate();
        }

        Matrix(T** v, int w, int h) : length{ w, h } {
            allocate();
            copy(v);
        }

        ~Matrix() {
            free();
        }

        Matrix(const Matrix& m) {
            length[0] = m.length[0];
            length[1] = m.length[1];
            allocate();
            copy(m.data);
        }

        Matrix & operator = (const Matrix & m) {
            if (this != &m) {
                length[0] = m.length[0];
                length[1] = m.length[1];
                allocate();
                copy(m.data);
            }
            return *this;
        }

        Matrix & operator = (Matrix && r) {
            assert(this != &r);
            this->free();
            this->data = r.data;
            length[0] = r.length[0];
            length[1] = r.length[1];
            r.data = nullptr;
            return *this;
        }

        Matrix(Matrix&& r) {
            data = r.data;
            length[0] = r.length[0];
            length[1] = r.length[1];
            r.data = nullptr;
        }

        // get the ith row
        T*& operator [] (int i) {
            assert((0 <= i) && (i <= length[1]));
            return data[i];
        }

        const T*& operator [] (int i) const {
            assert((0 <= i) && (i <= length[1]));
            return data[i];
        }

        // get the element at the ith row, the jth column
        T & operator () (int i, int j) {
            assert((0 <= i) && (i <= length[1]));
            assert((0 <= j) && (j <= length[0]));
            return data[i][j];
        }
        const T & operator () (int i, int j) const {
            assert((0 <= i) && (i <= length[1]));
            assert((0 <= j) && (j <= length[0]));
            return data[i][j];
        }

    protected:
        void free() {
             if (data != nullptr)
                 for (int i = 0; i < length[1]; i++)
                     delete[] data[i];
             delete[] data;
        }
        
        void allocate() {
            data = new T*[length[1]];
            for (int i = 0; i < length[1]; i++)
                data[i] = new T[length[0]]();
        }

        void copy(T** v) {
            if (!v) return;
            int rowlen = length[0] * sizeof(T);
            for (int i = 0; i < length[1]; i++) {
                memcpy(data[i], v[i], rowlen);
            }
        }

    };

}
#endif