#ifndef __ORION_UTILITIES_MATH_MATRIX_H__
#define __ORION_UTILITIES_MATH_MATRIX_H__

#include "Orion.h"
#include "Orion/Utilities/Math/Vector.hpp"

#include <stdint.h>
#include <string.h>

namespace Orion
{
    namespace Utilities
    {
        namespace Math
        {
            template<typename T>
            struct Matrix
            {
                T** _matrix;
                uint16_t _rows;
                uint16_t _columns;
                bool _initialized = false;

                bool Initialize(uint16_t rows, uint16_t columns)
                {
                    if (_initialized) this->Free();
                    _matrix = (T**)malloc(rows * sizeof(T*));
                    if (!_matrix) return false;
                    uint16_t i;
                    for (i = 0; i < rows; i++)
                    {
                        _matrix[i] = (T*)malloc(columns * sizeof(T*));
                        if (!_matrix[i])
                        {
                            for (uint16_t j = 0; j < i; j++)
                                free(_matrix[j]);
                            free(_matrix);
                            return false;
                        }
                    }
                    _rows = rows;
                    _columns = columns;
                    _initialized = true;
                    return true;
                }

                void Free()
                {
                    if (_initialized) return;
                    for (uint16_t i = 0; i < _rows; i++)
                        free(_matrix[i]);
                    free(_matrix);
                    _initialized = false;
                }

                static bool Multiply(Matrix<T>& result, Matrix<T>& m1, Matrix<T>& m2)
                {
                    if (m1._columns != m2._rows) return false;
                    if ((!result._initialized) || result._rows != m1._rows || result._columns != m2._columns)
                    {
                        if (!result.Initialize(m1._rows, m2._columns)) return false;
                    }
                    for (uint16_t i = 0; i < m1._rows; i++)
                    {
                        for (uint16_t j = 0; j < m2._columns; j++)
                        {
                            result._matrix[i][j] = 0;
                            for (uint16_t k = 0; k < m1._columns; k++)
                                result._matrix[i][j] += m1._matrix[i][k] * m2._matrix[k][j];
                        }
                    }
                    return true;
                }
                static bool Multiply(Vector<T>& result, Matrix<T>& m, Vector<T>& v)
                {
                    if ((!m._initialized) || (!v._initialized) || (m._columns != v._size)) return false;
                    if ((!result._initialized) || result._size != v._size)
                    {
                        if (!result.Initialize(v._size)) return false;
                    }
                    for (uint16_t i = 0; i < m._rows; i++)
                    {
                        result._vector[i] = 0;
                        for (uint16_t j = 0; j < m._columns; j++)
                        {
                            result._vector[i] += m._matrix[i][j] * v._vector[j];
                        }
                    }
                    return true;
                }
            };
        }
    }
}

#endif//__ORION_UTILITIES_MATH_MATRIX_H__