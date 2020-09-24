#include "Header.h"
std::vector<Users> users;
int authorizationWindow()
{
	menu.printString(menu.programHeadline, true, true);
	menu.printString(menu.windowHeadlines[2], true, false);
	menu.printString("\nЛогин: ", false, false);
	getline(std::cin, menu.input);
	bool conform = false;
	int userIndex;
	for (int i = 0; i < users.size(); i++)
	{
		if (menu.input == users[i].login)
		{
			conform = true;
			userIndex = i;
			break;
		}
	}
	if (conform)
	{
		menu.printString("Пароль: ", false, false);
		getline(std::cin, menu.input);
		if (menu.input == users[userIndex].password)
		{
			menu.printString("\n> Авторизация прошла успешно", true, false);
			system("pause");
			if (users[userIndex].role == 1)
				return 1;
			else
				return 0;
		}
		else
		{
			menu.printString("\n> Неверный пароль", true, false);
			system("pause");
			return 3;
		}
	}
	else
	{
		menu.printString("\n> Такого пользователя не существует", true, false);
		system("pause");
		return 2;
	}
}
void authorization()
{
	switch (authorizationWindow())
	{
	case (0):
		user();
		break;
	case (1):
		administrator();
		break;
	default:
		break;
	}
}