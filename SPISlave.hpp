/*
 * SPISlave.hpp
 *
 *  Created on: 16 Oct 2017
 *      Author: SengMing
 */

#ifndef SPISLAVE_HPP_
#define SPISLAVE_HPP_

typedef enum spiMode_e
{
    THREE_WIRE = 0,
    FOUR_WIRE,
    TOTAL_MODES
}spiMode;



class SPI_Slave
{
public:
    static SPI_Slave* allocateSPISlaveInstance(spiMode_e mode);
    static void deallocateSPISlaveInstance();
    void enable();

    virtual ~SPI_Slave();
private:
    SPI_Slave(spiMode_e mode);
    SPI_Slave() {}
    static SPI_Slave* s_spiInstance;
};

#endif /* SPISLAVE_HPP_ */
