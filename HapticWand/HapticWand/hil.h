/*
 * LogVariable.h
 *
 *  Created on: Oct 10, 2014
 *      Author: Cuneyt AY
 */
#ifndef HIL_H
#define HIL_H

#include "HapticWand_global.h"
#include "q8Config.h"
#include "hilexception.h"

/**
 *
 * The primary class used for accessing hardware.
 *
 */

namespace Hardware
{
    class HAPTICWANDSHARED_EXPORT HIL {
    public:
        HIL();

        /**
         * Opens the specified card of the given type.
         *
         * @param cardType          A string identifying the type of card.
         * @param cardIdentifier    An integer identifying the particular
         *                          board among all the boards of the same type.
         *
         * @throws HILException     If the open cannot be performed then an exception is thrown.
         */
        virtual void open(const char* cardType = "Q80", const int cardIdentifier = 0);

        /**
         * Closes the card.
         *
         * @throws HILException     If the close cannot be performed then an exception is thrown.
         */
        virtual void close();

        //========================================================================
        //  ANALOG FUNCTIONS
        //========================================================================

        /**
         * Analog output may be configured for a ±10V, ±5V or 0-10V range.
         */
        enum AnalogRange
        {
            UNIPOLAR_10V = 0,   // ±10V
            BIPOLAR_5V = 1,     // ±5V
            BIPOLAR_10V = 2     // 0-10V
        };

        /**
         * Sets the ranges of the analog output.
         *
         * @param channelNumber     The analog output channel whose ranges will be configured.
         * @param range             The value of the output range. Each channel may be assigned
         *                          one of the three supported ranges.
         */
        void setAnalogOutputRange( const unsigned int channelNumber, AnalogRange range );

        /**
         * Reads the voltage value from the specified channel.
         *
         * @param channelNumber     The number of the analog input channel to be read.
         * @return                  The voltage value read from the analog input.
         */
        double readAnalog( const unsigned int channelNumber );

        /**
         * Reads the voltage values from the specified channel.
         *
         * @param channelNumbers        The numbers of the analog input channels to be read.
         * @param voltages              The voltage values read from the analog inputs.
         * @param channelNumbersLength  Length of channelNumbers array.
         */
        void readAnalog( const unsigned int* channelNumbers, double* voltages, const int channelNumbersLength);

        /**
         * Writes user defined voltage value to the specified analog channel.
         *
         * @param channelNumber     The number of the analog output channel to be written.
         * @param voltage           The voltage value to write to the analog output.
         */
        void writeAnalog( const unsigned int channelNumber, const double voltage );

        /**
         * Writes user defined voltage values to the specified analog channels.
         *
         * @param channelNumbers        The numbers of the analog output channels to be written.
         * @param voltages              The voltage values to write to the analog outputs.
         * @param channelNumbersLength  Length of channelNumbers array.
         */
        void writeAnalog( const unsigned int* channelNumbers, const double* voltages, const int channelNumbersLength );

        //========================================================================
        //  ENCODER FUNCTIONS
        //========================================================================

        /**
         * Enumerates the different encoder quadrature modes.
         *
         * The NONE mode configures an encoder input to interpret its signals as count and direction
         * rather than as quadrature A and B channels.
         * The _X1 mode configures an encoder input to interpret its signals as A and B channels but
         * without taking advantage of the multiple edges to improve the encoder line resolution.
         * The _X2 mode configures an encoder input to interpret its signals as A and B channels but
         * only takes advantage of some of the edges to yield double the encoder line resolution.
         * The _X4 mode configures an encoder input to interpret its signals as A and B channels and
         * takes full advantage of the multiple edges to yield four times the encoder line resolution.
         */
        enum Quadrature
        {
            NONE    = 0,
            _1X     = 1,
            _2X     = 2,
            _4X     = 3
        };

        /**
         * Enumerates the encoder count modes.
         */
        enum CounterMode
        {
            NORMAL  = 0,
            RANGE_LIMIT = 1,
            NON_RECYCLE = 2,
            MODULO_NCount   = 3
        };


        /**
         * Enumerates the encoder count representation.
         */
        enum CounterRepresentation
        {
            BINARY   = 0,
            BCD      = 1
        };

        /**
         * Enumerates the encoder index polarity.
         */
        enum IndexPolarity
        {
            POS = 0,
            NEG = 1
        };

        /**
         * Enumerates the encoder index.
         */
        enum IndexMode
        {
            ENABLE     = 0,
            DISABLE    = 1
        };

        /**
         * Configures the specified encoder input channel.
         *
         * @param channelNumber     The encoder input channels to be configured.
         * @param countMode         Count mode to use.
         * @param counterRepresentation     Bcd or binary counting.
         * @param quadrature        Quadrature  type selection.
         * @param indexMode         Enable or disable index feature.
         * @param indexPolarity     Select index polarity.
         */
        void encoderConfig( const unsigned int channelNumber, CounterMode countMode = NORMAL,
                            CounterRepresentation counterRepresentation = BINARY, Quadrature quadrature = _4X,
                            IndexMode indexMode = DISABLE, IndexPolarity indexPolarity = POS );

        /**
         * Reads from the specified encoder input channel.
         *
         * @param channelNumber     The number of the encoder input channel to be read.
         * @return                  The count value read from the encoder input.
         */
        int readEncoder( const unsigned int channelNumber );

        /**
         * Reads from the specified encoder input channels.
         *
         * @param channelNumbers        The numbers of the encoder input channels to be read.
         * @param counts                The count values read from the encoder inputs.
         * @param channelNumbersLength  Length of channelNumbers array.
         */
        void readEncoder( const unsigned int* channelNumbers, int* counts, const int channelNumbersLength  );

        /**
         * Resets the specified encoder channel.
         *
         * @param channelNumber     The encoder channel to be reset.
         */
        void resetEncoder( const unsigned int channelNumber );

        /**
         * Resets the specified encoder channel.
         *
         * @param channelNumber         The number of the encoder channels to be reset.
         * @param channelNumbersLength  Length of channelNumbers array.
         */
        void resetEncoder( const unsigned int* channelNumbers, const int channelNumbersLength );

        //========================================================================
        //  DIGITAL FUNCTIONS
        //========================================================================

        /**
         * Reads from digital input.
         *
         * @param channelNumber     The number of the digital input channel to be read.
         * @return                  The binary value read from the digital input.
         */
        bool readDigital( const unsigned int channelNumber );

        /**
         * Reads from digital inputs.
         *
         * @param inputChannels         The numbers of the digital input channels to be read.
         * @param bits                  The binary values read from the digital inputs
         * @param inputChannelsLength   Length of input channels array.
         */
        void readDigital( const unsigned int* inputChannels, bool* bits, const int inputChannelsLength);

        /**
         * Configures digital channels as outputs.
         *
         * @param outputChannels        The numbers of digital channels which will be configured as outputs.
         * @param outputChannelsLength  Length of output channels array.
         */
        void setDigitalOutputDirection( const unsigned int *outputChannels, const int outputChannelsLength );

        /**
         * Writes to the specified digital output channels.
         *
         * @param outputChannels        The numbers of the digital output channels to be written.
         * @param bits                  The binary values to write to the digital outputs.
         * @param outputChannelsLength  Length of output channels array.
         */
        void writeDigital( const unsigned int* outputChannels, const bool* bits, const int outputChannelsLength);

    private:

        //========================================================================
        //  DEVICE READ/WRITE FUNCTIONS
        //========================================================================

        /**
         * Reads the q8_config from the device.
         *
         * @throws HILException     If the read cannot be performed then an exception is thrown.
         */
        void read();

        /**
         * Writes the q8_config to the device.
         *
         * @throws HILException     If the write cannot be performed then an exception is thrown.
         */
        void write();

        /**
         * Communication struct.
         */
        struct_Q8_Config q8_config;

        /**
         * Device file descriptor as returned by rt_dev_open().
         */
        int fd;

        /**
         * The ranges of the analog outputs.
         */
        AnalogRange analogOutputRanges[8];
    };
}


#endif // HIL_H
