#include <iostream>
#include <string>

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
	const int MAXSIZE = 100;
	Employee arr[SIZE];
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
	if (last <= table.currSize - 1 && last >= 0)
	{
		Employee temp = table.arr[last];
		table.arr[last] = newEmployee;
		table.arr[table.currSize] = temp;
	}
	else
	{
		table.arr[table.currSize] = newEmployee;
	}
	table.currSize++;
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
	int size = 0;
	int j = 0;
	for (int i = 0; i < table.currSize; i++)
	{
		if (table.arr[i].code != code)
		{
			table.arr[j].code = table.arr[i].code;
			j++;
			size++;
		}
		else
		{
			for (int i = j + 1; i < table.currSize; i++)
			{
				if (table.arr[i].code != code)
				{
					swap(table.arr[j], table.arr[i]);
					j++;
					size++;
					break;
				}
			}
		}
	}
	table.currSize = size;
}

int main()
{
	system("chcp 1251 > nul");
	Post manual[] = { {12, "Уборщик"}, {34, "Секретарь"}, {56, "Тимлид"}, {76, "Зам. директора"}, {99, "Директор"} }; //Массив должностей
	Table myTable; //Объявление таблицы

	//Задание #1
	cout << "Количество сотрудников >>> ";
	cin >> myTable.currSize;
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
	cout << endl;
	PrintTable(myTable);
}