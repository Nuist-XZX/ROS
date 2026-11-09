#include "ros/ros.h"
#include "demo2/hello2.h"


int main(int argc, char **argv){
    setlocale(LC_ALL,"");
    ros::init(argc,argv,"hello2");

    while(ros::ok()){
        hello2_ros();
    }
    
    return 0;
}