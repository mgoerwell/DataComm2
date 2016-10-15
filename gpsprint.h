#ifndef GPSPRINT_H
#define GPSPRINT_H

#include <gps.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

#define MAX_POSSIBLE_SATS (MAXCHANNELS - 2)

void print_data(struct gps_data_t *gpsdata);
#endif

