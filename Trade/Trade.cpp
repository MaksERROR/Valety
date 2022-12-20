#include <iostream>
#include "Traider.h"
#include <windows.h>
#include <string>

using namespace std;

const int Count_of_markets = 2;
CreateID A;

Market Market_Arr[Count_of_markets];
bool stop = 1;

void Market_log(Market& A)
{
	ofstream log_file_Market;
	log_file_Market.open("logs\\all_sum_market" + to_string(A.GetId()) + ".txt", ios_base::app);
	log_file_Market << A.GetId() << "\t"
		<< A.GetBank() << "\t"
		<< A.GetCoast() << "\n";
	log_file_Market.close();
}
void Traider_log(Traider& B)
{
	ofstream log_file_Traider;
	log_file_Traider.open("logs\\all_sum_Traider" + to_string(B.GetId()) + ".txt", ios_base::app);
	log_file_Traider << B.GetId() << "\t"
		<< B.GetName() << "\t"
		<< B.GetSummValet() << "\t"
		<< B.GetCapital() << "\n";
	log_file_Traider.close();
}


void Traider_pool(int index, string Name = "")
{
	Traider S(index);
	Traider_log(S);
	int arr[Count_of_markets];
	while (stop)
	{
		for (int g = 0; g < Count_of_markets; g++)
		{
			arr[g] = S.Parsing(Market_Arr[g].GetName());
		}
		int min = arr[0];
		int max = 0;
		for (int i = 0; i < Count_of_markets; i++)
		{
			if (arr[i] < arr[min])
				min = i;
			if (arr[i] > arr[max])
				max = i;
		}
		S.Ante(Market_Arr[min], -rand() % 10);
		S.Ante(Market_Arr[max], rand() % 100);

	}
	Traider_log(S);
	A.work_with_id(-1);
}


int main()
{
	ofstream logcmd;
	for (size_t i = 0; i < 20; i++)
	{
		Market_log(Market_Arr[i]);
		Market_Arr[i].Mlogs();
	}
	for (size_t i = 0; i < 4; i++)
	{
		CreateThread(
			NULL,
			NULL,
			(LPTHREAD_START_ROUTINE)Traider_pool,
			(LPVOID)(A.work_with_id(-1)),
			NULL,
			NULL
		);
	}
	while (stop)
	{
		cout << "Set 0 to shutdown the program:\n";
		cin >> stop;
		system("cls");
	}
	// delay to close the threads

	for (size_t i = 0; i < Count_of_markets; i++)
	{
		Market_log(Market_Arr[i]);
	}
}