#pragma once
#include <exception>
#include <string>


class ValidatorException:public std::exception {
private:
	std::string eroare;
public:
	ValidatorException(std::string msg) :eroare{msg} {}
	const char* what() const noexcept override{
		return eroare.c_str();
	}
};

class RepositoryException:public std::exception {
private:
	std::string eroare;
public:
	RepositoryException(std::string msg) :eroare{msg} {}
	const char* what() const noexcept override {
		return eroare.c_str();
	}
};

class ServiceException:public std::exception {
private:
	std::string eroare;
public:
	ServiceException(std::string msg) :eroare{ msg } {}
	const char* what() const noexcept override {
		return eroare.c_str();
	}
};

class BasketException : public std::exception {
private:
	std::string eroare;
public:
	BasketException(const std::string& msg): eroare{msg}{}
	const char* what() const noexcept override {
		return eroare.c_str();
	}
};