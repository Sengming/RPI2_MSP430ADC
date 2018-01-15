/*
 * DMA.cpp
 *
 *  Created on: 12 Oct 2017
 *      Author: SengMing
 */

#include <DMA.hpp>
#include <DmaSource.hpp>
#include <driverlib.h>

DMA::DMA()
{

}

DMA::~DMA()
{
    // TODO Auto-generated destructor stub
}

void DMA::attachToDma(volatile uint16_t& destination, uint8_t channel, DmaSource& source)
{
    DMA_initParam initializationParams = {0};
    initializationParams.channelSelect = channel;
    initializationParams.transferModeSelect = DMA_TRANSFER_REPEATED_SINGLE;
    initializationParams.transferSize = 1;
    initializationParams.transferUnitSelect = DMA_SIZE_SRCWORD_DSTWORD;
    initializationParams.triggerSourceSelect = source.getSourceTrigger();
    initializationParams.triggerTypeSelect = DMA_TRIGGER_RISINGEDGE;

    // Reset by disabling transfers before reinitializing
    DMA_disableTransfers(channel);
    DMA_init(&initializationParams);
    DMA_setSrcAddress(channel, source.getSourceAddress(), DMA_DIRECTION_UNCHANGED);
    DMA_setDstAddress(channel, (uint32_t)(&destination), DMA_DIRECTION_UNCHANGED);

}

void DMA::dmaEnable(uint16_t channel)
{
    DMA_enableTransfers(channel);
    DMA_enableInterrupt(channel);
}
