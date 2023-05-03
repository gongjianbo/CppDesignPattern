//Visitor（访问器模式-对象行为型）
//表示一个作用于某对象结构中的各元素的操作。
//它使你可以在不改变各元素的类的前提下定义作用于这些元素的新操作。
#include <iostream>
#include <string>

class Visitor;

class Element
{
public:
	virtual ~Element() {}
	virtual void accept(Visitor* vt) = 0;
};

class ElementA : public Element
{
public:
	void accept(Visitor* vt) override;
};

class ElementB : public Element
{
public:
	void accept(Visitor* vt) override;
};

class Visitor
{
public:
	virtual ~Visitor() {}
	virtual void visitElementA(ElementA* ea) = 0;
	virtual void visitElementB(ElementB* eb) = 0;
};

class Visitor1 : public Visitor
{
public:
	virtual void visitElementA(ElementA* ea) override {
		std::cout << "Visitor1 process ElementA" << std::endl;
	}
	virtual void visitElementB(ElementB* eb) override {
		std::cout << "Visitor1 process ElementB" << std::endl;
	}
};

class Visitor2 : public Visitor
{
public:
	virtual void visitElementA(ElementA* ea) override {
		std::cout << "Visitor2 process ElementA" << std::endl;
	}
	virtual void visitElementB(ElementB* eb) override {
		std::cout << "Visitor2 process ElementB" << std::endl;
	}
};

void ElementA::accept(Visitor* vt) {
	vt->visitElementA(this);
}

void ElementB::accept(Visitor* vt) {
	vt->visitElementB(this);
}

//测试
void testVisitorPattern()
{
	Visitor2 vt1;
	Visitor2 vt2;
	ElementB eb;
	eb.accept(&vt1);
	eb.accept(&vt2);
}
