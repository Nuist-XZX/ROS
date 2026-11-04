#include "ros/ros.h"
#include "turtlesim/Spawn.h"

int main(int argc, char **argv){
    setlocale(LC_ALL,"");

    ros::init(argc,argv,"turtle_cl");
    ros::NodeHandle np;

    ros::ServiceClient client = np.serviceClient<turtlesim::Spawn>("/spawn");

        //等待服务启动成功
    ros::service::waitForService("/spawn");

    // 去掉 roslaunch / rosrun 注入的 ROS 参数，只留用户参数
    std::vector<std::string> args;
    ros::removeROSArgs(argc, argv, args);

    if (args.size() < 4) {  // args[0] 是程序名
        ROS_ERROR("用法: request <x> <y> <theta> <name>");
        return 1;
    }

    turtlesim::Spawn ai;
    ai.request.x = atof(args[1].c_str());
    ai.request.y = atof(args[2].c_str());
    ai.request.theta = atof(args[3].c_str());
    ai.request.name = args[4];
    // 6.发送请求,返回 bool 值，标记是否成功
    bool flag = client.call(ai);
    // 7.处理响应
    if (flag)
    {
        ROS_INFO("请求正常处理,响应结果:%s",ai.response.name.c_str());
    }
    else
    {
        ROS_ERROR("请求处理失败....");
        return 1;
    }

    return 0;
}