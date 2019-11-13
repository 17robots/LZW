CC=g++

lzw: lzw.o
	$(CC) lzw.cpp -o lzw

part1: part1.o
	$(CC) part1.cpp -o part1

part2: part2.o
	$(CC) part2.cpp -o part2

debug: 
	$(CC) lzw.cpp -g -o lzw
	$(CC) part1.cpp -g -o part1
	$(CC) part2.cpp -g -o part2


clean:
	rm -f lzw part1 *.o binaryData.txt *.lzw
	