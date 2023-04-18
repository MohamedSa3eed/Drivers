SRC=APP/main.c 
PROJECT_NAME=led
OBJ=$(SRC:.c=.o)

CC=avr-gcc
LINKER=avr-objcopy
FLASHER=avrdude
# use gdwarf-2 in case of protues
CFLAGS=-mmcu=atmega32 -O0 -DF_CPU=8000000UL -Wall -gdwarf-2 -c -o $(OBJ) $(SRC)  
LFLAGS=-j .text -j .data -O ihex $(OBJ) $(PROJECT_NAME).hex 
FFLAGS=-c usbasp -p m32 -B 0.5 -U Flash:w:${PROJECT_NAME}.hex:a 

flash : link 
	@$(FLASHER) $(FFLAGS)
	@echo flashing done

link : compile 
	@$(LINKER) $(LFLAGS)
	@echo linking done

compile : $(SRC)
	@$(CC) $(CFLAGS)  
	@echo compiling done

clean :
	@rm $(PROJECT_NAME).hex $(OBJ)
	@echo every thing is clean
