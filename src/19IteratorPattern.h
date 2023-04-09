//Iterator（迭代器模式-对象行为型）
//别名游标（Cursor）
//提供一种方法顺序访问一个聚合对象中的各个元素，而不用暴露该对象的内部表示。
#include <iostream>
#include <vector>

//迭代器
template<typename T>
class Iterator
{
public:
	virtual ~Iterator() {}
	virtual void first() = 0;
	virtual void next() = 0;
	virtual bool isDone() const = 0;
	virtual T& current() = 0;
};

//容器
template<typename T>
class DataCollection
{
public:
	Iterator<T>* iterator();
	T& get(size_t index) {
		return dataArr[index];
	}
	size_t count() const {
		return dataArr.size();
	}
	void append(const T& item) {
		dataArr.push_back(item);
	}

private:
	//自己写容器太麻烦了，拿个vector意思意思
	std::vector<T> dataArr;
};

template<typename T>
class DataCollectionIterator : public Iterator<T>
{
public:
	DataCollectionIterator(DataCollection<T>* c) : collection(c) { }
	void first() override {
		index = 0;
	}
	void next() override {
		index++;
	}
	bool isDone() const override {
		return index >= collection->count();
	}
	T& current() override {
		return collection->get(index);
	}

private:
	size_t index{ 0 };
	DataCollection<T>* collection{ nullptr };
};

template<typename T>
inline Iterator<T>* DataCollection<T>::iterator()
{
	return new DataCollectionIterator<T>(this);
}

//测试
void testIteratorPattern()
{
	DataCollection<int> dc;
	dc.append(1);
	dc.append(3);
	dc.append(7);
	Iterator<int>* iter = dc.iterator();
	for (iter->first(); !iter->isDone(); iter->next())
	{
		std::cout << "item:" << iter->current() << std::endl;
	}
	delete iter;
}
