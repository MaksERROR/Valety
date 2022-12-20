#include <iostream>
#include "Traider.h"
#include <string>

using namespace std;

void Market_log(Market& A)
{
	ofstream log_file_Market;
	log_file_Market.open("logs\\all_sum_market" + to_string(A.GetId()) + ".txt", ios_base::app);
	log_file_Market << A.GetId() << "\t"
		<< A.GetName() << "\t"
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
const int size_A = 200;
int main()
{
	ofstream logcmd;
	Market A[size_A];
	//cout<<A.GetName();
	Traider B[10];
	for (size_t i = 0; i < size_A; i++)
	{
		A[i].Mlogs();
	}
	for (size_t i = 0; i < size_A; i++)
	{
		Market_log(A[i]);
	}
	for (size_t i = 0; i < 10; i++)
	{
		Traider_log(B[i]);
	}
	logcmd.open("logs\\cmd_log.txt", ios_base::app);
	for (size_t i = 0; i < 200; i++)
	{
		for (size_t j = 0; j < 10; j++)
		{
			for (size_t g = 0; g < size_A; g++)
			{
				B[j].Ante(A[g]);
				A[g].Mlogs();
			}
			for (size_t i = 0; i < size_A; i++)
			{
				cout << A[i].GetId() << "\t"
					<< A[i].GetCoast() << "\t"
					<< A[i].GetBank() << "\n";
				logcmd << A[i].GetId() << "\t"
					<< A[i].GetCoast() << "\t"
					<< A[i].GetBank() << "\n";
			}
				
		}
	}
	logcmd.close();
	for (size_t i = 0; i < 2; i++)
	{
		Market_log(A[i]);
	}
	for (size_t i = 0; i < 10; i++)
	{
		Traider_log(B[i]);
	}
}