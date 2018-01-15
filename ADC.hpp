/*
 * ADC.hpp
 *
 *  Created on: 11 Oct 2017
 *      Author: SengMing
 */

#ifndef ADC_HPP_
#define ADC_HPP_
#include <stdint.h>
#include "DmaSource.hpp"
#include "General.hpp"

class ADC : public DmaSource
{
public:

    // Constructor
    ADC();
    // Destructor
    ~ADC();

    void startADC();

    virtual uint32_t getSourceAddress(){return m_dmaAddress;};
    virtual uint8_t getSourceTrigger(){return m_dmaTriggerSource;};



    uint16_t m_dmaTriggerSource;
    uint16_t m_dmaAddress;
    volatile uint16_t m_adcResult;

protected:
};



#endif /* ADC_HPP_ */
