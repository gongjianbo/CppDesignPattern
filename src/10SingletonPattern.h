//Singleton（单例模式-对象创建型）
//保证一个类仅有一个实例，并提供一个访问它的全局访问点。
#include <iostream>

//拷贝构造和赋值禁用
#define DISABLE_COPY(Class) \
    Class(const Class &) = delete; \
    Class &operator=(const Class &) = delete;

//移动构造和赋值禁用
#define DISABLE_MOVE(Class) \
    Class(Class &&) = delete; \
    Class &operator=(Class &&) = delete;

#define DISABLE_COPY_MOVE(Class) \
    DISABLE_COPY(Class) \
    DISABLE_MOVE(Class)

class Singleton
{
private:
	Singleton() {}
	DISABLE_COPY_MOVE(Singleton)
public:
	//懒汉模式：在第一次调用getInstance时初始化
	static Singleton* getInstance() {
		static Singleton instance;
		return &instance;
	}
	//饿汉模式：在程序初始化时初始化
	// static Singleton* instance;
};

//测试
void testSingletonPattern()
{
	std::cout << "Singleton::getInstance() assign to p1" << std::endl;
	Singleton* p1 = Singleton::getInstance();
	std::cout << "Singleton::getInstance() assign to p2" << std::endl;
	Singleton* p2 = Singleton::getInstance();
	std::cout << "p1 equals p2? " << (p1 == p2 ? "true" : "false") << std::endl;
}
