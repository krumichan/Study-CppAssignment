#include <exception>
#include <iostream>

using namespace std;

struct FailToDecodeException : public exception
{
public:
	explicit FailToDecodeException(const char* message) : _msg(message)
	{
	}

	explicit FailToDecodeException(const string& message) : _msg(message)
	{
	}

	virtual ~FailToDecodeException() throw()
	{
	}

	virtual const char* what() const throw()
	{
	return _msg.c_str();
	}

protected:
	string _msg;
};
