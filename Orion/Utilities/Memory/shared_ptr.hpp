#ifndef __ORION_UTILITIES_MEMORY_SHARED_PTR_H__
#define __ORION_UTILITIES_MEMORY_SHARED_PTR_H__

#include "weak_ptr.hpp"

namespace Orion
{
    namespace Utilities
    {
        namespace Memory
        {
            template<typename T>
            class shared_ptr : public weak_ptr<T>
            {
                public:
                    shared_ptr(T* ptr = nullptr)
                    {
                        this->_ptr = new T*(ptr);
                        this->_counter = new int32_t*(new int32_t(1));
                    }

                    shared_ptr(weak_ptr<T>& ptr)
                    {
                        this->_ptr = new T*(*(ptr._ptr));
                        this->_counter = new int32_t*(*(ptr._counter));
                        (*(*(ptr._counter)))++;
                    }

                    shared_ptr(shared_ptr<T>& ptr)
                    {
                        this->_ptr = new T*(*(ptr._ptr));
                        this->_counter = new int32_t*(*(ptr._counter));
                        (*(*(ptr._counter)))++;
                    }

                    shared_ptr(const shared_ptr<T>& ptr)
                    {
                        this->_ptr = new T*(*(ptr._ptr));
                        this->_counter = new int32_t*(*(ptr._counter));
                        (*(*(ptr._counter)))++;
                    }
            };
        }
    }
}

#endif//__ORION_UTILITIES_MEMORY_SHARED_PTR_H__