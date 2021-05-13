#include <iostream>
#include <string.h>
#include <string>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <utility>
#include <stdlib.h>
#include <vector>
#include <thread>
#include <signal.h>

class InterFace
{
	struct sockaddr_in address;
	int InterFaceSocket_Id;
	socklen_t i;

	public:
	InterFace(char *port);
	struct sockaddr* getAddressStruct();
	int getInterFaceSocket();
	socklen_t* getAddressLength();
	int Bind_the_Socket();
};
socklen_t *InterFace::getAddressLength()
{
	return &i;
}

int InterFace::getInterFaceSocket()
{
	return InterFaceSocket_Id;
}

struct sockaddr *InterFace::getAddressStruct()
{
	return (struct sockaddr *) &address;
}

InterFace::InterFace(char *port)
{
	InterFaceSocket_Id = socket(AF_INET, SOCK_STREAM, 0);
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(atoi(port));
	i = sizeof(address);
	Bind_the_Socket();
}

int InterFace::Bind_the_Socket()
{
	if (InterFaceSocket_Id != -1)
	{
		if (bind(InterFaceSocket_Id, (struct sockaddr *) &address, i) != -1)
		{
			std::cout << "Interface Initialize!!" << std::endl;
		}
		else
		{
			perror("Error While Binding socket:");
			exit(EXIT_FAILURE);
		}
	}
}

class Postfix_Client_Comm
{
	int clientId, postfixId, flag;
	fd_set readfds;
	struct sockaddr_in serv_addr;
	public:
	Postfix_Client_Comm()
	{
		clientId=0;
		postfixId=0;
		flag=0;
	}
	void operator()(int clientID);
	void server_socket();
	void communication(int clientId, int postfixId);
};

void Postfix_Client_Comm :: operator()(int clientID)
{
			if (flag == 0)
			{
				serv_addr.sin_family = AF_INET;
				serv_addr.sin_port = htons(25);
				server_socket();
			}
			if (flag == 0)
				clientId = clientID;
			if (flag == 0)
				communication(clientId, postfixId);
}
void Postfix_Client_Comm::server_socket()
{
	if ((postfixId = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		std::cout << "\n Socket creation error \n";
		flag = 1;
		exit(EXIT_FAILURE);
	}

	if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0)
	{
		flag = 1;
		std::cout << "\nInvalid address/ Address not supported \n";
		perror("Address:");
		exit(EXIT_FAILURE);
	}

	if (connect(postfixId, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) == -1)
	{
		flag = 1;
		std::cout << "\nConnection Failed \n";
		perror("Connect:");
		exit(EXIT_FAILURE);
	}
}

void Postfix_Client_Comm::communication(int clientId, int postfixId)
{
	try
	{
		signal(SIGPIPE,SIG_IGN);
		char *buffer = new char[1025];
		int fd = clientId > postfixId ? clientId : postfixId;
		int bytes = 0;
		if (send(clientId, "COMMUNICATION THREAD STARTED:\n\0",strlen("COMMUNICATION THREAD STARTED:\n\0"), 0) < 0)
		{
			perror("Error in sending Hello  msg to client :");
			
		}
		while (1)
		{
			FD_ZERO(&readfds);
			FD_SET(clientId, &readfds);
			FD_SET(postfixId, &readfds);
			if (select(fd + 1, &readfds, NULL, NULL, NULL) > 0)
			{
				if (FD_ISSET(postfixId, &readfds))
				{
					if (send(clientId,"Waiting to Recv from postfix\n\0",strlen("Waiting to Recv from postfix\n\0"), 0) < 0)
					{
						perror("1Problem in sending to client :\n");
						break;
					}
					memset(buffer, 0, sizeof(buffer));
					if ((bytes = recv(postfixId, buffer, 1024, 0)) < 0)
					{
						perror("Error reciving from postfix:\n");
						break;
					}
					buffer[bytes] = '\0';
					if (send(clientId, buffer, strlen(buffer), 0) < 0)
					{
						perror("2Problem in sending to client :\n");
						break;
					}
					if (strstr(buffer, "Bye") != NULL)
					{
						FD_CLR(clientId, &readfds);
						FD_CLR(postfixId, &readfds);
						if (send(clientId, "bye client!!!\n", 15, 0) < 0)
						{
							perror("3Problem in sending to client :");
							break;
						}
						close(clientId);
						break;
					}
				}

				if (FD_ISSET(clientId, &readfds))
				{
					if (send(clientId, "sending to postfix!!\n", 23, 0) < 0)
					{
						perror("4Problem in sending msg to client:");
						break;
					}
					memset(buffer, 0, sizeof(buffer));
					if ((bytes = recv(clientId, buffer, 1024, 0)) < 0)
					{
						perror("Error reciving from client:");
						break;
					}
					buffer[bytes] = '\0';
					if (send(postfixId, buffer, strlen(buffer), 0) < 0)
					{
						perror("5Problem in sending to postfix:");
						break;
					}
				}
			}
			else
			{
				perror("Error in select:");
				break;
			}
		}
	}
	catch (std::bad_alloc e)
	{
		std::cout << "Error Allocating the buffer size:" << e.what();
	}
}

class Client_to_Interface: public InterFace
{
	std::vector <std::thread> threads;
	public:
		Client_to_Interface(char *port):InterFace(port){}
		void checkFor();
};
void Client_to_Interface::checkFor()
{
	int clientId, InterFaceSockId = getInterFaceSocket();
	if (!listen(InterFaceSockId, 3))
	{
		if ((clientId = accept(InterFaceSockId, getAddressStruct(), getAddressLength())) < 0)
		{
			perror("6Problem In Accept while Adding client :\n");
			
		}
		else
		{
			if (send(clientId, "Client Added\n", 14, 0) < 0)
			{
				perror("CLient Can't be Added:");
				
			}

			threads.push_back(std::thread(Postfix_Client_Comm(), clientId));
		}
	}
	else
	{
		perror("Unable to listen from Interface:");
		
	}
	std::cout<<threads.size()<<std::endl;
}

int main( int argc , char* argv[] )
{
	if(argc > 1)
	{
		Client_to_Interface a(argv[1]);
		while (1)
		{
			a.checkFor();
		}
	}
	else
	std::cout<<"Invalid Arguments !!!! Ex:\"./a.out (PORT_NUMBER)\""<<std::endl;
	return 0;
}