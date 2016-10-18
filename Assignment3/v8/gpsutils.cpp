/*------------------------------------------------------------------------------------------------------------------
--	SOURCE FILE:		gps-utils.cpp -	this file will read data from the gps sensors and send it to
--				be proccessed for display to the user.	
--
--	PROGRAM:		searchGPS
--
--	FUNCTIONS:
--				void readLoop(struct gps_data_t *gpsdata)
--                  		int sendToPrint(const struct gps_data_t *gpsdata)
--                  		bool errorCheck(int readstate)
--
--	DATE:			October 5, 2016
--
--	REVISIONS:		Initial version - October 5, 2016
--
--	DESIGNER:		Matt Goerwell
--
--	PROGRAMMER:		Matt Goerwell
--
--	NOTES:
--	This file will conatin at least two functions. One that continuously reads data from the GPS sensors,
--  	and one that sends the data from those sensors to be printed on screen. It is also recommended to have
--  	an error checking function in this file.
----------------------------------------------------------------------------------------------------------------------*/

#include <gps.h>
#include <stdlib.h>
#include <errno.h>
#include "gpsprint.h"

void readLoop(struct gps_data_t *gpsdata);
bool errorCheck(int readstate);
int sendToPrint(const struct gps_data_t *gpsdata) ;

void readLoop(struct gps_data_t *gpsdata) {
	int waitcycles = 0;
	int readstate;
	fprintf(stdout, "pre-read loop\n");
	for (;;) {
		fprintf(stdout, "In the for loop\n");
		if (!gps_waiting(gpsdata, 50000000)) {
			fprintf(stdout, "Timeout\n");
			waitcycles++;
			if (waitcycles > 200) {
				break;
			}
		continue;
		}

		if (gps_read(gpsdata) == -1) {
			fprintf(stderr, "Socket error\n");
		} else {
			print_data(gpsdata);
			//fprintf(stdout, "Printing data\n");
			//sendToPrint(gpsdata);
		}
		/*fprintf(stdout, "read loop\n");
		if(!gps_waiting(gpsdata,500000)) {
			fprintf(stdout, "tieout occured");
			if (4 < waitcycles++) {
				fprintf(stderr,"GPS Timeout\n");
				break;
			}
		} else {
			waitcycles = 0;
			errno = 0;
			readstate  = 0;
			readstate  = gps_read(gpsdata);
			if (errorCheck(readstate) == false) {
				break;
			} else {
				//sendToPrint(gpsdata);
			}
		}*/
	}
}


bool errorCheck(int readstate){
	if (readstate == -1) {
		if (errno == 0) {
			(void)fprintf(stderr, "GPS signal has dissapeared");
			return false;
		} else {
			(void)fprintf(stderr, "GPS Read has returned an error");
			return false;
		}
	} 
	return true;
}

int sendToPrint(struct gps_data_t *gpsdata) {

	print_data(gpsdata);
	return 0;
}


