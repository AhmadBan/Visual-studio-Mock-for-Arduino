#pragma once
#include "FSImpl.h"
#include "FS.h"
#include <fstream>
#include "FileFake.h"
#include <memory>
namespace fs {

	

	class FakeFs :public FSImpl
	{	
		
		
		// Inherited via FSImpl
		
		
		virtual bool setConfig(const FSConfig& cfg) override;
		virtual bool begin() override;
		virtual void end() override;
		virtual bool format() override;
		virtual bool info(FSInfo& info) override;
		virtual bool info64(FSInfo64& info) override;
		virtual FileImplPtr open(const char* path, OpenMode openMode, AccessMode accessMode) override;
		virtual bool exists(const char* path) override;
		virtual DirImplPtr openDir(const char* path) override;
		virtual bool rename(const char* pathFrom, const char* pathTo) override;
		virtual bool remove(const char* path) override;
		virtual bool mkdir(const char* path) override;
		virtual bool rmdir(const char* path) override;
	public:
		virtual ~FakeFs() override;
		std::shared_ptr<FileFake> file;
	};

}

