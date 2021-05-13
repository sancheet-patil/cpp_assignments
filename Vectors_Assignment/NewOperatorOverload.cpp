#include <iostream>

class A
{
	static int stackCount;
	static int dynamicCount;
	int flag;
	static int Abflag;
	public:
		A()
		{
			if (Abflag == 1)
			{
				dynamicCount++;
				flag = 1;
				Abflag = 0;
			}
			else
			{
				stackCount++;
				flag = 0;
				Abflag = 0;
			}
		}~A()
		{
			std::cout << "Destructor";
			stackCount--;
		}

	void *operator new(size_t count)
	{
		void *a = malloc(count);
		A::Abflag = 1;
		std::cout << "New Overloaded Function Called!!" << std::endl;
		return a;
	}

	void operator delete(void *p)
	{
		if ((*(A*) p).flag == 1)
		{
			dynamicCount--;
			stackCount++;
			std::cout << "Delete Overloaded Function Called!!" << std::endl;
		}

		free(p);
	}

	static int getstackCount()
	{
		return stackCount;
	}

	static int getDynamicCount()
	{
		return dynamicCount;
	}
};
int A::stackCount = 0;
int A::dynamicCount = 0;
int A::Abflag = 0;

int main()
{
	A s;
	A d;
	A *a = new A();
	std::cout << "After allocation!!\n";
	A *jh = NULL;
	delete a;
	A *fd = new A();
	jh = &s;
	delete jh;
	std::cout << "Stack Count:" << A::getstackCount() << std::endl;
	std::cout << "Dynamic Count:" << A::getDynamicCount() << std::endl;
}