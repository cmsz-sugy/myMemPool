#include "pch.h"
#include "MyMemPool.h"
#include<iostream>
#include <math.h>
#include<queue>
using namespace std;
void MyMemPool::memPoolDestroy( memoryPoolUnit *mObj)
{
	mtx_detroy.lock();
	if (mObj != nullptr) {
		mem_pool_queue.push(mObj);
	}
	mtx_detroy.unlock();
}

memoryPoolUnit * MyMemPool::memPoolAlloc(size_t blockNum)
{
	mtx_alloc.lock();
	memoryPoolUnit *alloc_mem = nullptr;

		if (mem_pool_queue.size() == 0) {
			memoryPoolUnit *memNode = new memoryPoolUnit();
			mem_pool_queue.push(memNode);
		}
		alloc_mem = mem_pool_queue.front();
		mem_pool_queue.pop();
		mtx_alloc.unlock();
	return alloc_mem;

}

void MyMemPool::printLengthMemLink()
{
	int lengthmpool = mem_pool_queue.size();
	cout << "this mpool length is :"<< lengthmpool<<endl;

}

MyMemPool::MyMemPool()
{
}

void MyMemPool::memPoolCreate(int blockNum)
{
	memoryPoolUnit *memNode = new memoryPoolUnit();
	while (blockNum--)
	{
		memoryPoolUnit *node = new memoryPoolUnit();
		mem_pool_queue.push(node);
	    
	}

}

MyMemPool::~MyMemPool()
{
}
