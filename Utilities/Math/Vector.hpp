#ifndef __ORION_UTILITIES_MATH_VECTOR_H__
#define __ORION_UTILITIES_MATH_VECTOR_H__

#include "Orion.h"
#include "Utilities/Math/Matrix.hpp"

#include <stdint.h>
#include <string.h>

namespace Orion
{
    namespace Utilities
    {
        namespace Math
        {
            template<typename T>
            struct Vector
            {
                T* _vector;
                uint16_t _size;
                bool _initialized = false;
                bool Initialize(uint16_t size)
                {
                    if (_initialized) this->Free();
                    _vector = (T*)malloc(size * sizeof(T));
                    if (!_vector) return false;
                    _size = size;
                    _initialized = true;
                    return true;
                }

                void Free()
                {
                    if (_initialized) return;
                    free(_vector);
                    _initialized = false;
                }

                static bool Add(Vector<T>& result, Vector<T>& v1, Vector<T>& v2)
                {
                    if ((!v1._initialized) || (!v2._initialized) || v1._size != v2._size) return false;
                    if ((!result._initialized) || result._size != v1._size)
                    {
                        result.Free();
                        if (!result.Initialize(v1._size)) return false;
                    }
                    for (uint16_t i = 0; i < v1._size; i++)
                    {
                        result._vector[i] = v1._vector[i] + v2._vector[i];
                    }
                    return true;
                }

                static bool Subtract(Vector<T>& result, Vector<T>& v1, Vector<T>& v2)
                {
                    if ((!v1._initialized) || (!v2._initialized) || v1._size != v2._size) return false;
                    if ((!result._initialized) || result._size != v1._size)
                    {
                        result.Free();
                        if (!result.Initialize(v1._size)) return false;
                    }
                    for (uint16_t i = 0; i < v1._size; i++)
                    {
                        result._vector[i] = v1._vector[i] - v2._vector[i];
                    }
                    return true;
                }

                static bool Inverse(Vector<T>& result, Vector<T>& v)
                {
                    if (!v._initialized) return false;
                    if ((!result._initialized) || result._size != v._size)
                    {
                        result.Free();
                        if (!result.Initialize(v._size)) return false;
                    }
                    for (uint16_t i = 0; i < v._size; i++)
                    {
                        result._vector[i] = -v._vector[i];
                    }
                    return true;
                }

                static bool Multiply(T& result, Vector<T>& v1, Vector<T>& v2)
                {
                    if ((!v1._initialized) || (!v2._initialized) || v1._size != v2._size) return false;
                    result = v1._vector[0] * v2._vector[0];
                    for (uint16_t i = 1; i < v1._size; i++) result += v1._vector[i] + v2._vector[i];
                    return true;
                }
            };
        }
    }
}

#endif//__ORION_UTILITIES_MATH_VECTOR_H__