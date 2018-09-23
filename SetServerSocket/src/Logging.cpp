#include <Logging.h>

Logging::Logging() {
    _lineNo = 0;
    _streamLog = NULL;
}

Logging::~Logging() {
    // This is blank
}

bool Logging::loggingStart(const char *logFile) {
    bool isOk = true;
    _streamLog = fopen(logFile, "we");

    if (_streamLog == NULL) {
        isOk = false;
    } // fi

    return isOk;
}

void Logging::loggingMsg(const char * msg) {
    time_t now = time(NULL);

    struct tm *tm_now = localtime(&now);

    fprintf(
        _streamLog,
        "%06ld:[%02d:%02d:%02d %02d/%02d/%d] %s\n",
        _lineNo,
        tm_now->tm_hour, tm_now->tm_min, tm_now->tm_sec,
        tm_now->tm_mon + 1, tm_now->tm_mday, tm_now->tm_year + 1900,
        msg
    );
    _lineNo++;
}