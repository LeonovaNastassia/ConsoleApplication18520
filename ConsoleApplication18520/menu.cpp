
#include <fstream>
#include "Header.h"

Menu menu;

int loading()
{
	std::ifstream usersFile("Users.txt");
	std::ifstream dataFile("Data.txt");
	std::string buffer;

	menu.printString(menu.programHeadline, true, true);
	menu.printString(menu.windowHeadlines[0], true, false);
	if (!usersFile && !dataFile)
	{
		menu.printString("\n> Файлы 'Users.txt' и 'Data.txt' не найдены", true, false);
		system("pause");
		return 1;
	}
	else
	{
		if (!usersFile && dataFile)
		{
			menu.printString("\n> Файл 'Users.txt' не найден", true, false);
			system("pause");
			return 2;
		}
		else
		{
			if (usersFile && !dataFile)
			{
				menu.printString("\n> Файл 'Data.txt' не найден", true, false);
				system("pause");
				return 3;
			}
			else
			{
				while (getline(usersFile, buffer))
				{
					Users user;
					user.login = buffer;
					if (getline(usersFile, buffer))
						user.password = buffer;
					else
						break;
					if (getline(usersFile, buffer))
					{
						try
						{
							user.role = stoi(buffer);
						}
						catch (std::invalid_argument)
						{
							break;
						}
					}
					else
						break;
					users.push_back(user);
				}
				usersFile.close();
				while (getline(dataFile, buffer)) {
					Data note;
					note.patientFullName = buffer;
					if (getline(dataFile, buffer))
						note.Diagnose = buffer;
					if (getline(dataFile, buffer))
					{
						try
						{
							note.averageMark = stof(buffer);
						}
						catch (std::invalid_argument)
						{
							break;
						}
					}
					for (int i = 0; i < 5; i++)
					{
						if (getline(dataFile, buffer))
						{
							try
							{
								note.optionalLessons[i] = stoi(buffer);
							}
							catch (std::invalid_argument)
							{
								break;
							}
						}
					}
					dataForAdmin.push_back(note);
				}
				dataFile.close();
				menu.printString("\n> Загрузка данных прошла успешно", true, false);
				system("pause");
				return 0;
			}
		}
	}
}

int mainMenu()
{
	menu.printString(menu.programHeadline, true, true);
	menu.printString(menu.windowHeadlines[1], true, false);
	menu.printString("\n1. Авторизация\n2. Сохранить и выйти\n0. Выход без сохранения", true, false);
	(std::cin >> menu.input).get();
	if (menu.input == "0")
		return 0;
	else
	{
		if (menu.input == "1")
			return 1;
		else
		{
			if (menu.input == "2")
				return 2;
			else
			{
				menu.inputError();
				return 3;
			}
		}
	}
}

void saving()
{
	std::ofstream usersFile("Users.txt");
	std::ofstream dataFile("Data.txt");
	for (int i = 0; i < users.size(); i++)
	{
		if (i > 0) usersFile << std::endl;
		usersFile << users[i].login << std::endl;
		usersFile << users[i].password << std::endl;
		usersFile << users[i].role;
	}
	for (int i = 0; i < dataForAdmin.size(); i++)
	{
		if (i > 0) dataFile << std::endl;
		dataFile << dataForAdmin[i].patientFullName << std::endl;
		dataFile << dataForAdmin[i].Diagnose << std::endl;
		dataFile << dataForAdmin[i].averageMark << std::endl;
		for (int j = 0; j < 4; j++)
		{
			dataFile << dataForAdmin[i].optionalLessons[j] << std::endl;
		}
		dataFile << dataForAdmin[i].optionalLessons[4];
	}
	usersFile.close();
	dataFile.close();
	menu.printString(menu.programHeadline, true, true);
	menu.printString(menu.windowHeadlines[9], true, false);
	menu.printString("\n> Изменения сохранены", true, false);
	system("pause");
}

int main()
{
	setlocale(LC_ALL, "rus");
	if (loading() == 0)
	{
	MainMenuStart:
		switch (mainMenu())
		{
		case (0):
			exit(0);
			break;
		case (1):
			authorization();
			goto MainMenuStart;
		case (2):
			saving();
			exit(0);
			break;
		default:
			goto MainMenuStart;
			break;
		}
	}
}