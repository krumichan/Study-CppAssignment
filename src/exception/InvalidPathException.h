#include <exception>
#include <iostream>

using namespace std;

struct InvalidPathException : public exception
{
public:
	explicit InvalidPathException(const char* message) : _msg(message)
	{
	}

	explicit InvalidPathException(const string& message) : _msg(message)
	{
	}

	virtual ~InvalidPathException() throw()
	{
	}

	virtual const char* what() const throw()
	{
	return _msg.c_str();
	}

protected:
	string _msg;
};
