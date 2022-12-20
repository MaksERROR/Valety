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
	void init();

public:

	double GetSummValet();
	Traider();
	Traider(int new_id);
	Traider(string Name);
	int GetId();
	void Ante(Market& MarketName,int sell_by);
	int Parsing(string Name_market);
	string GetName();
	double GetCapital();
	void Traider_log();

	void TLogs(Market& MarketName);

	~Traider();
};
