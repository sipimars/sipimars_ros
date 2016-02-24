# sipimars_ros
This is the repository for all of the ros packages in the SIPI mars yard
##To deploy this onto a raspberry pi:
```
cd 
git clone https://github.com/sipimars/sipimars_ros.git
```
this should give you a directory ~/sipimars_ros
`cd /sipimars_ros`
then type 
`catkin_make`
to build it.  It will take a while on Pi1, better to compile on Pi2 and then swap SD card.
##Make the Pi run ROS on boot
Edit the rc.local file to run the roslaunch file when it finishes booting 

`sudo vi /etc/rc.local`

add at the end just before the "exit 0" line

`su -c '/home/pi/sipimars_ros/bootup.sh' pi &`

then reboot


##Only compiling one package

Compiling on Pi is very slow so if you are working on one package it is best to only compile it.

If you only want to compile a package named "my_package"

`catkin_make -DCATKIN_WHITELIST_PACKAGES="my_package"`

this will persist unitl you change it.  to recompile all

`catkin_make -DCATKIN_WHITELIST_PACKAGES=""`
##Cloning a Raspberry Pi

To clone a Raspberry Pi:
Remove microSD card from the Pi, put it in an SD card adapter and put it into a Linux laptop.
From a terminal type:
`df`
It will show the sd card as something like /dev/mmblk0p1
```
unmount the card by typing:
umount /dev/mmblk0p1
umount /dev/mmblk0p2
```
copy the card to an image file by typing:

`sudo dd if=/dev/mmblk0 of=pi_2015_05_11.img`

This will take a long time (5 min).  Resulting file will be as big as the sd card (8GB)
if you want to store it, you might want to zip it by typing

`gzip pi_2015_05_11.img`

to clone it to a new card,  put in new card (or old one but it will be completely overwritten) and type

`sudo dd if=pi_2015_05_11.img of=/dev/mmblk0`

this will take even longer (8min)
then type "sync" and eject the card
put it in a Pi and boot it.  The new Pi will have the same network name as the old, so you must change it.
boot up the Pi.  remote login using the original hostname

`ssh pi@pi2.local`
`sudo vi /etc/hosts`

change 127.0.0.0 <name> to your new name

`sudo vi /etc/hostname`

change to your new name

`sudo reboot`
