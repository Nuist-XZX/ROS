// 生成一个新的乌龟
#include "ros/ros.h"
#include "turtlesim/Spawn.h"

int main(int argc, char* argv[]){

    setlocale(LC_ALL,"");
    ros::init(argc,argv,"client");
    ros::NodeHandle ns;
    ros::ServiceClient client = ns.serviceClient<turtlesim::Spawn>("/spawn");

    ros::service::waitForService("/spawn");
    turtlesim::Spawn ts;
    ts.request.x = 1.0; 
    ts.request.y = 2.0; 
    ts.request.theta = 3.1415926; 
    ts.request.name = "turtle2";

    bool flag = client.call(ts);
    if(flag){
        ROS_INFO("乌龟%s创建成功！",ts.response.name.c_str());
    }
    else{
        ROS_INFO("创建失败！");

    }

    ros::spin();
    return 0;
}