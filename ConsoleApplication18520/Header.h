#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

void authorization();
void administrator();
void user();

class Users
{
public:
	std::string login;
	std::string password;
	int role;
};

extern std::vector<Users> users;

class Data
{
public:
	std::string patientFullName;
	std::string Diagnose;
	float averageMark;
	int optionalLessons[5];
};

extern std::vector<Data> dataForAdmin;
extern std::vector<Data> dataForUser;
extern std::vector<Data> dataForIndividualTask;

class Menu
{
public:
	std::string programHeadline = "--------------- ÏĞÎÃĞÀÌÌÀ Ó×ÅÒÀ ÏÀÖÈÅÍÒÎÂ ---------------";
	std::string windowHeadlines[10] = {
		"\n>>> ÇÀÃĞÓÇÊÀ", "\n>>> ÃËÀÂÍÎÅ ÌÅÍŞ", "\n>>> ÀÂÒÎĞÈÇÀÖÈß", "\n>>> ÌÅÍŞ ÀÄÌÈÍÈÑÒĞÀÒÎĞÀ", "\n>>> ĞÀÁÎÒÀ Ñ Ó×¨ÒÍÛÌÈ ÇÀÏÈÑßÌÈ",
		"\n>>> ĞÀÁÎÒÀ Ñ ÄÀÍÍÛÌÈ", "\n>>> ÌÅÍŞ ÏÎËÜÇÎÂÀÒÅËß", "\n>>> ÏÎÈÑÊ", "\n>>> ÈÍÄÈÂÈÄÓÀËÜÍÎÅ ÇÀÄÀÍÈÅ", "\n>>> ÑÎÕĞÀÍÅÍÈÅ"
	};

	void printString(std::string string, bool endLine, bool clearScreen)
	{
		if (clearScreen)
			system("cls");
		std::cout << string;
		if (endLine)
			std::cout << std::endl;
	}

	void printTable(std::string dataVector)
	{
		std::cout << std::endl;
		if (dataVector == "users")
		{
			std::cout << "-----------------------------------------------------" << std::endl;
			std::cout << "| ¹ ï/ï | Ëîãèí        | Ïàğîëü            | Äîñòóï |" << std::endl;
			std::cout << "-----------------------------------------------------" << std::endl;
			for (int i = 0; i < users.size(); i++)
			{
				std::cout << "| " << std::setw(6) << std::left << std::to_string(i + 1).substr(0, 6);
				std::cout << "| " << std::setw(13) << std::left << users[i].login.substr(0, 13);
				std::cout << "| " << std::setw(18) << std::left << users[i].password.substr(0, 18);
				if (users[i].role == 1)
					std::cout << "| " << std::setw(8) << std::left << "Àäìèí. |" << std::endl;
				else
					std::cout << "| " << std::setw(8) << std::left << "Ïîëüç. |" << std::endl;
				std::cout << "-----------------------------------------------------" << std::endl;
			}
		}
		else
		{
			std::vector<Data> dataForTable;
			if (dataVector == "dataForAdmin")
				dataForTable = dataForAdmin;
			if (dataVector == "dataForUser")
				dataForTable = dataForUser;
			if (dataVector == "dataForIndividualTask")
				dataForTable = dataForIndividualTask;
			if (dataForTable.size() > 0)
			{
				std::cout << "-------------------------------------------------------------------------------------------------------------------------------" << std::endl;
				std::cout << "| ¹ ï/ï | Ô.È.Î. ïàöèåíòà     | Âîçğàñò | Ïîë | Äàòà ğîæäåíèÿ | Ìåñòî ïğîæèâàíèÿ(ãîğîä) | Êîíòàêòíûé òåëåôîí | Äèàãíîç |ÁÄ    |" << std::endl;
				std::cout << "-------------------------------------------------------------------------------------------------------------------------------" << std::endl;
				for (int i = 0; i < dataForTable.size(); i++)
				{
					std::cout << "| " << std::setw(6) << std::left << std::to_string(i + 1).substr(0, 6);
					std::cout << "| " << std::setw(20) << std::left << dataForTable[i].patientFullName.substr(0, 20);
					std::cout << "| " << std::setw(9) << std::left << dataForTable[i].Diagnose.substr(0, 9);
					std::cout << "| " << std::setw(9) << std::left << std::to_string(dataForTable[i].averageMark).substr(0, 9);
					for (int j = 0; j < 5; j++)
					{
						if (dataForTable[i].optionalLessons[j] == 1)
							std::cout << "|" << std::setw(6) << std::left << "+     ";
						else
							std::cout << "|" << std::setw(6) << std::left << "";
					}
					std::cout << "|" << std::endl;
					std::cout << "----------------------------------------------------------------------------------------" << std::endl;
				}
			}
			else
				std::cout << "--- Ïàöèåíòîâ íåò ---" << std::endl;
		}
		std::cout << std::endl;
	}

	std::string input;

	bool checkInputType(std::string input, std::string dataType)
	{
		if (dataType == "int")
		{
			try
			{
				if (stoi(input) >= 0)
					return true;
				else
					return false;
			}
			catch (std::invalid_argument)
			{
				return false;
			}
		}
		if (dataType == "float")
		{
			try
			{
				if (stof(input) >= 0)
					return true;
				else
					return false;
			}
			catch (std::invalid_argument)
			{
				return false;
			}
		}
	}

	void inputError()
	{
		printString("\n> Íåêîğğåêòíûé ââîä çíà÷åíèÿ", true, false);
		system("pause");
	}
};
extern Menu menu;

