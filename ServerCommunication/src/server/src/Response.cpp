#include "ros/ros.h"
#include "server/server_client.h"


bool dosrv(server::server_client::Request &req, server::server_client::Response &res)
{
    // 注意： 这里的num1、num2和num是在server.srv中定义的，不能谢厝名字，类型都是uint32
    ROS_INFO("接受请求数据: num1=%d, num2=%d", req.num1, req.num2);
    res.num = req.num1 + req.num2;
    ROS_INFO("发送回应数据: [%d]", res.num);
    return true;
}

int main (int argc, char **argv){
    
    setlocale(LC_ALL,"");
    ros::init(argc, argv, "server"); // 初始化一个名为server的节点
    ros::NodeHandle np;              // 创建一个名为np的节点句柄
    ros::ServiceServer server = np.advertiseService("server_client", dosrv); // 创建一个名为server_client的服务端, 并将回调函数绑定到dosrv函数
    ROS_INFO("准备接受请求。");
    ros::spin(); // 循环等待回调函数

    return 0;
}