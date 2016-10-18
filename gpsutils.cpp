/*------------------------------------------------------------------------------------------------------------------
--	SOURCE FILE:	gps-utils.cpp -	this file will read data from the gps sensors and send it to
--				    be proccessed for display to the user.	
--
--	PROGRAM:		searchGPS
--
--	FUNCTIONS:
--				    void readLoop(struct gps_data_t *gpsdata)
--                 	int sendToPrint(const struct gps_data_t *gpsdata)
--                 	bool errorCheck(int readstate)
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
--  and one that sends the data from those sensors to be printed on screen. It is also recommended to have
--  an error checking function in this file.
----------------------------------------------------------------------------------------------------------------------*/

#include <gps.h>
#include <stdlib.h>
#include <errno.h>
#include "gpsprint.h"

void readLoop(struct gps_data_t *gpsdata);
bool errorCheck(int readstate);

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION:  readLoop
--
-- DATE:      October 18, 2016
--
-- REVISIONS: Initial Version - October 5  2016
--            Final   Version - October 18 2016
--
-- DESIGNER:   Matt Goerwell
--
-- PROGRAMMER: Matt Goerwell
--
-- INTERFACE:  void readLoop(struct gps_data_t *gpsdata)
--                  struct gps_data_t *gpsdata: A pointer to a gps_data_t structure that holds all the gps data
--
-- RETURNS:    void.
--
-- NOTES:
--             Call this function to start the scanning loop of the program. It watches for timeouts and
--             reads any available data from the gps_stream 
----------------------------------------------------------------------------------------------------------------------*/
void readLoop(struct gps_data_t *gpsdata) {
	int waitcycles = 0;
	
	for (;;) {
		if (!gps_waiting(gpsdata, 500000)) {
			waitcycles++;
			if (waitcycles > 240) {
				fprintf(stdout, "GPS Wait Timeout\n");
				break;
			}			
		}
		else{
			waitcycles = 0;
			if (!errorCheck(gps_read(gpsdata))) {
				break;
			} else {
				print_data(gpsdata);					
			}
		}
	}
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION:  errorCheck
--
-- DATE:      October 18, 2008
--
-- REVISIONS: Initial Version - October 5  2016
--            Final   Version - October 18 2016
--
-- DESIGNER:   Matt Goerwell
--
-- PROGRAMMER: Matt Goerwell
--
-- INTERFACE:  bool errorCheck(int readstate)
--                  int readstate: an integer containing the return value of a gps_read call.
--
-- RETURNS:    A boolean. Equals true if no errors were detected, false otherwise.
--
-- NOTES:
--             Call this function to check for errors in a gps_read. It checks if the readstate returned by the
--             gps_read call was a failure, and then determines the type of error based on errno.
----------------------------------------------------------------------------------------------------------------------*/
bool errorCheck(int readstate){

	if (readstate == -1) {
		fprintf(stderr, "ags: Socket error 4\n");

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

