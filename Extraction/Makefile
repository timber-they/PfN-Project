CC?=clang
CFLAGS=-g -Wall -Werror -Wunused-parameter -Wunused-variable -O3 -pedantic -lm
FILE_BASE=ConfidenceIntervals

all:${FILE_BASE}.x

%.x:%.c
	${CC} ${CFLAGS} -o $@ $<

README:Makefile
	@echo "ConfidenceIntervals is implemented in ${FILE_BASE}.c" > $@

.PHONY:clean
clean:
	${RM} ${FILE_BASE}.[ox]
	${RM} -r ${FILE_BASE}.x.dSYM__pycache__
