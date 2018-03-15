#include <iostream>
#include <stdio.h>
#include <hil.h>

using namespace std;
using namespace Hardware;

int main()
{
    try
    {
        HIL card;
        card.open( "Q80", 0 );

        // Writes to the digital output channels
        unsigned int outputChannels[] = { 0, 1, 2, 3, 4, 5 };
        bool outputBuffer[]  = { 0, 1, 0, 1, 0, 1 };

        card.setDigitalOutputDirection( outputChannels, 6 );
        card.writeDigital( outputChannels, outputBuffer, 6 );

        printf("The voltages written are:\n");
        for ( int i = 0; i < 6; ++i )
        {
            printf("DIG[%d] : %d V\n", outputChannels[i], outputBuffer[i]);
        }


        // Reads from the digital input channels
        unsigned int inputChannels[] = { 6, 7, 8, 9, 10, 11 };
        bool inputBuffer[6];
        card.readDigital( inputChannels, inputBuffer, 6 );

        printf("The voltages read are:\n");
        for ( int i = 0; i < 6; ++i )
        {
            printf("DIG[%d] : %d V\n", inputChannels[i], inputBuffer[i]);
        }

        card.close();
    }
    catch( HILException& ex )
    {
        cout << "Exception occured: " << ex.what() << endl;
    }
    catch(...)
    {
        cout << "Unknown exception occured." << endl;
    }


    return 0;
}

