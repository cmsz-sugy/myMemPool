#pragma once
//#define size 4
#include<queue>
#include<mutex>
using namespace std;
struct  memoryPoolUnit
{
	memoryPoolUnit *next;
	char date[4];
};
class MyMemPool
{
public:
	void memPoolDestroy( memoryPoolUnit *mObj);
	memoryPoolUnit *memPoolAlloc(size_t allocMemSize);
	void printLengthMemLink();
	MyMemPool();
	void memPoolCreate(int linkLength);
	void memPoolFree();
	~MyMemPool();
private:
	queue <memoryPoolUnit*> mem_pool_queue;
	std::mutex mtx_alloc;
	std::mutex mtx_detroy;
};

