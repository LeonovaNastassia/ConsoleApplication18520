#include "Header.h"

std::vector<Data> dataForAdmin;

int administratorMenu()
{
	menu.printString(menu.programHeadline, true, true);
	menu.printString(menu.windowHeadlines[3], true, false);
	menu.printString("\n1. Работа с учётными записями\n2. Работа с данными\n0. Выход из аккаунта", true, false);
	(std::cin >> menu.input).get();
	if (menu.input == "1")
		return 1;
	else
	{
		if (menu.input == "2")
			return 2;
		else
		{
			if (menu.input == "0")
				return 0;
			else
			{
				menu.inputError();
				return 3;
			}
		}
	}
}

int accountManagement()
{
	menu.printString(menu.programHeadline, true, true);
	menu.printString(menu.windowHeadlines[4], true, false);
	menu.printTable("users");
	menu.printString("1. Создать учётную запись\n2. Изменить учётную запись\n3. Удалить учётную запись\n0. Выход в меню администратора", true, false);
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
				if (menu.input == "3")
					return 3;
				else
				{
					menu.inputError();
					return 4;
				}
			}
		}
	}
}
void createAccount()
{
	Users user;

	menu.printString("\n> СОЗДАНИЕ НОВОЙ УЧЁТНОЙ ЗАПИСИ:\nЛогин - ", false, false);
	getline(std::cin, menu.input);
	bool conform = false;
	for (int i = 0; i < users.size(); i++)
	{
		if (users[i].login == menu.input)
		{
			conform = true;
			break;
		}
	}
	if (!conform)
	{
		user.login = menu.input;
		menu.printString("Пароль - ", false, false);
		getline(std::cin, user.password);
		menu.printString("Права (1 - админ., 0 - польз.) - ", false, false);
		(std::cin >> menu.input).get();
		if (menu.input == "0" || menu.input == "1")
		{
			if (menu.input == "0")
				user.role = 0;
			else
				user.role = 1;
			users.push_back(user);
			menu.printString("\n> Учётная запись '" + user.login + "' успешно создана", true, false);
			system("pause");
		}
		else
			menu.inputError();
	}
	else
	{
		menu.printString("\n> Учётная запись с таким логином уже существует", true, false);
		system("pause");
	}
}

void changeAccount()
{
	int changingAccountNumber;
	std::string tempLogin;
	std::string tempPassword;

	menu.printString("\n> ИЗМЕНЕНИЕ УЧЁТНОЙ ЗАПИСИ №: ", false, false);
	(std::cin >> menu.input).get();
	if (!menu.checkInputType(menu.input, "int"))
	{
		menu.inputError();
		return;
	}
	if (stoi(menu.input) < 1 || stoi(menu.input) > users.size())
	{
		menu.inputError();
		return;
	}
	changingAccountNumber = stoi(menu.input) - 1;
	menu.printString("Новый логин - ", false, false);
	getline(std::cin, tempLogin);
	bool conform = false;
	for (int i = 0; i < users.size(); i++)
	{
		if (users[i].login == tempLogin && i != changingAccountNumber)
		{
			conform = true;
			break;
		}
	}
	if (conform)
	{
		menu.printString("\n> Учётная запись с таким логином уже существует", true, false);
		system("pause");
	}
	else
	{
		menu.printString("Новый пароль - ", false, false);
		getline(std::cin, tempPassword);
		menu.printString("Новые права (1 - админ., 0 - польз.) - ", false, false);
		(std::cin >> menu.input).get();
		if (menu.input != "0" && menu.input != "1")
		{
			menu.inputError();
			return;
		}
		if (users[changingAccountNumber].role == 1 && menu.input == "0")
		{
			int adminAccountsQuantity = 0;
			for (int i = 0; i < users.size(); i++)
			{
				if (users[i].role == 1)
					adminAccountsQuantity++;
			}
			if (adminAccountsQuantity < 2)
			{
				menu.printString("\n> Невозможно изменить права единственной учётной записи с правами администратора", true, false);
				system("pause");
				return;
			}
		}
		menu.printString("\n> Учётная запись '" + users[changingAccountNumber].login + "' успешно изменена", true, false);
		users[changingAccountNumber].login = tempLogin;
		users[changingAccountNumber].password = tempPassword;
		if (menu.input == "0")
			users[changingAccountNumber].role = 0;
		else
			users[changingAccountNumber].role = 1;
		system("pause");
	}
}

void deleteAccount()
{
	int deletingAccountNumber;

	menu.printString("\n> УДАЛЕНИЕ УЧЁТНОЙ ЗАПИСИ №: ", false, false);
	(std::cin >> menu.input).get();
	if (!menu.checkInputType(menu.input, "int"))
	{
		menu.inputError();
		return;
	}
	if (stoi(menu.input) < 1 || stoi(menu.input) > users.size())
	{
		menu.inputError();
		return;
	}
	deletingAccountNumber = stoi(menu.input) - 1;
	if (users[deletingAccountNumber].role == 1)
	{
		int adminAccountsQuantity = 0;
		for (int i = 0; i < users.size(); i++)
		{
			if (users[i].role == 1)
				adminAccountsQuantity++;
		}
		if (adminAccountsQuantity < 2)
		{
			menu.printString("\n> Невозможно удалить единственную учётную запись с правами администратора", true, false);
			system("pause");
			return;
		}
	}
	menu.printString("\n> Вы действительно хотите удалить учётную запись '" + users[deletingAccountNumber].login + "'?\n1. Да\n0. Нет", true, false);
	(std::cin >> menu.input).get();
	if (menu.input == "1")
	{
		menu.printString("\n> Учётная запись '" + users[deletingAccountNumber].login + "' успешно удалена", true, false);
		system("pause");
		users.erase(users.begin() + deletingAccountNumber);
	}
	else
	{
		if (menu.input != "0")
			menu.inputError();
	}
}

int dataManagement()
{
	menu.printString(menu.programHeadline, true, true);
	menu.printString(menu.windowHeadlines[5], true, false);
	menu.printTable("dataForAdmin");
	menu.printString("1. Создать запись\n2. Изменить запись\n3. Удалить запись\n0. Выход в меню администратора", true, false);
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
				if (menu.input == "3")
					return 3;
				else
				{
					menu.inputError();
					return 4;
				}
			}
		}
	}
}

void createNote()
{
	Data note;

	menu.printString("\n> СОЗДАНИЕ НОВОЙ ЗАПИСИ:\nФ.И.О. студента - ", false, false);
	getline(std::cin, note.patientFullName);
	menu.printString("Номер группы - ", false, false);
	getline(std::cin, note.Diagnose);
	menu.printString("Средний балл (дробная часть через запятую) - ", false, false);
	(std::cin >> menu.input).get();
	if (!menu.checkInputType(menu.input, "float"))
	{
		menu.inputError();
		return;
	}
	if (stof(menu.input) < 1 || stof(menu.input) > 10) {
		menu.inputError();
		return;
	}
	note.averageMark = stof(menu.input);
	menu.printString("Выбор факультативов (1 - выбран, 0 - не выбран):\n   математика - ", false, false);
	(std::cin >> menu.input).get();
	if (menu.input != "1" && menu.input != "0")
	{
		menu.inputError();
		return;
	}
	else
		note.optionalLessons[0] = stoi(menu.input);
	menu.printString("   физика - ", false, false);
	(std::cin >> menu.input).get();
	if (menu.input != "1" && menu.input != "0")
	{
		menu.inputError();
		return;
	}
	else
		note.optionalLessons[1] = stoi(menu.input);
	menu.printString("   программирование - ", false, false);
	(std::cin >> menu.input).get();
	if (menu.input != "1" && menu.input != "0")
	{
		menu.inputError();
		return;
	}
	else
		note.optionalLessons[2] = stoi(menu.input);
	menu.printString("   английский язык - ", false, false);
	(std::cin >> menu.input).get();
	if (menu.input != "1" && menu.input != "0")
	{
		menu.inputError();
		return;
	}
	else
		note.optionalLessons[3] = stoi(menu.input);
	menu.printString("   базы данных - ", false, false);
	(std::cin >> menu.input).get();
	if (menu.input != "1" && menu.input != "0")
	{
		menu.inputError();
		return;
	}
	else
		note.optionalLessons[4] = stoi(menu.input);
	dataForAdmin.push_back(note);
	menu.printString("\n> Запись о студенте '" + note.patientFullName + "' успешно создана", true, false);
	system("pause");
}

void changeNote()
{
	int changingNoteNumber;

	std::string studentFullNameTemp;
	std::string groupNumberTemp;
	float averageMarkTemp;
	int optionalLessonsTemp[5];

	menu.printString("\n> ИЗМЕНЕНИЕ ЗАПИСИ №: ", false, false);
	(std::cin >> menu.input).get();
	if (!menu.checkInputType(menu.input, "int"))
	{
		menu.inputError();
		return;
	}
	if (stoi(menu.input) < 1 || stoi(menu.input) > dataForAdmin.size())
	{
		menu.inputError();
		return;
	}
	changingNoteNumber = stoi(menu.input) - 1;
	menu.printString("Новые Ф.И.О. студента - ", false, false);
	getline(std::cin, studentFullNameTemp);
	menu.printString("Новый номер группы - ", false, false);
	getline(std::cin, groupNumberTemp);
	menu.printString("Новый средний балл (дробная часть через запятую) - ", false, false);
	(std::cin >> menu.input).get();
	if (!menu.checkInputType(menu.input, "float"))
	{
		menu.inputError();
		return;
	}
	if (stof(menu.input) < 0 || stof(menu.input) > 10)
	{
		menu.inputError();
		return;
	}
	averageMarkTemp = stof(menu.input);
	menu.printString("Новый выбор факультативов (1 - выбран, 0 - не выбран):\n   математика - ", false, false);
	(std::cin >> menu.input).get();
	if (menu.input != "1" && menu.input != "0")
	{
		menu.inputError();
		return;
	}
	else
		optionalLessonsTemp[0] = stoi(menu.input);
	menu.printString("   физика - ", false, false);
	(std::cin >> menu.input).get();
	if (menu.input != "1" && menu.input != "0")
	{
		menu.inputError();
		return;
	}
	else
		optionalLessonsTemp[1] = stoi(menu.input);
	menu.printString("   программирование - ", false, false);
	(std::cin >> menu.input).get();
	if (menu.input != "1" && menu.input != "0")
	{
		menu.inputError();
		return;
	}
	else
		optionalLessonsTemp[2] = stoi(menu.input);
	menu.printString("   английский язык - ", false, false);
	(std::cin >> menu.input).get();
	if (menu.input != "1" && menu.input != "0")
	{
		menu.inputError();
		return;
	}
	else
		optionalLessonsTemp[3] = stoi(menu.input);
	menu.printString("   базы данных - ", false, false);
	(std::cin >> menu.input).get();
	if (menu.input != "1" && menu.input != "0")
	{
		menu.inputError();
		return;
	}
	else
		optionalLessonsTemp[4] = stoi(menu.input);
	menu.printString("\n> Запись о студенте '" + dataForAdmin[changingNoteNumber].patientFullName + "' успешно изменена", true, false);
	dataForAdmin[changingNoteNumber].patientFullName = studentFullNameTemp;
	dataForAdmin[changingNoteNumber].Diagnose = groupNumberTemp;
	dataForAdmin[changingNoteNumber].averageMark = averageMarkTemp;
	for (int i = 0; i < 5; i++)
	{
		dataForAdmin[changingNoteNumber].optionalLessons[i] = optionalLessonsTemp[i];
	}
	system("pause");
}

void deleteNote()
{
	int deletingNoteNumber;

	menu.printString("\n> УДАЛЕНИЕ ЗАПИСИ №: ", false, false);
	(std::cin >> menu.input).get();
	if (!menu.checkInputType(menu.input, "int"))
	{
		menu.inputError();
		return;
	}
	if (stoi(menu.input) < 1 || stoi(menu.input) > dataForAdmin.size())
	{
		menu.inputError();
		return;
	}
	deletingNoteNumber = stoi(menu.input) - 1;
	menu.printString("\n> Вы действительно хотите удалить запись о студенте '" + dataForAdmin[deletingNoteNumber].patientFullName + "'?\n1. Да\n0. Нет", true, false);
	(std::cin >> menu.input).get();
	if (menu.input == "1")
	{
		menu.printString("\n> Запись о студенте '" + dataForAdmin[deletingNoteNumber].patientFullName + "' успешно удалена", true, false);
		system("pause");
		dataForAdmin.erase(dataForAdmin.begin() + deletingNoteNumber);
	}
	else
	{
		if (menu.input != "0")
			menu.inputError();
	}
}

void administrator()
{
AdministratorMenuStart:
	switch (administratorMenu())
	{
	case (0):
		break;
	case (1):
	AccountManagementStart:
		switch (accountManagement())
		{
		case (0):
			goto AdministratorMenuStart;
			break;
		case (1):
			createAccount();
			goto AccountManagementStart;
			break;
		case (2):
			changeAccount();
			goto AccountManagementStart;
			break;
		case (3):
			deleteAccount();
			goto AccountManagementStart;
			break;
		default:
			goto AccountManagementStart;
			break;
		}
		break;
	case (2):
	DataManagementStart:
		switch (dataManagement())
		{
		case (0):
			goto AdministratorMenuStart;
			break;
		case (1):
			createNote();
			goto DataManagementStart;
			break;
		case (2):
			changeNote();
			goto DataManagementStart;
			break;
		case (3):
			deleteNote();
			goto DataManagementStart;
			break;
		default:
			goto DataManagementStart;
			break;
		}
		break;
	default:
		goto AdministratorMenuStart;
		break;
	}
}
