/*  
    该文件实现:需要订阅 turtle1 和 turtle2 的 pose，然后广播相对 world 的坐标系信息

    注意: 订阅的两只 turtle,除了命名空间(turtle1 和 turtle2)不同外,
            其他的话题名称和实现逻辑都是一样的，
            所以我们可以将所需的命名空间通过 args 动态传入
*/
#include "ros/ros.h"
#include "tf2/LinearMath/Quaternion.h"
#include "tf2_ros/transform_broadcaster.h"
#include "turtlesim/Pose.h"
#include "geometry_msgs/TransformStamped.h"

std::string turtle_name; // 保存乌龟名称

void domsg(const turtlesim::Pose::ConstPtr& msg){
    // 创建一个广播器，注意是static的
    static tf2_ros::TransformBroadcaster tsb;
    // 创建一个相对位置关系
    geometry_msgs::TransformStamped ts;
    ts.header.frame_id = "world";
    ts.child_frame_id = turtle_name;
    ts.header.stamp = ros::Time::now();
    ts.transform.translation.x = msg->x;
    ts.transform.translation.y = msg->y;
    ts.transform.translation.z = 0.0; // 乌龟是2d，没有z轴
    tf2::Quaternion qtn;
    qtn.setRPY(0,0,msg->theta);
    ts.transform.rotation.x = qtn.getX();
    ts.transform.rotation.y = qtn.getY();
    ts.transform.rotation.z = qtn.getZ();
    ts.transform.rotation.w = qtn.getW();
    tsb.sendTransform(ts); // 将位置信息广播出去

}

int main(int argc, char **argv){

    setlocale(LC_ALL,"");
    ros::init(argc,argv,"turtle_pub");
    if (argc != 2)
    {
        ROS_ERROR("请传入正确的参数");
    } else {
        turtle_name = argv[1];
        ROS_INFO("乌龟 %s 坐标发送启动",turtle_name.c_str());
    }
    ros::NodeHandle nh;

    // 创建订阅乌龟的位姿信息
    ros::Subscriber sub = nh.subscribe<turtlesim::Pose>(turtle_name+"/pose",1000,domsg);

    ros::spin();

    return 0;
}