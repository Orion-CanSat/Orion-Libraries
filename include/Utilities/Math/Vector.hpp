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
            template<typename T, uint32_t N>
            class Vector
            {
                private:
                    T _vec[N];

                public:
                    Vector() { memset(_vec, 0, N * sizeof(T)); }

                    Vector(T* arr, uint32_t len) { memset(_vec, 0, sizeof(T) * N); memcpy(_vec, arr, (len < N) ? len : N); }

                    Vector& operator=(const Vector& v)
                    {
                        for (uint32_t i = 0; i < N; i++)
                            _vec[i] = v._vec[i];
                        return *this;
                    }

                    T& operator[](uint32_t pos) { return _vec[pos]; }

                    T operator[](uint32_t pos) const { return _vec[pos]; }

                    T& operator()(uint32_t pos) { return _vec[pos]; }

                    T operator()(uint32_t pos) const { return _vec[pos]; }

                    Vector operator+(const Vector& v) const
                    {
                        Vector ret;
                        for (uint32_t i = 0; i < N; i++)
                            ret._vec[i] = _vec[i] + v._vec[i];
                        return ret;
                    }

                    Vector operator-(const Vector& v) const
                    {
                        Vector ret;
                        for (uint32_t i = 0; i < N; i++)
                            ret._vec[i] = _vec[i] - v._vec[i];
                        return ret;
                    }

                    Vector operator*(T val)
                    {
                        Vector ret;
                        for (uint32_t i = 0; i < N; i++)
                            ret._vec[i] = _vec[i] * val;
                        return ret;
                    }

                    T operator*(const Vector& v)
                    {
                        T ret = _vec[0] * v._vec[0];
                        for (uint32_t i = 1; i < N; i++)
                            ret += _vec[i] * v._vec[i];
                        return ret;
                    }

                    Vector operator/(T val)
                    {
                        Vector ret;
                        for (uint32_t i = 0; i < N; i++)
                            ret._vec[i] = _vec[i] / val;
                        return ret;
                    }
            };
        }
    }
}

#endif//__ORION_UTILITIES_MATH_VECTOR_H__