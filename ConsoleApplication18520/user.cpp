
#include <algorithm>
#include "Header.h"

std::vector <Data> dataForUser;
std::vector <Data> dataForIndividualTask;

int sortingColumnNumber;

int userMenu() {
	menu.printString(menu.programHeadline, true, true);
	menu.printString(menu.windowHeadlines[6], true, false);
	menu.printTable("dataForUser");
	menu.printString("1. Поиск данных\n2. Сортировка\n3. Индивидуальное задание\n0. Выход из аккаунта", true, false);
	(std::cin >> menu.input).get();
	if (menu.input == "1")
		return 1;
	else {
		if (menu.input == "2")
			return 2;
		else {
			if (menu.input == "3")
				return 3;
			else {
				if (menu.input == "0")
					return 0;
				else {
					menu.inputError();
					return 4;
				}
			}
		}
	}
}

void search() {
	menu.printString(menu.programHeadline, true, true);
	menu.printString(menu.windowHeadlines[7], true, false);
	menu.printString("\nФ.И.О. искомого студента: ", false, false);
	getline(std::cin, menu.input);
	dataForIndividualTask.clear();
	for (int i = 0; i < dataForUser.size(); i++) {
		if (dataForUser[i].patientFullName == menu.input)
			dataForIndividualTask.push_back(dataForUser[i]);
	}
	if (dataForIndividualTask.size() < 1)
		menu.printString("\n> Студентов с Ф.И.О. '" + menu.input + "' не существует", true, false);
	else
		menu.printTable("dataForIndividualTask");
	system("pause");
}

bool comparator(Data& left, Data& right) {
	switch (sortingColumnNumber) {
	case(1):
		if (menu.input == "1") return (left.patientFullName < right.patientFullName);
		else return (left.patientFullName > right.patientFullName);
		break;
	case(2):
		if (menu.input == "1") return (left.Diagnose < right.Diagnose);
		else return (left.Diagnose > right.Diagnose);
		break;
	case(3):
		if (menu.input == "1") return (left.averageMark < right.averageMark);
		else return (left.averageMark > right.averageMark);
		break;
	case(4):
		if (menu.input == "1") return (left.optionalLessons[0] < right.optionalLessons[0]);
		else return (left.optionalLessons[0] > right.optionalLessons[0]);
		break;
	case(5):
		if (menu.input == "1") return (left.optionalLessons[1] < right.optionalLessons[1]);
		else return (left.optionalLessons[1] > right.optionalLessons[1]);
		break;
	case(6):
		if (menu.input == "1") return (left.optionalLessons[2] < right.optionalLessons[2]);
		else return (left.optionalLessons[2] > right.optionalLessons[2]);
		break;
	case(7):
		if (menu.input == "1") return (left.optionalLessons[3] < right.optionalLessons[3]);
		else return (left.optionalLessons[3] > right.optionalLessons[3]);
		break;
	default:
		if (menu.input == "1") return (left.optionalLessons[4] < right.optionalLessons[4]);
		else return (left.optionalLessons[4] > right.optionalLessons[4]);
		break;
	}
}

void sorting() {
	menu.printString("\n> Сортировать данные по столбцу:\n1. Ф.И.О. студента\n2. Номер группы\n3. Средний балл\nВыбранные факультативы:\n4. математика\n5. физика\n6. программирование\n7. английский язык\n8. базы данных", true, false);
	(std::cin >> menu.input).get();
	if (!menu.checkInputType(menu.input, "int")) {
		menu.inputError();
		return;
	}
	if (stoi(menu.input) < 1 || stoi(menu.input) > 8) {
		menu.inputError();
		return;
	}
	sortingColumnNumber = stoi(menu.input);
	menu.printString("\n> Направление сортировки:\n1. По возрастанию\n2. По убыванию", true, false);
	(std::cin >> menu.input).get();
	if (menu.input == "1" || menu.input == "2")
		std::sort(dataForUser.begin(), dataForUser.end(), comparator);
	else {
		menu.inputError();
		return;
	}
}

void individualTask() {
	int interestingDiscipline;

	dataForIndividualTask.clear();
	menu.printString(menu.programHeadline, true, true);
	menu.printString(menu.windowHeadlines[8], true, false);
	menu.printString("\nВыберите дисциплину:\n1. математика\n2. физика\n3. программирование\n4. английский язык\n5. базы данных", true, false);
	(std::cin >> menu.input).get();
	if (!menu.checkInputType(menu.input, "int")) {
		menu.inputError();
		return;
	}
	if (stoi(menu.input) < 1 || stoi(menu.input) > 5) {
		menu.inputError();
		return;
	}
	interestingDiscipline = stoi(menu.input) - 1;
	for (int i = 0; i < dataForUser.size(); i++) {
		if (dataForUser[i].optionalLessons[interestingDiscipline] == 1)
			dataForIndividualTask.push_back(dataForUser[i]);
	}
	menu.printString("\nДисциплину желают прослушать " + std::to_string(dataForIndividualTask.size()) + " чел.", true, false);
	if (dataForIndividualTask.size() > 15) {
		menu.printString("Желающие (15 лучших по успеваемости):", false, false);
		sortingColumnNumber = 3;
		menu.input = "2";
		std::sort(dataForIndividualTask.begin(), dataForIndividualTask.end(), comparator);
		while (dataForIndividualTask.size() > 15) {
			dataForIndividualTask.erase(dataForIndividualTask.begin() + 15);
		}
		menu.printTable("dataForIndividualTask");
	}
	else {
		menu.printString("Список желающих:", false, false);
		menu.printTable("dataForIndividualTask");
	}
	menu.printString("Дисциплины по популярности:", true, false);
	for (int i = 0; i < 5; i++) {
		std::string disciplineName;
		int studentsNumber;

		switch (i) {
		case(0):
			disciplineName = "Математика - ";
			break;
		case(1):
			disciplineName = "Физика - ";
			break;
		case(2):
			disciplineName = "Программирование - ";
			break;
		case(3):
			disciplineName = "Английский язык - ";
			break;
		default:
			disciplineName = "Базы данных - ";
			break;
		}
		studentsNumber = 0;
		for (int j = 0; j < dataForUser.size(); j++) {
			if (dataForUser[j].optionalLessons[i] == 1)
				studentsNumber++;
		}
		menu.printString(disciplineName + std::to_string(studentsNumber), true, false);
	}
	menu.printString("", true, false);
	system("pause");
}

void user() {
	dataForUser = dataForAdmin;
UserMenuStart:
	switch (userMenu()) {
	case(0):
		break;
	case(1):
		search();
		goto UserMenuStart;
		break;
	case(2):
		sorting();
		goto UserMenuStart;
		break;
	case(3):
		individualTask();
		goto UserMenuStart;
		break;
	default:
		goto UserMenuStart;
		break;
	}
}