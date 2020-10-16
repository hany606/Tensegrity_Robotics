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


int nodes_num = 24;
int endpoints_mapping [24][2] = {{0, 0}, {1, 0}, {2, 0}, {3, 0}, {4, 0}, {5, 0}, {6, 0}, {7, 0}, {0, 1}, {1, 1}, {2, 1}, {3, 1}, {4, 1}, {5, 1}, {6, 1}, {7, 1}, {16, 1}, {17, 1}, {18, 1}, {19, 1}, {20, 1}, {21, 1}, {22, 1}, {23, 1}};

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

  // printf("Number of actuators: %d , Number of Rods: %d\n", (int) actuators.size(), (int) rods.size());//DEBUG
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
    // printf("Actutor of string #%d -> start Lenght: %lf\n", (int) i, start_Simple);//DEBUG
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
        // std::cout<<"Nodes:\n";
        for(int i = 0; i < nodes_num; i++){
          if(endpoints_mapping[i][0] < 0){
            // std::cout<<"Cannot find node with index: "<<i<<"\n";
            continue;
          }

          btVector3 node = actuators[endpoints_mapping[i][0]]->getAnchors_mod()[endpoints_mapping[i][1]]->getWorldPosition();
          
          // std::cout<<"Node "<<i<<":"<< node<<"\n";
        }

        // std::cout<<"End Points:\n";
        // for(int i = 0; i < actuators.size(); i++){
        //     btVector3 end_point1 = actuators[i]->getAnchors_mod()[0]->getWorldPosition();
        //     btVector3 end_point2 = actuators[i]->getAnchors_mod()[1]->getWorldPosition();
            
        //     std::cout<<"Cable"<<i<<"-anchor-1: "<<end_point1<<"\n";
        //     std::cout<<"Cable"<<i<<"-anchor-2: "<<end_point2<<"\n";
                   
        // }
        // btVector3 CoM = btVector3(0.0, 0.0, 0.0);
        // for(int i = 0; i <rods.size(); i++){
        //   CoM += rods[i]->centerOfMass();
        // }
        // CoM /= double(rods.size());
        // std::cout<<"CoM: "<<CoM;
        // std::cout << endl << "--------------------------------------------------------------------------" << endl;

      }
    }
  }

}