vpath %.c src
vpath %.h include
vpath %.o obj

CC := gcc
target := test
STD := c99

$(target).exe:$(target).o testFrame.o leptjson.o
	$(CC) -o $@ $^ -std=$(STD)
	$(target)

obj/$(target).o:$(target).c testFrame.h
	$(CC) -c -o $@ $< -I include -std=$(STD)

obj/leptjson.o:leptjson.c leptjson.h
	$(CC) -c -o $@ $< -I include -std=$(STD)

obj/testFrame.o:testFrame.c
	$(CC) -c -o $@ $< -I include -std=$(STD)

.PHONY:clean
clean:
	cd obj && cmd /C del *.o
	cmd /C del $(target).exe