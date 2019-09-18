#include "pch.h"
#include "memoryPool.h"
#include<iostream>
using namespace std;
memoryPool::~memoryPool()
{
	block  * p = blocksPtr;
	while (blocksPtr != NULL) {
		p = blocksPtr->next;
		delete blocksPtr;
		blocksPtr = p;
	}
}

void * memoryPool::allocate()
{
	block * p = firstHasFreeChunksBlock;
	while (p != NULL && p->numofFreeChunks <= 0) p = p->next;
	if (p == NULL) {
		p = blocksPtrTail;
		increaseBlocks();
		p = p->next;
		firstHasFreeChunksBlock = p;
	}
	unsigned int pos = p->freepos.front();
	void * chunkStart = (void *)(p->data + pos * (chunkSize + sizeof(unsigned int) + sizeof(void *)));
	void * res = (char *)chunkStart + sizeof(unsigned int) + sizeof(void *);
	p->freepos.pop();
	p->numofFreeChunks--;
	return res;
}

void memoryPool::increaseBlocks()
{
	block * p = blocksPtrTail;
	for (int i = 0; i < steps; i++) {
		p->next = new block(initNumofChunks, chunkSize, numofBlocks);
		numofBlocks++;
		p = p->next;
		blocksPtrTail = p;
	}
}
/*
 传入待释放的地址指针_data，
 通过对_data的地址移动可以找到chunk中的ChunkNum和blockAddress两个数据，
 通过blockAddress可以找到该chunk所属的block，
 然后将ChunkNum添加到该block的freepos中，其他相应属性更新。
 */
void memoryPool::freeMemory(void * _data)
{
	void * p = _data;
	p = (char *)p - sizeof(void *);
	int * blockpos = (int *)p;
	block * b = (block *)(*blockpos);
	p = (char *)p-sizeof(unsigned int);
	int * num = (int *)p;
	b->freepos.push(*num);
	b->numofFreeChunks++;
	if (b->numofFreeChunks > 0 && b->blockNum < firstHasFreeChunksBlock->blockNum)
		firstHasFreeChunksBlock = b;
}

void memoryPool::echoPositionNum(char * p)
{
	p -= (sizeof(void *) + sizeof(unsigned int));
	int * num = (int *)p;
	cout << *num << endl;
}

void memoryPool::test0()
{
	memoryPool mp;
	char * s1 = (char *)mp.allocate();
	char * s2 = (char *)mp.allocate();

	char str[256];
	char str2[256];
	char str3[256];
	for (int i = 0; i < 255; i++) {
		str[i] = 'a'; str2[i] = 'b'; str3[i] = 'c';
	}
	str[255] = '\0';
	str2[255] = '\0';
	strcpy(s1, str);
	strcpy(s2, str2);
	str3[255] = '\0';
	echoPositionNum(s1);

	cout << s1 << endl;
	mp.freeMemory(s1);
	echoPositionNum(s2);
	cout << s2 << endl;
	char * s3 = (char *)mp.allocate();
	strcpy(s3, str3);

	echoPositionNum(s3);
	cout << s3 << endl;

}

void memoryPool::test1()
{
	clock_t clock_begin = clock();
	const int N = 50000;
	char * s[N];
	int round = 100;
	while (round >= 0) {
		round--;
		for (int i = 0; i < N; i++) {
			s[i] = new char[256];
		}
		for (int i = 0; i < N; i++) {
			delete[] s[i];
		}
	}
	clock_t clock_end = clock();
	cout << "Time cost\t" << clock_end - clock_begin << endl;
}

void memoryPool::test2()
{
	memoryPool mp(256);
	clock_t clock_begin = clock();
	const int N = 50000;
	char * s[N];
	int round = 100;
	while (round >= 0) {
		round--;
		for (int i = 0; i < N; i++) {
			s[i] = (char *)mp.allocate();
		}
		for (int i = 0; i < N; i++) {
			mp.freeMemory(s[i]);
		}
	}
	clock_t clock_end = clock();
	cout << "Time cost\t" << clock_end - clock_begin << endl;
}
