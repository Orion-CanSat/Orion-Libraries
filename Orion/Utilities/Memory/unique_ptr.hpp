#ifndef __ORION_UTILITIES_MEMORY_UNIQUE_PTR_H__
#define __ORION_UTILITIES_MEMORY_UNIQUE_PTR_H__

#include "Orion.h"

namespace Orion
{
    namespace Utilities
    {
        namespace Memory
        {
            template<typename T>
            class unique_ptr
            {
            private:
                T* _var = nullptr;

            public:
                unique_ptr() { _var = NULL; }
                unique_ptr(T* ptr) { _var = ptr; }
                unique_ptr(const T* ptr) { _var = ptr; }
                unique_ptr(unique_ptr<T>&& ptr) { _var = ptr._var; ptr._var = nullptr; }
                unique_ptr(unique_ptr<T>& ptr) { _var = ptr._var; ptr._var = nullptr; }

                T* get() { return _var; }
                T* release() { return get(); }
                void reset(T* ptr = nullptr) { if (_var) delete _var; _var = ptr; }
                T& operator*() { return *_var; }
                T& operator->() { return *_var; }
                bool operator==(const unique_ptr<T>& ptr) { return _var == ptr._var; }

                ~unique_ptr() { if (_var) delete _var; }
            };
        }
    }
}

#endif//__ORION_UTILITIES_MEMORY_UNIQUE_PTR_H__