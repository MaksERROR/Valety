#include "CraeteID.h"
#include <string>
#include <fstream>
using namespace std;

class Market
{
private:
	string Name;
	int id;
	int active;
	unsigned long long _sumSession;
	double session;//count of currency
	double coast;//coast of 1 point
	double bank;//bank of currency
	int BaseUp; 
	ofstream log;
	
	void init();

public:

	Market();
	Market(int new_id);
	Market(string Market_name);
	void Mlogs();
	double MakeOrder(double count,bool sell_buy = 1);
	int GetId();
	double GetBank();
	string GetName();
	double GetCoast();

	~Market();
};