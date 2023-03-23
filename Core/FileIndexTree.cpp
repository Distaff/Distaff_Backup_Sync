#pragma once
#include "FileIndexTree.h"

#include <exception>

template<typename T>
std::vector<std::basic_string<T>> splitString(std::basic_string<T> str, T separator) {
	std::vector<std::basic_string<T>> res;

	if (str.back() != separator)
		str += separator;

	int last_end = 0;
	for (int i = 0; i < str.size(); i++) {
		if (str[i] == separator) {
			res.push_back(str.substr(last_end, i - last_end));
			last_end = i + 1;
		}
	}
	return res;
}



void IndexTreeNode::addChild(IndexEntry entry, std::vector<std::wstring> path) {
	if (!(this->entry.is_directory))
		throw std::logic_error("Adding children to non-directory index entry is prohibited");

	if (path.size() == 1) {
		if (children.contains(path[0]))
			return;
			//throw std::logic_error("Duplicates in index are not allowed");
		else {
			children[path[0]] = std::make_unique<IndexTreeNode>(entry);
		}
	}
	else {
		std::wstring dir_name = path.front();
		path.erase(path.begin());
		if (!children.contains(dir_name)) {
			IndexEntry traversed_dir(std::filesystem::directory_entry(this->entry.file_path + dir_name));
			children[dir_name] = std::make_unique<IndexTreeNode>(traversed_dir);
		}
		children[dir_name]->addChild(entry, path);
	}
}

IndexTreeNode::IndexTreeNode(IndexEntry entry) {
	this->entry = entry;
}

void FileIndexTree::addEntry(IndexEntry entry) {
	std::wstring path = entry.file_path;
	std::vector<std::wstring> splitted_path = splitString(path, L'\\');

	if (splitted_path.size() < 2)
		throw std::logic_error("Inserting empty path or root path to index is not allowed");

	splitted_path.erase(splitted_path.begin());
	root.addChild(entry, splitted_path);

	entries_count++;
}

FileIndexTree::FileIndexTree(IndexEntry root) : root(IndexTreeNode(root)) {
	this->entries_count = 0;
};

size_t FileIndexTree::size() {
	return this->entries_count;
}


std::wostream& operator<<(std::wostream& os, const FileIndexTree& tree)
{
	os << tree.root;
	return os;
}

std::wostream& operator<<(std::wostream& os, const IndexTreeNode& node)
{
	os << "Entry: " << node.entry.date_modified << '\t' << node.entry.file_path << '\n';
	for (auto& i : node.children) {
		os << *(i.second);
	}
	return os;
}