#include "Menu.h"
#include "../../Game.h"
void Menu::constructMenu(bool awakeOnPush)
{
	Game::getUIInstance()->pushContainer(this, awakeOnPush, false);
}

void Menu::initMenu()
{
}

void Menu::tickMenu()
{
}
