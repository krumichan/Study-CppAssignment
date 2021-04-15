#include <exception>
#include <iostream>

using namespace std;

struct FailToGetImageException : public exception
{
public:
	explicit FailToGetImageException(const char* message) : _msg(message)
	{
	}

	explicit FailToGetImageException(const string& message) : _msg(message)
	{
	}

	virtual ~FailToGetImageException() throw()
	{

	}

	virtual const char* what() const throw()
	{
	return _msg.c_str();
	}

protected:
	string _msg;
};
