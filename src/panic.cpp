#include <stdbool.h>

#include "Orion.h"


static _Bool _canPanic = 0;
void(*_panicFunctionCallback)(void) = NULL;


extern "C"
{
    void SetPanic(_Bool value)
    {
        _canPanic = value;
    }
    void SetPanicCallback(void(*panicFunctionCallback)(void))
    {
        _panicFunctionCallback = panicFunctionCallback;
    }
    void Panic()
    {
        if (_canPanic)
        {
            _panicFunctionCallback();
            while (1) ;
        }
    }
}