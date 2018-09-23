#include <stdbool.h>

#include <stdint.h>
#include <stdio.h>

#include <time.h>

#include <sys/stat.h>
#include <sys/types.h>

#include <fcntl.h>

class Logging {
    public:
        Logging();
        ~Logging();

        void loggingMsg(const char * msg);
        bool loggingStart(const char *logFile); 

    private:
        uint64_t _lineNo;
        FILE *_streamLog;

};