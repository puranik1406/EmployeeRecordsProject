#include"salaries.h"

float da(emp *staff)
{
	return (staff->basic)/5;
}

float hra(emp *staff)
{
	return (staff->basic)/4;
}

float gross(emp *staff)
{
	return (da(staff)+hra(staff)+staff->basic);
}

float tds(emp *staff)
{
	return gross(staff)/10;
}

float nps(emp *staff)
{
	return gross(staff)/10;
}

float gi(emp *staff)
{
	return gross(staff)/50;
}

float deductions(emp *staff)
{
	return (tds(staff)+nps(staff)+gi(staff));
}

float netsal(emp *staff)
{
	return (gross(staff)-deductions(staff));
}
