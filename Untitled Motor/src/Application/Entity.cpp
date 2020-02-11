#include "Entity.h"

#include <stdio.h>
#include <thread>
#include <chrono>

using namespace std;

void Entity::update()
{
	this_thread::sleep_for(chrono::milliseconds(50));

	printf("ostia");

	this_thread::sleep_for(chrono::milliseconds(1000));
}
