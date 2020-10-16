/*
 * Copyright © 2012, United States Government, as represented by the
 * Administrator of the National Aeronautics and Space Administration.
 * All rights reserved.
 * 
 * The NASA Tensegrity Robotics Toolkit (NTRT) v1 platform is licensed
 * under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * http://www.apache.org/licenses/LICENSE-2.0.
 * 
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
 * either express or implied. See the License for the specific language
 * governing permissions and limitations under the License.
*/

/**
 * @file AppTwiceCubeModel.cpp
 * @brief Contains the definition function main() for the Three strut
 * tensegrity TwiceCube example application
 * @author Brian Tietz
 * $Id$
 */

// This application
#include "TwiceCubeModel.h"
#include "SimpleController.h"
// This library
#include "core/terrain/tgBoxGround.h"
#include "core/tgModel.h"
#include "core/tgSimViewGraphics.h"
#include "core/tgSimulation.h"
#include "core/tgWorld.h"
// Bullet Physics
#include "LinearMath/btVector3.h"
// The C++ Standard Library
#include <iostream>
#include <string>
#include <boost/program_options.hpp>
namespace po = boost::program_options;
#include <iterator>
#include <string>
#include <time.h>



tgSimView* view;
bool render_flag = false;


/**
 * The entry point.
 * @param[in] argc the number of command-line arguments
 * @param[in] argv argv[0] is the executable name
 * @return 0
 */
int main(int argc, char** argv)
{

    po::options_description desc("Allowed options");
    desc.add_options()
        ("render", "set the flag for rendering flag to true to enable rendering")
    ;

    po::variables_map vm;        
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);    

    if (vm.count("render"))
        render_flag = true;

    std::cout << "AppTwiceCubeModel" << std::endl;

    // First create the ground and world. Specify ground rotation in radians
    const double yaw = 0.0;
    const double pitch = 0.0;
    const double roll = 0.0;
    const tgBoxGround::Config groundConfig(btVector3(yaw, pitch, roll));
    // the world will delete this
    tgBoxGround* ground = new tgBoxGround(groundConfig);
    
    const tgWorld::Config config(981); // gravity, cm/sec^2
    tgWorld world(config, ground);

    // Second create the view
    const double timestep_physics = 0.001; // seconds
    const double timestep_graphics = 1.f/60.f; // seconds
    const long long simulation_time = 10000; // in seconds
    if(render_flag)
        view = new tgSimViewGraphics(world, timestep_physics, timestep_graphics, "Tensegrity Jumping Robot", render_flag);
    else
        view = new tgSimView(world, timestep_physics, timestep_graphics, render_flag);

    // Third create the simulation
    tgSimulation simulation(*view);

    // Fourth create the models with their controllers and add the models to the
    // simulation

    TwiceCubeModel* const myModel = new TwiceCubeModel();
    
    // const char* host_name = argv[1];
    // const long long  port_num = std::stoll(argv[2]);
    // const int control_type = std::stoi(argv[3]);
    // printf("host_name: %s\t port_num: %s\t control_type: %s\n", argv[1], argv[2], argv[3]);
    // LengthController* const myController = new LengthController(host_name, port_num, control_type);
    // myModel->attach(myController);

    SimpleController * const myController = new SimpleController();
    myModel->attach(myController);


    // Add the model to the world
    simulation.addModel(myModel);
    
    std::vector<tgRod*> rods = myModel->getAllRods();
    for(int i = 0; i < rods.size(); i++){
        // https://pybullet.org/Bullet/phpBB3/viewtopic.php?t=11690
        std::string rodTag = rods[i]->getTags().getTags()[0];
        if (rodTag.compare("box_rod") == 0) {
            std::cout << i<<"found!" << '\n';
            rods[i]->getPRigidBody()->setCollisionFlags(rods[i]->getPRigidBody()->getCollisionFlags() | btCollisionObject::CF_STATIC_OBJECT);
        }
        if (rodTag.compare("cube_rod") == 0) {
            std::cout << i<<"found!" << '\n';
            // to make static object
            // rods[i]->getPRigidBody()->setCollisionFlags(rods[i]->getPRigidBody()->getCollisionFlags() | btCollisionObject::CF_STATIC_OBJECT);
            // to make no contact object
            rods[i]->getPRigidBody()->setCollisionFlags(rods[i]->getPRigidBody()->getCollisionFlags() | btCollisionObject::CF_NO_CONTACT_RESPONSE);
        }

    }

    // clock_t t;
    // t = clock();
    // printf("Timer starts\n");
    
    // for(int i = 0; i < 200000; i++){
    //                 std::cout << i<<"found!" << '\n';

    // }
    // printf("Timer ends \n");
    // t = clock() - t;
    // double time_taken = ((double)t)/CLOCKS_PER_SEC; // calculate the elapsed time
    // printf("The program took %f seconds to execute", time_taken);

    if(render_flag)
        // With GUI, no exact number of steps until the user press q
        simulation.run();
    else
        // Without GUI
        //for example simulation_time/timestep_physics = 10,000,000 timestep of simulation
        simulation.run(simulation_time/timestep_physics);    // for tgSimView -- without window, without rendering, without any graphics
    
    //Teardown is handled by delete, so that should be automatic
    return 0;
}