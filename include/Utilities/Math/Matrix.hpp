#ifndef __ORION_UTILITIES_MATH_MATRIX_H__
#define __ORION_UTILITIES_MATH_MATRIX_H__

#include "Orion.h"
#include "Utilities/Math/Vector.hpp"

#include <stdint.h>
#include <string.h>

namespace Orion
{
    namespace Utilities
    {
        namespace Math
        {
            template<typename T, uint32_t N, uint32_t M>
            class Matrix
            {
                private:
                    T _mat[N * M];

                public:
                    Matrix() { memset(_mat, 0, M * N * sizeof(T)); }

                    Matrix(T* arr, uint32_t len) { memset(_mat, 0, M * N * sizeof(T)); memcpy(_mat, arr, (len < N * M) ? len : N * M); }

                    T cell(uint32_t i, uint32_t j) const { return _mat[ i * N + j]; }
                    T& cell(uint32_t i, uint32_t j) { return _mat[i * N + j]; }

                    Vector<T, N> rowToVector(uint32_t i) const
                    {
                        Vector<T, N> ret;
                        for (uint32_t j = 0; j < N; j++)
                            ret[i] = cell(i, j);
                        return ret;
                    }

                    Vector<T, N> colToVector(uint32_t j) const
                    {
                        Vector<T, M> ret;
                        for (uint32_t i = 0; i < M; i++)
                            ret[i] = cell(i, j);
                        return ret;
                    }
                    
                    Matrix& operator=(const Matrix& m)
                    {
                        for (uint32_t i = 0; i < N * M; i++)
                            _mat[i] = m._mat[i];
                        return *this;
                    }

                    T& operator()(uint32_t i, uint32_t j) { return cell(i, j); }

                    T operator()(uint32_t i, uint32_t j) const { return cell(i, j); }

                    Matrix operator+(const Matrix& m) const
                    {
                        Matrix ret;
                        for (uint32_t i = 0; i < N * M; i++)
                            ret._mat[i] = _mat[i] + m._mat[i];
                        return ret;
                    }
                
                    Matrix operator-(const Matrix& m) const
                    {
                        Matrix ret;
                        for (uint32_t i = 0; i < N * M; i++)
                            ret._mat[i] = _mat[i] - m._mat[i];
                        return ret;
                    }

                    Matrix operator*(T val)
                    {
                        Matrix ret;
                        for (uint32_t i = 0; i < N * M; i++)
                            ret._mat[i] = _mat[i] * val;
                        return ret;
                    }

                    Matrix operator*(const Matrix& m) const
                    {
                        Matrix ret;
                        for (uint32_t i = 0; i < N; i++)
                        {
                            Vector<T, N> row = rowToVector(i);
                            for (uint32_t j = 0; j < M; i++)
                                ret(i, j) = row *  colToVector(j);
                        }
                        return ret;
                    }
            };
        }
    }
}

#endif//__ORION_UTILITIES_MATH_MATRIX_H__