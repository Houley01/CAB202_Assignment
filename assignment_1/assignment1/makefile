# *********************************************
# *        Student Name: Ethan Houley         *
# *      Student Number: n10353950            *
# *           File Name: nakefile             *
# *********************************************

OBJ=main.o ethanHelpers.o helpers.o screenLayout.o vacuum.o trash.o collision.o battery.o charger.o

# Fix the directories to match your file organisation.
CC_FLAGS=-std=gnu99 -I./ZDK -Wall -Werror -g
LD_FLAGS=-L./ZDK -lzdk -lncurses -lm

a1_n10353950: $(OBJ)
	gcc $(OBJ) $(LD_FLAGS) -o $@

%.o : %.c
	gcc -c $< $(CC_FLAGS)
