#include "hil.h"

using namespace Hardware;

#define DAC_BIPOLAR_ZERO   (0X0800)

/*
#define UNIPOLAR_10V        0
#define BIPOLAR_5V          1
#define BIPOLAR_10V         2
*/

HIL::HIL() : fd(-1)
{
    for( int i = 0; i < 8 ; ++i )
        analogOutputRanges[i] = BIPOLAR_10V;
}

void HIL::open(const char *cardType, const int cardIdentifier)
{
    q8_config.iCardNum = cardIdentifier;
    fd = rt_dev_open(cardType, O_RDWR);

    // If the open cannot be performed then an exception is thrown.
    if ( fd < 0 )
    {
        throw HILException( -fd );
    }
}

void HIL::close()
{
    int ret = rt_dev_close( fd );

    // If the close cannot be performed then an exception is thrown.
    if (ret < 0) {
        throw HILException( -ret );
    }

    fd = -1;
}

//========================================================================
//  ANALOG I/0 FUNCTIONS
//========================================================================

void HIL::setAnalogOutputRange(const unsigned int channelNumber, HIL::AnalogRange range)
{
    analogOutputRanges[channelNumber] = range;

    q8_config.ubDacMode = range;
    q8_config.iChannelNum = channelNumber;
    q8_config.uiFuncIndex = 30;

    write();
}

double HIL::readAnalog(const unsigned int channelNumber)
{
    q8_config.uiFuncIndex = channelNumber+8;
    read();

    return q8_config.wValueSigned * (10.0 / 8192);
}

void HIL::readAnalog(const unsigned int *channelNumbers, double *voltages, const int channelNumbersLength)
{
    for ( int i = 0; i < channelNumbersLength; ++i )
    {
        voltages[i] = readAnalog( channelNumbers[i] );
    }
}

void HIL::writeAnalog(const unsigned int channelNumber, const double voltage)
{
    q8_config.uiFuncIndex = channelNumber;

    if ( voltage <= 0 )
    {
        if( analogOutputRanges[channelNumber] == BIPOLAR_10V )
        {
            q8_config.uwValueUnsigned = ( DAC_BIPOLAR_ZERO - (uint16_t)((-voltage)*4096/20) );
        }
        else if( analogOutputRanges[channelNumber] == BIPOLAR_5V )
        {
            q8_config.uwValueUnsigned = ( DAC_BIPOLAR_ZERO - (uint16_t)((-voltage)*4096/10) );
        }
        else
        {
            // if the voltage is negative and the channel is configured as a 0-10V range (UNIPOLAR_10V),
            // do nothing
            return;
        }
    }
    else
    {
        if( analogOutputRanges[channelNumber] == BIPOLAR_10V )
        {
            q8_config.uwValueUnsigned = ( DAC_BIPOLAR_ZERO + (uint16_t)(voltage*4096/20) );
        }
        else if( analogOutputRanges[channelNumber] == BIPOLAR_5V )
        {
            q8_config.uwValueUnsigned = ( DAC_BIPOLAR_ZERO + (uint16_t)(voltage*4096/10) );
        }
        else if( analogOutputRanges[channelNumber] == UNIPOLAR_10V )
        {
            q8_config.uwValueUnsigned = (uint16_t)(voltage*4096/10);
        }
    }

    write();
}

void HIL::writeAnalog(const unsigned int *channelNumbers, const double *voltages, const int channelNumbersLength)
{
    for ( int i = 0; i < channelNumbersLength; ++i )
    {
        writeAnalog( channelNumbers[i], voltages[i] );
    }
}

//========================================================================
//  ENCODER FUNCTIONS
//========================================================================

void HIL::encoderConfig(const unsigned int channelNumber, HIL::CounterMode countMode,
                        HIL::CounterRepresentation counterRepresentation, HIL::Quadrature quadrature,
                        HIL::IndexMode indexMode, HIL::IndexPolarity indexPolarity)
{

    q8_config.uiFuncIndex = 29;
    q8_config.iChannelNum = channelNumber;
    q8_config.ubEcountMode = countMode;
    q8_config.ubEbcdMode = counterRepresentation;
    q8_config.ubEquadratureMode = quadrature;
    q8_config.ubIndexEnable = indexMode;
    q8_config.ubIndexPolarity = indexPolarity;

    write();
}

int HIL::readEncoder(const unsigned int channelNumber)
{
    q8_config.uiFuncIndex = channelNumber+16;
    read();

    return q8_config.dwNvalue;
}

void HIL::readEncoder(const unsigned int *channelNumbers, int *counts, const int channelNumbersLength)
{
    for ( int i = 0; i < channelNumbersLength; ++i )
    {
        counts[i] = readEncoder( channelNumbers[i] );
    }
}

void HIL::resetEncoder(const unsigned int channelNumber)
{
    q8_config.uiFuncIndex = channelNumber+31;
    write();
}

void HIL::resetEncoder(const unsigned int *channelNumbers, const int channelNumbersLength)
{
    for ( int i = 0; i < channelNumbersLength; ++i )
    {
        resetEncoder( channelNumbers[i] );
    }
}

//========================================================================
//  DIGITAL FUNCTIONS
//========================================================================

bool HIL::readDigital(const unsigned int channelNumber)
{
    uint32_t digitalInConstant = 0x00000001;
    uint32_t mask = (digitalInConstant << channelNumber);

    q8_config.uiFuncIndex = 25;
    q8_config.onlyDigitalData = -1;
    q8_config.udwDataDirection = mask;
    read();

    return q8_config.udwDataRegister & mask;
}

void HIL::readDigital(const unsigned int *inputChannels, bool *bits, const int inputChannelsLength)
{
    for ( int i = 0; i < inputChannelsLength; ++i )
    {
        bits[i] = readDigital( inputChannels[i] );
    }
}

void HIL::setDigitalOutputDirection(const unsigned int *outputChannels, const int outputChannelsLength)
{
    uint32_t digOutConstant = 0x00000001;
    uint32_t digOutChannelCurrent = 0x0;

    for ( int i = 0; i < outputChannelsLength; ++i )
    {
        digOutChannelCurrent |= (digOutConstant << outputChannels[i]);
    }

    q8_config.uiFuncIndex = 24;
    q8_config.onlyDigitalData = 0;
    q8_config.udwDataRegister = 0;
    q8_config.udwDataDirection = digOutChannelCurrent;

    write();
}

void HIL::writeDigital(const unsigned int *outputChannels, const bool *bits, const int outputChannelsLength)
{
    uint32_t digOutConstant = 0x00000001;
    uint32_t digOutChannelCurrent = 0x0;
    uint32_t digOutDataCurrent = 0x0;

    for ( int i = 0; i < outputChannelsLength; ++i )
    {
        digOutChannelCurrent |= (digOutConstant << outputChannels[i]);

        if ( bits[i] )
        {
            digOutDataCurrent |= (digOutConstant << outputChannels[i]);
        }
    }

    q8_config.uiFuncIndex = 24;
    q8_config.onlyDigitalData = -1;
    q8_config.udwDataRegister = digOutDataCurrent;
    q8_config.udwDataDirection = digOutChannelCurrent;

    write();
}

//========================================================================
//  DEVICE READ/WRITE FUNCTIONS
//========================================================================

void HIL::read()
{
    int ret = rt_dev_read(fd, &q8_config, sizeof(struct_Q8_Config));
    // If the read cannot be performed then an exception is thrown.
    if (ret < 0) {
        throw HILException( -ret );
    }
}

void HIL::write()
{
    int ret = rt_dev_write( fd, &q8_config, sizeof(struct_Q8_Config) );
    // If the write cannot be performed then an exception is thrown.
    if (ret < 0) {
        throw HILException( -ret );
    }
}

