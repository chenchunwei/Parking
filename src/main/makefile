# Project: Parking
# Makefile created by S.H.M ,Email:posinfo@126.com

CPP  = arm-elf-g++.exe
CC   = arm-elf-gcc.exe
AR  = arm-elf-ar.exe
LD   = arm-elf-ld.exe
OBJCOPY   = arm-elf-objcopy.exe
OBJ  = gprs.o main.o card.o
LINKOBJ  = gprs.o  main.o card.o
LIBS =   
INCS = 
CXXINCS = 
AllConf = main.cof 
Cof  = main.cof
BIN  = main.bin
CXXFLAGS = $(CXXINCS)   -Wall
CFLAGS = $(INCS)   -Wall
RM = rm -f

.PHONY: all clean

all: $(Cof)

card.o: card.c
	$(CC) $(CFLAGS) -c card.c -o card.o
	
gprs.o: gprs.c
	$(CC) $(CFLAGS) -c gprs.c -o gprs.o
	
main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o
	
clean:
	${RM} $(OBJ) $(AllConf) $(BIN)
	
main.cof: $(OBJ)
	$(LD) C:/soft/HandPos/IDE/crt0.o $(LINKOBJ) -o main.cof $(LIBS) -T C:/soft/HandPos/IDE/ldscript
	$(OBJCOPY) -O binary main.cof $(BIN)
	
	
