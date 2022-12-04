#include "Market.h"

CreateID M_ID;

void Market::init()
{
	id = M_ID.work_with_id(-1);
	this->session = 1000;
	this->_sumSession = this->session;
	this->BaseUp = this->session / 2;
	this->bank = 1000;
	this->coast = bank/_sumSession;
	if (this->Name != "")
		return;
	this->Name = "Market_No_" + to_string(id);
}

void Market::Mlogs()
{
	if (this->session<= (BaseUp/2))
	{
		this->session += BaseUp;
		this->_sumSession += BaseUp;
	}

	coast = bank/_sumSession;

	string adres = "logs\\" + Name + "_coast.txt";
	log.open(adres, ios_base::app);
	log << coast << '\t' << session << '\t' << bank << '\t' << this->_sumSession << '\n';
	log.close();
	
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
		Mlogs();
		return ret;
	}
	else
	{//buy $money$ traider <- market
		//count of tokens
		double ret = count * this->coast;
		this->bank -= ret ;
		this->session += count;
		Mlogs();
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