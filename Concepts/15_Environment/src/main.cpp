#include <iostream>
#include <cstdlib>
#include <unistd.h>

//std::setenv, std::putenv - in c
//std::getenv("id") //gets the string value of specified env variable.
//int main(int argc,char* argv[],char** envp) // part of cmdline; envp is null terminated.
// extern char **environ; //defined in cstdlib; null terminated.

extern char **environ;

int main(int ,char** ,char** envp)
{
	setenv("PASSCODE1","passcode1",1);
	putenv((char*)("PASSCODE2=passcode2"));

	std::cout <<"std::getenv(\"HOME\") = "<<std::getenv("HOME")<< std::endl;

	for(int i = 0; envp[i] != nullptr; i++)
	{
		std::cout << " envp[i] = " << envp[i] << std::endl;
	}

	for(int i = 0; environ[i] != nullptr; i++)
	{
		std::cout << " environ[i] = " << environ[i] << std::endl;
	}

	return 0;
}