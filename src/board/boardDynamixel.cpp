
#include "../include/board/boardDynamixel.h"
#include <iostream>
#include "../3rdParty/dynamixel/dynamixel.h"
#include "../3rdParty/dynamixel/dxl_hal.h"
#include "board/board.h"

using namespace controller;

/// A single instance of BoardDynamixel
BoardDynamixel::Ptr boardDynamixel;

BoardDynamixel::BoardDynamixel(void) : Board("Board Dynamixel", TYPE_USB2DYNAMIXEL) {
    //Every operation is executed on two objects in the same time (One object on one side of port)
    for(int i=0 ; i < 2 ; i++){
       int result =  dynamixelMotors[i].dxl_initialize(i+1, DEFAULT_BAUDNUM);
    }

    zero_angle[0]=450; zero_angle[1]=240; zero_angle[2]=1140;
    zero_angle[3]=0; zero_angle[4]=240; zero_angle[5]=1140;
    zero_angle[6]=-450; zero_angle[7]=240; zero_angle[8]=1140;
    zero_angle[9]=450; zero_angle[10]=-240; zero_angle[11]=-1140;
    zero_angle[12]=0; zero_angle[13]=-240; zero_angle[14]=-1140;
    zero_angle[15]=-450; zero_angle[16]=-240; zero_angle[17]=-1140;

    angle_offset[0]=-30; angle_offset[1]=30; angle_offset[2]=80;
    angle_offset[3]=265; angle_offset[4]=20; angle_offset[5]=-30;
    angle_offset[6]=-30; angle_offset[7]=125; angle_offset[8]=0;
    angle_offset[9]=60; angle_offset[10]=40; angle_offset[11]=0;
    angle_offset[12]=-190; angle_offset[13]=45; angle_offset[14]=80;
    angle_offset[15]=80; angle_offset[16]=75; angle_offset[17]=100;
}

BoardDynamixel::~BoardDynamixel(void) {
}

/// Set reference position value for servomotor, returns error value
unsigned int BoardDynamixel::setPosition(unsigned char legNo, unsigned char jointNo, float_type angle){

    angle = angle*180/M_PI;
    angle = angle*10;
    angle=-(angle+angle_offset[legNo*3+jointNo]-zero_angle[legNo*3+jointNo])*0.341333 + 512;

    CDynamixel *pointMotor = &dynamixelMotors[legNo < 3 ?0:1 ];
    pointMotor->dxl_write_word(legNo*10+jointNo, MOVE_SERWOMOTOR, angle);
    pointMotor->dxl_terminate();     //end of transmision    
    delete pointMotor;
    return 0;
}

/// Set reference position value for servomotors, returns error value
unsigned int BoardDynamixel::setPosition(unsigned char legNo, const std::vector<float_type>& angle){

    std::vector <float> angleLocal;
    //DB lepszy sposób na kopiowanie fragmentu wektora:
    //DB vector<float_type> angleLocal(angle.begin(), angle.begin+3);
    //DB w tym przypadku jednak kopiowanie zawartosci jest niepotrzebne
    for(int i = 0; i < 3 ; i++){    //typical duplication of vector doesnt work :(
        angleLocal[i] = angle[i];
    }
    CDynamixel *pointMotor = &dynamixelMotors[ legNo < 3 ?0:1 ];
    if(legNo < 3){
        for(int i=0; i<3; i++ ){    // i -> jointNo
            angleLocal[i] = angleLocal[i]*180/M_PI;
            angleLocal[i] = angleLocal[i]*10;
            angleLocal[i]=-(angleLocal[i]+angle_offset[legNo*3+i]-zero_angle[legNo*3+i])*0.341333 + 512;

            pointMotor->dxl_write_word(legNo*10+i, MOVE_SERWOMOTOR, angleLocal[i]);
        }

    }else{
        for(int i=0; i<3; i++ ){    // i -> jointNo
            angleLocal[i] = angleLocal[i]*180/M_PI;
            angleLocal[i] = angleLocal[i]*10;
            angleLocal[i]=-(angleLocal[i]+angle_offset[legNo*3+i]-zero_angle[legNo*3+i])*0.341333 + 512;

            pointMotor->dxl_write_word(legNo*10+i, MOVE_SERWOMOTOR, angleLocal[i]);
        }
    }

    pointMotor->dxl_terminate();     //end of transmision
    delete pointMotor;
    return 0;
}

/// Set reference position value for servomotors, returns error value
unsigned int BoardDynamixel::setPosition(const std::vector<float_type>& angle){

    /* how many elements have this vector?
       - angle for every joint? 18
       - angle for joint in every leg? 6
    */

  /*  std::vector <float> angleLocal;
    for(int i = 0; i < 6 ; i++){    //typical duplication of vector doesnt work :(
        angleLocal[i] = angle[i];
    }

    for(int i = 0; i < 2; i++){     //port
        CDynamixel *pointMotor = &dynamixelMotors[i];
        for(int j = 0; j < 6; j++ ){    //angle for every leg
            angleLocal[i] = angleLocal[i]*180/M_PI;
            angleLocal[i] = angleLocal[i]*10;
            angleLocal[i]=-(angleLocal[i]+angle_offset[legNo*3+i]-zero_angle[legNo*3+i])*0.341333 + 512;

            pointMotor->dxl_write_word(legNo*10+i, MOVE_SERWOMOTOR, angleLocal[i]);
        }

    }   */

    return 0;
}

/// Set reference speed value for servomotor, returns error value
unsigned int BoardDynamixel::setSpeed(unsigned char legNo, unsigned char jointNo, float_type speed){
    return 0;
}

/// Set reference speed value for servomotors, returns error value
unsigned int BoardDynamixel::setSpeed(unsigned char legNo, const std::vector<float_type>& speed){
    return 0;
}

/// Set reference speed value for servomotors, returns error value
unsigned int BoardDynamixel::setSpeed(const std::vector<float_type>& speed){
    return 0;
}

/// Set compliance margin [0,254]- dead zone -- for this area the torque is zero, returns error value
unsigned int BoardDynamixel::setComplianceMargin(unsigned char legNo, unsigned char jointNo, float_type margin){
    return 0;
}

/// Set compliance margins [0,254]- dead zone -- for this area the torque is zero, returns error value
unsigned int BoardDynamixel::setComplianceMargin(unsigned char legNo, const std::vector<float_type> margin){
    return 0;
}

/// Set compliance margins [0,254]- dead zone -- for this area the torque is zero, returns error value
unsigned int BoardDynamixel::setComplianceMargin(const std::vector<float_type> margin){
    return 0;
}

/// Set compiance slope [1,254] - the area with the reduced torque, returns error value
unsigned int BoardDynamixel::setComplianceSlope(unsigned char legNo, unsigned char jointNo, float_type slope){
    return 0;
}

/// Set compiance slope [1,254] - the area with the reduced torque, returns error value
unsigned int BoardDynamixel::setComplianceSlope(unsigned char legNo, const std::vector<float_type>& slope){
    return 0;
}

/// Set compiance slope [1,254] - the area with the reduced torque, returns error value
unsigned int BoardDynamixel::setComplianceSlope(const std::vector<float_type>& slope){
    return 0;
}

/// Set torque limit torque_limit [0,1023] - the torque limit, returns error value
unsigned int BoardDynamixel::setTorqueLimit(unsigned char legNo, unsigned char jointNo, float_type torqueLimit){
    return 0;
}

/// Set torque limit torque_limit [0,1023] - the torque limit, returns error value
unsigned int BoardDynamixel::setTorqueLimit(unsigned char legNo, const std::vector<float_type>& torqueLimit){
    return 0;
}

/// Set torque limit torque_limit [0,1023] - the torque limit, returns error value
unsigned int BoardDynamixel::setTorqueLimit(const std::vector<float_type>& torqueLimit){
    return 0;
}

/// Returns current position of the servomotor, returns error value
unsigned int BoardDynamixel::readPosition(unsigned char legNo, unsigned char jointNo, float_type& angle){
    return 0;
}

/// Returns current position of the servomotors, returns error value
unsigned int BoardDynamixel::readPositions(unsigned char legNo, const std::vector<float_type>& angle){
    return 0;
}

/// Returns current position of the servomotor, returns error value
unsigned int BoardDynamixel::readPosition(const std::vector<float_type>& angle){
    return 0;
}

/// Returns contact force from 1-axis force sensor
unsigned int BoardDynamixel::readForce(unsigned char legNo, float_type& contactForce){
    return 0;
}

/// Returns contact force from 1-axis force sensor
unsigned int BoardDynamixel::readForce(const std::vector<float_type>& contactForce){
    return 0;
}

/// Returns contact force from 3-axis torque/force sensor
unsigned int BoardDynamixel::readTorqueForce(unsigned char legNo, TorqueForce& valueTF){
    return 0;
}

/// Returns contact force from 3-axis torque/force sensor
unsigned int BoardDynamixel::readTorqueForce(const std::vector<float_type>& valueTF){
    return 0;
}

/// Returns contact or from microswitch
bool BoardDynamixel::readContact(unsigned char legNo){
    return false;
}

/// Returns contact or from microswitches
void BoardDynamixel::readContact(const std::vector<bool> contact){

}

/// Returns current from servo
unsigned int BoardDynamixel::readCurrent(unsigned char legNo, unsigned char jointNo, float_type& servoCurrent){
    return 0;
}

/// Returns current from servo
unsigned int BoardDynamixel::readCurrent(unsigned char legNo, const std::vector<float_type>& servoCurrent){
    return 0;
}

/// Returns current from servo
unsigned int BoardDynamixel::readCurrent(const std::vector<float_type>& servoCurrent){
    return 0;
}

/// Returns torque/load from servo
unsigned int BoardDynamixel::readTorque(unsigned char legNo, unsigned char jointNo, float_type& servoTorque){
    return 0;
}

/// Returns torque/load from servo
unsigned int BoardDynamixel::readTorque(unsigned char legNo, const std::vector<float_type>& servoTorque){
    return 0;
}

/// Returns torque/load from servo
unsigned int BoardDynamixel::readTorque(const std::vector<float_type>& servoTorque){
    return 0;
}

/// Set servo Offset
void BoardDynamixel::setOffset(unsigned char legNo, unsigned char jointNo, float_type offset){


}

/// Set servo Offset
void BoardDynamixel::setOffset(unsigned char legNo, const std::vector<float_type> offset){

}

/// Set servo Offset
void BoardDynamixel::setOffset(const std::vector<float_type> offset){

}

/// Board configuration -- set default value
void BoardDynamixel::setDefault(void){ }

controller::Board* controller::createBoardDynamixel(void) {
    boardDynamixel.reset(new BoardDynamixel());
    return boardDynamixel.get();
}

