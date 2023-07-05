#include "Controller.h"


int main() try
{
	Controller().run();
	return EXIT_SUCCESS;

}
catch(std::exception e)
{
	std::cout << e.what();
	return EXIT_FAILURE;
}
