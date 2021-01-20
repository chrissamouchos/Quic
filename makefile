# paths
INCLUDE_PATH = ./include
SRC_PATH = ./src
OBJS_PATH = ./bin

#Define the compiler
CC = gcc

# Compile options. The -I<dir> informs the compiler where to seek include files
CFLAGS = -I$(INCLUDE_PATH)

#Define the dependencies
PDEP =	main.c \
		Utils.c \
		Directory_Functions.c

#Create the .o file with the needed functions
POBJS = $(patsubst %.c,$(OBJS_PATH)/%.o,$(PDEP))		#For primary program

#UNLEASH THE FUll POWER OF VALGRIND!!!
FULLVAL = --leak-check=full -v

# The executable programms
PEXEC = quic		#Primary program

#Compile all three main executables
all : $(PEXEC)

#Create all objects independently
$(OBJS_PATH)/%.o: $(SRC_PATH)/%.c
	$(CC) -c $^ -o $@ $(CFLAGS)

#Compile Primary Executable
$(PEXEC): $(POBJS)
	$(CC) $(POBJS) -o $(PEXEC) $(CFLAGS)


#Determine full valgrind
fvalgrind: $(PEXEC)
	valgrind $(FULLVAL) ./$(PEXEC)

#Determine simple valgrind
svalgrind: $(PEXEC)
	valgrind ./$(PEXEC) 

#Profiling for executed code, then show analysis on shell
profiling:
	{ \
	gprof $(PEXEC) gmon.out > analysis.txt;\
	cat analysis.txt;\
	rm -f gmon.out;\
	}

#Clean workspace, delete all executables and gmon files
clean:
	{ \
	rm -f $(POBJS) $(PEXEC) $(SOBJS) $(SLAVE);\
	rm -f gmon.out;  \
	}