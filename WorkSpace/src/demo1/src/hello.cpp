/*
    // 自定义头文件调用
*/ 

#include "ros/ros.h"
#include "demo1/hello.h"

namespace hello_demo{

void hellopub::run(){
    ROS_INFO("This is a demo for head file and cpp file!");
}

}

int main(int argc, char** argv){
    setlocale(LC_ALL,"");
    ros::init(argc,argv,"hello");
    hello_demo::hellopub hello_run;
    hello_run.run();

    return 0;
}