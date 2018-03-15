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

        // read one analog channel
        float voltage = card.readAnalog( 0 );
        printf("ADC[0] : %f V\n", voltage);

        // read array of analog channel
        const unsigned int analogChannels[] = { 1, 2, 3, 4, 5 };
        double voltages[5];
        card.readAnalog( analogChannels, voltages, 5 );
        for ( int i = 0; i < 5; ++i )
        {
            printf("ADC[%d] : %f V\n", analogChannels[i], voltages[i]);
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

