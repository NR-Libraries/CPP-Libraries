#include <iostream>
#include <vector>
#include <fstream>

// Using HexReaper Namespace

namespace hr
{
    namespace File_Support
    {
        enum class FileWrite { Write, Append, Clear };
        enum class Output { All, File, Folder };

        bool FileExist(const char* Path)
        {
            std::ifstream TFile;
            TFile.open(Path);
            if(TFile)
            {
                TFile.close();
                return true;
            }
            TFile.close();
            return false;
        }

        bool FileCreate(const char* Path)
        {
            try
            {
                // Check If File Not Exists
                if(!FileExist(Path))
                {
                    // Create New File
                    std::ofstream TFile(Path);
                    TFile.close();
                }
            }
            catch(...)
            {
                return false;
            }
            return true;
        }

        bool FileDestroy(const char* Path)
        {
            try
            {
                // Check If File Exists
                if(FileExist(Path))
                {
                    // Delete Existing File
                    remove(Path);
                }
            }
            catch(...)
            {
                return false;
            }
            return true;
        }

        bool FileSet(const char* Path, const FileWrite& FileWriteType, const std::vector<std::string>& Data = {})
        {
            try
            {
                // Check If File Exists
                if(FileExist(Path))
                {
                    std::ofstream T_File;
                    // Check for Write Flags
                    switch(FileWriteType)
                    {
                        case FileWrite::Append:
                            {
                                // Open Stream
                                T_File.open(Path, std::ofstream::app);
                                // Feed Data
                                for(std::string line : Data)
                                {
                                    T_File << line << "\n";
                                }
                                // Close Stream
                                T_File.close();
                            }
                            break;
                        case FileWrite::Clear:
                            {
                                // Open Stream
                                T_File.open(Path, std::ofstream::trunc);
                                // Close Stream
                                T_File.close();
                            }
                            break;
                        case FileWrite::Write:
                            {
                                // Open Stream
                                T_File.open(Path, std::ofstream::trunc);
                                // Feed Data
                                for(std::string line : Data)
                                {
                                    T_File << line << "\n";
                                }
                                // Close Stream
                                T_File.close();
                            }
                            break;
                    }
                }
            }
            catch(...)
            {
                return false;
            }
            return true;
        }

        std::vector<std::string> FileGet(const char* Path)
        {
            std::vector<std::string> Datas;
            try
            {
                std::string line;
                std::ifstream T_File(Path);
                // Open Stream
                if(T_File.is_open())
                {
                    while(std::getline(T_File, line))
                    {
                        // Feed Stream
                        Datas.push_back(line);
                    }
                }
                // Close Stream
                T_File.close();
            }
            catch(...)
            {
                return {};
            }
            return Datas;
        }

        std::vector<std::string> ListDir(const char* Path, Output& OutputType)
        {
            // Boost: https://stackoverflow.com/questions/15141536/c-alternative-to-os-walk
            return {};
        }
    }
}
