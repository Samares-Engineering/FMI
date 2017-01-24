int instantiateFMU(FMU* fmu, fmi2Component* c, ModelDescription* md, const char* fmuFileName, fmi2Boolean loggingOn, int nCategories, const fmi2String categories[], double tStart, double tEnd);
int initializeModel(FMU* fmu, fmi2Component c, const char* fmuFileName);
int fmuSimulate(FMU* fmu, const char* fmuFileName, double tEnd, double h, fmi2Boolean loggingOn, char separator, int nCategories, const fmi2String categories[]);
