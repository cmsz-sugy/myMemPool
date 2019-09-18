#include "pch.h"
#include "Link.h"


node * Link::createLink()
{
	int len = 4;
	head = new node();
	node *p = head;
	while (len--)
	{
		node *s = new node();
		s->value = 4 - len;
		p->next = s;//将此节点与头节点连接
		p = s;//向后移动指针,以便下一次
	}
	head = head->next;
	p->next = nullptr;
	return head;

}

Link::Link()
{
}


Link::~Link()
{
}
