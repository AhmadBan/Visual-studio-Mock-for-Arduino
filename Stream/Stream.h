#pragma once

#include "../Arduino/Arduino.h"
#include "../Print/Print.h"
class Stream : public Print {
protected:
    unsigned long _timeout;      // number of milliseconds to wait for the next char before aborting timed read
    unsigned long _startMillis;  // used for timeout measurement
    int timedRead();    // private method to read stream with timeout
    int timedPeek();    // private method to peek stream with timeout
    int peekNextDigit(); // returns the next numeric digit in the stream or -1 if timeout

public:
    virtual int available() = 0;
    virtual int read() = 0;
    virtual int peek() = 0;

    Stream() {
        _timeout = 1000;
        _startMillis = 0;
    }

    // parsing methods

    void setTimeout(unsigned long timeout);  // sets maximum milliseconds to wait for stream data, default is 1 second

    bool find(const char* target);   // reads data from the stream until the target string is found
    bool find(uint8_t* target) {
        return find((char*)target);
    }
    // returns true if target string is found, false if timed out (see setTimeout)

    bool find(const char* target, size_t length);   // reads data from the stream until the target string of given length is found
    bool find(const uint8_t* target, size_t length) {
        return find((char*)target, length);
    }
    // returns true if target string is found, false if timed out

    bool find(char target) { return find(&target, 1); }

    bool findUntil(const char* target, const char* terminator);   // as find but search ends if the terminator string is found
    bool findUntil(const uint8_t* target, const char* terminator) {
        return findUntil((char*)target, terminator);
    }

    bool findUntil(const char* target, size_t targetLen, const char* terminate, size_t termLen);   // as above but search ends if the terminate string is found
    bool findUntil(const uint8_t* target, size_t targetLen, const char* terminate, size_t termLen) {
        return findUntil((char*)target, targetLen, terminate, termLen);
    }

    long parseInt(); // returns the first valid (long) integer value from the current position.
    // initial characters that are not digits (or the minus sign) are skipped
    // integer is terminated by the first character that is not a digit.

    float parseFloat();               // float version of parseInt

    virtual size_t readBytes(char* buffer, size_t length); // read chars from stream into buffer
    virtual size_t readBytes(uint8_t* buffer, size_t length) {
        return readBytes((char*)buffer, length);
    }
    // terminates if length characters have been read or timeout (see setTimeout)
    // returns the number of characters placed in the buffer (0 means no valid data found)

    size_t readBytesUntil(char terminator, char* buffer, size_t length); // as readBytes with terminator character
    size_t readBytesUntil(char terminator, uint8_t* buffer, size_t length) {
        return readBytesUntil(terminator, (char*)buffer, length);
    }
    // terminates if length characters have been read, timeout, or if the terminator character  detected
    // returns the number of characters placed in the buffer (0 means no valid data found)

    // Arduino String functions to be added here
    virtual String readString();
    String readStringUntil(char terminator);

protected:
    long parseInt(char skipChar); // as above but the given skipChar is ignored
    // as above but the given skipChar is ignored
    // this allows format characters (typically commas) in values to be ignored

    float parseFloat(char skipChar);  // as above but the given skipChar is ignored
};

