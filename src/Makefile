.PHONY: clean, mrproper

.SUFFIXES:

EXECS = \
	FMI_prototype

all: $(EXECS)

clean:
	rm -rf *.bak rm -rf *.o

# mrproper
mrproper: clean
	rm -rf ../bin/

CC = gcc
CFLAGS = -W -Wall -v

IMPORT_SRCS = \
	fmu_import/fmu_import.c

CXX=c++

FMI_prototype: bin/
	$(CC) $(CFLAGS) -g -Wall \
		-Ifmu_import \
		main.c $(IMPORT_SRCS) \
		-c
	$(CXX) $(CFLAGS) -g -Wall \
		-Ifmu_import \
		main.o fmu_import.o \
		-o $@
	cp FMI_prototype ../bin/
	rm FMI_prototype

bin/:
	if [ ! -d ../bin ]; then \
		echo "Creating ../bin/"; \
		mkdir ../bin; \
	fi
