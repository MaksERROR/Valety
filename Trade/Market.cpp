#include "Market.h"

CreateID M_ID;

void Market::init()
{
	id = M_ID.work_with_id(-1);
	this->session = 1000;
	this->_sumSession = this->session;
	this->BaseUp = this->session / 2;
	this->bank = 1000;
	UpDateCource();
	if (this->Name != "")
		return;
	this->Name = "Market_No_" + to_string(id);
}

void Market::Mlogs(bool all_log)
{
	if (this->session<= (BaseUp/2))
	{
		this->session += BaseUp;
		this->_sumSession += BaseUp;
	}

	coast = bank/_sumSession;

	string adres = "logs\\" + Name + "_coast.txt";
	log.open(adres, ios_base::app);
	log << this->coast << '\t'
		<< this->session << '\t'
		<< this->bank << '\t'
		<< this->_sumSession << '\n';
	log.close();
	if (all_log)
	{
		ofstream log_file_Market;
		log_file_Market.open("logs\\all_sum_market" + to_string(this->id) + ".txt", ios_base::app);
		log_file_Market << this->id << "\t"
			<< this->Name << "\t"
			<< this->bank << "\t"
			<< this->coast << "\n";
		log_file_Market.close();
	}
}

void Market::UpDateCource() 
{
	this->coast = bank / _sumSession;
}



Market::Market()
{
	init();
}

Market::Market(string Market_name)
{
	Name = Market_name;
	init();
}

double Market::MakeOrder(double count, bool sell_buy)
{
	if (sell_buy)
	{//sell $money$ traider -> market
		//count of money
		double ret = count / this->coast;
		this->bank += count;
		this->session -= ret;
		Mlogs(0);
		return ret;
	}
	else
	{//buy $money$ traider <- market
		//count of tokens
		double ret = count * this->coast;
		this->bank -= ret ;
		this->session += count;
		Mlogs(0);
		return ret;
	}
	
	
	
}

int Market::GetId()
{
	return this->id;
}

double Market::GetBank()
{
	return bank;
}

string Market::GetName()
{
	return this->Name;
}

double Market::GetCoast()
{
	return this->coast;
}

Market::~Market()
{
	M_ID.work_with_id(id);
}