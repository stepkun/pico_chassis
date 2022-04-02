
#!/bin/sh

echo "Installing micro-ROS-Agent"

# micro-ROS-Agent:
cd ..
if [ -d micro-ROS-Agent ]
then
    echo "The micro-ROS-Agent is already installed"
else
    git clone  https://github.com/micro-ROS/micro-ROS-Agent.git
    cd micro-ROS-Agent
    git submodule update --init
fi
