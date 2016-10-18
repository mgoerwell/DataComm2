/*------------------------------------------------------------------------------------------------------------------
--	SOURCE FILE:	gpsprint.cpp -	this file will print the information given by a gps tracker to
--					the user's console terminal		
--
--	PROGRAM:		printGPS
--
--	FUNCTIONS:
--					void get_satellites(struct gps_data_t *gpsdata);
--                  void print_lat_long(struct gps_data_t *gpsdata);
--                  void print_sat_parameters(struct gps_data_t *gpsdata);
--                  void print_time(struct gps_data_t *gpsdata);
--                  void print_data(struct gps_data_t *gpsdata);
--                  void test()
--
--	DATE:			October 5, 2016
--
--	REVISIONS:		Initial version - October 5, 2016
--
--	DESIGNER:		Robert Arendac
--
--	PROGRAMMER:		Robert Arendac
--
--	NOTES:
--	This file will primarily contain one function. It will take the gps_data_t structure, given to it by gps-utils.cpp,
--  and then extract the data from it and print it to the screen. It must display the following: Time Stamp (UTC),
--  Lattitude and Longitude, the PRN of each sattelite found, altitude, the azimuth, SNR, and the used flag for each
--  sattelite. A graphical implementation is not required, but will give bonus marks.
----------------------------------------------------------------------------------------------------------------------*/
#include <gps.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

#define MAX_POSSIBLE_SATS (MAXCHANNELS - 2)

static bool usedflags[MAXCHANNELS];

void get_satellites(struct gps_data_t *gpsdata);
void print_lat_long(struct gps_data_t *gpsdata);
void print_sat_parameters(struct gps_data_t *gpsdata);
void print_time(struct gps_data_t *gpsdata);
void print_data(struct gps_data_t *gpsdata);
//static void test();


/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION:     get_satellites
--
-- DATE:         Oct 15, 2016
--
-- REVISIONS:
--
-- DESIGNER:     Robert Arendac
--
-- PROGRAMMER:   Robert Arendac
--
-- INTERFACE:    void get_satellites(struct gps_data_t *gpsdata)
--                    struct gps_data_t *gpsdata: A pointer to a gps_data_t structure that holds all the gps data
--
-- RETURNS:      void.
--
-- NOTES:
-- This function will get all the satellites in view and that will be used to collect data.
----------------------------------------------------------------------------------------------------------------------*/
void get_satellites(struct gps_data_t *gpsdata) {
	for (int i = 0; i < MAXCHANNELS; i++) {
		usedflags[i] = false;
		for (int j = 0; j < gpsdata->satellites_used; j++) {
			if (gpsdata->used[0] == gpsdata->PRN[0])
				usedflags[i] = true;
		}
	}
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION:      print_lat_long
--
-- DATE:          Oct 15, 2016
--
-- REVISIONS:
--
-- DESIGNER:      Robert Arendac
--
-- PROGRAMMER:    Robert Arendac
--
-- INTERFACE:     void print_lat_long(struct gps_data_t *gpsdata)
--                     struct gps_data_t *gpsdata: A pointer to a gps_data_t structure that holds all the gps data
--
-- RETURNS:       void.
--
-- NOTES:
-- This function will print both the latitude and longitude if it can get a good fix.  If not, it will print N/A
----------------------------------------------------------------------------------------------------------------------*/
void print_lat_long(struct gps_data_t *gpsdata) {
	if (gpsdata->fix.mode >= MODE_2D && isnan(gpsdata->fix.latitude) == 0) {
		fprintf(stdout, "Latitude:\t%.2f %c\n", gpsdata->fix.latitude,
		                                  (gpsdata->fix.latitude > 0) ? 'N' : 'S');
	} else
		fprintf(stderr, "N/A");
	
	if (gpsdata->fix.mode >= MODE_2D && isnan(gpsdata->fix.longitude) == 0) {
		fprintf(stdout, "Longitude:\t%.2f %c\n\n", gpsdata->fix.longitude,
		                                  (gpsdata->fix.longitude > 0) ? 'E' : 'W');
	} else
		fprintf(stderr, "LAT/LONG:\tN/A");
}


/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION:     print_sat_parameters
--
-- DATE:         Oct 15, 2016
--
-- REVISIONS:
--
-- DESIGNER:     Robert Arendac
--
-- PROGRAMMER:   Robert Arendac
-- 
-- INTERFACE:    void print_sat_parameters(struct gps_data_t *gpsdata)
--                    struct gps_data_t *gpsdata: A pointer to a gps_data_t structure that holds all the gps data
--
-- RETURNS:      void.
--
-- NOTES:
-- This function will print information about the satellites that are visible.  This will include the PRN, elevation,
-- azimuth, SNR, and whether or not it is used.
----------------------------------------------------------------------------------------------------------------------*/
void print_sat_parameters(struct gps_data_t *gpsdata) {
	if (gpsdata->satellites_visible != 0) {
		for (int i = 0; i < MAX_POSSIBLE_SATS; i++) {
			if (i < gpsdata->satellites_visible) {
				fprintf(stdout, "PRN: %3d\tElevation: %02d\tAzimuth: %03d\tSNR: %05.2f\t Used: %c\n",
				        gpsdata->PRN[i],
						gpsdata->elevation[i],
						gpsdata->azimuth[i],
						gpsdata->ss[i],
						(usedflags[i]) ? 'Y' : 'N');
			}
		}
	} else
		fprintf(stderr, "\nNo satellites visible\n");
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION:     print_time
--
-- DATE:         Oct 15, 2016
--
-- REVISIONS:
--
-- DESIGNER:     Robert Arendac
--
-- PROGRAMMER:   Robert Arendac
--
-- INTERFACE:    void print_time(struct gps_data_t *gpsdata)
--                    struct gps_data_t *gpsdata: A pointer to a gps_data_t structure that holds all the gps data
--
-- RETURNS:      void.
--
-- NOTES:
-- This function prints out the timestamp of when the satellite fix was last updated.  The timestamp_t is converted into
-- a time_t in order to more easily print out the data.  The data is then converted into a string so it can be printed
-- to the console.
----------------------------------------------------------------------------------------------------------------------*/
void print_time(struct gps_data_t *gpsdata) {
	time_t gpstime;
	gpstime = (time_t) gpsdata->fix.time;
	
	fprintf(stdout, "Time:\t\t%s", ctime(&gpstime));
}


/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION:     print_data
--
-- DATE:         Oct 15, 2016
--
-- REVISIONS:
--
-- DESIGNER:     Robert Arendac
--
-- PROGRAMMER:   Robert Arendac
--
-- INTERFACE:    void print_data(struct gps_data_t *gpsdata)
--                    struct gps_data_t *gpsdata: A pointer to a gps_data_t structure that holds all the gps data
--
-- RETURNS:      void.
--
-- NOTES:
-- This function first determines which satellites will be used, and then prints out all the necessary information.
-- This is the main printing function that will be called from gps-utils.
----------------------------------------------------------------------------------------------------------------------*/
void print_data(struct gps_data_t *gpsdata) {
	get_satellites(gpsdata);
	print_sat_parameters(gpsdata);
	print_time(gpsdata);
	print_lat_long(gpsdata);
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION:     test
--
-- DATE:         Oct 15, 2016
--
-- REVISIONS:
--
-- DESIGNER:     Robert Arendac
--
-- PROGRAMMER:   Robert Arendac
--
-- INTERFACE:    void test()
--
-- RETURNS:      void.
--
-- NOTES:
-- This function is used for testing purposes.  A gps_data_t struct is created and values are hard-coded into it.
-- The main print function is then called to see if the values were printed succesfully.  This verifies that as long
-- as the gps-utils was able to succesfully read data into the gps_data_t struct, it should print succesfully as well.
----------------------------------------------------------------------------------------------------------------------*/

/*void test() {
	struct gps_data_t *gpsdata;
	
	gpsdata->satellites_used = 1;
	gpsdata->satellites_visible = 1;
	gpsdata->used[0] = 24;
	gpsdata->PRN[0] = 24;
	gpsdata->elevation[0] = 10;
	gpsdata->azimuth[0] = 30;
	gpsdata->ss[0] = 40;
	gpsdata->fix.mode = 2;
	gpsdata->fix.latitude = 5;
	gpsdata->fix.longitude = 5;
	gpsdata->skyview_time = 1476255458;
	gpsdata->fix.time = 1476255458;
	
	print_data(gpsdata);
}*/


