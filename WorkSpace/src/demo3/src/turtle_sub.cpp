// 订阅 turtle1 和 turtle2 的 TF 广播信息，查找并转换时间最近的 TF 信息
//     将 turtle1 转换成相对 turtle2 的坐标，在计算线速度和角速度并发布
#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "geometry_msgs/TransformStamped.h"
#include "tf2_ros/transform_listener.h"
#include "tf2_ros/buffer.h"

int main(int argc, char **argv){
    setlocale(LC_ALL,"");

    ros::init(argc, argv, "turtle_sub");
    ros::NodeHandle nh;

    tf2_ros::Buffer buffer;
    tf2_ros::TransformListener listener(buffer);

    ros::Publisher pub = nh.advertise<geometry_msgs::Twist>("/turtle2/cmd_vel", 1000); // 发布乌龟2运动的速度控制，控制乌龟运动

    ros::Rate rate(10);
    while(ros::ok()){
        try{
            // 查找并转换时间最近的 TF 信息，转换两只乌龟相对坐标系
            geometry_msgs::TransformStamped transformStamped;
            transformStamped = buffer.lookupTransform("turtle2", "turtle1", ros::Time(0));

            // 根据位置信息计算速度,linear.x为线速度，angular.z为角速度
            geometry_msgs::Twist twist;
            twist.linear.x = 0.5 * sqrt(pow(transformStamped.transform.translation.x,2) + pow(transformStamped.transform.translation.y,2));
            twist.angular.z = 4 * atan2(transformStamped.transform.translation.y,transformStamped.transform.translation.x);
            
            pub.publish(twist);
        }
        catch(const std::exception& e){
            ROS_INFO("错误提示:%s",e.what());
        }
        rate.sleep();
        ros::spinOnce();
    }
    return 0;
}