CC = g++ #c++ compiler
CFLAGS = -O2 -Wall -std=c++17 #compilation flags
SRC = member.h member.cpp lattice.h lattice.cpp main.cpp #source files
EXEC = program #names the executable as program
OBJ = $(SRC:.cpp=.o) #converts .cpp to .o

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@ #command

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(EXEC) #command
	@echo "Build complete" #confirms build made

#command for removing object files after
clean:
	rm -f $(EXEC)
	find . -name "*.o" -type f -delete
