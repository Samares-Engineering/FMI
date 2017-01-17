#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdarg.h>
#include "fmu_import.h"

// fmuFileName is an absolute path, e.g. "C:\test\a.fmu"
// or relative to the current dir, e.g. "..\test\a.fmu"
static char* getFmuPath(const char* fmuFileName){
  /* Not sure why this is useful.  Just returning the filename. */
  return strdup(fmuFileName);
}

static char* getTmpPath() {
  char template[13];  // Lenght of "fmuTmpXXXXXX" + null
  sprintf(template, "%s", "fmuTmpXXXXXX");
  char *tmp = mkdtemp(template);
  if (tmp==NULL) {
    fprintf(stderr, "Couldn't create temporary directory\n");
    exit(1);
  }
  char * results = calloc(sizeof(char), strlen(tmp) + 2);
  strncat(results, tmp, strlen(tmp));
  return strcat(results, "/");
}

int unzip(const char *zipPath, const char *outPath) {
    int code;
    char cwd[BUFSIZE];
    int n;
    char* cmd;

    // remember current directory
    if (!getcwd(cwd, BUFSIZE)) {
      printf ("error: Could not get current directory\n");
      return 0; // error
    }
        
    // run the unzip command
    n = strlen(UNZIP_CMD) + strlen(outPath) + 1 +  strlen(zipPath) + 16;
    cmd = (char*)calloc(sizeof(char), n);
    sprintf(cmd, "%s%s \"%s\" > /dev/null", UNZIP_CMD, outPath, zipPath); 
    printf("cmd='%s'\n", cmd);
    code = system(cmd);
    free(cmd);
    if (code!=SEVEN_ZIP_NO_ERROR) {
        printf("%s: ", UNZIP_CMD);
        switch (code) {
            case 1:            printf("warning\n"); break;
            case 2:            printf("error\n"); break;
	    case 3:            printf("severe error\n"); break;
            case 4:      
            case 5:
	    case 6:
	    case 7:
	      printf("out of memory\n"); break;
   	    case 10:           printf("command line error\n"); break;
	    default:           printf("unknown problem %d\n", code);
        }
    }
    
    // restore current directory
    chdir(cwd);
    
    return (code==SEVEN_ZIP_NO_ERROR || code==SEVEN_ZIP_WARNING) ? 1 : 0;  
}

void loadFMU(const char* fmuFileName) {
    char* fmuPath;
    char* tmpPath;
    char* xmlPath;
    char* dllPath;
    const char *modelId;
    
    printf("Loading FMU %s. \n", fmuFileName);

    // get absolute path to FMU, NULL if not found
    fmuPath = getFmuPath(fmuFileName);
    if (!fmuPath) exit(EXIT_FAILURE);
    
    tmpPath = getTmpPath();

    printf("Unzip the %s file.\n", fmuFileName);
    if (!unzip(fmuPath, tmpPath)) exit(EXIT_FAILURE);

    printf("FMU %s Loaded.\n", fmuFileName);
}
