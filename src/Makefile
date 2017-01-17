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

FMUSDK2_DEP = \
	../fmusdk2/fmu20/src

IMPORT_SRCS = \
	fmu_import/fmu_import.c

CPP_SRCS = \
	$(FMUSDK2_DEP)/shared/parser/XmlElement.cpp \
	$(FMUSDK2_DEP)/shared/parser/XmlParser.cpp \
	$(FMUSDK2_DEP)/shared/parser/XmlParserCApi.cpp

SHARED_DEPS = \
	$(FMUSDK2_DEP)/shared/fmi2.h \
	$(FMUSDK2_DEP)/shared/include/fmi2Functions.h \
	$(FMUSDK2_DEP)/shared/include/fmi2FunctionTypes.h \
	$(FMUSDK2_DEP)/shared/include/fmi2TypesPlatform.h \
	$(FMUSDK2_DEP)/shared/parser/XmlElement.h \
	$(FMUSDK2_DEP)/shared/parser/XmlParser.h \
	$(FMUSDK2_DEP)/shared/parser/XmlParserCApi.h \
	$(FMUSDK2_DEP)/shared/parser/XmlParserException.h

CXX=c++

FMI_prototype: $(SHARED_DEPS) bin/
	$(CC) $(CFLAGS) -g -Wall -DFMI_COSIMULATION \
		-DSTANDALONE_XML_PARSER -DLIBXML_STATIC \
		-I$(FMUSDK2_DEP)/shared/include -I$(FMUSDK2_DEP)/shared/parser/libxml -I$(FMUSDK2_DEP)/shared/parser -I$(FMUSDK2_DEP)/shared -Ifmu_import \
		main.c $(IMPORT_SRCS) \
		-c
	$(CXX) $(CFLAGS) -g -Wall -DFMI_COSIMULATION \
		-DSTANDALONE_XML_PARSER -DLIBXML_STATIC \
		-I$(FMUSDK2_DEP)/shared/include -I$(FMUSDK2_DEP)/shared/parser/libxml -I$(FMUSDK2_DEP)/shared/parser -I$(FMUSDK2_DEP)/shared -Ifmu_import \
		main.o fmu_import.o $(CPP_SRCS) \
		-o $@ -lexpat -ldl -lxml2
	cp FMI_prototype ../bin/
	rm FMI_prototype
	cp ../models/MoonLanding/MoonLanding.fmu ../bin/

bin/:
	if [ ! -d ../bin ]; then \
		echo "Creating ../bin/"; \
		mkdir ../bin; \
	fi
