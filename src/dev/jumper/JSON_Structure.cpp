#include "JSON_Structure.h"
#include<stdio.h>
#include<iostream>
#include<string>



using json = nlohmann::json;

void JSON_Structure::setup(){
    JSON_Structure::jsonFile = {
        {"Cables_lengths", 
            {0,0,0,0,0,0,0,0}
        },
        {"End_points",
            {{0.,0.,0.},{0.,0.,0.}
            ,{0.,0.,0.},{0.,0.,0.}
            ,{0.,0.,0.},{0.,0.,0.}}
        },
        {"Flags", {1,0,0}},
        {"Time", 0.},
        {"ZFinished", 1}
    };

}
void JSON_Structure::setup(json jsonFile){
    JSON_Structure::jsonFile = jsonFile;
}

void JSON_Structure::setController(int num, double val){
    JSON_Structure::jsonFile["Cables_lengths"][num] = val;
}

void JSON_Structure::setEndPoints(int num, btVector3 end_point){
    JSON_Structure::jsonFile["End_points"][num][0] = end_point[0];
    JSON_Structure::jsonFile["End_points"][num][1] = end_point[1];
    JSON_Structure::jsonFile["End_points"][num][2] = end_point[2];
}

void JSON_Structure::setFlags(int index, int value){
    JSON_Structure::jsonFile["Flags"][index] = value;
}

void JSON_Structure::setTime(double t){
    JSON_Structure::jsonFile["Time"] = t;
}

std::string JSON_Structure::jsonToString(){
    std::string value = JSON_Structure::jsonFile.dump();
    return value;
}

nlohmann::json JSON_Structure::stringToJson(char *s){
    return (json::parse(s));
}