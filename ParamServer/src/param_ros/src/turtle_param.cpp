#include "ros/ros.h"

int main(int argc, char**argv){
    setlocale(LC_ALL,"");

    ros::init(argc,argv,"TURL_PA");
    ros::NodeHandle np;
    np.setParam("/turtlesim/background_r",0);
    np.setParam("/turtlesim/background_g",0);
    np.setParam("/turtlesim/background_b",0);

    return 0;
}