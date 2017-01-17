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

# Folder of the FMUSDK2 submodule
FMUSDK2_PATH = \
	../fmusdk2/fmu20/src/shared

# Sources shared between co-simulation and model exchange
SHARED_SRCS = \
	$(FMUSDK2_PATH)/sim_support.c \
	fmu_import/fmu_import.c \
	fmu_simulate/fmu_simulate.c 

CPP_SRCS = \
	$(FMUSDK2_PATH)/parser/XmlElement.cpp \
	$(FMUSDK2_PATH)/parser/XmlParser.cpp \
	$(FMUSDK2_PATH)/parser/XmlParserCApi.cpp

# Dependencies shared between both fmusim_cs and fmusim_me
SHARED_DEPS = \
	$(FMUSDK2_PATH)/fmi2.h \
	$(FMUSDK2_PATH)/include/fmi2Functions.h \
	$(FMUSDK2_PATH)/include/fmi2FunctionTypes.h \
	$(FMUSDK2_PATH)/include/fmi2TypesPlatform.h \
	$(FMUSDK2_PATH)/parser/XmlElement.h \
	$(FMUSDK2_PATH)/parser/XmlParser.h \
	$(FMUSDK2_PATH)/parser/XmlParserCApi.h \
	$(FMUSDK2_PATH)/parser/XmlParserException.h

CXX=c++

FMI_prototype: $(SHARED_DEPS) bin/
	$(CC) $(CFLAGS) -g -Wall -DFMI_COSIMULATION \
		-DSTANDALONE_XML_PARSER -DLIBXML_STATIC \
		-I$(FMUSDK2_PATH)/include -I$(FMUSDK2_PATH)/parser/libxml -I$(FMUSDK2_PATH)/parser -I$(FMUSDK2_PATH) -Ifmu_import -Ifmu_simulate \
		main.c $(SHARED_SRCS) \
		-c
	$(CXX) $(CFLAGS) -g -Wall -DFMI_COSIMULATION \
		-DSTANDALONE_XML_PARSER -DLIBXML_STATIC \
		-I$(FMUSDK2_PATH)/include -I$(FMUSDK2_PATH)/parser/libxml -I$(FMUSDK2_PATH)/parser -I$(FMUSDK2_PATH) -Ifmu_import -Ifmu_simulate \
		main.o fmu_import.o fmu_simulate.o sim_support.o $(CPP_SRCS) \
		-o $@ -lexpat -ldl -lxml2
	cp FMI_prototype ../bin/
	rm FMI_prototype
	cp ../models/BouncingBall/bouncingBall.fmu ../bin/

bin/:
	if [ ! -d ../bin ]; then \
		echo "Creating ../bin/"; \
		mkdir ../bin; \
	fi
