//Observer���۲���ģʽ��
//����������Dependents��������-���ģ�Publish-Subscribe��
//���������һ��һ�Զ��������ϵ����һ�������״̬�����ı�ʱ��
//�������������Ķ��󶼵õ�֪ͨ�����Զ����¡�
//��ģ�ͣ�Ŀ����۲��߷��͹��ڸı����ϸ��Ϣ��������������Ҫ���
//��ģ�ͣ�Ŀ�����С֪ͨ��ʲôҲ���ͳ������ڴ�֮���ɹ۲�����ʽ����Ŀ���ѯϸ�ڡ�
#include <iostream>
#include <string>
#include <list>

//�۲���
class AbstractObserver
{
public:
	virtual ~AbstractObserver() {}
	//����
	virtual void update(const std::string& message) = 0;
};

//Ŀ��
class AbstractSubject
{
public:
	virtual ~AbstractSubject() {}
	//ע��
	void attach(AbstractObserver* observer) {
		observerList.push_back(observer);
	}
	//ȡ������
	void detach(AbstractObserver* observer) {
		auto it = std::find(observerList.begin(), observerList.end(), observer);
		if (it != observerList.end()) {
			observerList.erase(it);
		}
	}
	//֪ͨ
	void notify(const std::string& message) {
		for (auto observer : observerList)
			observer->update(message);
	}

private:
	std::list<AbstractObserver*> observerList;
};

class ConcreateObserver : public AbstractObserver
{
public:
	void update(const std::string& message) override {
		std::cout << "observer update:" << message << std::endl;
	}
};

class ConcreateSubject : public AbstractSubject
{
public:
	//֪ͨ�۲���
	void doSome() {
		std::cout << "subject notify: do some begin" << std::endl;
		notify("do some begin.");
		// ... ...
		std::cout << "subject notify: do some finished" << std::endl;
		notify("do some finished.");
	}
};

//����
static void testObserverPattern()
{
	ConcreateSubject subject;
	ConcreateObserver ab1;
	ConcreateObserver ab2;
	subject.attach(&ab1);
	subject.attach(&ab2);
	subject.doSome();
}
