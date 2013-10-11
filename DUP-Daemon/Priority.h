#if !defined(PRIORITY_H)
#define PRIORITY_H
#include "Logic.h"

#define DUP_LOCALSTORESIZE 256

class PriorityQueue
{
};

class HashEntry
{
public:
	HashEntry(char*, size_t);
	HashEntry();
	bool isContinued();
	void clear();
	void serialize(void *, size_t);
private:
	char *continuation;
	char localstore[256];
};

class HashTable
{
public:
	HashTable(size_t);

private:
	HashEntry table[];
};

#endif