#include "TestEntity.h"

#include <stdio.h>
#include <thread>
#include <chrono>
#include "TestEntity.h"
#include <iostream>

void TestEntity::update()
{
	switch (type_)
	{
	case 0:
		std::cout << "0 " + message_ << std::endl;
		break;
	case 1:
		std::cout << "1 " + message_ << std::endl;
		break;
	case 2:
		std::cout << "2 "+ message_ << std::endl;
		break;
	}
}

TestEntity::TestEntity(int type, std::string message)
{
	type_ = type;
	message_ = message;
}
