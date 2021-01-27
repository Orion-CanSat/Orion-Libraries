#ifndef __ORION_UTILITIES_MEMORY_UNIQUE_PTR_H__
#define __ORION_UTILITIES_MEMORY_UNIQUE_PTR_H__

#include "weak_ptr.hpp"

namespace Orion
{
    namespace Utilities
    {
        namespace Memory
        {
            template<typename T>
            class unique_ptr : public weak_ptr<T>
            {
                public:
                    unique_ptr(T* ptr = nullptr)
                    {
                        this->_ptr = new T * (ptr);
                        this->_counter = new int32_t*(new int32_t(1));
                    }

                    unique_ptr(weak_ptr<T>& ptr)
                    {
                        this->_ptr = new T*(new T(*(*(ptr._ptr))));
                        this->_counter = new int32_t*(new int32_t(1));
                    }

                    unique_ptr(unique_ptr<T>& ptr)
                    {
                        this->_ptr = new T*(new T(*(*(ptr._ptr))));
                        delete *(ptr._ptr);
                        *(ptr._ptr) = nullptr;
                        *(*(ptr._ptr)) = 0;
                        this->_counter = new int32_t*(new int32_t(1));
                    }

                    unique_ptr(const unique_ptr<T>& ptr)
                    {
                        this->_ptr = new T*(new T(*(*(ptr._ptr))));
                        delete *(ptr._ptr);
                        *(ptr._ptr) = nullptr;
                        *(*(ptr._ptr)) = 0;
                        this->_counter = new int32_t*(new int32_t(1));
                    }

                    void reset(T* ptr = nullptr)
                    {
                        delete *(this->_ptr);

                        *(this->_ptr) = ptr;
                    }

                    bool operator==(const unique_ptr<T>& ptr) { return false; }


                    ~unique_ptr()
                    {
                        delete *(this->_ptr);
                        delete *(this->_counter);

                        delete this->_ptr;
                        delete this->_counter;
                    }
            };
        }
    }
}

#endif//__ORION_UTILITIES_MEMORY_UNIQUE_PTR_H__