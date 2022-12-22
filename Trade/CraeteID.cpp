#include "CraeteID.h"
#include "Constants.h"


CreateID::CreateID()
{
	s_Id = 0;
	ids = 0;
	Free_ids = 0;
	Free_id = new int[free_ids_range];
}

CreateID::~CreateID()
{
	delete[] Free_id;
}

int CreateID::work_with_id(int What)
{/*is work; input(-1;from 1 to sizeof(int))*/

	switch (What)//give -1 to generate id and give >=0 to destroy id==What
	{
	case(-1)://give new id
		if (Free_ids > 0)
		{
			ids = Free_id[Free_ids];
			Free_id[Free_ids] = 0;
			Free_ids--;
		}
		else
		{
			ids = s_Id;
			s_Id++;
		}
		return ids;
	default://delete id==What and add this id in list of free ids
		Free_ids += 1;
		Free_id[Free_ids] = What;
		return -1;
	}
}

int CreateID::Max_used_ids()
{
	return s_Id;
}

bool CreateID::This_id_created(int get_id)
{
	if (get_id<=s_Id)
		for (size_t i = 0; i < Free_ids; i++)
			if (get_id == Free_id[i])
				return 0;
	else
		return 0;
	return 1;
}
