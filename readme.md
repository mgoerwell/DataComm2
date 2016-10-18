This is the gps project for this group.
To use it, you need to run the following commands on a raspberry PI

    dnf install gpsd
    dnf install gpsd-devel

Assuming you can SSH into your raspberry PI, you can then prepare to run the program
by doing the following.

	sudo killall gpsd
	sudo systemctl stop gpsd.socket
	sudo systemctl disable gpsd.socket
	sudo gpsd /dev/ttyUSB0 -F -n /var/run/gpsd.sock

This will kill any existing streams and then restart gpsd to ensure it hasn't gone to a low priority.
The project itself can then be prepared like so:

    navigate to the project directory on your PI
    make
    ./dcgps