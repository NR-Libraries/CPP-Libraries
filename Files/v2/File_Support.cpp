#include "File_Support.h"

namespace hr
{
	// Definitions

	File::File(const File::FileOps& fileops)
	{
		m_FileFlags = 0;

		switch (fileops)
		{
		case FileOps::All:
			m_FileFlags = std::ios_base::in | std::ios_base::out;
			break;
		case FileOps::Read:
			m_FileFlags = std::ios_base::in;
			break;
		case FileOps::Write:
			m_FileFlags = std::ios_base::out;
			break;
		}
	}

	File::~File()
	{
		m_FileInstance.~shared_ptr();
	}

	bool File::Open(const std::string& FilePath)
	{
		try
		{
			if (isFileExists(FilePath.c_str()))
			{
				std::shared_ptr<std::fstream> OpenedFile = std::make_shared<std::fstream>(FilePath, m_FileFlags);
				m_FileInstance = OpenedFile;
				m_FilePath = FilePath;
			}
			else
				throw "Error";
			return true;
		}
		catch (...)
		{
			std::cout << "File.Open() Operation Failed!" << std::endl;
		}
		return false;
	}

	bool File::Close()
	{
		try
		{
			if (m_FilePath != "")
			{
				m_FileInstance->close();
			}
			return true;
		}
		catch (...)
		{
			std::cout << "File.Close() Operation Failed!" << std::endl;
		}
		return false;
	}

	bool File::Write(const std::string& writedata, const int& PositionAfterFlag, const std::ios_base::seekdir& Flag)
	{
		try
		{
			m_FileInstance.get()->seekp(PositionAfterFlag, Flag);
			*(m_FileInstance.get()) << writedata;
			return true;
		}
		catch (...)
		{
			std::cout << "File.Write() Operation Failed!" << std::endl;
		}
		return false;
	}

	std::vector<std::string> File::Read(const int& PositionAfterFlag, const std::ios_base::seekdir& Flag)
	{
		std::vector<std::string> ret_vec;
		try
		{
			m_FileInstance.get()->seekg(0, std::ios::beg);
			std::string temp_line;
			if (m_FileInstance.get()->is_open())
			{
				while (std::getline(*(m_FileInstance.get()), temp_line))
				{
					ret_vec.push_back(temp_line);
					std::cout << temp_line << "\n";
				}
			}
			return ret_vec;
		}
		catch (...)
		{
			std::cout << "File.Read() Operation Failed!" << std::endl;
		}
		return {};
	}

	bool File::isFileExists(const char* Path)
	{
		try
		{
			std::ifstream file(Path);
			if (file.is_open())
				return true;
			return false;
		}
		catch (...)
		{
			std::cout << "File.isFileExists() Operation Failed!" << std::endl;
		}
		return false;
	}

	bool File::Create(const char* Path, const File::ObjType& objtype)
	{
		try
		{
			switch (objtype)
			{
			case ObjType::File:
			{
				std::ofstream file;
				file.open(Path);
				file.close();
				return true;
			}
			break;
			case ObjType::Folder:
			{
				if (_mkdir(Path))
					return true;
				return false;
			}
			}
		}
		catch (...)
		{
			std::cout << "File.Create() Operation Failed!" << std::endl;
		}
		return false;
	}

	bool File::Delete(const char* Path, const ObjType& objtype)
	{
		try
		{
			switch (objtype)
			{
			case ObjType::File:
			{
				if (remove(Path) == 0)
					return true;
				return false;
			}
			break;
			case ObjType::Folder:
			{
				if (_rmdir(Path) == 0)
					return true;
				return false;
			}
			}
		}
		catch (...)
		{
			std::cout << "File.Delete() Operation Failed!" << std::endl;
		}
		return false;
	}

	std::vector<std::string> File::Walk(const char* TopPath)
	{
		std::vector<std::string> ret_vec;
		try
		{
			using recursive_directory_iterator = std::filesystem::recursive_directory_iterator;
			for (const auto dirEntry : recursive_directory_iterator(TopPath))
				ret_vec.push_back(dirEntry.path().string());
			return ret_vec;
		}
		catch (...)
		{
			std::cout << "File.Walk() Operation Failed!" << std::endl;
		}
		return ret_vec;
	}

	std::string File::BaseFile(const std::string& Path)
	{
		try
		{
			if (Path.find("/\\") == std::string::npos)
				return Path.substr(Path.find_last_of("/\\") + 1);
			else
				return Path;
		}
		catch (...)
		{
			std::cout << "File.ExtractFile() Operation Failed!" << std::endl;
		}
		return "";
	}

	std::string File::FileExt(const std::string& Path)
	{
		try
		{
			std::string BasePath = BaseFile(Path);
			if (BasePath.find('.') != std::string::npos)
				return BasePath.substr(BasePath.find_last_of('.') + 1);
			else
				return "";
		}
		catch (...)
		{
			std::cout << "File.Ext() Operation Failed!" << std::endl;
		}
		return "";
	}

	bool File::Clone(const char* SrcFile, const char* DestFile)
	{
		try
		{
			std::ifstream src(SrcFile, std::ios::binary);
			std::ofstream dst(DestFile, std::ios::binary);
			dst << src.rdbuf();
			return true;
		}
		catch (...)
		{
			std::cout << "File.Clone() Operation Failed!" << std::endl;
		}
		return false;
	}

	bool File::FixPath(std::string& Path)
	{
		try
		{
			for (auto pos = Path.find('\\'); pos != std::string::npos; pos = Path.find('\\', ++pos))
				Path.insert(++pos, 1, '\\');
			return true;
		}
		catch (...)
		{
			std::cout << "File.FixPath() Operation Failed!" << std::endl;
		}
		return false;
	}
}