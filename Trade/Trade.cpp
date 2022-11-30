#include <iostream>
#include "Traider.h"
#include <string>

using namespace std;


int main()
{
	Market A[2];
	//cout<<A.GetName();
	Traider B[10];
	A[0].Mlogs();
	A[1].Mlogs();

	for (size_t i = 0; i < 400; i++)
	{
		for (size_t j = 0; j < 10; j++)
		{
			for (size_t g = 0; g < 2; g++)
			{
				B[j].ante(A[g]);
				A[g].Mlogs();
			}
			cout << A[0].GetId() << "\t"
				<< A[0].GetCoast() << "\t"
				<< A[0].GetBank() << "\n"
				<< A[1].GetId() << "\t"
				<< A[1].GetCoast() << "\t"
				<< A[1].GetBank() << "\n";
		}
	}
}