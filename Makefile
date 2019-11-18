CC=g++

PHONY all: lzw lzwm

lzw: lzw.o
	$(CC) lzw.cpp -o lzw

lzwm: lzwm.o
	$(CC) lzwm.cpp -o lzwm

debug: 
	$(CC) lzw.cpp -g -o lzw
	$(CC) part1.cpp -g -o lzwm


clean:
	rm -f lzw lzwm *.o binaryData.txt *.lzw *.lzw2 *.lzw22
	