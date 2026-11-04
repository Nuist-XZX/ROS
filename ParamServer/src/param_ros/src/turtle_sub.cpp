

#include "ros/ros.h"
#include "turtlesim/Pose.h"

void callback(const turtlesim::Pose::ConstPtr& p){
    ROS_INFO("乌龟的位姿信息: x = %.2f, y = %.2f, theta = %.2f, linear_velocity = %.2f, angular_velocity = %.2f",
            p->x,
            p->y,
            p->theta,
            p->linear_velocity,
            p->angular_velocity
            );

}


int main(int argc, char *argv[])
{
    setlocale(LC_ALL,"");
    // 2.初始化 ROS 节点
    ros::init(argc,argv,"sub");
    ros::NodeHandle nh;
    // 3.创建发布者对象
    ros::Subscriber sub = nh.subscribe<turtlesim::Pose>("/turtle1/pose",1000, callback);

    ros::spin();
    


    return 0;
}