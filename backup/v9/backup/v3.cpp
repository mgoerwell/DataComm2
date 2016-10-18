/*------------------------------------------------------------------------------------------------------------------
--	SOURCE FILE:	dcgps.cpp -	An application that will create a basic gps tracker for
--					a raspberry PI
--
--	PROGRAM:		dcGPS
--
--	FUNCTIONS:
--				int Main ()
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
--	This file will contain the main function only. It will allocate the gps_data_t structure, open the stream to gpsd,
--  and then start the stream. It will also perform any clean-up or freeing operations upon application termination.
----------------------------------------------------------------------------------------------------------------------*/

#include <gps.h>
#include <stdlib.h>
#include "gps-utils.cpp"
#include "gpsprint.cpp"
#include "structure.h"

static unsigned int flags = WATCH_ENABLE;

static struct fixsource_t source;
static struct gps_data_t *gpsdata;
int main() {
	
	gpsdata  = (gps_data_t*) malloc(sizeof(struct gps_data_t));
	
	int stream;
	stream = gps_open(source.server,source.port,gpsdata);
	if (stream == -1) {
		fprintf(stderr,"Stream failed to open\n");
		return 1;
	} else {
		fprintf(stdout,"Stream open\n");
	}
	if (source.device == NULL) {
		fprintf(stderr,"GPS device source not found\n");
		return 1;
	} else {
		flags |= WATCH_DEVICE;
	}

	gps_stream(gpsdata,flags,source.device);
	
	//readLoop(gpsdata);
	
	gps_stream(gpsdata,WATCH_DISABLE,NULL);
	gps_close(gpsdata);
	
}
