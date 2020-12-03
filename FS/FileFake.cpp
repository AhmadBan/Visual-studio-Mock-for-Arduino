#include "FileFake.h"
using namespace std;
size_t FileFake::write(const uint8_t* buf, size_t size)
{
	file << ((std::string)(const char*)buf).substr(0, size);
	return size;
}

size_t FileFake::read(uint8_t* buf, size_t size)
{
	file.read((char*)buf, size);
	return size;
}

void FileFake::flush()
{
	file.flush();
}

bool FileFake::seek(uint32_t pos, SeekMode mode)
{
	file.seekg(pos, mode);
	return !file.fail();
}

size_t FileFake::position() 
{
	//DEBUGV("position: %d", file.tellg());
	return (size_t)file.tellg();
}

size_t FileFake::size() 
{

	size_t cur_pos= (size_t)file.tellg();
	file.seekg(0, std::ios::end);
	size_t sz= (size_t)file.tellg();

	//DEBUGV("size: %d", file.tellg());
	file.seekg(cur_pos, std::ios::beg);
	return (size_t)sz;
	
}

bool FileFake::truncate(uint32_t size)
{
	//file.trunc();
	return true;
}

void FileFake::close()
{
	file.close();
}

const char* FileFake::name() const
{
	return nullptr;
}

const char* FileFake::fullName() const
{
	return nullptr;
}

bool FileFake::isFile() const
{
	return true;
}

bool FileFake::isDirectory() const
{
	return false;
}
