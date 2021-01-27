#ifndef __ORION_UTILITIES_MEMORY_WEAK_PTR_H__
#define __ORION_UTILITIES_MEMORY_WEAK_PTR_H__

#include "Orion.h"

#include <stdint.h>

namespace Orion
{
    namespace Utilities
    {
        namespace Memory
        {
            template<typename T>
            class weak_ptr
            {
                protected:
                    T** _ptr = nullptr;
                    int32_t** _counter = nullptr;

                public:
                    weak_ptr(T* ptr = nullptr)
                    {
                        this->_ptr = new T * (ptr);
                        this->_counter = new int32_t * (new int32_t(1));
                    }

                    weak_ptr(weak_ptr<T>& ptr)
                    {
                        this->_ptr = new T * (*(ptr._ptr));
                        this->_counter = new int32_t * (*(ptr._counter));
                        (*(*(ptr._counter)))++;
                    }

                    weak_ptr(const weak_ptr<T>& ptr)
                    {
                        this->_ptr = new T * (*(ptr._ptr));
                        this->_counter = new int32_t * (*(ptr._counter));
                        (*(*(ptr._counter)))++;
                    }


                    T* get()
                    {
                        return (this->_ptr) ? *(this->_ptr) : nullptr;
                    }

                    T* release()
                    {
                        return get();
                    }

                    virtual void reset(T* ptr = nullptr)
                    {
                        if (this->_ptr && *(this->_ptr))
                        {
                            if (--(*(*(this->_counter))) == 0)
                            {
                                delete (*(this->_ptr));
                                delete (*(this->_counter));
                            }
                            delete this->_ptr;
                            delete this->_counter;
                        }

                        this->_ptr = new T * (ptr);
                        this->_counter = new int32_t * (new int32_t(1));
                    }

                    int32_t use_count()
                    {
                        return (this->_counter && *(this->_counter)) ? *(*(this->_counter)) : -1;
                    }

                    bool expired()
                    {
                        return this->get() == nullptr;
                    }

                    T& operator*()
                    {
                        return (this->_ptr && *(this->_ptr)) ? *(*(this->_ptr)) : *((T*)NULL);
                    }

                    T& operator->()
                    {
                        return (this->_ptr && *(this->_ptr)) ? *(*(this->_ptr)) : *((T*)NULL);
                    }

                    virtual bool operator==(const weak_ptr<T>& ptr)
                    {
                        return (this->_ptr && ptr._ptr && *(this->_ptr) && *(ptr._ptr) && *(this->_ptr) == *(ptr._ptr));
                    }

                    ~weak_ptr()
                    {
                        if (this->_ptr && *(this->_ptr))
                        {
                            if (--(*(*(this->_counter))) == 0)
                            {
                                delete (*(this->_ptr));
                                delete (*(this->_counter));
                            }
                            delete this->_ptr;
                            delete this->_counter;
                        }
                    }
            };
        }
    }
}

#endif//__ORION_UTILITIES_MEMORY_WEAK_PTR_H__