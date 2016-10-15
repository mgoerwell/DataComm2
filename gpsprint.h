#ifndef GPSPRINT_H
#define GPSPRINT_H

void get_satellites(struct gps_data_t *gpsdata);
void print_lat_long(struct gps_data_t *gpsdata);
void print_sat_parameters(struct gps_data_t *gpsdata);
void print_time(struct gps_data_t *gpsdata);
void print_data(struct gps_data_t *gpsdata);