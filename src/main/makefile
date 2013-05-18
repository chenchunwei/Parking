# Project: Parking
# Makefile created by S.H.M ,Email:posinfo@126.com

CPP  = arm-elf-g++.exe
CC   = arm-elf-gcc.exe
AR  = arm-elf-ar.exe
LD   = arm-elf-ld.exe
OBJCOPY   = arm-elf-objcopy.exe
OBJ  = main.o gprs.o
LINKOBJ  = main.o gprs.o
LIBS =   
INCS = 
CXXINCS = 
Cof  = main.cof
BIN  = main.bin
CXXFLAGS = $(CXXINCS)   -Wall
CFLAGS = $(INCS)   -Wall
RM = rm -f
	
.PHONY: all  clean

all: $(Cof)

gprs.o: gprs.c
	$(CC) $(CFLAGS) -c gprs.c -o gprs.o
		
clean:
	${RM} $(OBJ) $(Cof) $(BIN)

main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o

$(Cof): $(OBJ)
	$(LD) C:/soft/HandPos/IDE/crt0.o $(LINKOBJ)  -o $(Cof) $(LIBS) -T C:/soft/HandPos/IDE/ldscript
	$(OBJCOPY) -O binary $(Cof) $(BIN)
