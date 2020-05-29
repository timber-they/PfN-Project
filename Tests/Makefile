cc?=clang
CFLAGS=-g -Wall -Werror -Wunused-parameter -Wunused-variable -O3 -pedantic -lcheck
FILE_BASE=Check_Lazy_Sampling

all:${FILE_BASE}.x

%.x:%.c
	${CC} ${CFLAGS} -o $@ $< ../Sampling/Lazy_Sampling.c

README:Makefile
	@echo "Tests are (currently) implemented in Check_Lazy_Sampling.c" >$@

.PHONY:clean
clean:
	${RM} ${FILE_BASE}.[ox]
