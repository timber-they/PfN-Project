CC?=clang
CFLAGS=-g -Wall -Werror -Wunused-parameter -Wunused-variable -O3 -pedantic -Wno-gnu-zero-variadic-macro-arguments
CLIBS=-lcheck -pthread -pthread -lrt -lm
UBUNTUFLAGS=-lsubunit
FILE_BASE=Checks
DEPENDENCIES=../Sampling/Lazy_Sampling.c ../Extraction/Histograms.c

OS?=$(shell ([ -e "/etc/os-release" ] && grep ^NAME=".*" /etc/os-release))

all:${FILE_BASE}.x

%.x:%.c
ifneq (,$(findstring Ubuntu,${OS}))
	${CC} ${CFLAGS} -o $@ $< ${CLIBS} ${UBUNTUFLAGS} ${DEPENDENCIES}
else
	${CC} ${CFLAGS} -o $@ $< ${CLIBS} ${DEPENDENCIES}
endif

README:Makefile
	@echo "Tests are implemented referenced in Checks.c \
and implemented in header files. \
Note that you might need to add source files here to be compiled." >$@

.PHONY:clean
clean:
	${RM} ${FILE_BASE}.[ox]
