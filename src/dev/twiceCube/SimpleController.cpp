/**
 * @file SimpleController.h
 * @brief Implementation of class SimpleController
 * @author Hany Hamed
 * This was built over one of the source codes of NTRTsim codes
 */

// This module
#include "SimpleController.h"
#include <core/tgSpringCableActuator.h>


// The C++ Standard Library
#include <cassert>
#include <stdexcept>
#include <time.h>
#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <algorithm>

using namespace std;


// control_type: 0 for rest_Simple control and 1 for current_Simple control
SimpleController::SimpleController()
{
}

SimpleController::~SimpleController()
{
}	

void SimpleController::onSetup(TwiceCubeModel& subject)
{

  m_controllers.clear(); //clear vector of controllers
    
  //get all of the tensegrity structure's cables
  actuators = subject.getAllActuators();
  rods = subject.getAllRods();

  printf("Number of actuators: %d , Number of Rods: %d\n", (int) actuators.size(), (int) rods.size());//DEBUG
  // std::cout<<rods[1]->getTags()[0][1]<<"\n";

  //Attach a tgBasicController to each actuator
  for (size_t i = 0; i < actuators.size(); ++i)
  {
    tgBasicActuator * const pActuator = actuators[i];
    assert(pActuator != NULL);  //precondition
    //instantiate controllers for each cable
    tgBasicController* m_lenController = new tgBasicController(pActuator);
    //add controller to vector
    m_controllers.push_back(m_lenController);
    // getStartSimple
    double start_Simple = actuators[i]->getRestLength();
    printf("Actutor of string #%d -> start Lenght: %lf\n", (int) i, start_Simple);//DEBUG
  }
  
}

//This function is being activated each step
void SimpleController::onStep(TwiceCubeModel& subject, double dt)
{

  if (dt <= 0.0) {
    throw std::invalid_argument("dt is not positive");
  }
  else {
    globalTime += dt;
    if(globalTime > 0){ //delay start of cable actuation
      if(toggle==0){    //print once when motors start moving        
        
        std::cout<<"End Points:\n";
        for(int i = 0; i < actuators.size(); i++){
            btVector3 end_point1 = actuators[i]->getAnchors_mod()[0]->getWorldPosition();
            btVector3 end_point2 = actuators[i]->getAnchors_mod()[1]->getWorldPosition();
            
            std::cout<<"Cable"<<i<<"-anchor-1: "<<end_point1<<"\n";
            std::cout<<"Cable"<<i<<"-anchor-2: "<<end_point2<<"\n";
                   
        }
        btVector3 CoM = btVector3(0.0, 0.0, 0.0);
        for(int i = 0; i <rods.size(); i++){
          CoM += rods[i]->centerOfMass();
        }
        CoM /= double(rods.size());
        std::cout<<"CoM: "<<CoM;
        std::cout << endl << "--------------------------------------------------------------------------" << endl;

      }
    }
  }

}