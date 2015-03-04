#Capybara Robot

Capybara is a firmware for the ![dspic33FJ128MC802](http://www.microchip.com/wwwproducts/Devices.aspx?product=dsPIC33FJ128MC802) providing basic robot odometry and serial communication.
Aim of the project is to develop an open-firmware and open-hardware mobile base for robotics students in particular 
and for all roboticists and hobbists.

## Main features
* 1khz pid control loop for each motor
* Fully extensible serial command protocol, ascii and binary for free! Tx and Rx fully managed by interrupts
* ROS nodes (control, odomtetry) available here https://github.com/mauriliodc/capybarauno
* Not the usual "while(1)" thing, firmware fully event driven
* Open hardware, board schematics soon available
* The biggest rodent ever

![alt text](http://i.imgur.com/QOzCvIJ.jpg "Capybara")



