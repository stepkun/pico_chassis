
#!/bin/sh

echo "Installing micro-ROS-Agent"

# fastrtps packages are needed for compile
sudo apt install ros-$ROS_DISTRO-fastrtps ros-$ROS_DISTRO-fastrtps-cmake-module ros-$ROS_DISTRO-fastrtps-dbgsym

# micro-ROS-Agent:
cd ..
if [ -d micro_ros_msgs ]
then
    echo "The micro_ros_msgs are already installed"
else
    git clone https://github.com/micro-ROS/micro_ros_msgs.git
fi
if [ -d micro-ROS-Agent ]
then
    echo "The micro-ROS-Agent is already installed"
else
    git clone https://github.com/micro-ROS/micro-ROS-Agent.git
fi
