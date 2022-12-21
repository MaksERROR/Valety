#include "Market.h"

CreateID M_ID;

void Market::init()
{
	id = M_ID.work_with_id(-1);
	this->session = 1000;
	this->active = 0;
	this->_sumSession = this->session;
	this->BaseUp = this->session;
	this->bank = 1000;
	this->coast = bank/_sumSession;
	if (this->Name != "")
		return;
	this->Name = "Market_No_" + to_string(id);
}

void Market::Mlogs()
{
	if (this->session<= (BaseUp))
	{
		this->session += BaseUp;
		this->_sumSession += BaseUp;
	}

	coast = bank/_sumSession;

	string adres = "logs\\" + this->Name + "_coast.txt";
	log.open(adres, ios_base::app);
	log << coast << '\t' << session << '\t' << bank << '\t' << this->_sumSession << '\n';
	log.close();
}

Market::Market()
{
	init();
}

Market::Market(int new_id)
{
	init();
	this->id = new_id;
}

Market::Market(string Market_name)
{
	Name = Market_name;
	init();
}

double Market::MakeOrder(double count, bool sell_buy)
{
	active += 1;
	if (this->active > 1) 
	{
		active -= 1;
		Mlogs();
		return 0;
	}


	double ret;
	if (sell_buy)
	{//sell $money$ traider -> market
		//count of money
		ret = count / this->coast;
		if (this->session > ret)
		{
			this->bank += count;
			this->session -= ret;
		}
		else 
		{
			Mlogs();
			return -this->session;
		}
	}
	else
	{//buy $money$ traider <- market
		//count of tokens
		ret = count * this->coast;
		if (ret < this->bank)
		{
			this->bank -= ret;
			this->session += count;
		}
		else 
		{
			Mlogs();
			return -this->bank;
		}
	}
	Mlogs();
	active -= 1;
	return ret;
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