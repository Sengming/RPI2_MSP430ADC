/*
 * SPISlave.cpp
 *
 *  Created on: 16 Oct 2017
 *      Author: SengMing
 */

#include <SPISlave.hpp>
#include <driverlib.h>
#include <stdio.h>

SPI_Slave::SPI_Slave(spiMode_e mode)
{
    EUSCI_A_SPI_initSlaveParam initParams = {0};
    if (mode == THREE_WIRE)
    {
        initParams.spiMode = EUSCI_A_SPI_3PIN;
    }
    else if (mode == FOUR_WIRE)
    {
        initParams.spiMode = EUSCI_A_SPI_4PIN_UCxSTE_ACTIVE_LOW;
    }

    // Clock phase and polarity settings:
    initParams.clockPhase = EUSCI_A_SPI_PHASE_DATA_CHANGED_ONFIRST_CAPTURED_ON_NEXT;
    initParams.clockPolarity = EUSCI_A_SPI_CLOCKPOLARITY_INACTIVITY_LOW;

    // Clock out the MSB first
    initParams.msbFirst = EUSCI_A_SPI_MSB_FIRST;
    __disable_interrupt();
    EUSCI_A_SPI_initSlave(EUSCI_A0_BASE, &initParams);

    GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P2, GPIO_PIN0, GPIO_PRIMARY_MODULE_FUNCTION);
    GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P2, GPIO_PIN2, GPIO_PRIMARY_MODULE_FUNCTION);
    GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P2, GPIO_PIN1, GPIO_PRIMARY_MODULE_FUNCTION);
    __enable_interrupt();
}

SPI_Slave::~SPI_Slave()
{
    EUSCI_A_SPI_disable(EUSCI_A0_BASE);
    EUSCI_A_SPI_disableInterrupt(EUSCI_A0_BASE, EUSCI_A_SPI_RECEIVE_INTERRUPT);
    EUSCI_A_SPI_enableInterrupt(EUSCI_A0_BASE, EUSCI_A_SPI_TRANSMIT_INTERRUPT);
}

void SPI_Slave::enable()
{
    __disable_interrupt();
    EUSCI_A_SPI_enable(EUSCI_A0_BASE);
    EUSCI_A_SPI_enableInterrupt(EUSCI_A0_BASE, EUSCI_A_SPI_RECEIVE_INTERRUPT);
    EUSCI_A_SPI_enableInterrupt(EUSCI_A0_BASE, EUSCI_A_SPI_TRANSMIT_INTERRUPT);
    __enable_interrupt();
}

SPI_Slave* SPI_Slave::s_spiInstance = NULL;

SPI_Slave* SPI_Slave::allocateSPISlaveInstance(spiMode_e mode)
{
    SPI_Slave* retVal = NULL;
    if (s_spiInstance == NULL)
    {
        retVal = new SPI_Slave(mode);
        s_spiInstance = retVal;
    }
    else
    {
        retVal = s_spiInstance;
    }
    return retVal;
}

void SPI_Slave::deallocateSPISlaveInstance()
{
    delete s_spiInstance;
    s_spiInstance = NULL;
}

#pragma vector=USCI_A0_VECTOR
__interrupt void spiReceive()
{
    __disable_interrupt();
    EUSCI_A_SPI_transmitData(EUSCI_A0_BASE, 0x0F);
    GPIO_toggleOutputOnPin(GPIO_PORT_P1, GPIO_PIN0);
    __enable_interrupt();
}
