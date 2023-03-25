#pragma once
#include "FileIndex.h"
#include <vector>
#include <map>
#include <memory>
#include <fstream>

class FileIndexTree;

class IndexTreeNode {
private:
	std::map<std::wstring, std::unique_ptr<IndexTreeNode>> children;

public:
	IndexEntry entry;

	IndexTreeNode();

	IndexTreeNode(IndexEntry entry);

	void addChild(IndexEntry entry, std::vector<std::wstring> path);

	friend std::wostream& operator<<(std::wostream& os, const FileIndexTree& tree);
	friend std::wostream& operator<<(std::wostream& os, const IndexTreeNode& node);
};

class FileIndexTree {
private:
	uint64_t entries_count;

	IndexTreeNode root;

public:
	FileIndexTree(IndexEntry root);

	FileIndexTree(std::ifstream dat_file);

	size_t size();

	void addEntry(IndexEntry entry);

	friend std::wostream& operator<<(std::wostream& os, const FileIndexTree& tree);
};

