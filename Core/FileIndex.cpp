#include "FileIndex.h"


IndexEntry::IndexEntry(std::filesystem::directory_entry file) {
	this->file_path = file.path();
	this->date_modified = file.last_write_time();
	this->is_directory = file.is_directory();
}

IndexEntry::IndexEntry(const IndexEntry& rhs) {
	this->file_path = rhs.file_path;
	this->date_modified = rhs.date_modified;
	this->is_directory = rhs.is_directory;
}

IndexEntry::IndexEntry(void) {
	return;
}
