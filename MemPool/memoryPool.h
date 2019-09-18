#pragma once
#include<queue>
#include <string.h>
#include <ctime>
using namespace std;

struct block {
	block * next;
	unsigned int numofChunks;//指向下一个block指针
	unsigned int numofFreeChunks;//剩余free的chunk数量
	unsigned int blockNum;//该block的编号
	char * data;
	//记录可用chunk序号
	queue<int> freepos;
	block(unsigned int _numofChunks, unsigned int _chunkSize, unsigned int _blockNum) {
		numofChunks = _numofChunks;
		numofFreeChunks = _numofChunks;
		blockNum = _blockNum;
		next = NULL;
		data = new char[numofChunks * (sizeof(unsigned int) + sizeof(void *) + _chunkSize)];
		char * p = data;
		//每个chunk的结构：4byte的chunk序号 + 4byte的所属block地址 + 真正的数据
		for (int i = 0; i < numofChunks; i++) {
			char * ptr = p + i * (_chunkSize + sizeof(unsigned int) + sizeof(void *));
			unsigned int * num = (unsigned int *)(ptr);
			*num = i;
			ptr += sizeof(void *);
			int * blockpos = (int *)ptr;
			*blockpos = (int)this;
			freepos.push(i);
		}
	}
	~block() {
		delete[] data;
	}
};
class memoryPool
{
public:
	memoryPool(unsigned int _chunkSize = 256, unsigned int _initNumofChunks = 4096, unsigned int _steps = 64) {
		initNumofChunks = _initNumofChunks;
		chunkSize = _chunkSize;
		steps = _steps;
		numofBlocks = steps;
		//创建内存池时，初始化一定数量的内存空间
		block * p = new block(initNumofChunks, chunkSize, 0);
		blocksPtr = p;
		for (int i = 1; i < steps; i++) {
			p->next = new block(initNumofChunks, chunkSize, i);
			p = p->next;
			blocksPtrTail = p;
		}
		firstHasFreeChunksBlock = blocksPtr;
	}
	~memoryPool();
	void * allocate();
	void increaseBlocks();
	void freeMemory(void * _data);
	void echoPositionNum(char * p);
	//测试
	void test0();
	//测试
	void test1();
	//测试
	void test2();
private:
	unsigned int initNumofChunks; //每个block的chunk数量
	unsigned int chunkSize;//每个chunk的数据大小
	unsigned int steps;//每次扩展的chunk数量
	unsigned int numofBlocks;//当前管理多少个blocks
	block * blocksPtr;//指向起始block
	block * blocksPtrTail;//指向末尾block
	block * firstHasFreeChunksBlock;//指向第一个不为空的block
};

