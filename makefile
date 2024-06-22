.SUFFIXES : .cpp

CC = g++

CXXFLAGS = -g -std=c++11

OBJS = Lab2.o

TARGET = Lab2

$(TARGET) : $(OBJS)
	$(CC) -o $@ $(OBJS)

.cpp.o:
	$(CC) -c $(CXXFLAGS) $(INCDIR) $<
clean:
	rm -f $(OBJS) $(TARGET) core
zipIt:
	zip -r Lab2.cpp makefile
