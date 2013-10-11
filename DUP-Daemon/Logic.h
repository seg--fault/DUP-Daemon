#if !defined(LOGIC_H)
#define LOGIC_H

//#include <boost/functional/hash.hpp>
#include <vector>

#if defined(CYCLE_SCAVENGING)
//usage settings for the CPU, RAM, and DISK
//to ease configuration these are decided at compile time
#define DUP_CPU 0.01f;
#define DUP_RAM 0.01f;
#define DUP_DISK 0.01f;

//a function that sets up the OS to use cycle scavenging
void scavenge_initialize();
#endif //CYCLE_SCAVENGING

//set up the interfaces for each of the classes for which polymorphism is necessary
template<class Order>
class IStackFrame
{
public:
	//returns the string of words that the given stackframe hashes to
	virtual std::size_t[] getHash() {}

	//with boost support make it a transform iterator
	virtual std::iterator<std::forward_iterator_tag, class IStackFrame<Order>> getOutEdges() {}

	//execute whatever computation comes before processing adjacent vertices
	virtual void expand() {}

	//the known (min) indegree and the known outdegree
	virtual int outEdges() {}
	virtual int inEdges() {}

	//an upper bound (max confidence in O(1)) on the indegree (as a perfect inverse is not always available)
	virtual int inEdgesUpper() {}

	//the cumulative cost of this stackframe
	Order cost;
};

template<class Order, class Solution>
class IOpenList
{
public:
	//the completed or semi-completed instance of the solution
	Solution *sl;
};

template<class Order>
class IOpenList<Order, void>
{
public:
};

template<class Order, class Solution>
class IStack
{
public:
};

template<class Orders>
class IStack<Order, void>
{
public:
};

//similar to the stackframe used in traditional languages, this is an atomic unit of computation for our system
//unlike the stackframe used in traditional languages, a whole program could potentially be run within it
template<class Order>
class StackFrame : public class IStackFrame<Order>
{
public:
	StackFrame();
	~StackFrame();

	//the cumulative cost of this stackframe
	Order cost;

	//the known (min) indegree and the known outdegree
	int outEdges();
	int inEdges();

	//an upper bound (max confidence in O(1)) on the indegree (as a perfect inverse is not always available)
	int inEdgesUpper();

	//returns the string of words that the given stackframe hashes to
	std::size_t[] getHash();

	//with boost support make it a transform iterator
	std::iterator<std::forward_iterator_tag, class IStackFrame<Order>> getOutEdges();

	//execute whatever computation comes before processing adjacent vertices
	void expand();
private:
};

template<class Order, class Solution>
class OpenList : public class IOpenList<Order, Solution>
{
public:
	//with boost support make it a transform iterator
	OpenList(std::iterator<std::forward_iterator_tag, class StackFrame<Order>>);
	~OpenList();

	//deletes the smallest element of the open list
	class StackFrame<Order>* deleteMin();

	//adds an element to the OpenList
	void add(class StackFrame<Order>*);
private:
	//static class HashTable ht;
};

template<class Order, class Solution>
class Stack : public class IStack<Order, Solution>
{
public:
	Stack(class OpenList<Order, Solution>&, class ClosedList&);
	~Stack();
	class OpenList<Order, Solution> ol;
private:
	class ClosedList cl;
};

template<class Order, class Solution>
class GreedyStack : public class IStack<Order, Solution>
{
public:
	Stack(class OpenList<Order, Solution>&, class ClosedList&);
	~Stack();
	class OpenList<Order, Solution> ol;
private:
	class ClosedList cl;
};

template<class Order>
class OpenList<Order, void> : public class IOpenList<Order, void>
{
public:
	// with boost support make it a transform iterator
	OpenList(std::iterator<std::forward_iterator_tag, class StackFrame<Order>>);
	~OpenList();
	class StackFrame<Order>* deleteMin();
	void add(class StackFrame<Order>&);
private:
	//static class HashTable ht;
};

template<class Order>
class Stack<Order, void> : public class IStack<Order, void>
{
public:
	Stack(class OpenList<Order, void>&, class ClosedList&);
	~Stack();
	class OpenList<Order, void> ol;
private:
	class ClosedList cl;
};

template<class Order>
class GreedyStack<Order, void> : public class IStack<Order, void>
{
public:
	GreedyStack(class OpenList<Order, void>&, class ClosedList&);
	~GreedyStack();
	class OpenList<Order, void> ol;
private:
	class ClosedList cl;
};

//the closed list doesn't actually need to be a template because it's entirely constructed out of hash information
//
class ClosedList
{
public:
	ClosedList(std::size_t, std::size_t);
	~ClosedList();

	//check returns true for the edges which are "in" the closed list
	//false for the edges that have yet to be added
	bool check(std::size_t[], std::size_t[]);

	//the functions start add and end is the way that the closed list handles
	//adding edges already in edge to the set that will be found true by check
	void start(std::size_t[]);
	void add(std::size_t[]);
	void end();

	//edge adds an edge to the set that will be found false by check
	//no edges are even considered unless edge is called on them
	void edge(std::size_t[], std::size_t[]);

	//remove edge is the inverse of the edge operation
	void removeEdge(std::size_t[], std::size_t[]);
private:
	std::size_t hashlength;
	std::vector<std::size_t> contents;
};
#endif //LOGIC_H