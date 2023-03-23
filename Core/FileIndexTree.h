#pragma once
#include "FileIndex.h"
#include <vector>
#include <map>
#include <memory>

class FileIndexTree;

class IndexTreeNode {
private:
	std::map<std::wstring, std::unique_ptr<IndexTreeNode>> children;

public:
	IndexTreeNode(IndexEntry entry);

	IndexEntry entry;

	void addChild(IndexEntry entry, std::vector<std::wstring> path);

	friend std::wostream& operator<<(std::wostream& os, const FileIndexTree& tree);
	friend std::wostream& operator<<(std::wostream& os, const IndexTreeNode& node);
};

class FileIndexTree {
private:
	uint64_t entries_count;

	IndexTreeNode root;

public:
	void addEntry(IndexEntry entry);

	size_t size();

	FileIndexTree(IndexEntry root);

	friend std::wostream& operator<<(std::wostream& os, const FileIndexTree& tree);
};

