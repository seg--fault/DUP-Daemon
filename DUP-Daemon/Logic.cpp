#include "Logic.h"

//base functions

#if defined(CYCLE_SCAVENGING)
//scavenging functions
void scavenge_initialize()
{

}
#endif //CYCLE_SCAVENGING

//stack
template<class Order, class Solution>
Stack<Order, Solution>::Stack(class OpenList<Order, Solution> &initOl, class ClosedList &initCl)
{
	if(!initOl)
		return;
	this.cl = initCl;
	this.ol = initOl;
	for(class StackFrame<Order>* currentMin; Solution.is((currentMin = this.ol.deleteMin()));)
	{
	}
}

template<class Order>
Stack<Order, void>::Stack(class OpenList<Order, void> &initOl, class ClosedList &initCl)
{
	if(!initOl)
	{
		return;
	}
	this.cl = initCl;
	this.ol = initOl;
	for(;;)
	{
	}
}

template<class Order, class Solution>
Stack<Order, Solution>::~Stack()
{
}

template<class Order>
Stack<Order, void>::~Stack()
{
}

ClosedList::ClosedList(std::size_t hl, std::size_t length)
{
	hashlength = hl;
	contents = std::vector<std::size_t>();
	contents.resize(length);
}