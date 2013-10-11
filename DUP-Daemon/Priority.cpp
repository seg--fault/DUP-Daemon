#include "Priority.h"

HashEntry::HashEntry(char *toSerialize, size_t length)
{
	if(length < DUP_LOCALSTORESIZE)
	{
		for(int i = 0; i < length; i++)
		{
			localstore[i] = toSerialize[i];
		}
		continuation = NULL;
	}
	else
	{
		if(continuation = (char *)malloc(length))
		{
			for(int i = 0; i < DUP_LOCALSTORESIZE; i++)
			{
				localstore[i] = toSerialize[i];
			}
			for(int i = DUP_LOCALSTORESIZE; i < length; i++)
			{
				continuation[i] = toSerialize[i];
			}
		}
		else
		{
			//fail quickly!
		}
	}
}

void HashEntry::clear()
{
	if(continuation)
	{
		free(continuation);
	}
}

HashTable::HashTable(size_t length)
{
}

