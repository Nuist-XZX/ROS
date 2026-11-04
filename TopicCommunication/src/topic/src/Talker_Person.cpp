#include "ros/ros.h"
#include "topic/person.h" //自定义消息头文件

int main(int argc, char **argv){

    setlocale(LC_ALL,"");
    ros::init(argc,argv,"talker_person");
    ros::NodeHandle nh;
    
    ros::Publisher pub = nh.advertise<topic::person>("person_info",10);

    topic::person person_msg;
    person_msg.name = "Alice";
    person_msg.age = 25;
    person_msg.height = 1.65;

    ros::Rate r(1);
    while (ros::ok())
    {
        pub.publish(person_msg);
        ROS_INFO("发布的消息: name=%s, age=%d, height=%.2f", person_msg.name.c_str(), person_msg.age, person_msg.height);
        r.sleep();
    }

    return 0;
}