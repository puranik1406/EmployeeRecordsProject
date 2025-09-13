#ifndef SALARIES_H
#define SALARIES_H

#include "employee.h"

float da(emp *staff);
float hra(emp *staff);
float gross(emp *staff);
float tds(emp *staff);
float nps(emp *staff);
float gi(emp *staff);
float deductions(emp *staff);
float netsal(emp *staff);

#endif
