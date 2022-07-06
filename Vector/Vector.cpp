#include <iostream>
#include <string>
#include <vector>

using namespace std;

const int SIZE = 100;

//Структура даты, все даты - битовые поля
struct Date
{
	unsigned short day : 5;
	unsigned short month : 4;
	unsigned short year : 11;
};

//Структура сотрудника
struct Employee
{
	unsigned short perNum : 10;
	unsigned short code : 7;
	string secondName;
	Date data;
};

//Структура должности
struct Post
{
	unsigned short code : 7;
	string postName;
};

//Структура таблицы
struct Table
{
	int currSize;
	vector<Employee> myVec;
};

//Заполняет сотрудника
Employee FillEmployee(Employee pers)
{
	unsigned short a, b, c;
	cout << "\nТабельный номер сотрудника: ";
	cin >> a;
	pers.perNum = a;
	cout << "Код занимаемой должности: ";
	cin >> b;
	pers.code = b;
	cout << "Фамилия и инициалы сотрудника: ";
	cin.ignore();
	getline(cin, pers.secondName);
	cout << "Дата поступления на работу в формате dd.MM.yy: ";
	cin >> a >> b >> c;
	pers.data.day = a, pers.data.month = b, pers.data.year = c;
	return pers;
}

//Добавление сотрудника
void NewEmployee(Table& table)
{
	//Объявление и инициализация нового сотрудника
	Employee newEmployee;
	newEmployee = FillEmployee(newEmployee);

	auto it = table.myVec.begin();
	int last = -1;
	for (int i = 0; i < table.currSize; i++)
	{
		if (table.myVec[i].code == newEmployee.code) last = i;
	}
	if (last != -1) table.myVec.insert(it + last + 1, newEmployee);
	else table.myVec.push_back(newEmployee);
	table.currSize++;
}

//Смена рабочего кода сотрудников
void NewPost(Table& table)
{
	cout << "Старый код >> ";
	int oldCode;
	cin >> oldCode;
	cout << "Новый код >> ";
	int newCode;
	cin >> newCode;
	for (int i = 0; i < table.currSize; i++)
	{
		if (table.myVec[i].code == oldCode) table.myVec[i].code = newCode;
	}
}

//Вывод всех сотрудников
void PrintTable(Table table)
{
	for (int i = 0; i < table.currSize; i++)
	{
		cout << "Табельный номер: " << table.myVec[i].perNum << "\tКод занимаемой должности: " << table.myVec[i].code << "\tФамилия: " << table.myVec[i].secondName << "\tДата начала работы: " <<
			table.myVec[i].data.day << "." << table.myVec[i].data.month << "." << table.myVec[i].data.year << endl;
	}
}

//Удаление сотрудников
void Delete(Table& table, const unsigned short code)
{
	auto it = table.myVec.begin();
	for (int i = 0; i < table.myVec.size(); i++)
	{
		if (table.myVec[i].code == code) table.myVec.erase(it + i);
	}
	table.currSize = table.myVec.size();
}

int main()
{
	system("chcp 1251 > nul");
	Post manual[] = { {12, "Уборщик"}, {34, "Секретарь"}, {56, "Тимлид"}, {76, "Зам. директора"}, {99, "Директор"} }; //Массив должностей
	Table myTable; //Объявление таблицы

	//Задание #1
	cout << "Количество сотрудников >>> ";
	cin >> myTable.currSize;
	myTable.myVec.resize(myTable.currSize);
	for (int i = 0; i < myTable.currSize; i++)
	{
		Employee pers; //Создание пустого сотрудника
		myTable.myVec[i] = FillEmployee(pers); //Заполняет сотрудника
	}
	cout << endl;
	PrintTable(myTable); //Вывод таблицы с сотрудниками

	//Задание #2
	NewEmployee(myTable);
	cout << endl;
	PrintTable(myTable);

	//Задание #3
	NewPost(myTable);
	cout << endl;
	PrintTable(myTable);

	//Задание #4
	cout << "Выбери удаляемую должноть от 1 до 5: ";
	for (int i = 0; i < 5; i++)
	{
		cout << manual[i].postName << " ";
	}
	cout << endl;
	int index;
	cin >> index;
	Delete(myTable, manual[index - 1].code);
	PrintTable(myTable);
}