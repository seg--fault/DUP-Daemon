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
	HashEntry(char *toSerialize, size_t length);

private:
	void *continuation;
	char localstore[256];
};

class HashTable
{
public:
	HashTable(size_t length);

private:
	HashEntry table[];
};

#endif