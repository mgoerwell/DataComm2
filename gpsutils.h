// this file exists to allow the key function of gpsutils to be used
// from other files.
#ifndef GPSUTILS_H
#define GPSUTILS_H

#include <gps.h>
#include <stdlib.h>
#include <errno.h>
#include "gpsprint.h"

void readLoop(struct gps_data_t *gpsdata);

#endif
