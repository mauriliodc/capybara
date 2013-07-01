#!/usr/bin/env python
import rospy
import roslib
roslib.load_manifest('capybara_running_wild')
from std_msgs.msg import String
from nav_msgs.msg import Odometry
from geometry_msgs.msg import Quaternion
from geometry_msgs.msg import Twist
from geometry_msgs.msg import Pose
import tf
from math import sin
from math import cos
import serial
import threading
import sys
import traceback
import time


def MainLoop():
	#LANCIARE CON  rosrun capybara_running_wild capybara_parameter_test.py _cose:=fatti
	a = default_param = rospy.get_param('~cose', 'default_value')
	while 1:
		print "A: "+str(a)
	rospy.spin()


if __name__ == '__main__':
	rospy.init_node('capybara_parameter_test', anonymous=True)
	MainLoop()
