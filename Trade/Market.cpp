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

	string adres = Name + "_coast.txt";
	log.open(adres, ios_base::app);
	log << coast << '\n';
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
	if (!sell_buy)
	{//sell traider -> market
		this->session += count;
		coast = bank / session;//lower curse
		this->bank -= count * this->coast;
	}
	else
	{//buy traider <- market
		this->session -= count;
		this->bank += count * coast;
	}
	Mlogs();
	double ret = count * this->coast;
	coast = bank / session;//hier curse comission?
	return ret;//old curce
	
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