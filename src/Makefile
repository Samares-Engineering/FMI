EXECS = FMI_prototype

all: $(EXECS)

clean:
	rm -rf *.bak *.BAK
	rm -rf *.o *~

distclean: clean
	rm -rf ../bin/

################################################################################
CC = gcc
CFLAGS = -g -Wall
CXX=c++

# Folder of the shared src from the FMUSDK2 submodule
FMUSDK2_PATH = ../fmusdk2/fmu20/src/shared

FMUSDK2_DEFINE = -DFMI_COSIMULATION -DSTANDALONE_XML_PARSER	\
	-DLIBXML_STATIC

FMUSDK2_INCLUDE = -I$(FMUSDK2_PATH)/include \
	-I$(FMUSDK2_PATH)/parser/libxml -I$(FMUSDK2_PATH)/parser \
	-I$(FMUSDK2_PATH) -I$(FMUSDK2_MODELS_PATH) -Ifmu_wrapper

# Folder of the shared model template from the FMUSDK2 submodule
FMUSDK2_MODELS_PATH = ../fmusdk2/fmu20/src/models

# Sources shared between co-simulation and model exchange
SHARED_SRCS = $(FMUSDK2_PATH)/sim_support.c fmu_wrapper/fmu_wrapper.c

CPP_SRCS = $(FMUSDK2_PATH)/parser/XmlElement.cpp	\
	$(FMUSDK2_PATH)/parser/XmlParser.cpp		\
	$(FMUSDK2_PATH)/parser/XmlParserCApi.cpp

################################################################################

FMI_prototype: bin/
	$(CC) $(CFLAGS) -c $(FMUSDK2_DEFINE) $(FMUSDK2_INCLUDE) main.c	\
	$(SHARED_SRCS)

	$(CXX) $(CFLAGS) $(FMUSDK2_DEFINE) $(FMUSDK2_INCLUDE) \
		main.o fmu_wrapper.o sim_support.o $(CPP_SRCS) \
		-o $@ -lexpat -ldl -lxml2
	cp FMI_prototype ../bin/
	cp ../models/MoonLanding/MoonLanding.fmu ../bin/
	cp ../models/BouncingBall/bouncingBall.fmu ../bin/

bin/:
	if [ ! -d ../bin ]; then \
		echo "Creating ../bin/"; \
		mkdir ../bin; \
	fi

indent:
	indent  -ci2 -cli2 -i2 -l80 -nut -sob -pcs -lp *.c
