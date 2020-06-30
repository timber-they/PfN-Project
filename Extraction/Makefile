CC?=clang
CFLAGS=-g -Wall -Werror -Wunused-parameter -Wunused-variable -O3 -pedantic
CLIBS=-lm
FILE_BASE=Program
DEPENDENCIES=AbsoluteData.c CSV_Output.c ConfidenceIntervals.c Histograms.c Median.c Medium.c RelativeData.c Sort.c InputCheck.c

all:${FILE_BASE}.x

%.x:%.c ${DEPENDENCIES} 
	${CC} ${CFLAGS} -o $@ $< ${DEPENDENCIES} ${CLIBS}

README:Makefile
	@echo "This could be a nice readme." > $@

.PHONY:clean
clean:
	${RM} ${FILE_BASE}.[ox]
	${RM} -r ${FILE_BASE}.x.dSYM__pycache__
