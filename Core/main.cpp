#include <iostream>
#include <chrono>

#include "FileIndexTree.h"
//
//
//
//using namespace std::string_literals;
//
//std::map<std::filesystem::path, int> mapFileSizes(std::string dirPath) {
//	std::map<std::filesystem::path, int> res;
//	std::filesystem::recursive_directory_iterator dirIter(dirPath);	//ftw()
//
//	for (auto& dirEntry : dirIter) {	//readdir()
//		if (!dirEntry.is_directory())	//!S_ISDIR(bufor_stat.st_mode)
//			res[dirEntry.path()] = std::filesystem::file_size(dirEntry.path());
//	}
//
//	return res;
//}
//
//int main(int argc, char** argv)
//{
//	std::string pathname;
//
//	if (argc == 1)
//		pathname = "./";
//	else if (argc == 2)
//		pathname = std::string(argv[1]);
//	else
//		throw std::runtime_error("Imporper arguments count!"s);
//
//
//	std::cout << "Listing files in directory " << pathname << ":\n"
//		<< std::setw(96) << std::left << "FILENAME:" << "SIZE (BYTES):\n";
//
//
//	for (auto& i : mapFileSizes(pathname))
//		std::cout << std::setw(96) << std::left << i.first << ' ' << i.second << '\n';
//
//	return 0;
//}


int main() {

	auto begin = std::chrono::high_resolution_clock::now();

	std::wstring path = L".\\";


	std::filesystem::recursive_directory_iterator dir_iter(path, std::filesystem::directory_options::skip_permission_denied);

	FileIndexTree index((IndexEntry(std::filesystem::directory_entry(path))));


	for (auto& dir_entry : dir_iter) {
		index.addEntry(IndexEntry(dir_entry));
	}

	auto end = std::chrono::high_resolution_clock::now();

	std::cout << index.size() << " files indexed. Time needed:" << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin) / 1000.0f << "s.";

	system("pause");

	std::wcout << index;


}