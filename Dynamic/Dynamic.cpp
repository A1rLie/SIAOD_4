#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

//Структура даты, все даты - битовые поля
struct Date
{
	unsigned short day : 5;
	unsigned short month : 4;
	unsigned short year : 11;
};

//Структура записи
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
	Employee* arr;
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

	int last = -1;
	for (int i = 0; i < table.currSize; i++)
	{
		if (table.arr[i].code == newEmployee.code) last = i + 1;
	}

	Employee* arr = new Employee[table.currSize + 1];
	if (last == -1 || last == table.currSize) //Если не найден
	{
		for (int i = 0; i < table.currSize; i++)
		{
			arr[i] = table.arr[i];
		}
		arr[table.currSize] = newEmployee;
	}
	else
	{
		for (int i = 0, j = 0; i < table.currSize; i++, j++)
		{
			if (i != last)
			{
				arr[j] = table.arr[i];
			}
			else
			{
				arr[j] = newEmployee;
				j++;
				arr[j] = table.arr[i];
			}	
		}
	}
	table.currSize++;
	delete[] *&(table.arr);
	table.arr = arr;
}

//Смена рабочего кода сотрудников
void NewPost(Table& table)
{
	int oldCode;
	cout << "\nСтарый код >> ";
	cin >> oldCode;
	int newCode;
	cout << "Новый код >> ";
	cin >> newCode;
	for (int i = 0; i < table.currSize; i++)
	{
		if (table.arr[i].code == oldCode) table.arr[i].code = newCode;
	}
}

//Вывод всех сотрудников
void PrintTable(Table table)
{
	for (int i = 0; i < table.currSize; i++)
	{
		cout << "Табельный номер: " << table.arr[i].perNum << "\tКод занимаемой должности: " << table.arr[i].code << "\tФамилия: " << table.arr[i].secondName << "\tДата начала работы: " <<
			table.arr[i].data.day << "." << table.arr[i].data.month << "." << table.arr[i].data.year << endl;
	}
}

//Удаление сотрудников
void Delete(Table& table, const unsigned short code)
{
	int count = 0;
	for (int i = 0; i < table.currSize; i++)
	{
		if (table.arr[i].code == code) count++;
	}

	Employee* arr = new Employee[table.currSize - count];
	for (int i = 0, j = 0; i < table.currSize; i++)
	{
		if (table.arr[i].code != code)
		{
			arr[j] = table.arr[i];
			j++;
		}
	}

	table.currSize -= count;
	delete[] * &(table.arr);
	table.arr = arr;
}

int main()
{
	system("chcp 1251 > nul");
	Post manual[] = { {12, "Уборщик"}, {34, "Секретарь"}, {56, "Тимлид"}, {76, "Зам. директора"}, {99, "Директор"} }; //Массив должностей
	Table myTable; //Объявление таблицы

	//Задание #1
	cout << "Количество сотрудников >>> ";
	cin >> myTable.currSize;
	myTable.arr = new Employee[myTable.currSize];
	for (int i = 0; i < myTable.currSize; i++)
	{
		Employee pers; //Создание пустого сотрудника
		myTable.arr[i] = FillEmployee(pers); //Заполняет сотрудника

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
	cout << "\nВыбери удаляемую должноть от 1 до 5: ";
	for (int i = 0; i < 5; i++)
	{
		cout << manual[i].postName << "; ";
	}
	cout << endl;
	int index;
	cin >> index;
	Delete(myTable, manual[index - 1].code);
	PrintTable(myTable);

	delete[] myTable.arr;
}