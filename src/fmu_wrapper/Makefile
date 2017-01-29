################################################################################
CC = gcc
CFLAGS = -g -Wall
CXX=c++

# Folder of the shared src from the FMUSDK2 submodule
FMUSDK2_PATH = ../../fmusdk2/fmu20/src/shared

FMUSDK2_DEFINE = -DFMI_COSIMULATION -DSTANDALONE_XML_PARSER	\
	-DLIBXML_STATIC

FMUSDK2_INCLUDE = -I$(FMUSDK2_PATH)/include \
	-I$(FMUSDK2_PATH)/parser/libxml -I$(FMUSDK2_PATH)/parser \
	-I$(FMUSDK2_PATH)


################################################################################
all: check

check:
	$(CC) $(CFLAGS) -c $(FMUSDK2_DEFINE) $(FMUSDK2_INCLUDE) fmu_wrapper.c

clean:
	rm -rf *.bak *.BAK
	rm -rf *.o *~

indent:
	indent  -ci2 -cli2 -i2 -l80 -nut -sob -pcs -lp *.c

distclean: clean
