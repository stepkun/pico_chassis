
#!/bin/sh

echo "Installing micro-ROS-Agent"

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
