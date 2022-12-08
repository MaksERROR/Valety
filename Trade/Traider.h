#include "CraeteID.h"
#include <string>
#include "Market.h"
#include <fstream>
#include <cmath>

using namespace std;
class Traider
{
private:
	
	string s_Name;
	int s_id;
	double s_free_capital;// 
	ifstream read;
	ofstream log;
	
	double** s_valet;//id;traiders active[n][1]
	int s_Marketplace_count_activity;//count of active markets
	int s_old_parse;
	int Parsing(string Name_market);
	void init();
public:

	Traider();
	Traider(string Name);
	void Ante(Market& MarketName);
	int GetId();
	string GetName();
	double GetSummValet();
	double GetCapital();

	void TLogs(Market& MarketName);

	~Traider();
};
