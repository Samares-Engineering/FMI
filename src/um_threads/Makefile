################################################################################
# Makefile for the um_threads library
#
################################################################################
C_FILES = fifo.c test_fifo.c test_rr_preempt.c um_threads.c rr.c	\
	 test_rr_nopreempt.c timer_interrupt.c workload.c user_code.c	\
	 table_driven.c test_table.c debug.c mutex.c semaphore.c \
	 user_code_mutex.c fmi2_api_impl.c test_fmi2_um_threads.c

H_FILES = bits.h constants.h debug.h fifo.h rr.h timer_interrupt.h	\
	 um_threads.h workload.h user_code.h table_driven.h mutex.h semaphore.h \
	 user_code_mutex.h AADL_fmi2CS.h

BINARIES = test_rr_preempt test_rr_nopreempt test_fifo test_table test_fmi2_um_threads

################################################################################
CFLAGS  = -Wall -g
LDFLAGS = -lrt -pthread
CC      = gcc

SRC     = $(H_FILES) $(C_FILES)
OBJS    = $(C_FILES:.c=.o)
################################################################################
# Folder of the shared src from the FMUSDK2 submodule
FMUSDK2_PATH = ../../fmusdk2/fmu20/src/shared

FMUSDK2_DEFINE = -DFMI_COSIMULATION -DSTANDALONE_XML_PARSER	\
	-DLIBXML_STATIC

FMUSDK2_INCLUDE = -I$(FMUSDK2_PATH)/include \
	-I$(FMUSDK2_PATH)/parser/libxml -I$(FMUSDK2_PATH)/parser \
	-I$(FMUSDK2_PATH) -I$(FMUSDK2_MODELS_PATH)

# Folder of the shared model template from the FMUSDK2 submodule
FMUSDK2_MODELS_PATH = ../../fmusdk2/fmu20/src/models

CPP_SRCS = $(FMUSDK2_PATH)/parser/XmlElement.cpp	\
	$(FMUSDK2_PATH)/parser/XmlParser.cpp		\
	$(FMUSDK2_PATH)/parser/XmlParserCApi.cpp
################################################################################

all: help

help:
	@echo Available targets:
	@echo - test_fifo: test case for the priority driven scheduler
	@echo - test_rr_nopreempt: test case for the RR no preempt scheduler
	@echo - test_rr_preempt: test case for the RR preemptive scheduler
	@echo - test_table: test case for the table scheduler
	@echo - test_fmi2_um_threads: test case for the FMI 2.0 API with the scheduler
	@echo - compile_all: compile all test cases

test_fifo: $(OBJS)
	@$(CC) $(LDFLAGS) -o test_fifo					\
		test_fifo.o um_threads.o fifo.o timer_interrupt.o	\
		workload.o user_code.o debug.o mutex.o semaphore.o user_code_mutex.o
	@echo Compilation of test_fifo completed

test_rr_nopreempt: $(OBJS)
	@$(CC) $(LDFLAGS) -o test_rr_nopreempt				\
		test_rr_nopreempt.o um_threads.o rr.o			\
		timer_interrupt.o workload.o user_code.o debug.o mutex.o semaphore.o
	@echo Compilation of test_rr_nopreempt completed

test_rr_preempt: $(OBJS)
	@$(CC) $(LDFLAGS) -o test_rr_preempt				\
		test_rr_preempt.o um_threads.o rr.o timer_interrupt.o	\
		workload.o user_code.o debug.o mutex.o semaphore.o
	@echo Compilation of test_rr_preempt completed

test_table: $(OBJS)
	@$(CC) $(LDFLAGS) -o test_table			\
		test_table.o um_threads.o		\
		table_driven.o timer_interrupt.o	\
		workload.o user_code.o debug.o mutex.o semaphore.o
	@echo Compilation of test_table completed

test_fmi2_um_threads: $(OBJS)
	@$(CC) $(LDFLAGS) -o test_fmi2_um_threads	\
		test_fmi2_um_threads.o fmi2_api_impl.o	\
		um_threads.o rr.o timer_interrupt.o	\
		workload.o user_code.o debug.o mutex.o semaphore.o
	@echo Compilation of test_fmi2_um_threads completed

compile_all: test_rr_preempt test_rr_nopreempt test_fifo test_table test_fmi2_um_threads

################################################################################
%.o: %.c
	@$(CC) -c $(CFLAGS) $(FMUSDK2_DEFINE) $(FMUSDK2_INCLUDE) $*.c -o $*.o
	@$(CC) -MM $(CFLAGS) $(FMUSDK2_DEFINE) $(FMUSDK2_INCLUDE) $*.c > $*.d  

clean:
	-rm -rf *.o *~ *.d

distclean: clean
	-rm -rf $(BINARIES)

################################################################################
# pull in dependency info for *existing* .o files
-include $(OBJS:.o=.d)

###############################################################################
# Packaging of the lab

PACKAGE_FILES = bits.h table_driven.c um_threads.c constants.h		\
table_driven.h um_threads.h debug.c test_fifo.c user_code.c debug.h	\
test_rr_nopreempt.c user_code.h fifo.c test_rr_preempt.c workload.c	\
fifo.h test_table.c workload.h rr.c timer_interrupt.c rr.h		\
timer_interrupt.h

STUDENT_DIR=um_threads
PROF_DIR=um_threads_correction

dist: package_student package_prof

package_student:
	-rm -rf $(STUDENT_DIR)
	mkdir $(STUDENT_DIR)
	cp Makefile $(STUDENT_DIR)
	for file in $(PACKAGE_FILES); do \
	   unifdef -D__STUDENT__ $$file > $(STUDENT_DIR)/$$file; \
	done
	tar zcvf $(STUDENT_DIR).tar.gz $(STUDENT_DIR)

package_prof:
	-rm -rf $(PROF_DIR)
	mkdir $(PROF_DIR)
	cp Makefile $(PROF_DIR)
	for file in $(PACKAGE_FILES); do \
	   unifdef -U__STUDENT__ $$file > $(PROF_DIR)/$$file; \
	done
	tar zcvf $(PROF_DIR).tar.gz $(PROF_DIR)

