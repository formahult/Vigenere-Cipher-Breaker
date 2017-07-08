# PolyCrack: Makefile
# Edited: 26MAR16
# Author: Leo Sleet

NAME = polycrack
INCLUDE = -I./include
CC = g++
CFLAGS = -Wall -Werror -pedantic -std=c++11 $(INCLUDE)
DEBUG = -g
OBJECTS = TextUtils.o Frequency.o KeyAnalyser.o Vigenere.o FileManager.o
HEADERS = PolyCrack.hpp
TESTING = test.cpp
SUBDIR = ./src

$(NAME):	main.o $(OBJECTS)
	$(CC) $(CFLAGS) $(DEBUG) -o $(NAME) $^

check: $(SUBDIR)/$(TESTING) $(OBJECTS)
	$(CC) $(CFLAGS) -g -o testPolyCrack $^
	./testPolyCrack
	rm -f testPolyCrack

test.o: $(SUBDIR)/test.cpp
	$(CC) $(CFLAGS) $(DEBUG) -c $^

main.o: $(SUBDIR)/main.cpp
	$(CC) $(CFLAGS) $(DEBUG) -c $^

TextUtils.o: $(SUBDIR)/TextUtils.cpp
	$(CC) $(CFLAGS) $(DEBUG) -c $^

FileManager.o: $(SUBDIR)/FileManager.cpp
	$(CC) $(CFLAGS) $(DEBUG) -c $^

Frequency.o: $(SUBDIR)/Frequency.cpp
	$(CC) $(CFLAGS) $(DEBUG) -c $^

KeyAnalyser.o: $(SUBDIR)/KeyAnalyser.cpp
	$(CC) $(CFLAGS) $(DEBUG) -c $^

Vigenere.o: $(SUBDIR)/Vigenere.cpp
	$(CC) $(CFLAGS) $(DEBUG) -c $^

clean:
	rm -f *.o

erase:
	rm -f *.o $(NAME)

docs:
	doxygen ./doxy.config
