#include<iostream>
#include<string>
#include<pthread.h>

void func()
{
	std::cout<<"executed"<<std::endl;
}

class Thread
{
	int id;
	pthread_attr_t attr;
	pthread_t t;
	
public:

	template <class Fn, class... Args>
	Thread (Fn&& fn, Args&&... args) noexcept;
	int get_id();
	bool joinable() noexcept;
	void join();
	void detach();
	
};


int Thread::get_id()
{
	return id;
}

template <class Fn, class... Args>
Thread::Thread (Fn&& fn, Args&&... args) noexcept
{
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_JOINABLE);
 	int c=pthread_create(&t,&attr,(void *(*)(void *))fn,NULL);
	if(c)
	throw("Thread Not Created :" + std::to_string(c));
}

void Thread::join()
{
	if(pthread_join(t,NULL))
	std::cout<<"Thread join failed"<<std::endl;
	
	
}

bool Thread::joinable() noexcept
{
	int result;
	if(!pthread_attr_getdetachstate(&attr,&result))
		if((result)==PTHREAD_CREATE_JOINABLE)
		return true;
		else
		return false;
	else
	throw("Cann't check the state:");	
}

void Thread::detach()
{
	if(pthread_detach(t))
	std::cout<<"Detach Failed";
}

int main()
{
 	try
	{
  		Thread T(func,NULL);
		if(T.joinable())
		T.join();
	
	}
	catch(std::string e)
	{
		std::cout<<e<<std::endl;
	}
}

