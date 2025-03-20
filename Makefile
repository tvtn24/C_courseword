CC = gcc
CFLAGS = -Wall -g -std=gnu99


all: demo_histogram demo_shuffle wordlengths anagram anaquery patience pstatistics

# Wordlengths
wordlengths: wordlengths.o histogram.o
	$(CC) $(CFLAGS) -o wordlengths wordlengths.o histogram.o -lm

histogram.o: histogram.c histogram.h
	$(CC) $(CFLAGS) -c histogram.c

demo_histogram: demo_histogram.o histogram.o
	$(CC) $(CFLAGS) -o demo_histogram demo_histogram.o histogram.o

demo_histogram.o: demo_histogram.c
	$(CC) $(CFLAGS) -c demo_histogram.c

wordlengths.o: wordlengths.c histogram.h
	$(CC) $(CFLAGS) -c wordlengths.c histogram.h

# Anagram

anaquery: anaquery.o make_anagram_list.o
	$(CC) $(CFLAGS) -o anaquery anaquery.o make_anagram_list.o -lm

anagram: anagram.o make_anagram_list.o histogram.o
	$(CC) $(CFLAGS) -o anagram anagram.o make_anagram_list.o histogram.o -lm

make_anagram_list.o: make_anagram_list.c make_anagram_list.h
	$(CC) $(CFLAGS) -c make_anagram_list.c 

anagram.o: anagram.c make_anagram_list.h histogram.h
	$(CC) $(CFLAGS) -c  anagram.c 

anaquery.o: anaquery.c make_anagram_list.h
	$(CC) $(CFLAGS) -c anaquery.c 

# Shuffle

demo_shuffle: demo_shuffle.o shuffle.o
	$(CC) $(CFLAGS) -o demo_shuffle demo_shuffle.o shuffle.o

shuffle.o:  shuffle.c shuffle.h
	$(CC) $(CFLAGS) -c shuffle.c

demo_shuffle.o: demo_shuffle.c shuffle.h
	$(CC) $(CFLAGS) -c demo_shuffle.c

# Patience 

patience: patience.o play.o shuffle.o histogram.o
	$(CC) $(CFLAGS) -o patience patience.o play.o shuffle.o histogram.o -lm

pstatistics: pstatistics.o play.o shuffle.o histogram.o
	$(CC) $(CFLAGS) -o pstatistics pstatistics.o play.o shuffle.o histogram.o -lm

play.o: play.c play.h
	$(CC) $(CFLAGS) -c play.c

pstatistics.o: pstatistics.c play.h shuffle.h histogram.h
	$(CC) $(CFLAGS) -c pstatistics.c histogram.h

patience.o: patience.c play.h shuffle.h
	$(CC) $(CFLAGS) -c patience.c

#Clean up
clean:
	rm -f anaquery anagram patience pstatistics demo_shuffle demo_histogram wordlengths

