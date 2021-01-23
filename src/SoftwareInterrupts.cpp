#include "Orion.h"
#include "Orion/Utilities/Interrupts/SoftwareInterrupts.hpp"
#include "Orion/Utilities/Memory/List.hpp"

using namespace Orion::Utilities;

class InterruptStruct
{
    public:
        int interruptNumber;
        void(*interruptCallback)(va_list);
};

bool isDisabled = true;
Memory::List<InterruptStruct> interrupts = Memory::List<InterruptStruct>(30);

static int GetInterruptCallback(int interruptNumber)
{
    uint32_t min = 0;
    uint32_t max = interrupts.GetSize();
    uint32_t pivot = (min + max) / 2;
    InterruptStruct ret;
    ret.interruptNumber = 0;
    ret.interruptCallback = NULL;
    while (max > min)
    {
        if (interrupts[pivot].interruptNumber > interruptNumber)
            max = pivot;
        else if (interrupts[pivot].interruptNumber < interruptNumber)
            min = pivot;
        else
            return pivot;
    }

    return -1;
}

static void InterruptListSorter()
{
    for (uint32_t i = interrupts.GetSize() - 1; i > 0; i--)
    {
        if (interrupts[i].interruptNumber < interrupts[i - 1].interruptNumber)
        {
            InterruptStruct temp = interrupts[i - 1];
            interrupts[i - 1] = interrupts[i];
            interrupts[i] = temp;
        }
        else
            break;
    }
}

void Interrupts::Interrupts::EnableInterrupts() { isDisabled = false; }
void Interrupts::Interrupts::DisableInterrupts() { isDisabled = true; }

void Interrupts::Interrupts::AddInterrupt(int interruptNumber, void(*interruptCallback)(va_list))
{
    InterruptStruct interrupt;
    interrupt.interruptNumber = interruptNumber;
    interrupt.interruptCallback = interruptCallback;
    int checkerIfExists = GetInterruptCallback(interruptNumber);
    if (checkerIfExists == -1)
        interrupts.Add(interrupt);
    else
        interrupts[checkerIfExists].interruptCallback = interruptCallback;
    InterruptListSorter();
}
