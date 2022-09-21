//Decorator（装饰模式-对象结构型）
//别名包装器（Wrapper ，书上装饰器和适配器别名都叫 Wrapper）
//动态地给一个对象添加一些额外的职责。
//就添加功能来说，装饰模式比生成子类更为灵活。
#include <iostream>
#include <string>

//被装饰对象基类，此处为数据流
class Stream
{
public:
	virtual ~Stream() {}
	virtual bool open() = 0;
	virtual uint64_t read(char* out, uint64_t max) = 0;
	virtual uint64_t write(const char* in, uint64_t len) = 0;
	virtual void close() = 0;
};

//文件数据流
class FileStream : public Stream
{
public:
	FileStream(const std::string& filepath)
		: currentPath(filepath) {}
	bool open() override {
		//... ...
		std::cout << "FileStream open" << std::endl;
		return true;
	}
	uint64_t read(char* out, uint64_t max) override {
		uint64_t read_len = 0;
		//此处为读取文件数据逻辑
		std::cout << "FileStream read" << std::endl;
		return read_len;
	}
	uint64_t write(const char* in, uint64_t len) override {
		uint64_t write_len = 0;
		//此处为数据写入文件逻辑
		std::cout << "FileStream write" << std::endl;
		return write_len;
	}
	void close() override {
		//... ...
		std::cout << "FileStream close" << std::endl;
	}

private:
	std::string currentPath;
};

//内存数据流
//class MemoryStream : public Stream

//网络数据流
//class NetworkStream : public Stream

//装饰器基类
//通过组合的方式对对象扩展
class Decorator : public Stream
{
public:
	Decorator(Stream* s) : stream(s) {}

	Stream* getStream() {
		return stream;
	}

private:
	Stream* stream;
};

//具体装饰类，此处为给输入输出添加加密装饰
class CryptDecorator : public Decorator
{
public:
	CryptDecorator(Stream* s) : Decorator(s) {}

	bool open() override {
		//... ...
		std::cout << "CryptDecorator open" << std::endl;
		return getStream()->open();
	}
	uint64_t read(char* out, uint64_t max) override {
		std::cout << "CryptDecorator read and decrypt" << std::endl;
		char* crypt_data = nullptr;
		//初始化缓冲区略
		uint64_t read_len = getStream()->read(crypt_data, max);
		//decrypt解密数据--此处假设加解密不影响长度
		//解密之后输出到out缓冲区
		//memcpy(out, crypt_data, read_len);
		return read_len;
	}
	uint64_t write(const char* in, uint64_t len) override {
		std::cout << "CryptDecorator encrypt and write" << std::endl;
		char* crypt_data = nullptr;
		//初始化缓冲区略
		//encrypt加密数据--此处假设加解密不影响长度
		//加密之后写入文件
		return getStream()->write(crypt_data, len);
	}
	void close() override {
		//... ...
		std::cout << "CryptDecorator close" << std::endl;
		getStream()->close();
	}
};

//测试
static void testDecoratorPattern()
{
	FileStream fs("filepath");
	CryptDecorator cd(&fs);
	if (cd.open()) {
		char buffer[256];
		cd.read(buffer, 256);
		cd.write(buffer, 256);
		cd.close();
	}
}