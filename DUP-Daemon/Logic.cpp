#include "Logic.h"

namespace Logic
{
	//base functions
	//scavenging functions
	void scavenge_initialize()
	{

	}

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
			return;
		this.cl = initCl;
		this.ol = *initOl;
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
}