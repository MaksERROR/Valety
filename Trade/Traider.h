#include "CraeteID.h"
#include <vector>
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
	
	vector <vector<double>> s_valet;//id;traiders active[n][1] course
	int s_Marketplace_count_activity;//count of active markets
	int s_old_parse;
	int Parsing(string Name_market);
	void init();
	double GetSummValet();

public:

	Traider();
	Traider(string Name);
	void Ante(Market& MarketName);
	int GetId();
	string GetName();
	double GetCapital();
	void Traider_log();

	void TLogs(Market& MarketName);

	~Traider();
};
