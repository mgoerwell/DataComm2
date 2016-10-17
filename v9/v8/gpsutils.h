#ifndef GPSUTILS_H
#define GPSUTILS_H

#include <gps.h>
#include <stdlib.h>
#include <errno.h>
#include "gpsprint.h"

void readLoop(struct gps_data_t *gpsdata);

#endif
