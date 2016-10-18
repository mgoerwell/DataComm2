CC=g++ 
CFLAGS =-c -std=c++11 -Wall -W -pedantic
CLIB=-lgps -pthread

dcgps: dcgps.o gpsutils.o gpsprint.o
	$(CC) -o dcgps dcgps.o gpsutils.o gpsprint.o $(CLIB)

clean:
	rm -f *.o core.* dcgps
dcgps.o:
	$(CC) $(CFLAGS)  dcgps.cpp 
gpsutils.o: 
	$(CC) $(CFLAGS)  gpsutils.cpp
gpsprint.o:
	$(CC) $(CFLAGS)  gpsprint.cpp


