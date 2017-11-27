#include <iostream>

#include "Handler.h"

int main()
{
    using namespace XelM;

    Handler l_DefaultMap(Handler::DefaultMap());

    if ( l_DefaultMap.EnterRoom(1) )
    {
        while ( l_DefaultMap.Active() )
        {
            l_DefaultMap.HandleUserInput();
        }
    }

}