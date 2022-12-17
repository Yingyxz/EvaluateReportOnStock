CC = g++
CFLAGS = -Wall -ggdb3 -std=c++11 -lcurl -pthread

main: main.o ReadData.o Transaction.o Stock.o Utility.o gnuplot_CAAR.h
	$(CC) $(CFLAGS) -o main main.o ReadData.o Transaction.o Stock.o Utility.o

main.o: main.cpp ReadData.h Transaction.h Stock.h Utility.h
	$(CC) $(CFLAGS) -c main.cpp

ReadData.o: ReadData.cpp ReadData.h Stock.h Utility.h
	$(CC) $(CFLAGS) -c ReadData.cpp

Stock.o: Stock.cpp Stock.h Utility.h Transaction.h
	$(CC) $(CFLAGS) -c Stock.cpp
	
Transaction.o: Transaction.cpp Transaction.h
	$(CC) $(CFLAGS) -c Transaction.cpp
	
Utility.o: Utility.cpp Utility.h
	$(CC) $(CFLAGS) -c Utility.cpp
	
plot.exe: main.o gnuplot_CAAR.h
	$(CC) $(CFLAGS) -o plot.exe main.o

clean:
	rm -rf  main  *.o
