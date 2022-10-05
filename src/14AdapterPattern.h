//Adapter（适配器模式-类/对象结构型）
//别名包装器（Wrapper ，书上装饰器和适配器别名都叫 Wrapper）
//将一个类的接口转换成客户希望的另外一个接口。
//Adapter 模式使得原本由于接口不兼容而不能一起工作的那些类可以一起工作。
//GoF 23 定义类对象适配器和类适配器两种模式，
//类适配器采用多继承，对象适配器采用对象组合。
//适配器模式能为被封装对象提供不同的接口， 代理模式能为对象提供相同的接口， 
//装饰模式则能为对象提供加强的接口。
#include <iostream>
#include <string>
#include <vector>
#include <memory>

struct Point
{
	int x;
	int y;
};

//原本只有drawLines接口
class OldPainter
{
public:
	virtual ~OldPainter() {}
	virtual void drawLines(const std::vector<Point>& points) = 0;
};

class SDKPainter : public OldPainter
{
public:
	void drawLines(const std::vector<Point>& points) {
		std::cout << "call old drawLines" << std::endl;
	}
};

//新封装的绘图系统具有更丰富的接口
class NewPainter
{
public:
	virtual ~NewPainter() {}
	virtual void drawLine(const Point& p1, const Point& p2) = 0;
	virtual void drawLines(const std::vector<Point>& points) = 0;
};

//适配调用SDKPainter接口
class PainterAdapter : public NewPainter
{
public:
	explicit PainterAdapter(const std::shared_ptr<OldPainter>& ptr)
		: painter(ptr) {
	}
	//适配成已有接口的参数
	void drawLine(const Point& p1, const Point& p2) override {
		std::cout << "new drawLine" << std::endl;
		painter->drawLines(std::vector<Point>{p1, p2});
	}
	void drawLines(const std::vector<Point>& points) override {
		std::cout << "new drawLines" << std::endl;
		painter->drawLines(points);
	}

private:
	std::shared_ptr<OldPainter> painter;
};

//测试
void testAdapterPattern()
{
	std::shared_ptr<OldPainter> oldp{ new SDKPainter };
	std::shared_ptr<NewPainter> newp{ new PainterAdapter(oldp) };
	Point p1, p2;
	newp->drawLine(p1, p2);
	newp->drawLines(std::vector<Point>{p1, p2});
}
