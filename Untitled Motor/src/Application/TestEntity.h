#pragma once

#include <string>
using namespace std;

class TestEntity {
public:
	virtual void update();
	TestEntity(int type, std::string message);
protected:

private:
	int type_;
	std::string message_;
};