#ifndef __ORION_UTILITIES_IO_IO_H__
#define __ORION_UTILITIES_IO_IO_H__

#include "Orion/Orion.hpp"

#include <stdint.h>

namespace Orion
{
    namespace Utilities
    {
        namespace IO
        {
            class IO {
                protected:
                    uint8_t* _buffer = (uint8_t*)NULL;
                    uint16_t _sizeOfBuffer;
                    uint16_t _bytesWritten = 0;

                    /**
                     * @brief Checks if buffer needs flushing and flushes it
                     * 
                     */
                    void FlushIfNecessary();


                    /**
                     * @brief Create a Buffer object
                     * 
                     * @param size Number of bytes to be in the buffer
                     * @return true If buffer creation succesffuly
                     * @return false If buffer creation failed
                     */
                    bool CreateBuffer(uint32_t size);

                public:
                    /**
                     * @brief Initialize the IO Class
                     */
                    IO();

                    /**
                     * @brief Construct a new IO object with a specified buffer size
                     * 
                     * @param size Size of the buffer to be created
                     */
                    IO(uint32_t size);

                    
                    /**
                     * @brief Flush Buffer
                     * Flush all the data to the desired output
                     * and zero out the buffer
                     */
                    virtual void Flush();

                    
                    /**
                     * @brief Append data to buffer
                     * 
                     * @param val Data to append in the buffer
                     * @return IO& Return IO class it's self
                     */
                    IO& operator<<(bool val);

                    /**
                     * @brief Append data to buffer
                     * 
                     * @param val Data to append in the buffer
                     * @return IO& Return IO class it's self
                     */
                    IO& operator<<(int8_t val);

                    /**
                     * @brief Append data to buffer
                     * 
                     * @param val Data to append in the buffer
                     * @return IO& Return IO class it's self
                     */
                    IO& operator<<(uint8_t val);

                    /**
                     * @brief Append data to buffer
                     * 
                     * @param val Data to append in the buffer
                     * @return IO& Return IO class it's self
                     */
                    IO& operator<<(int16_t val);

                    /**
                     * @brief Append data to buffer
                     * 
                     * @param val Data to append in the buffer
                     * @return IO& Return IO class it's self
                     */
                    IO& operator<<(uint16_t val);

                    /**
                     * @brief Append data to buffer
                     * 
                     * @param val Data to append in the buffer
                     * @return IO& Return IO class it's self
                     */
                    IO& operator<<(int32_t val);

                    /**
                     * @brief Append data to buffer
                     * 
                     * @param val Data to append in the buffer
                     * @return IO& Return IO class it's self
                     */
                    IO& operator<<(uint32_t val);

                    /**
                     * @brief Append data to buffer
                     * 
                     * @param val Data to append in the buffer
                     * @return IO& Return IO class it's self
                     */
                    IO& operator<<(int64_t val);

                    /**
                     * @brief Append data to buffer
                     * 
                     * @param val Data to append in the buffer
                     * @return IO& Return IO class it's self
                     */
                    IO& operator<<(uint64_t val);

                    /**
                     * @brief Append data to buffer
                     * 
                     * @param val Data to append in the buffer
                     * @return IO& Return IO class it's self
                     */
                    IO& operator<<(float val);

                    /**
                     * @brief Append data to buffer
                     * 
                     * @param val Data to append in the buffer
                     * @return IO& Return IO class it's self
                     */
                    IO& operator<<(double val);

                    /**
                     * @brief Append data to buffer
                     * 
                     * @param val Data to append in the buffer
                     * @return IO& Return IO class it's self
                     */
                    IO& operator<<(const char* val);

                    ~IO();
            };
        }
    }
}

#endif//__ORION_UTILITIES_IO_IO_H__