#!/bin/bash
#
# shell script for starting/stopping the PCI device driver.

# device driver name
DEVICE_NAME=q8_hil_card

# module name
MODULE_NAME=q8driver
MODULE=$MODULE_NAME.ko

# integer i for counting
typeset -i i=0 

case $1 in
    start)
	    # cleanup
		rm -f /dev/$DEVICE_NAME
		# load the module
		insmod ./$MODULE || exit 1
		# get the major number(s) of the device driver
		MAJOR_NUMBERS=`cat /proc/devices | awk -v dev=$DEVICE_NAME '$2==dev { print $1 }'`
		# count the devices 
		for N in $MAJOR_NUMBERS ; do
			if [ $i -eq 0 ] ; then
		    # store the first major number
				MAJOR=$N
			fi
			i=i+1
		done
		if [ ! $i -eq 1 ] ; then
		    	echo "Warning: Found $i devices."
		fi
		if [ $i -eq 0 ] ; then
			echo "No device found. Aborting now."
			exit -1
		fi
		# create device file
		mknod /dev/$DEVICE_NAME c $MAJOR 0
		# set to read only
		chmod a-x-w+r /dev/$DEVICE_NAME          
		~/Zenom/HapticWand/examples/ReadWriteDigital/ReadWriteDigital
		;;
	stop)
	    # remove (unload) the module
		rmmod $MODULE_NAME
		# cleanup: remove the device file
		rm -f /dev/$DEVICE_NAME
    	;;
    restart)
	    $0 stop
		$0 start
		exit -1
	    ;;
    *)
	    echo "Syntax: $0 {start|stop|restart}"
	    exit -1
	    ;;
esac

exit 0
