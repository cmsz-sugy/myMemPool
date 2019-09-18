#pragma once
struct node
{
	node *next;
	int value;
};

class Link
{
public:
	node* createLink();
	Link();
	~Link();
private:
	node *head;
};

