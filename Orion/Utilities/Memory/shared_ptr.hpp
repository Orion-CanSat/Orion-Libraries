#ifndef __ORION_UTILITIES_MEMORY_SHARED_PTR_H__
#define __ORION_UTILITIES_MEMORY_SHARE_PTR_H__

#include "Orion.h"

#include <stdint.h>

namespace Orion
{
    namespace Utilities
    {
        namespace Memory
        {
            template<typename T>
            class shared_ptr
            {
            private:
                T* _var = nullptr;
                uint32_t* _counter = nullptr;

            public:
                shared_ptr() { _var = (T*)NULL; _counter = new uint32_t(0); *_counter = 1; }
                shared_ptr(T* ptr) { _var = ptr; _counter = new uint32_t(0); *_counter = 1; }
                shared_ptr(const T* ptr) { _var = ptr; _counter = new uint32_t(0); *_counter = 1; }
                shared_ptr(shared_ptr<T>&& ptr) { _var = ptr._var; _counter = ptr._counter; (*_counter)++; }
                shared_ptr(shared_ptr<T>& ptr) { _var = ptr._var; _counter = ptr._counter; (*_counter)++; }

                T* get() { return _var; }
                T* release() { return get(); }
                void reset(T* ptr = nullptr)
                {
                    if (*_counter > 0)
                        (*_counter)--;
                    if (_var && *_counter == 0)
                        delete _var;
                }
                uint32_t use_count() { return *_counter; }
                T& operator*() { return *_var; }
                T& operator->() { return *_var; }
                bool operator==(const shared_ptr<T>& ptr) { return _var == ptr._var; }
                bool operator=(shared_ptr<T> ptr) const { _var = ptr._var; _counter = ptr._counter; return true; }
                bool operator=(shared_ptr<T>& ptr) { _var = ptr._var; _counter = ptr._counter; return true; }

                ~shared_ptr()
                {
                    if (*_counter > 0)
                        (*_counter)--;
                    if (_var && *_counter == 0)
                        delete _var;
                }
            };
        }
    }
}

#endif//__ORION_UTILITIES_MEMORY_SHARED_PTR_H__