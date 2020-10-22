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
 * @file AppTwiceCubeGymModel.cpp
 * @brief Contains the definition function main() for the Three strut
 * tensegrity TwiceCube example application
 * @author Brian Tietz
 * $Id$
 */

// This application
#include "TwiceCubeGymModel.h"
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
// #include <boost/program_options.hpp>
// namespace po = boost::program_options;
#include <iterator>
#include <string>
#include <time.h>
#include <vector>
#include <cmath>

# define COLLISIONS_FLAG false



tgSimView* view;
bool render_flag = false;

void modifyRods(TwiceCubeGymModel *model){
    if(!COLLISIONS_FLAG){
        std::vector<tgRod*> rods = model->getAllRods();
        // https://pybullet.org/Bullet/phpBB3/viewtopic.php?t=11690
        rods[0]->getPRigidBody()->setCollisionFlags(rods[0]->getPRigidBody()->getCollisionFlags() | btCollisionObject::CF_STATIC_OBJECT);
		rods[1]->getPRigidBody()->setCollisionFlags(rods[1]->getPRigidBody()->getCollisionFlags() | btCollisionObject::CF_STATIC_OBJECT);
		rods[2]->getPRigidBody()->setCollisionFlags(rods[2]->getPRigidBody()->getCollisionFlags() | btCollisionObject::CF_STATIC_OBJECT);
		rods[3]->getPRigidBody()->setCollisionFlags(rods[3]->getPRigidBody()->getCollisionFlags() | btCollisionObject::CF_STATIC_OBJECT);
		rods[4]->getPRigidBody()->setCollisionFlags(rods[4]->getPRigidBody()->getCollisionFlags() | btCollisionObject::CF_STATIC_OBJECT);
		rods[5]->getPRigidBody()->setCollisionFlags(rods[5]->getPRigidBody()->getCollisionFlags() | btCollisionObject::CF_STATIC_OBJECT);
		rods[6]->getPRigidBody()->setCollisionFlags(rods[6]->getPRigidBody()->getCollisionFlags() | btCollisionObject::CF_STATIC_OBJECT);
		rods[7]->getPRigidBody()->setCollisionFlags(rods[7]->getPRigidBody()->getCollisionFlags() | btCollisionObject::CF_STATIC_OBJECT);
		rods[8]->getPRigidBody()->setCollisionFlags(rods[8]->getPRigidBody()->getCollisionFlags() | btCollisionObject::CF_STATIC_OBJECT);
		rods[9]->getPRigidBody()->setCollisionFlags(rods[9]->getPRigidBody()->getCollisionFlags() | btCollisionObject::CF_STATIC_OBJECT);
		rods[10]->getPRigidBody()->setCollisionFlags(rods[10]->getPRigidBody()->getCollisionFlags() | btCollisionObject::CF_STATIC_OBJECT);
		rods[11]->getPRigidBody()->setCollisionFlags(rods[11]->getPRigidBody()->getCollisionFlags() | btCollisionObject::CF_STATIC_OBJECT);
		rods[12]->getPRigidBody()->setCollisionFlags(rods[12]->getPRigidBody()->getCollisionFlags() | btCollisionObject::CF_NO_CONTACT_RESPONSE);
		rods[13]->getPRigidBody()->setCollisionFlags(rods[13]->getPRigidBody()->getCollisionFlags() | btCollisionObject::CF_NO_CONTACT_RESPONSE);
		rods[14]->getPRigidBody()->setCollisionFlags(rods[14]->getPRigidBody()->getCollisionFlags() | btCollisionObject::CF_NO_CONTACT_RESPONSE);
		rods[15]->getPRigidBody()->setCollisionFlags(rods[15]->getPRigidBody()->getCollisionFlags() | btCollisionObject::CF_NO_CONTACT_RESPONSE);
		rods[16]->getPRigidBody()->setCollisionFlags(rods[16]->getPRigidBody()->getCollisionFlags() | btCollisionObject::CF_NO_CONTACT_RESPONSE);
		rods[17]->getPRigidBody()->setCollisionFlags(rods[17]->getPRigidBody()->getCollisionFlags() | btCollisionObject::CF_NO_CONTACT_RESPONSE);
		rods[18]->getPRigidBody()->setCollisionFlags(rods[18]->getPRigidBody()->getCollisionFlags() | btCollisionObject::CF_NO_CONTACT_RESPONSE);
		rods[19]->getPRigidBody()->setCollisionFlags(rods[19]->getPRigidBody()->getCollisionFlags() | btCollisionObject::CF_NO_CONTACT_RESPONSE);
		rods[20]->getPRigidBody()->setCollisionFlags(rods[20]->getPRigidBody()->getCollisionFlags() | btCollisionObject::CF_NO_CONTACT_RESPONSE);
		rods[21]->getPRigidBody()->setCollisionFlags(rods[21]->getPRigidBody()->getCollisionFlags() | btCollisionObject::CF_NO_CONTACT_RESPONSE);
		rods[22]->getPRigidBody()->setCollisionFlags(rods[22]->getPRigidBody()->getCollisionFlags() | btCollisionObject::CF_NO_CONTACT_RESPONSE);
		rods[23]->getPRigidBody()->setCollisionFlags(rods[23]->getPRigidBody()->getCollisionFlags() | btCollisionObject::CF_NO_CONTACT_RESPONSE);
		rods[24]->getPRigidBody()->setCollisionFlags(rods[24]->getPRigidBody()->getCollisionFlags() | btCollisionObject::CF_NO_CONTACT_RESPONSE);
		rods[25]->getPRigidBody()->setCollisionFlags(rods[25]->getPRigidBody()->getCollisionFlags() | btCollisionObject::CF_NO_CONTACT_RESPONSE);
		rods[26]->getPRigidBody()->setCollisionFlags(rods[26]->getPRigidBody()->getCollisionFlags() | btCollisionObject::CF_NO_CONTACT_RESPONSE);
		rods[27]->getPRigidBody()->setCollisionFlags(rods[27]->getPRigidBody()->getCollisionFlags() | btCollisionObject::CF_NO_CONTACT_RESPONSE);
		
    }
    
}

double fullTimeForward(long long num_steps, tgSimulation &simulation, TwiceCubeGymModel *model){
    clock_t begin = clock();    // Calculate CPU time on Linux and Wall time on Windows
    simulation.reset();
    modifyRods(model);
    simulation.run(num_steps);
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    return time_spent;
}

double noResetForward(long long num_steps, tgSimulation &simulation){
    clock_t begin = clock();    // Calculate CPU time on Linux and Wall time on Windows
    simulation.run(num_steps);
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    return time_spent;
}

double calculateMean(std::vector<double> vec){
    double total = 0;
    for(int i = 0; i < vec.size(); i++){
        total += vec[i];
    }
    total /= vec.size();
    return total;
}

double calculateSD(std::vector<double> vec){
    double mean = calculateMean(vec);
    double std = 0;
    for(int i = 0; i < vec.size(); i++){
        std += pow(vec[i] - mean, 2);
    }
    std = sqrt(std/(float)vec.size());
    return std;
}

void benchmark(int num_repetitions, int num_steps, tgSimulation &simulation, TwiceCubeGymModel *model){
    std::vector<double> durations_full;
    std::vector<double> durations_no_reset;
    for(int i = 0; i < num_repetitions; i++){
        durations_full.push_back(fullTimeForward(num_steps, simulation, model));
        simulation.reset();
        modifyRods(model);
        durations_no_reset.push_back(noResetForward(num_steps, simulation));
    }

    printf("Full-Time: Num repetitions: %d; Total: %0.5lfs (+/- %0.5lfs); Per step: %0.5lfs\n", num_repetitions, calculateMean(durations_full), calculateSD(durations_full), calculateMean(durations_full)/(float)num_steps);
    printf("No-Reset: Num repetitions: %d; Total: %0.5lfs (+/- %0.5lfs); Per step: %0.5lfs\n",  num_repetitions, calculateMean(durations_no_reset), calculateSD(durations_no_reset), calculateMean(durations_no_reset)/(float)num_steps);
}


/**
 * The entry point.
 * @param[in] argc the number of command-line arguments
 * @param[in] argv argv[0] is the executable name
 * @return 0
 */
int main(int argc, char** argv)
{
    // po::options_description desc("Allowed options");
    // desc.add_options()
    //     ("render", "set the flag for rendering flag to true to enable rendering")
    //     ("hostname", po::value<std::string>(), "set the hostname for the tcp communication")
    //     ("portnum", po::value<int>(), "set the port number for the tcp communication")
    // ;

    // po::variables_map vm;        
    // po::store(po::parse_command_line(argc, argv, desc), vm);
    // po::notify(vm);    

    // if (vm.count("render"))
    //     render_flag = true;


    // std::cout << "AppTwiceCubeGymModel" << std::endl;

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
    render_flag = std::stoi(argv[3]);
    if(render_flag)
        view = new tgSimViewGraphics(world, timestep_physics, timestep_graphics, "Tensegrity Jumping Robot", render_flag);
    else
        view = new tgSimView(world, timestep_physics, timestep_graphics, render_flag);

    // Third create the simulation
    tgSimulation simulation(*view);

    // Fourth create the models with their controllers and add the models to the
    // simulation

    TwiceCubeGymModel* const myModel = new TwiceCubeGymModel();
    
    // const char* hostname = vm["hostname"].as<std::string>().c_str();
    // const long long  port_num = vm["portnum"].as<int>();
    const char* hostname = argv[1];
    const long long  port_num = std::stoll(argv[2]);

    // std::cout<<hostname<<":"<<port_num<<"\n";
    SimpleController* const myController = new SimpleController(hostname, port_num);
    myModel->attach(myController);


    // // Add the model to the world
    simulation.addModel(myModel);
    
    modifyRods(myModel);

    
    // // return 0;

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