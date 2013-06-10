#!/usr/bin/env python
# encoding: utf-8

"""

"""
__author__ = "Caprinus"

###  Imports  ###

# ROS imports
import roslib; roslib.load_manifest('human_interface')
import rospy
import serial

# ROS msg and srv imports
from sensor_msgs.msg import Joy
from geometry_msgs.msg import Twist

# Python Libraries
import sys
import traceback
import time

###SERIAL

ser = serial.Serial('/dev/ttyACM0', 115200)
ser.xonxoff = False
ser.rtscts = False
ser.dsrdtr = False
ser.open()
ser.isOpen()

###  Variables  ###
LINEAR_SPEED = 100
ANGULAR_SPEED = 100

def add_nulls(num, cnt=2):
	cnt = cnt - len(str(num))
	nulls = '0' * cnt
	return '%s%s' % (nulls, num)

header = "$"
footer = "%"
k1=0.7
k2=0.4

class Joy2Twist(object):
	joyEnabled = True
	mode = 0
	def __init__(self):
		# Initialize the Node
		rospy.init_node("Joy2Twist")
		mode = 0
		# Setup the Joy topic subscription
		self.joy_subscriber = rospy.Subscriber("joy", Joy, self.handleJoyMessage, queue_size=1)
		# Setup the Twist topic publisher
		self.twist_publisher = rospy.Publisher("cmd_vel", Twist)
		# Spin
		rospy.spin()
		
	def handleJoyMessage(self, data):
		"""Handles incoming Joy messages"""
		leftSpeed = data.axes[1] * LINEAR_SPEED
		if self.mode == 0: #DUE STICK
			rightSpeed = data.axes[2] * ANGULAR_SPEED
		if self.mode == 1: #UNO STICK
			rightSpeed = data.axes[0] * ANGULAR_SPEED 
		if self.mode == 2: #MODALITA ACCELEROMETRO, INGUIDABILE
			leftSpeed = data.axes[13] * ANGULAR_SPEED
			rightSpeed = data.axes[14] * ANGULAR_SPEED
		command=""

		if data.buttons[12]==1: #TRIANGOLO CAMBIA TIPOLOGIA DI GUIDA
			time.sleep(0.5)
			self.mode=self.mode+1
			if self.mode >= 2:
				self.mode = 0
				
		if data.buttons[14]==1: #X BOOST
			leftSpeed *= 2;
			rightSpeed *= 2;
		if data.buttons[15]==1: #QUADRATO STOP
			leftSpeed *= 0;
			rightSpeed *= 0;
			
		#print "LEFT:  "+str(k1*leftSpeed)
		#print "RIGHT: "+str(k2*rightSpeed)
		rval=str(int(k1*leftSpeed+k2*rightSpeed))
		lval=str(int(k1*leftSpeed-k2*rightSpeed))
		#print "V Right Wheel: "+rval
		#print "V Left  Wheel: "+lval
		rval=int(rval)
		lval=int(lval)
		if rval>=0:
			code1="02"
		if rval<0:
			code1="03"
			rval=-rval
		if lval>=0:
			code2="05"
		if lval<0:
			code2="06"
			lval=-lval
		command=header+str(code1)+add_nulls(int(rval),4)+footer+"     "+header+str(code2)+add_nulls(int(lval),4)+footer
		print command
		print "MODE: "+str(self.mode)
		ser.flushInput
		ser.write(command)



###  If Main  ###
if __name__ == '__main__':
	try:
		Joy2Twist()
	except:
		rospy.logerr("Unhandled Exception in the joy2Twist Node:+\n"+traceback.format_exc())

