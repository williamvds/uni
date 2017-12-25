all: recommend find_artist sort_artists query_plays

clean:	
	rm *.o recommend find_artist sort_artists query_plays

list.o: list.c list.h
	gcc -g -c list.c

sort.o: sort.c sort.h
	gcc -g -c sort.c

ascrobbler.o: ascrobbler.c ascrobbler.h
	gcc -g -c ascrobbler.c

find_artist.o: find_artist.c
	gcc -g -c find_artist.c

sort_artists.o: sort_artists.c
	gcc -g -c sort_artists.c

query_plays.o: query_plays.c
	gcc -g -c query_plays.c

recommend.o: recommend.c
	gcc -std=c99 -g -c recommend.c

find_artist: find_artist.o ascrobbler.o list.o sort.o
	gcc -g -o find_artist find_artist.o ascrobbler.o list.o sort.o

sort_artists: sort_artists.o ascrobbler.o list.o sort.o
	gcc -g -o sort_artists sort_artists.o ascrobbler.o list.o sort.o

query_plays: query_plays.o ascrobbler.o list.o sort.o
	gcc -g -o query_plays query_plays.o ascrobbler.o list.o sort.o

recommend: recommend.o list.o sort.o ascrobbler.o
	gcc -g -o recommend recommend.o list.o sort.o ascrobbler.o
