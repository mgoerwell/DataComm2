/*------------------------------------------------------------------------------------------------------------------
--	SOURCE FILE:	dcgps.cpp -	An application that will create a basic gps tracker for
--					a raspberry PI
--
--	PROGRAM:		dcGPS
--
--	FUNCTIONS:
--				    int Main ()
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
#include "gpsutils.h"
#include "structure.h"


static unsigned int flags = WATCH_ENABLE;

static struct fixsource_t source;
static struct gps_data_t *gpsdata;

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION:  main
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
-- INTERFACE:  int main()
--
-- RETURNS:    an int equal to zero.
--
-- NOTES:
--             Call this function to start the program. It allocates the data structure for the gpsdata,
--             then attempts to open a stream. Once the stream is opened it starts the read loop. It then
--             performs cleanup once the program closes.
----------------------------------------------------------------------------------------------------------------------*/
int main() {
	
	gpsdata  = (gps_data_t*) malloc(sizeof(struct gps_data_t));
	
	int stream;
	stream = gps_open(source.server,source.port,gpsdata);
	if (stream != 0) {
		fprintf(stderr,"Stream failed to open\n");
		return 1;
	} 
	
    if (source.device != NULL) {
		flags |= WATCH_DEVICE;
	}

	gps_stream(gpsdata,flags,source.device);
	
	readLoop(gpsdata);
	
	gps_stream(gpsdata,WATCH_DISABLE,NULL);
	gps_close(gpsdata);
	
}
