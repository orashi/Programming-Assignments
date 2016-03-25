#include <iostream>

using namespace std;


class datas {
public:
	int ci, xi;
	datas(int a,int b):ci(a),xi(b){}
};

class PNode {
	friend class PoQueue;
	friend class Poly;
public:
	PNode(datas a,PNode *p) :data(a), next(p) {}
private:
	datas data;
	PNode* next;
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PoQueue {
	friend class Poly;
	friend PoQueue addterm(PoQueue a, PoQueue &b, PoQueue &r);
	friend PoQueue addterm(PoQueue a, PoQueue b);
	friend PoQueue subterm(PoQueue a, PoQueue &b, PoQueue &r);
	friend PoQueue subterm(PoQueue a, PoQueue b);
	friend PoQueue multtermAll(datas a, PoQueue& b, PoQueue &r);
	friend PoQueue multtermAll(datas a, PoQueue& b);
	friend PoQueue multterm(PoQueue a, PoQueue b);
private:
	void deenQueue(datas);
	datas deQueue();
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
	void enQueue(datas);
	PoQueue& enIt(int ci, int xi);
};


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

PoQueue addterm(PoQueue a, PoQueue &b, PoQueue &r) {
	if (a.isEmpty()&& b.isEmpty())	return r;
	else if (b.isEmpty()) { 
		r.enQueue(a.deQueue()); 
		return addterm(a, b, r);
	
	}
	else if (a.isEmpty()) { 
		r.enQueue(b.deQueue()); 
		return addterm(a, b, r);
	}
	else {
		datas as = a.deQueue(), bs = b.deQueue();
		if (as.ci>bs.ci)
		{
			r.enQueue(as);
			b.deenQueue(bs);
			return addterm(a, b, r);
		}
		else 	if (as.ci<bs.ci)
		{
			r.enQueue(bs);
			a.deenQueue(as);
			return addterm(a, b, r);
		}
		else
		{
			datas oh(as.ci, as.xi + bs.xi);
			r.enQueue(oh);
			return addterm(a, b, r);
		}
	}
	return r;

}
PoQueue addterm(PoQueue a, PoQueue b) {
	PoQueue result;
	if (a.isEmpty() && b.isEmpty())	return result;
	else if (b.isEmpty()) {
		result.enQueue(a.deQueue());
		return addterm(a, b, result);

	}
	else if (a.isEmpty()) {
		result.enQueue(b.deQueue());
		return addterm(a, b, result);
	}
	else {
		datas as = a.deQueue(), bs = b.deQueue();
		if(as.ci>bs.ci)
		{
			result.enQueue(as);
			b.deenQueue(bs);
			return addterm(a, b, result);
		}
		else 	if (as.ci<bs.ci)
		{
			result.enQueue(bs);
			a.deenQueue(as);
			return addterm(a, b, result);
		}
		else
		{
			datas oh(as.ci, as.xi + bs.xi);
			result.enQueue(oh);
			return addterm(a, b, result);
		}
	}
	return result;
}

PoQueue subterm(PoQueue a, PoQueue &b, PoQueue &r) {
	if (a.isEmpty() && b.isEmpty())	return r;
	else if (b.isEmpty()) {
		r.enQueue(a.deQueue());
		return addterm(a, b, r);

	}
	else if (a.isEmpty()) {
		r.enQueue(b.deQueue());
		return addterm(a, b, r);
	}
	else {
		datas as = a.deQueue(), bs = b.deQueue();
		if (as.ci>bs.ci)
		{
			r.enQueue(as);
			b.deenQueue(bs);
			return addterm(a, b, r);
		}
		else 	if (as.ci<bs.ci)
		{
			r.enQueue(bs);
			a.deenQueue(as);
			return addterm(a, b, r);
		}
		else
		{
			datas oh(as.ci, as.xi + bs.xi);
			r.enQueue(oh);
			return addterm(a, b, r);
		}
	}
	return r;

}
PoQueue subterm(PoQueue a, PoQueue b) {
	datas fuhao(0, -1);
	PoQueue newb(multtermAll(fuhao, b));
	PoQueue result;
	if (a.isEmpty() && newb.isEmpty())	return result;
	else if (newb.isEmpty()) {
		result.enQueue(a.deQueue());
		return addterm(a, newb, result);
	}
	else if (a.isEmpty()) {
		result.enQueue(newb.deQueue());
		return addterm(a, newb, result);
	}
	else {
		datas as = a.deQueue(), bs = newb.deQueue();
		if (as.ci>bs.ci)
		{
			result.enQueue(as);
			newb.deenQueue(bs);
			return addterm(a, newb, result);
		}
		else 	if (as.ci<bs.ci)
		{
			result.enQueue(bs);
			a.deenQueue(as);
			return addterm(a, newb, result);
		}
		else
		{
			datas oh(as.ci, as.xi + bs.xi);
			result.enQueue(oh);
			return addterm(a, newb, result);
		}
	}
	return result;
}


PoQueue multtermAll(datas a, PoQueue &b, PoQueue &r) {
	if (b.isEmpty())
		return r;
	datas ee = b.deQueue();
	datas oh(a.ci + ee.ci, a.xi * ee.xi);
	r.enQueue(oh);
	return multtermAll(a, b, r);
}
PoQueue multtermAll(datas a, PoQueue &b) {
	PoQueue result;
	if (b.isEmpty())
		return result;
	datas ee = b.deQueue();
	datas oh(a.ci + ee.ci, a.xi * ee.xi);
	result.enQueue(oh);
	return multtermAll(a, b,result);
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

class Poly {
	friend Poly addPoly(Poly a, Poly b);
	friend Poly multPoly(Poly a, Poly b);
	friend Poly subPoly(Poly a, Poly b);
private:
	PoQueue w;

public:
	Poly(PoQueue ps) :w(ps) {};
	Poly& show();

};
Poly& Poly::show() {
	PNode* tp = w.first;
	for (int i = w.N; i > 0; i--)
	{
		cout << tp->data.xi << "x^" << tp->data.ci;
		tp = tp->next;
		if (i != 1)
			cout << '+';
	}
	cout << endl;
	return *this;

}
Poly addPoly(Poly a, Poly b) {
	Poly newp(addterm(a.w, b.w));
	return newp;
}
Poly multPoly(Poly a, Poly b) {
	Poly newp(multterm(a.w, b.w));
	return newp;
}
Poly subPoly(Poly a, Poly b) {
	Poly newp(subterm(a.w, b.w));
	return newp;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
/*
API:PoQueue：
PoQueue& PoQueue::enIt(int xi, int ci）  次数由大到小
Poly：
Poly addPoly(Poly a, Poly b)
Poly subPoly(Poly a, Poly b)
Poly multPoly(Poly a, Poly b)
Poly& Poly::show()
*/
void main(void) {
	PoQueue a, b,c;
	a.enIt(2,1); b.enIt(2,5).enIt(3,4).enIt(2,3),c.enIt(2,2);//enIt 次数由大到小
	Poly aa(a), bb(b),cc(c);
	subPoly(multPoly(addPoly(aa, bb).show(), aa).show(),cc).show();
}