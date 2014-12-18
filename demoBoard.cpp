#include "include/defs/defs.h"
#include "include/board/board.h"
#include "include/board/boardDynamixel.h"
#include "3rdParty/dynamixel/dynamixel.h"
#include "3rdParty/dynamixel/dxl_hal.h"
#include <iostream>
#include <stdio.h>

using namespace std;
using namespace controller;

int main( int argc, const char** argv )
{
    int deg;
    float_type kat0 = 0;
    float_type kat1 = 0;
    float_type kat2 = 0;

    float_type moment0 = 0;
    float_type moment1 = 0;
    float_type moment2 = 0;

    vector <float_type> motorSpeed;
    for(int i = 0; i < 18; i++ ){
        motorSpeed.push_back(5);
    }
    vector <float_type> motorOffset;
    for(int i = 0; i < 18; i++ ){
        motorOffset.push_back(0);
    }
    vector <float_type> motorComplianceSlope;
    for(int i = 0; i < 18; i++ ){
        motorComplianceSlope.push_back(120);
    }
    vector <float_type> polozeniePoczatkowe;
    polozeniePoczatkowe.push_back( 0 );
    polozeniePoczatkowe.push_back( 24 );
    polozeniePoczatkowe.push_back( -114 );


    Board *demo = createBoardDynamixel();

    demo->readPosition( LEG_1, JOINT_0, kat0);
    demo->readPosition( LEG_1, JOINT_1, kat1);
    demo->readPosition( LEG_1, JOINT_2, kat2);

    cout << kat0 << endl;

    demo->setSpeed( motorSpeed );

    demo->setComplianceSlope( motorComplianceSlope );
    demo->setOffset( motorOffset );

    demo->setPosition(LEG_0, polozeniePoczatkowe );
    //demo->setPosition(LEG_1, polozeniePoczatkowe );
    //demo->setPosition(LEG_2, polozeniePoczatkowe );
    //demo->setPosition(LEG_3, polozeniePoczatkowe );
    //demo->setPosition(LEG_4, polozeniePoczatkowe );
    //demo->setPosition(LEG_5, polozeniePoczatkowe );

    cout << kat1 << endl << kat2 << endl;

    while (true){

    }

    return 0;
}
