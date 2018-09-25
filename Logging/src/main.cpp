#include "Logging.h"

int main() {
    const char *logFilePath = "./logFile.log";
    Logging logger;
    if(!logger.loggingStart(logFilePath)) {
        printf("Start logger failed!");
    }
    else {
        logger.loggingMsg("This is logger sample!");
        logger.loggingMsg("This is second line of log file!");
        logger.loggingMsg("End line of log file!");
    }
    return 0;
}