# Project: Parking
# Makefile created by S.H.M ,Email:posinfo@126.com

CPP  = arm-elf-g++.exe
CC   = arm-elf-gcc.exe
AR  = arm-elf-ar.exe
LD   = arm-elf-ld.exe
OBJCOPY   = arm-elf-objcopy.exe
OBJ  = utility.o gprs.o cardTest.o cardService.o paymentService.o main.o
LINKOBJ  = utility.o gprs.o cardTest.o cardService.o paymentService.o main.o
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

cardTest.o: cardTest.c
	$(CC) $(CFLAGS) -c cardTest.c -o cardTest.o
	
cardService.o: cardService.c
	$(CC) $(CFLAGS) -c cardService.c -o cardService.o
	
utility.o: utility.c
	$(CC) $(CFLAGS) -c utility.c -o utility.o
		
gprs.o: gprs.c
	$(CC) $(CFLAGS) -c gprs.c -o gprs.o
	
paymentService.o: paymentService.c
	$(CC) $(CFLAGS) -c paymentService.c -o paymentService.o	
	
main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o
	
clean:
	${RM} $(OBJ) $(AllConf) $(BIN)
	
main.cof: $(OBJ)
	$(LD) C:/soft/HandPos/IDE/crt0.o $(LINKOBJ) -o main.cof $(LIBS) -T C:/soft/HandPos/IDE/ldscript
	$(OBJCOPY) -O binary main.cof $(BIN)
	
	
