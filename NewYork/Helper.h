#pragma once
#include <exception>
#define prt std::cout
#define pres std::cout<< ">> "
#define nl std::endl
#define GM GameManager::instance()
#define ls std::cout<<"\n=======================================================================\n";
#define le std::cout<<"=======================================================================\n\n";

class FailException : public std::exception {
private:
	std::string message_;
public:
	explicit FailException(const std::string& message) : message_(message) {
	}
	virtual const char* what() const throw() {
		return message_.c_str();
	}
};

class InputException : public std::exception {
private:
	std::string message_;
public:
	explicit InputException(const std::string& message="") : message_(message) {
	}
	virtual const char* what() const throw() {
		if (message_ == "") return "Invalid entry, please try again...";
		return message_.c_str();
	}
};