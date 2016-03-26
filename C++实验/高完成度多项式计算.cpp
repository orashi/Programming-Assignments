#include <iostream>

using namespace std;

class datas {
	friend class PNode;
	friend class PoQueue;
	friend PoQueue addterm(PoQueue a, PoQueue b);
	friend PoQueue subterm(PoQueue a, PoQueue b);
	friend PoQueue multterm(PoQueue a, PoQueue b);
	friend PoQueue multtermAll(datas a, PoQueue b);
private:
	int ci, xi;
public:
	datas(int a,int b):ci(a),xi(b){}
};

class PNode {
	friend class PoQueue;
public:
	PNode(datas a,PNode *p) :data(a), next(p) {}
private:
	datas data;
	PNode* next;
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PoQueue {
	friend PoQueue addterm(PoQueue a, PoQueue b);
	friend PoQueue subterm(PoQueue a, PoQueue b);
	friend PoQueue multtermAll(datas a, PoQueue b);
	friend PoQueue multterm(PoQueue a, PoQueue b);
private:
	void deenQueue(datas);
	datas deQueue();
	void enQueue(datas);
	int size() { return N; }
	bool isEmpty() { return N == 0; }
	PNode *first,*last;
	int N;
public:
	PoQueue() :N(0), first(NULL), last(NULL) {}
	PoQueue(PoQueue& y) :N(0), first(NULL), last(NULL) {
		PNode* tp = y.first;
		for (int i = y.N; i > 0; i--)
		{
			enQueue(tp->data);
			tp = tp->next;
		}
	}
	~PoQueue() {
		for (int i = N; i > 0; i--)
		{
			PNode* tp = first;
			first = first->next;
			delete tp;
		}
	}
	PoQueue& enIt(int ci, int xi);
	PoQueue& show();
};
PoQueue& PoQueue::show() {
	PNode* tp = first;
	for (int i = N; i > 0; i--)
	{
		cout << tp->data.xi << "x^" << tp->data.ci;
		tp = tp->next;
		if (i != 1)
			cout << '+';
	}
	cout << endl;
	return *this;

}
void PoQueue::enQueue(datas a) {
	PNode* oldlast = last;
	last = new PNode(a, NULL);
	if (isEmpty())	 first = last;
	else			oldlast->next = last;
	N++;
}
void PoQueue::deenQueue(datas a) {
	PNode* oldfirst = first;
	first = new PNode(a, oldfirst);
	N++;
}
datas PoQueue::deQueue() {
	if (first)
	{
		datas t = first->data;
		PNode* tp = first;
		first = first->next;
		delete tp;
		N--;
		return t;
	}
	throw underflow_error("Nothing to deQueue!");
}

PoQueue& PoQueue::enIt(int xi, int ci) {
	datas a1(ci, xi);
	enQueue(a1);
	return *this;
}

PoQueue addterm(PoQueue a, PoQueue b) {
	PoQueue result;
	while (1) {
		if (a.isEmpty() && b.isEmpty())	return result;
		else if (b.isEmpty()) {
			result.enQueue(a.deQueue());
		}
		else if (a.isEmpty()) {
			result.enQueue(b.deQueue());
		}
		else {
			datas as = a.deQueue(), bs = b.deQueue();
			if (as.ci>bs.ci)
			{
				result.enQueue(as);
				b.deenQueue(bs);
			}
			else 	if (as.ci<bs.ci)
			{
				result.enQueue(bs);
				a.deenQueue(as);
			}
			else
			{
				datas oh(as.ci, as.xi + bs.xi);
				result.enQueue(oh);
			}
		}
	}
	
}
PoQueue subterm(PoQueue a, PoQueue b) {
	datas fuhao(0, -1);
	PoQueue newb(multtermAll(fuhao, b));
	PoQueue result;
	while (1) {
		if (a.isEmpty() && newb.isEmpty())	return result;
		else if (newb.isEmpty()) {
			result.enQueue(a.deQueue());
		}
		else if (a.isEmpty()) {
			result.enQueue(newb.deQueue());
		}
		else {
			datas as = a.deQueue(), bs = newb.deQueue();
			if (as.ci>bs.ci)
			{
				result.enQueue(as);
				newb.deenQueue(bs);
			}
			else 	if (as.ci<bs.ci)
			{
				result.enQueue(bs);
				a.deenQueue(as);
			}
			else
			{
				datas oh(as.ci, as.xi + bs.xi);
				result.enQueue(oh);
			}
		}
	}
	
}
PoQueue multtermAll(datas a, PoQueue b) {
	PoQueue result;
	while (1)
	{
		if (b.isEmpty())
			return result;
		datas ee = b.deQueue();
		datas oh(a.ci + ee.ci, a.xi * ee.xi);
		result.enQueue(oh);
	}
}
PoQueue multterm(PoQueue a, PoQueue b) {
	static PoQueue empty;
	if (a.isEmpty())
		return empty;
	else
	{
		datas temp = a.deQueue();
		PoQueue tempb(b);
		return addterm(multtermAll(temp, tempb), multterm(a, b));
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
API:PoQueue：


PoQueue& PoQueue::enIt(int xi, int ci）  次数由大到小
PoQueue addterm(PoQueue a, PoQueue b)
PoQueue subterm(PoQueue a, PoQueue b)
PoQueue multterm(PoQueue a, PoQueue b)
PoQueue multtermAll(datas a, PoQueue b)
PoQueue& PoQueue::show()


*/
void main(void) {
	PoQueue a, b,c;
	a.enIt(2,1); b.enIt(2,5).enIt(3,4).enIt(2,3),c.enIt(2,2);//enIt 次数由大到小
	subterm(multterm(addterm(a, b).show(), a).show(),c).show();
}