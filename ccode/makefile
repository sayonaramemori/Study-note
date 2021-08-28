src=$(wildcard src/*.c)
obj=$(patsubst %.c, %.o, $(src))
arg=-Wall -I inc
ALL:main

clean:
	-rm -f $(obj)

main:$(obj)
	gcc $^ -o $@ $(arg)

%.o:%.c
	gcc -c $^ -o $@ $(arg)

.PHONY:ALL clean
