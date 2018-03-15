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

        // read one encoder channel
        int count = card.readEncoder( 0 );
        printf("ENC[0] : %d V\n", count);

        // read encoder counts
        const unsigned int encoderChannels[] = { 1, 2, 3, 4, 5 };
        int counts[5];
        card.readEncoder( encoderChannels, counts, 5 );
        for ( int i = 0; i < 5; ++i )
        {
            printf("ENC[%d] : %d V\n", encoderChannels[i], counts[i]);
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

