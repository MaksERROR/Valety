#include "Traider.h"

#include "Constants.h"
CreateID T_ID;

void Traider::init()
{
	s_id = T_ID.work_with_id(-1);

	s_Marketplace_count_activity = 0;
	s_free_capital = 10000;
	for (size_t i = 0; i < Count_of_markets; i++)
	{
		s_valet.push_back(vector<double>(3));
		s_valet[i][0] = -4;
	}
	if (this->s_Name != "")
		return;
	s_Name = "Traider_Bot_No_" + to_string(s_id);
}

double Traider::Parsing(string Name_market)
{
	double ansver = 0;
	double buf;
	double old = 0;
	string adres = path + Name_market + "_coast.txt";
	read.open(adres, ios_base::end);
	int size = read.tellg();
	read.seekg((size - (size / (rand() % 10+1))), ios_base::beg);

	do
	{
		read >> buf;

		ansver += buf - old;
		old = buf;
		read >> buf;
		read >> buf;
		read >> buf;

	} while (!read.eof());

	read.close();
	return ansver;
}

void Traider::Traider_log()
{
	ofstream log_file_Traider;
	log_file_Traider.open("logs\\all_sum_Traider" + to_string(this->s_id) + ".txt", ios_base::app);
	log_file_Traider << this->s_id << "\t"
		<< this->s_Name << "\t"
		<< this->GetSummValet() << "\t"
		<< this->s_free_capital << "\n";
	log_file_Traider.close();
}

Traider::Traider()
{
	init();
}

Traider::Traider(int new_id)
{
	init();
	this->s_id = new_id;
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


void Traider::Ante(Market& Market_indexing, int sell_by = 0)
{
	//get neaded parametrs
	double free9_10 = this->s_free_capital - this->s_free_capital / 10;
	int Market_id = -1;

	for (int i = 0; i < s_Marketplace_count_activity && Market_indexing.GetId() != (int)s_valet[i][0]; i++) 
	{
		Market_id = i;
	}
	Market_id++;
	if (s_valet[Market_id][0] != Market_indexing.GetId())//create new 
	{
		this->s_valet.push_back(vector<double>(3));
		this->s_valet[s_Marketplace_count_activity][0] = Market_indexing.GetId();
		this->s_valet[s_Marketplace_count_activity][1] = 0;
		s_valet[s_valet.size() - 1][0] = -1;
		this->s_Marketplace_count_activity++;
	}
	this->s_valet[Market_id][2] = Market_indexing.GetCoast();


	if (sell_by !=0)
	{
		if (sell_by>0)
		{//buy
			double sum = sell_by;

			if (free9_10 < sum && this->s_free_capital>sum)
			{
				double geted = Market_indexing.MakeOrder(sum);
				if (geted > 0)
				{
					this->s_valet[Market_id][1] += geted;
					this->s_free_capital -= sum;
				}
				else
				{
					sum = -geted/2;
					geted = Market_indexing.MakeOrder(sum);
					if (geted > 0)
					{
						this->s_valet[Market_id][1] += geted;
						this->s_free_capital -= sum;
					}
				}
			}
			else
			{
				double geted = Market_indexing.MakeOrder(this->s_free_capital/1.09);
				if (geted > 0)
				{
					this->s_valet[Market_id][1] += geted;
					this->s_free_capital = 0;
				}
				else
				{
					sum = -geted/2;
					geted = Market_indexing.MakeOrder(sum);
					if (geted > 0)
					{
						this->s_valet[Market_id][1] += geted;
						this->s_free_capital -= sum;
					}
				}
			}
		}
		else 
		{//sell
			double count_of_tokens = -sell_by;
			if ((int)(this->s_valet[Market_id][1]) > 0 && count_of_tokens < this->s_valet[Market_id][1])
			{
				double poop = Market_indexing.MakeOrder(count_of_tokens, 0);
				if (poop > 0)
				{
					this->s_free_capital += poop * Market_indexing.GetCoast();
					this->s_valet[Market_id][1] -= poop;
				}
				else
				{
					poop = Market_indexing.MakeOrder(-poop/2, 0);
					if (poop > 0)
					{
						this->s_free_capital += poop * Market_indexing.GetCoast();
						this->s_valet[Market_id][1] -= poop;
					}
				}
			}
			else
			{
				if (this->s_valet[Market_id][1] == 0) 
				{
					TLogs(Market_indexing);
					return;
				}
				double poop = Market_indexing.MakeOrder(this->s_valet[Market_id][1]/1.09, 0);
				if (poop > 0)
				{
					this->s_free_capital += poop;
					this->s_valet[Market_id][1] -= count_of_tokens;
				}
				else
				{
					poop = Market_indexing.MakeOrder(-poop/2, 0);
					if (poop > 0)
					{
						this->s_free_capital += poop;
						this->s_valet[Market_id][1] -= count_of_tokens;
					}
				}
			}
		}
		TLogs(Market_indexing);
		return;
	}

	//int rezult = Parsing(Market_indexing.GetName());
	if (rand() % 200 > 100)
	{//buy
		double sum = rand() % (int)pow(10, max_order_coast);

		if (free9_10 < sum && this->s_free_capital>0)
		{
			sum = free9_10;
		}
		this->s_valet[Market_id][1] += Market_indexing.MakeOrder(sum);
		this->s_free_capital -= sum;
	}
	else
	{//sell
		double count_of_tokens = this->s_valet[Market_id][1];
		if ((int)(this->s_valet[Market_id][1]) > 0)
		{
			count_of_tokens = rand() % (int)(this->s_valet[Market_id][1]);
		}
		this->s_free_capital += Market_indexing.MakeOrder(count_of_tokens, 0);
		this->s_valet[Market_id][1] -= count_of_tokens;
	}
	TLogs(Market_indexing);
	//s_old_parse = rezult;
}
//*/
void Traider::TLogs(Market& MarketName)
{
	string adres = path + this->s_Name + ".txt";
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

double Traider::GetSummValet()
{
	double summ = 0;
	for (size_t i = 0; i < s_Marketplace_count_activity; i++)
	{
		summ += this->s_valet[i][1] * this->s_valet[i][2];
	}
	return summ;
}


double Traider::GetCapital()
{
	return this->s_free_capital;
}


Traider::~Traider()
{
	T_ID.work_with_id(s_id);

	ofstream bacup;
	string adres = path + this->s_Name + "_Bacup.txt";
	bacup.open(adres, ios_base::app);

	bacup << "& " << this->s_free_capital << "\t"
		<< this->s_Marketplace_count_activity << "\t";
	for (size_t i = 0; i < s_Marketplace_count_activity; i++)
	{
		bacup << this->s_valet[i][0] << "\t" << this->s_valet[i][1] << "\t";
	}
	bacup << "\n";
	bacup.close();
}

