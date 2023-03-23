#pragma once
#include <string>
#include <filesystem>

class FileIndexHeader {
public:
	uint16_t version_major;		//Difference means hard non-compatibility - If file has higher minor version number throw an error
	uint16_t version_minor;		//If file has higher minor version number, then it might contain some info that will be omited - warning should be raised
	uint16_t version_patch;
	uint16_t version_build;

	std::filesystem::file_time_type date_modified;

	uint64_t entries_count;
};

class IndexEntry {
public:
	std::wstring file_path;

	std::filesystem::file_time_type date_modified;

	uint32_t file_checksum[4];	//MD5

	bool is_directory;

	uint32_t record_checksum;	//CRC32



	IndexEntry(std::filesystem::directory_entry file);

	IndexEntry(const IndexEntry& rhs);

	IndexEntry(void);
};	
