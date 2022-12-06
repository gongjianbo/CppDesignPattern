//Composite（组合模式-对象结构型）
//将对象组合成树形结构以表示“部分-整体”的层次结构。
//Composite使得用户对单个对象和组合对象的使用具有一致性。
#include <iostream>
#include <list>

//书中定义了Leaf功能节点和Composite容器节点，
//在有的资料上Leaf和Composite接口融合的叫透明组合模式，
//Leaf和Composite一样也有增删接口但没有内部实现；
//只在Composite有子节点管理接口的叫安全组合模式。

//基类
class Component
{
public:
	explicit Component(Component* parent = nullptr)
		: parentPtr(parent) {
	}
	virtual ~Component() {}

	Component* parent() const {
		return parentPtr;
	}

	void setParent(Component* parent) {
		parentPtr = parent;
	}

	virtual void add(Component* sub) {}
	virtual void remove(Component* sub) {}
	//一致性的操作接口
	virtual void doing() = 0;

private:
	Component* parentPtr;
};

class Composite : public Component
{
public:
	using Component::Component;
	//析构时释放对象树上的子节点
	~Composite() {
		for (auto&& child : childrenList)
		{
			delete child;
		}
		childrenList.clear();
	}

	void add(Component* child) override {
		if (!child) return;
		child->setParent(this);
		childrenList.push_back(child);
	}
	void remove(Component* child) override {
		if (!child) return;
		child->setParent(nullptr);
		childrenList.remove(child);
	}
	void doing() override {
		std::cout << "composite doing. for children..." << std::endl;
		for (auto&& child : childrenList)
		{
			child->doing();
		}
	}

private:
	std::list<Component*> childrenList;
};

class Leaf : public Component
{
public:
	using Component::Component;
	void doing() override {
		std::cout << "leaf doing." << std::endl;
	}
};


//测试
void testCompositePattern()
{
	//如果leaf和composite合二为一，就可以把children管理放到基类了
	Composite* c01 = new Composite;
	Leaf* l01 = new Leaf;
	Leaf* l02 = new Leaf;
	c01->add(l01);
	c01->add(l02);

	Composite* c11 = new Composite;
	Leaf* l11 = new Leaf;
	Leaf* l12 = new Leaf;
	c11->add(l11);
	c11->add(l12);

	c01->add(c11);
	c01->doing();
	delete c01;
}
