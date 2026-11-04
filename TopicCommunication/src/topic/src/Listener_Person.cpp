#include "ros/ros.h"
#include "topic/person.h" //自定义消息头文件

void doMsg(const topic::person::ConstPtr& msg_p){
    ROS_INFO("我听见: name=%s, age=%d, height=%.2f", msg_p->name.c_str(), msg_p->age, msg_p->height);
}

int main(int argc, char** argv){

    setlocale(LC_ALL,"");
    ros::init(argc,argv,"listener_person");
    ros::NodeHandle nh;
    ros::Subscriber sub = nh.subscribe<topic::person>("person_info",10,doMsg);

    ros::spin();

    return 0;
}