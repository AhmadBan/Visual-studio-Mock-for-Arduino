#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <fstream>
#include <iostream>

using namespace std;






//
//int main() {
//    char data[100];
//
//    // open a file in write mode.
//    
//   
//
//
//    // write inputted data into the file.
//    outfile << data << endl;
//
//    cout << "Enter your age: ";
//    cin >> data;
//    cin.ignore();
//
//    // again write inputted data into the file.
//    outfile << data << endl;
//
//    // close the opened file.
//    outfile.close();
//
//    // open a file in read mode.
//    ifstream infile;
//    infile.open("afile.dat");
//
//    cout << "Reading from the file" << endl;
//    infile >> data;
//
//    // write the data at the screen.
//    cout << data << endl;
//
//    // again read the data from the file and display it.
//    infile >> data;
//    cout << data << endl;
//
//    // close the opened file.
//    infile.close();
//
//    return 0;
//}

enum SeekMode {
    SeekSet = 0,
    SeekCur = 1,
    SeekEnd = 2
};
#define FILE_READ       "r"
#define FILE_WRITE      "w"
#define FILE_APPEND     "a"
class FileImpl;
typedef std::shared_ptr<FileImpl> FileImplPtr;
class FSImpl;
typedef std::shared_ptr<FSImpl> FSImplPtr;

class File 
{
    
    string read;
    string write;

public:
   fstream file;

    size_t write(uint8_t buf) {
        file << (char)buf;
        return 1;
    };
    size_t write(const uint8_t* buf, size_t size) {
        file << (char*)buf;
            return size;
    };
    bool print(const char* buf) {
        file << buf;
        return true;
    }
    int available() { 
        
        return file.peek() != std::ifstream::traits_type::eof();
    };
    int read() { 
        char temp;
        if (!available())
            return -1;
        file.read(&temp, 1);

        return temp;
    };
    int peek() {
        return file.peek();
    };
    void flush() {
        file.flush();
    };
    size_t read(uint8_t* buf, size_t size) {
        readBytes((char*)buf, size);
        return size;
    };
    size_t readBytes(char* buffer, size_t size)
    {
        file.read(buffer, size);
        return size;
    }

    bool seek(uint32_t pos, SeekMode mode) {
        
        if (mode == SeekSet)
            file.seekg(pos, ios_base::beg);
        if(mode==SeekCur)
            file.seekg(pos, ios_base::cur);
        if (mode == SeekEnd)
            file.seekg(pos, ios_base::end);
        return true;

    };
    bool seek(uint32_t pos)
    {
        return seek(pos, SeekSet);
    }
    size_t position() const {
        return 0;
    };
    size_t size() const {
        return 0;
    };
    void close() {
        file.close();
    };
    operator bool() const { return file.fail(); };
    time_t getLastWrite() { return 2; };
    const char* name() const { return "name"; };

    bool isDirectory(void) {};
    File openNextFile(const char* mode = FILE_READ) {};
    void rewindDirectory(void) {};
    
protected:
    FileImplPtr _p;
};




class FS
{
    
public:
    //FS(FSImplPtr impl) : _impl(impl) { timeCallback = _defaultTimeCB; }

    //bool setConfig(const FSConfig& cfg);

    bool begin() {
    
    };
    void end() {};
    bool begin(bool){}
    bool format() {}
    // bool info(FSInfo& info);
     //bool info64(FSInfo64& info);

    File open(const char* path, const char* mode) {
        File temp;
        if(mode=="r")
            temp.file.open(path,ios::in);
        if (mode == "w")
            temp.file.open(path, ios::out);
        if (mode == "a")
            temp.file.open(path, ios::app);
        return temp;
    }
    File open(const string& path, const char* mode) { 
        
        return open(path.c_str(),mode);
    
    }

    bool exists(const char* path) {
        File temp;
        temp.file.open(path);
        return temp.file.fail();
    }
    
    bool exists(const string& path) {
        return exists(path.c_str());
    }

    //Dir openDir(const char* path);
   // Dir openDir(const string& path);
   

    bool remove(const char* path) {}
    bool remove(const string& path) {}

    bool rename(const char* pathFrom, const char* pathTo) {}
    bool rename(const string& pathFrom, const string& pathTo) {}

    bool mkdir(const char* path) {}
    bool mkdir(const string& path) {}

    bool rmdir(const char* path){}
    bool rmdir(const string& path){}

    // Low-level FS routines, not needed by most applications
    bool gc(){}
    bool check(){}

    void setTimeCallback(time_t(*cb)(void)){}

    //friend class ::SDClass; // More of a frenemy, but SD needs internal implementation to get private FAT bits
protected:
    FSImplPtr _impl;
    FSImplPtr getImpl() { return _impl; }
    time_t(*timeCallback)(void);
    //static time_t _defaultTimeCB(void) { return time(NULL); }
};

class SPIFFS:public FS
{
public:
    SPIFFS() {};
    bool begin(bool formatOnFail = false, const char* basePath = "/spiffs", uint8_t maxOpenFiles = 10) {
    
    };
    bool format() {};
    size_t totalBytes() {};
    size_t usedBytes() {};
    void end() {};
};
