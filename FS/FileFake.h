#pragma once
#include "FSImpl.h"
#include <fstream>


class FileFake:public fs::FileImpl
{

	// Inherited via FileImpl
	virtual size_t write(const uint8_t* buf, size_t size) override;
	virtual size_t read(uint8_t* buf, size_t size) override;
	virtual void flush() override;
	virtual bool seek(uint32_t pos, SeekMode mode) override;
	virtual size_t position() override;
	virtual size_t size()  override;
	virtual bool truncate(uint32_t size) override;
	virtual void close() override;
	virtual const char* name() const override;
	virtual const char* fullName() const override;
	virtual bool isFile() const override;
	virtual bool isDirectory() const override;

public:
	std::fstream file;
	~FileFake() {
		if (file)
			file.close();
	}
};

