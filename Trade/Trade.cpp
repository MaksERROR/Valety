#include <iostream>
#include "Traider.h"
#include <string>

using namespace std;

const int Markets_count = 5;
const int Traiders_count = 10;
int main()
{
	ofstream logcmd;
	Market A[Markets_count];
	Traider B[Traiders_count];
	for (size_t i = 0; i < Markets_count; i++)
	{
		A[i].Mlogs(1);
	}
	for (size_t i = 0; i < Traiders_count; i++)
	{
		B[i].Traider_log();
	}
	logcmd.open("logs\\cmd_log.txt", ios_base::app);
	for (size_t i = 0; i < 200; i++)
	{
		for (size_t j = 0; j < Traiders_count; j++)
		{
			for (size_t g = 0; g < Markets_count; g++)
			{
				B[j].Ante(A[g]);
				A[g].Mlogs(0);
				cout << A[g].GetId() << "\t"
					<< A[g].GetCoast() << "\t"
					<< A[g].GetBank() << "\n";
				logcmd << A[g].GetId() << "\t"
					<< A[g].GetCoast() << "\t"
					<< A[g].GetBank() << "\n";
			}
			
		}
	}
	logcmd.close();
	for (size_t i = 0; i < 2; i++)
	{
		A[i].Mlogs(1);
	}
	for (size_t i = 0; i < 10; i++)
	{
		B[i].Traider_log();
	}
}