#include <iostream>

using namespace std;

int main()
{

	int* arr = new int[1];

	arr[0] = 1;

	cout << arr[0] << " " << arr[1] << endl;

	arr = (int*)realloc(arr, 2*sizeof(int));

	arr[1] = 100;
	cout << arr[0] << " " << arr[1] << endl;

	cout << sizeof(arr) << endl;
	/*int arr[] = { 1,1,1,1,1 };
	int SIZE = 5;
	int size = 0;
	int j = 0;
	for (int i = 0; i < SIZE; i++)
	{
		if (arr[i] != 2)
		{
			arr[j] = arr[i];
			j++;
			size++;
		}
		else
		{
			for (int i = j+1; i < SIZE; i++)
			{
				if (arr[i] != 2)
				{
					swap(arr[j], arr[i]);
					j++;
					size++;
					break;
				}
			}
		}
	}

	for (int i = 0; i < size; i++)
	{
		cout << arr[i] << " ";
	}*/
}