#include "../renderEngine/DisplayManager.h"

int main(void)
{
	DisplayManager dm;

	dm.open();

	while (dm.isActive()) {
		dm.update();
	}

	dm.close();
}