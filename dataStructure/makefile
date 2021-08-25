src=$(wildcard src/*.c)
obj=$(patsubst %.c, %.o, $(src))
arg=-Wall -I inc
ALL:main

$(obj):%.o:%.c
	gcc -c $^ -o $@ $(arg)

main:$(obj)
	gcc $^ -o $@ $(arg)

clean:
	-rm -rf $(obj)
move:
	-mv $(src) oth

.PHNOY:clean ALL move
