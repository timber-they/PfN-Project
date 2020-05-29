cc?=clang
CFLAGS=-g -Wall -Werror -Wunused-parameter -Wunused-variable -O3 -pedantic -lcheck
FILE_BASE=Checks

all:${FILE_BASE}.x

%.x:%.c
	${CC} ${CFLAGS} -o $@ $< ../Sampling/Lazy_Sampling.c

README:Makefile
	@echo "Tests are implemented referenced in Checks.c \
and implemented in header files. \
Note that you might need to add source files here to be compiled." >$@

.PHONY:clean
clean:
	${RM} ${FILE_BASE}.[ox]
