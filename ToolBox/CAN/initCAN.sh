#!/bin/sh 
#load can modules and set/enable can interface
set -e
NO_CAN_HW_FOUND=1
deviceCAN0Path="/sys/class/net/can0"
deviceCAN1Path="/sys/class/net/can1"
if [ -d "$deviceCAN0Path" ] || [ -d "$deviceCAN1Path" ]; then
    modprobe can_dev
    modprobe can
    modprobe can_raw
    echo "Done: load driver!"
    state=$(cat /sys/class/net/can0/operstate)
    echo "$state"
    if [ "$state" = "down" ]; then
        ip link set can0 type can bitrate 500000
        ip link set up can0
        echo "Done: device configured! CAN HW is ready"
    fi
else
    echo "no CAN HW found"
    exit $NO_CAN_HW_FOUND
fi
