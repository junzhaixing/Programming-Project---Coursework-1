
# code details

EXE = ./library
SRC= main.c book_management.c library.c  reg_login.c user.c utility.c

# generic build details

CC=      gcc
CFLAGS= -std=c99 -Wall
CLINK= 

# compile to object code

OBJ= $(SRC:.c=.o)

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $<

# build executable: type 'make'

$(EXE): $(OBJ)
	$(CC) $(OBJ) $(CLINK) -o $(EXE) 

# clean up and remove object code and executable: type 'make clean'

clean:
	rm -f $(OBJ) $(EXE)

# dependencies

main.o:      main.c library.h book_management.h
library.o:   library.c library.h reg_login.h user.h  book_management.h utility.h
reg_login.o: reg_login.c reg_login.h  book_management.h utility.h
user.o:      user.c user.h  book_management.h utility.h
book_management.o:      book_management.c book_management.h utility.h
utility.o:   utility.c utility.h 

