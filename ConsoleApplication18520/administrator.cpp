#include "Header.h"

std::vector<Data> dataForAdmin;

int administratorMenu()
{
	menu.printString(menu.programHeadline, true, true);
	menu.printString(menu.windowHeadlines[3], true, false);
	menu.printString("\n1. ������ � �������� ��������\n2. ������ � �������\n0. ����� �� ��������", true, false);
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
	menu.printString("1. ������� ������� ������\n2. �������� ������� ������\n3. ������� ������� ������\n0. ����� � ���� ��������������", true, false);
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

	menu.printString("\n> �������� ����� �ר���� ������:\n����� - ", false, false);
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
		menu.printString("������ - ", false, false);
		getline(std::cin, user.password);
		menu.printString("����� (1 - �����., 0 - �����.) - ", false, false);
		(std::cin >> menu.input).get();
		if (menu.input == "0" || menu.input == "1")
		{
			if (menu.input == "0")
				user.role = 0;
			else
				user.role = 1;
			users.push_back(user);
			menu.printString("\n> ������� ������ '" + user.login + "' ������� �������", true, false);
			system("pause");
		}
		else
			menu.inputError();
	}
	else
	{
		menu.printString("\n> ������� ������ � ����� ������� ��� ����������", true, false);
		system("pause");
	}
}

void changeAccount()
{
	int changingAccountNumber;
	std::string tempLogin;
	std::string tempPassword;

	menu.printString("\n> ��������� �ר���� ������ �: ", false, false);
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
	menu.printString("����� ����� - ", false, false);
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
		menu.printString("\n> ������� ������ � ����� ������� ��� ����������", true, false);
		system("pause");
	}
	else
	{
		menu.printString("����� ������ - ", false, false);
		getline(std::cin, tempPassword);
		menu.printString("����� ����� (1 - �����., 0 - �����.) - ", false, false);
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
				menu.printString("\n> ���������� �������� ����� ������������ ������� ������ � ������� ��������������", true, false);
				system("pause");
				return;
			}
		}
		menu.printString("\n> ������� ������ '" + users[changingAccountNumber].login + "' ������� ��������", true, false);
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

	menu.printString("\n> �������� �ר���� ������ �: ", false, false);
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
			menu.printString("\n> ���������� ������� ������������ ������� ������ � ������� ��������������", true, false);
			system("pause");
			return;
		}
	}
	menu.printString("\n> �� ������������� ������ ������� ������� ������ '" + users[deletingAccountNumber].login + "'?\n1. ��\n0. ���", true, false);
	(std::cin >> menu.input).get();
	if (menu.input == "1")
	{
		menu.printString("\n> ������� ������ '" + users[deletingAccountNumber].login + "' ������� �������", true, false);
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
	menu.printString("1. ������� ������\n2. �������� ������\n3. ������� ������\n0. ����� � ���� ��������������", true, false);
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

	menu.printString("\n> �������� ����� ������:\n�.�.�. �������� - ", false, false);
	getline(std::cin, note.patientFullName);
	menu.printString("����� ������ - ", false, false);
	getline(std::cin, note.Diagnose);
	menu.printString("������� ���� (������� ����� ����� �������) - ", false, false);
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
	menu.printString("����� ������������� (1 - ������, 0 - �� ������):\n   ���������� - ", false, false);
	(std::cin >> menu.input).get();
	if (menu.input != "1" && menu.input != "0")
	{
		menu.inputError();
		return;
	}
	else
		note.optionalLessons[0] = stoi(menu.input);
	menu.printString("   ������ - ", false, false);
	(std::cin >> menu.input).get();
	if (menu.input != "1" && menu.input != "0")
	{
		menu.inputError();
		return;
	}
	else
		note.optionalLessons[1] = stoi(menu.input);
	menu.printString("   ���������������� - ", false, false);
	(std::cin >> menu.input).get();
	if (menu.input != "1" && menu.input != "0")
	{
		menu.inputError();
		return;
	}
	else
		note.optionalLessons[2] = stoi(menu.input);
	menu.printString("   ���������� ���� - ", false, false);
	(std::cin >> menu.input).get();
	if (menu.input != "1" && menu.input != "0")
	{
		menu.inputError();
		return;
	}
	else
		note.optionalLessons[3] = stoi(menu.input);
	menu.printString("   ���� ������ - ", false, false);
	(std::cin >> menu.input).get();
	if (menu.input != "1" && menu.input != "0")
	{
		menu.inputError();
		return;
	}
	else
		note.optionalLessons[4] = stoi(menu.input);
	dataForAdmin.push_back(note);
	menu.printString("\n> ������ � �������� '" + note.patientFullName + "' ������� �������", true, false);
	system("pause");
}

void changeNote()
{
	int changingNoteNumber;

	std::string studentFullNameTemp;
	std::string groupNumberTemp;
	float averageMarkTemp;
	int optionalLessonsTemp[5];

	menu.printString("\n> ��������� ������ �: ", false, false);
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
	menu.printString("����� �.�.�. �������� - ", false, false);
	getline(std::cin, studentFullNameTemp);
	menu.printString("����� ����� ������ - ", false, false);
	getline(std::cin, groupNumberTemp);
	menu.printString("����� ������� ���� (������� ����� ����� �������) - ", false, false);
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
	menu.printString("����� ����� ������������� (1 - ������, 0 - �� ������):\n   ���������� - ", false, false);
	(std::cin >> menu.input).get();
	if (menu.input != "1" && menu.input != "0")
	{
		menu.inputError();
		return;
	}
	else
		optionalLessonsTemp[0] = stoi(menu.input);
	menu.printString("   ������ - ", false, false);
	(std::cin >> menu.input).get();
	if (menu.input != "1" && menu.input != "0")
	{
		menu.inputError();
		return;
	}
	else
		optionalLessonsTemp[1] = stoi(menu.input);
	menu.printString("   ���������������� - ", false, false);
	(std::cin >> menu.input).get();
	if (menu.input != "1" && menu.input != "0")
	{
		menu.inputError();
		return;
	}
	else
		optionalLessonsTemp[2] = stoi(menu.input);
	menu.printString("   ���������� ���� - ", false, false);
	(std::cin >> menu.input).get();
	if (menu.input != "1" && menu.input != "0")
	{
		menu.inputError();
		return;
	}
	else
		optionalLessonsTemp[3] = stoi(menu.input);
	menu.printString("   ���� ������ - ", false, false);
	(std::cin >> menu.input).get();
	if (menu.input != "1" && menu.input != "0")
	{
		menu.inputError();
		return;
	}
	else
		optionalLessonsTemp[4] = stoi(menu.input);
	menu.printString("\n> ������ � �������� '" + dataForAdmin[changingNoteNumber].patientFullName + "' ������� ��������", true, false);
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

	menu.printString("\n> �������� ������ �: ", false, false);
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
	menu.printString("\n> �� ������������� ������ ������� ������ � �������� '" + dataForAdmin[deletingNoteNumber].patientFullName + "'?\n1. ��\n0. ���", true, false);
	(std::cin >> menu.input).get();
	if (menu.input == "1")
	{
		menu.printString("\n> ������ � �������� '" + dataForAdmin[deletingNoteNumber].patientFullName + "' ������� �������", true, false);
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
