#pragma once
#include "easyx.h"; 
class start
{
public:
	void loading();
	int select();


private:
	IMAGE kaishi;
	bool selectpvpcheck(int x,int y);
	bool selectpvecheck(int x,int y);
};

