#define UNZIP_CMD "unzip -o -d "
#define XML_FILE  "modelDescription.xml"
#define RESULT_FILE "result.csv"
#define BUFSIZE 4096

// Linux
#ifdef __x86_64
#define DLL_DIR   "binaries/linux64/"
#define DLL_DIR2   "binaries/linux32/"
#else
// It may be necessary to compile with -m32, see ../Makefile
#define DLL_DIR   "binaries/linux32/"
#define DLL_DIR2   "binaries/linux64/"
#endif /*__x86_64*/
	
#define DLL_SUFFIX ".so"
#define DLL_SUFFIX2 ".so"


#define RESOURCES_DIR "resources\\"

// return codes of the 7z command line tool
#define SEVEN_ZIP_NO_ERROR 0 // success
#define SEVEN_ZIP_WARNING 1  // e.g., one or more files were locked during zip
#define SEVEN_ZIP_ERROR 2
#define SEVEN_ZIP_COMMAND_LINE_ERROR 7
#define SEVEN_ZIP_OUT_OF_MEMORY 8
#define SEVEN_ZIP_STOPPED_BY_USER 255

int unzip(const char *zipPath, const char *outPath);
void deleteUnzippedFiles();
void loadFMU(const char *fmuFileName);
