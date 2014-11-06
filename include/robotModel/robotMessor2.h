/**
* @author Maciej Okoniewski
* @author Emil Waledziak
* @author Jerzy Wiatrow
* @author Marcin Zgolinski
* @mainpage
*/

#ifndef _ROBOTMESSOR_H_INCLUDED
#define _ROBOTMESSOR_H_INCLUDED

#include "robot.h"
#include <iostream>


namespace controller {

                    Robot* createRobotMessor(void);
                    Robot* createRobotMessor(std::string filename);

                     }

using namespace controller;

class RobotMessor: public Robot
{
public:


    /// Name of the robot model
    const std::string& getName() const { return name; }

    ///Compute configuration of the robot for the reference motion
    /**
    * @param motion - specified motion
    * @return tmp
    */
    std::vector<float_type> movePlatform(const Mat34& motion);

    ///Compute configuration of the robot for the reference motion (in relation to neutral pose)
    /**
    * @param motion - specified motion
    * @return tmp
    */
    std::vector<float_type> movePlatformNeutral(const Mat34 motion);

    ///Compute force in each joint of the legs, input configuration of the robot
    /**
    * @param vector<float_type>
    * @return tmp
    */
    std::vector<float_type> computeCompliance(std::vector<float_type>);
private:

};

#endif


