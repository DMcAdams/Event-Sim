# build an executable named eventsim
event_sim: eventsim.c
	gcc -o eventsim eventsim.c
	gcc -o test test.c
