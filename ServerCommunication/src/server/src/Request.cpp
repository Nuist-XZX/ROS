#include "ros/ros.h"
#include "server/server_client.h"

int main(int argc, char **argv){
    setlocale(LC_ALL,"");
    ros::init(argc, argv, "client");
    ros::NodeHandle np;
    ros::ServiceClient client = np.serviceClient<server::server_client>("server_client");
    //等待服务启动成功
    ros::service::waitForService("server_client");

    // 去掉 roslaunch / rosrun 注入的 ROS 参数，只留用户参数
    std::vector<std::string> args;
    ros::removeROSArgs(argc, argv, args);

    if (args.size() < 3) {  // args[0] 是程序名
        ROS_ERROR("用法: request <num1> <num2>");
        return 1;
    }

    server::server_client ai;
    ai.request.num1 = atoi(args[1].c_str());
    ai.request.num2 = atoi(args[2].c_str());
    // 6.发送请求,返回 bool 值，标记是否成功
    bool flag = client.call(ai);
    // 7.处理响应
    if (flag)
    {
        ROS_INFO("请求正常处理,响应结果:%d",ai.response.num);
    }
    else
    {
        ROS_ERROR("请求处理失败....");
        return 1;
    }

    return 0;
}