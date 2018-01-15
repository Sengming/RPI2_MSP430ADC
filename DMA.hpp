/*
 * DMA.hpp
 *
 *  Created on: 12 Oct 2017
 *      Author: SengMing
 */

#ifndef DMA_HPP_
#define DMA_HPP_
#include <stdint.h>

// Forward Delcaration:
class DmaSource;

class DMA
{
public:
    DMA();
    virtual ~DMA();

    void attachToDma(volatile uint16_t& destination, uint8_t channel, DmaSource& source);
    void dmaEnable(uint16_t channel);
};

#endif /* DMA_HPP_ */
