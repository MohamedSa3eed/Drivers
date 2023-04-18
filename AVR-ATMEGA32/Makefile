SRC:= $(wildcard ./*/*.c) 
SRC+= $(wildcard ./*/*/*.c) 
PROJECT_NAME=led
OBJ=$(SRC:.c=.o)

CC=avr-gcc
LINKER=avr-objcopy
FLASHER=avrdude
MCU=atmega32
FRQ=8000000UL
# use gdwarf-2 in case of protues
CFLAGS=-mmcu=$(MCU) -O0 -DF_CPU=$(FRQ) -Wall -gdwarf-2 -g 
LFLAGS=-j .text -j .data -O ihex 
FFLAGS=-c usbasp -p m32 -B 0.5 -U Flash:w:${PROJECT_NAME}.hex:a 

all : $(PROJECT_NAME).hex

$(PROJECT_NAME).hex : $(PROJECT_NAME).elf
	@$(LINKER) $(LFLAGS) $< $@
	@echo linking done

$(PROJECT_NAME).elf: $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $@
	@echo compiling done

%.o : %.c
	@$(CC) $(CFLAGS) -c $< -o $@ 

flash : link 
	@$(FLASHER) $(FFLAGS)
	@echo flashing done

clean :
	@rm $(PROJECT_NAME).hex $(PROJECT_NAME).elf $(OBJ)
	@echo every thing is clean
