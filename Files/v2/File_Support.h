#pragma once
#include "pch.h"

namespace hr
{
	class File
	{
	private:
		std::string m_FilePath = "";
		std::shared_ptr<std::fstream> m_FileInstance;
		std::ios_base::openmode m_FileFlags;
	public:
		enum class ObjType { File, Folder };
		enum class FileOps { All, Read, Write };

		File(const FileOps& fileops);
		~File();

		bool Open(const std::string& FilePath);
		bool Close();
		bool Write(const std::string& writedata, const int& PositionAfterFlag = 0, const std::ios_base::seekdir& Flag = std::ios_base::end);
		std::vector<std::string> Read(const int& PositionAfterFlag = 0, const std::ios_base::seekdir& Flag = std::ios_base::beg);
		
		static bool isFileExists(const char* Path);
		static bool Create(const char* Path, const ObjType& objtype);
		static bool Delete(const char* Path, const ObjType& objtype);
		static std::vector<std::string> Walk(const char* TopPath);
		static std::string BaseFile(const std::string& Path);
		static std::string FileExt(const std::string& Path);
		static bool Clone(const char* SrcFile, const char* DestFile);
		static bool FixPath(std::string& Path);
	};
}

