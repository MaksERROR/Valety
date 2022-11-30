#include "Traider.h"
#include "Constants.h"
CreateID T_ID;

void Traider::init()
{
	s_id = T_ID.work_with_id(-1);
	s_valet = new double* [2];
	s_Marketplace_count_activity = 0;
	s_free_capital = 10000;
	for (size_t i = 0; i < 2; i++)
	{
		s_valet[i] = new double[s_MaxMarkets];
	}
	if (this->s_Name != "")
		return;
	s_Name = "Traider_Bot_No_" + to_string(s_id);
}

int Traider::Parsing(string Name_market)
{
	int ansver = 0;
	double buf;
	double old = 0;

	read.open(Name_market + "_coast.txt", ios_base::end);
	int size = read.tellg();
	read.seekg((size - (size / rand()%40)), ios_base::beg);

	do
	{
		read >> buf;
		if (buf)
			read >> buf;
		
		old > buf ? ansver++ : ansver--;
		old = buf;

	} while (!read.eof());

	read.close();
	return ansver;
}

Traider::Traider()
{
	init();
}

Traider::Traider(string Name)
{
	this->s_Name = Name;
	init();
}

int Traider::GetId()
{
	return this->s_id;
}

Traider::~Traider()
{
	T_ID.work_with_id(s_id);

	ofstream bacup;
	bacup.open(this->s_Name + "_Bacup.txt", ios_base::app);

	bacup << "& " << this->s_free_capital << "\t"
		<< this->s_Marketplace_count_activity << "\t";
	for (size_t i = 0; i < s_Marketplace_count_activity; i++)
	{
		bacup << this->s_valet[i][0] << "\t" << this->s_valet[i][1] << "\t";
	}
	bacup << "\n";
	bacup.close();

	for (size_t i = 0; i < s_Marketplace_count_activity; i++)
	{
		delete[] s_valet[i];
	}
	delete[] s_valet;
}

void Traider::ante(Market& MarketName)
{
	//get neaded parametrs
	double free9_10 = this->s_free_capital - this->s_free_capital / 10;
	int rezult = Parsing(MarketName.GetName());
	int Market_id = MarketName.GetId();
	for (int i = 0; i < s_Marketplace_count_activity && Market_id != s_valet[i][0]; i++)
		Market_id = i;
	double sum = rand() % (int)pow(10, max_order_coast);

	if (s_valet[Market_id][0] != MarketName.GetId())//create new 
	{
		this->s_valet[s_Marketplace_count_activity][0] = MarketName.GetId();
		this->s_valet[s_Marketplace_count_activity][1] = 0;
		this->s_Marketplace_count_activity++;
	}

	if (free9_10 < sum && this->s_free_capital>0)
	{
		sum = free9_10;
	}
	
	double Marketreqest = sum / MarketName.GetCoast();
	if (rezult > s_old_parse)
	{//buy
		if (MarketName.MakeOrder(Marketreqest))
		{
			this->s_free_capital -= sum;
			s_valet[Market_id][1] += Marketreqest;
		}
		else
		{
			Marketreqest = sum / MarketName.GetCoast();
			MarketName.MakeOrder(Marketreqest);
		}
	}
	else
	{//sell
		if (MarketName.MakeOrder(Marketreqest, 0) && s_valet[Market_id][1] > Marketreqest)
		{
			this->s_free_capital += sum;
			s_valet[Market_id][1] -= Marketreqest;
		}
	}
	Tlogs(MarketName);
	s_old_parse = rezult;
}
//*/


void Traider::Tlogs(Market& MarketName) 
{
	string adres = this->s_Name + ".txt";
	log.open(adres, ios_base::app);
	double Currency = MarketName.GetCoast();
	int e = MarketName.GetId();
	int i = 0;
	for (; i < s_Marketplace_count_activity && e != s_valet[i][0]; i++);
	e = i;
	
	log << MarketName.GetName() + "_coast.txt" << "\t"		//file_name
		<< this->s_free_capital << "\t"						//free capital
		<< "\t" << this->s_valet[e][0] << "\t"				//id
		<< Currency << "\t"									//currency: bank/count
		<< this->s_valet[e][1] * Currency << "\n";			//capital in this market
	log.close();
}

string Traider::GetName()
{
	return this->s_Name;
}