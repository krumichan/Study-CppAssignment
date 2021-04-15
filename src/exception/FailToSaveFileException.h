#include <exception>
#include <iostream>

using namespace std;

struct FailToSaveFileException : public exception
{
public:
	explicit FailToSaveFileException(const char* message) : _msg(message)
	{
	}

	explicit FailToSaveFileException(const string& message) : _msg(message)
	{
	}

	virtual ~FailToSaveFileException() throw()
	{
	}

	virtual const char* what() const throw()
	{
	return _msg.c_str();
	}

protected:
	string _msg;
};
