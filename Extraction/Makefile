CC?=clang
CFLAGS=-g -Wall -Werror -Wunused-parameter -Wunused-variable -O3 -pedantic
CLIBS=-lm
FILE_BASE=Program


all:${FILE_BASE}.x

%.x:%.c
	${CC} ${CFLAGS} -o $@ $< ${CLIBS}

README:Makefile
	@echo "ConfidenceIntervals is implemented in ConfidenceIntervals.c > $@

.PHONY:clean
clean:
	${RM} ${FILE_BASE}.[ox]
	${RM} -r ${FILE_BASE}.x.dSYM__pycache__
