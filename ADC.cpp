/*
 * ADC.cpp
 *
 *  Created on: 11 Oct 2017
 *      Author: SengMing
 */

#include "ADC.hpp"
#include <driverlib.h>
// Constructor
ADC::ADC() :m_dmaTriggerSource(DMA_TRIGGERSOURCE_26), m_dmaAddress(0), m_adcResult(0)
{
    ADC12_B_initParam initParam = {0};
       initParam.sampleHoldSignalSourceSelect = ADC12_B_SAMPLEHOLDSOURCE_SC;
       initParam.clockSourceSelect = ADC12_B_CLOCKSOURCE_ADC12OSC;
       initParam.clockSourceDivider = ADC12_B_CLOCKDIVIDER_1;
       initParam.clockSourcePredivider = ADC12_B_CLOCKPREDIVIDER__1;
       initParam.internalChannelMap = ADC12_B_NOINTCH;
       ADC12_B_init(ADC12_B_BASE, &initParam);

       //Enable the ADC12B module
       ADC12_B_enable(ADC12_B_BASE);

       /*
        * Base address of ADC12B Module
        * For memory buffers 0-7 sample/hold for 64 clock cycles
        * For memory buffers 8-15 sample/hold for 4 clock cycles (default)
        * Disable Multiple Sampling
        */
       ADC12_B_setupSamplingTimer(ADC12_B_BASE,
                                  ADC12_B_CYCLEHOLD_4_CYCLES,
                                  ADC12_B_CYCLEHOLD_4_CYCLES,
                                  ADC12_B_MULTIPLESAMPLESENABLE);

       //Configure Memory Buffer
       /*
        * Base address of the ADC12B Module
        * Configure memory buffer 0
        * Map input A1 to memory buffer 0
        * Vref+ = AVcc
        * Vref- = AVss
        * Memory buffer 0 is not the end of a sequence
        */
       ADC12_B_configureMemoryParam configureMemoryParam = {0};
       configureMemoryParam.memoryBufferControlIndex = ADC12_B_MEMORY_0;
       configureMemoryParam.inputSourceSelect = ADC12_B_INPUT_A3;
       configureMemoryParam.refVoltageSourceSelect =
           ADC12_B_VREFPOS_AVCC_VREFNEG_VSS;
       configureMemoryParam.endOfSequence = ADC12_B_NOTENDOFSEQUENCE;
       configureMemoryParam.windowComparatorSelect =
           ADC12_B_WINDOW_COMPARATOR_DISABLE;
       configureMemoryParam.differentialModeSelect =
           ADC12_B_DIFFERENTIAL_MODE_DISABLE;
       ADC12_B_configureMemory(ADC12_B_BASE, &configureMemoryParam);

//       //Enable memory buffer 0 interrupt
//       ADC12_B_enableInterrupt(ADC12_B_BASE,
//                               ADC12_B_IE0,
//                               0,
//                               0);

       // Configure for DMA
       m_dmaAddress = ADC12_B_getMemoryAddressForDMA(ADC12_B_BASE, ADC12_B_MEMORY_0);
}

// Destructor
ADC::~ADC()
{
    // Leave empty for now.
}

void ADC::startADC()
{
    ADC12_B_startConversion(ADC12_B_BASE,
                            ADC12_B_MEMORY_0,
                            ADC12_B_REPEATED_SINGLECHANNEL);
}


//#pragma vector=45
//__interrupt void adcInt()
//{
//    GPIO_toggleOutputOnPin(GPIO_PORT_P1, GPIO_PIN0);
//    DMA_startTransfer(DMA_CHANNEL_0);
//}
