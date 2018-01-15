/*
 * general.cpp
 *
 *  Created on: 11 Oct 2017
 *      Author: SengMing
 */
#include <General.hpp>
#include <driverlib.h>
#include "ADC.hpp"
#include "DMA.hpp"
#include "SPISlave.hpp"

extern "C" struct cExec {};

class cppExec : public cExec
{
public:
    void runExec()
    {
        ADC* adc0 = new ADC();
        DMA* dmaController = new DMA();
        SPI_Slave* spiSlave = spiSlave->allocateSPISlaveInstance(THREE_WIRE);
        spiSlave->enable();
        dmaController->attachToDma(adc0->m_adcResult, DMA_CHANNEL_0, *adc0);
        dmaController->dmaEnable(DMA_CHANNEL_0);
        PMM_unlockLPM5();

        __enable_interrupt();

        adc0->startADC();

        while (1);
    }
};



cExec* newExec()
{
    return new cppExec();
}
void deleteExec(cExec* exec)
{
    delete ((cppExec*)exec);
}
void runExec(cExec* exec)
{
    ((cppExec*)exec)->runExec();
}




