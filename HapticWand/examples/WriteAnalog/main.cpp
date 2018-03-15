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


        printf("The voltages written are:\n");

        // write constant voltage to the first analog output channel
        float voltage = 4;
        card.writeAnalog( 0, voltage );
        printf("DAC[0] : %f V\n", voltage);

        // write constant voltages to the analog output channels
        const unsigned int analogChannels[] = { 1, 2, 3, 4, 5 };
        const double voltages[] = { 5, -5, 6, -6, 7 };
        card.writeAnalog( analogChannels, voltages, 5 );
        for ( int i = 0; i < 5; ++i )
        {
            printf("DAC[%d] : %f V\n", analogChannels[i], voltages[i]);
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

