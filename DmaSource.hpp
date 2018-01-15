/*
 * DmaSource.hpp
 *
 *  Created on: 12 Oct 2017
 *      Author: SengMing
 */

#ifndef DMASOURCE_HPP_
#define DMASOURCE_HPP_
#include <stdint.h>

class DmaSource
{
public:
    DmaSource();
    virtual ~DmaSource() = 0;

    virtual uint32_t getSourceAddress() = 0;
    virtual uint8_t getSourceTrigger() = 0;
};

#endif /* DMASOURCE_HPP_ */
