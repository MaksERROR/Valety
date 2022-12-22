#pragma once
class CreateID
{
private:
	
	int s_Id;
	int ids;

	int Free_ids;
	int* Free_id;

public:
	CreateID();
	
	int work_with_id(int What);
	int Max_used_ids();
	bool This_id_created(int get_id);

	~CreateID();
};
