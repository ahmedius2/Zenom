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
        card.openDevice( "/dev/q8_hil_card", 0 );

        // Writes to the digital output channels

        unsigned int outputChannels[] ={0,1,2,3,4,5, 6, 7, 8, 9, 10, 11,12,13,14
                                        ,15,16,17,18,19,20,21,22,23,24,25,26,27
                                        ,28,29,30,31};
        bool outputBuffer[32]  = { 0,0,0,0,0,0,0,0,0,0,0,
                                   0,0,0,0,0,0,0,0,0,0,0,
                                   0,0,0,0,0,0,0,0,0,0};

        card.setDigitalOutputDirection( outputChannels, 32 );
        card.writeDigital( outputChannels, outputBuffer, 32 );
        printf("Wrote 0 to all channels\n");

        //printf("The voltages written are:\n");
        //for ( int i = 0; i < 32; ++i )
        //{
        //    printf("DIG[%d] : %d V\n", outputChannels[i], outputBuffer[i]);
        //}



        // Reads from the digital input channels
        unsigned int inputChannels[] = {0,1,2,3,4,5, 6, 7, 8, 9, 10, 11,12,13,14
                                        ,15,16,17,18,19,20,21,22,23,24,25,26,27
                                        ,28,29,30,31};
        bool inputBuffer[32];
        card.readDigital( inputChannels, inputBuffer, 32 );

        printf("The voltages read are:\n");
        for ( int i = 0; i < 32; ++i )
        {
            printf("DIG[%d] : %d V\n", inputChannels[i], inputBuffer[i]);
        }



        bool outputBuffer2[32]  = { 1,1,1,1,1,1,1,1,1,1,1,
                                   1,1,1,1,1,1,1,1,1,1,1,
                                   1,1,1,1,1,1,1,1,1,1};

        card.setDigitalOutputDirection( outputChannels, 32 );
        card.writeDigital( outputChannels, outputBuffer2, 32 );
        printf("Wrote 1 to all channels\n");

        card.readDigital( inputChannels, inputBuffer, 32 );

        printf("The voltages read are:\n");
        for ( int i = 0; i < 32; ++i )
        {
            printf("DIG[%d] : %d V\n", inputChannels[i], inputBuffer[i]);
        }

        card.closeDevice();
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

