#if defined(__cplusplus)
  extern "C" {
#endif
  int FmuExportCrossCompile_mayer(DATA* data, modelica_real** res, short*);
  int FmuExportCrossCompile_lagrange(DATA* data, modelica_real** res, short *, short *);
  int FmuExportCrossCompile_pickUpBoundsForInputsInOptimization(DATA* data, modelica_real* min, modelica_real* max, modelica_real*nominal, modelica_boolean *useNominal, char ** name, modelica_real * start, modelica_real * startTimeOpt);
  int FmuExportCrossCompile_setInputData(DATA *data, const modelica_boolean file);
  int FmuExportCrossCompile_getTimeGrid(DATA *data, modelica_integer * nsi, modelica_real**t);
#if defined(__cplusplus)
}
#endif