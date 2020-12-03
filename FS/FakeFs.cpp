#include "FakeFs.h"
#include <iostream>
#include <fstream>
#include <cstdint>
#include <filesystem>
fs::FakeFs::~FakeFs() {
	
}

bool fs::FakeFs::setConfig(const FSConfig& cfg)
{

	return false;
}

bool fs::FakeFs::begin()
{
	
	return true;
}

void fs::FakeFs::end()
{
	return;
}

bool fs::FakeFs::format()
{

	return true;
}

bool fs::FakeFs::info(FSInfo& info)
{
	return false;
}

bool fs::FakeFs::info64(FSInfo64& info)
{
	return false;
}

fs::FileImplPtr fs::FakeFs::open(const char* path, OpenMode openMode, AccessMode accessMode)
{
	int mode = 0;
	file = std::make_shared<FileFake>();
	if (openMode == OM_DEFAULT)
		openMode = OM_CREATE;
	if (openMode == OM_CREATE)
		mode |= std::fstream::out;
	if (openMode == OM_APPEND)
		mode |= std::fstream::app;
	if (openMode == (OM_APPEND| OM_CREATE))
		mode |= std::fstream::app| std::fstream::out;
	if (openMode == OM_TRUNCATE)
		mode |= std::fstream::trunc;
	if (accessMode == AM_READ)
		mode |= std::fstream::in;
	if (accessMode == AM_WRITE)
		mode |= std::fstream::out;
	if (accessMode == AM_RW)
		mode |= std::fstream::in | std::fstream::out;
	mode |= std::ifstream::binary;
	 file->file.open(path, mode);
	 return file;

}

bool fs::FakeFs::exists(const char* path)
{
	std::ifstream f(path);
	return f.good();
	
}

fs::DirImplPtr fs::FakeFs::openDir(const char* path)
{
	return DirImplPtr();
}

bool fs::FakeFs::rename(const char* pathFrom, const char* pathTo)
{

	return false;
}

bool fs::FakeFs::remove(const char* path)
{
	return std::remove(path);
	
}

bool fs::FakeFs::mkdir(const char* path)
{
	return false;
}

bool fs::FakeFs::rmdir(const char* path)
{
	return false;
}
