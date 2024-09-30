#include "trie.h"
#include <iostream>

Trie::Trie()
{
	root = NULL;
}

// Returns new trie node (initialized to NULLs)
struct TrieNode *Trie::getNode(void)
{
	TrieNode *temp = new TrieNode;
	temp->isWordEnd = false;

	for (int i = 0; i < ALPHABET_SIZE; i++)
	{
		temp->children[i] = nullptr;
	}
	return temp;
}

// If not present, inserts key into trie. If the
// key is prefix of trie node, just marks leaf node
void Trie::insert(struct TrieNode *root, const std::string key)
{
	int size = key.length();
	TrieNode *temp = root;

	bool present = true;
	if (temp == nullptr)
	{
		temp = getNode();
		int size = key.size();
		for (int i = 0; i < size; i++)
		{
			TrieNode *newnode = getNode();
			temp->children[CHAR_TO_INDEX(key[i])] = newnode;
			temp = newnode;
		}
		temp->isWordEnd = true;
	}
	else
	{
		int i;
		present = true;
		for (i = 0; i < size; i++)
		{
			// if (not(present))
			// {
			// 	TrieNode *newnode = getNode();
			// 	temp->children[CHAR_TO_INDEX(key[i])] = newnode;
			// 	temp = newnode;
			// }
			// else if (temp->children[CHAR_TO_INDEX(key[i])])
			// 	temp = temp->children[CHAR_TO_INDEX(key[i])];
			// else
			// 	present = false;
			if (present && temp->children[CHAR_TO_INDEX(key[i])] == nullptr)
			{
				present = false;
			}

			if (not(present))
			{
				TrieNode *newnode = getNode();
				temp->children[CHAR_TO_INDEX(key[i])] = newnode;
				temp = newnode;
			}
			else
			{
				temp = temp->children[CHAR_TO_INDEX(key[i])];
			}
		}
		temp->isWordEnd = true;
	}
}
bool Trie::search(struct TrieNode *root, std::string key)
{
	TrieNode *temp = root;
	bool present = true;
	for (int i = 0; i < key.size(); i++)
	{
		if (temp->children[CHAR_TO_INDEX(key[i])] == nullptr)
		{
			present = false;
			break;
		}
		temp = temp->children[CHAR_TO_INDEX(key[i])];
	}
	return present && temp->isWordEnd;
}

// Returns 0 if current node has a child
// If all children are NULL, return 1.
bool Trie::isLastNode(struct TrieNode *node)
{
	for (int i = 0; i < ALPHABET_SIZE; i++)
	{
		if (node->children[i] != nullptr)
			return false;
	}
	return true;
}

// Recursive function to print auto-suggestions for given
// node.
void Trie::suggestionsRec(struct TrieNode *root,
						  std::string currPrefix)
{
	// found a std::string in Trie with the given prefix
	TrieNode *node = root;
	// for (int i = 0; i < currPrefix.size(); i++)
	// {
	// 	node = node->children[CHAR_TO_INDEX(currPrefix[i])];
	// }
	// // std::cout << currPrefix + suggestionsRec(node, )
	if (node->isWordEnd)
		std::cout << currPrefix << std::endl;

	for (int i = 0; i < ALPHABET_SIZE; i++)
	{
		if (node->children[i] != nullptr)
		{
			std::string c = currPrefix + char(i + 97);
			suggestionsRec(root, c);
		}
	}
}

// print suggestions for given query prefix.
int Trie::printAutoSuggestions(TrieNode *root, const std::string query)
{
	TrieNode *temp = root;
	bool found = true;
	for (int i = 0; i < query.size(); i++)
	{
		if (not(found))
			break;
		else
		{
			if (temp->children[CHAR_TO_INDEX(query[i])])
			{
				temp = temp->children[CHAR_TO_INDEX(query[i])];
			}
			else
			{
				found = false;
			}
		}
	}
	if (not(found))
		return 0;

	else if (isLastNode(temp))
	{

		return -1;
	}
	else
	{
		suggestionsRec(temp, query);
		return 1;
	}
}
