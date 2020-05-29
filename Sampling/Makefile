CC?=clang
CFLAGS=-g -Wall -Werror -Wunused-parameter -Wunused-variable -O3 -pedantic
FILE_BASE=Program

all:${FILE_BASE}.x

%.x:%.c
	${CC} ${CFLAGS} -o $@ $< Lazy_Sampling.c

README:Makefile
	@echo "Lazy Sampling is implemented in Lazy_Sampling.c" > $@

.PHONY:clean
clean:
	${RM} ${FILE_BASE}.[ox]
	${RM} -r ${FILE_BASE}.x.dSYM__pycache__
