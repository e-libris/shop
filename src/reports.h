#ifndef REPORTS_H
#define REPORTS_H

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>
#include "src/item.h"
#include "src/receipt.h"

using std::vector;
using std::string;
using std::fixed;
using std::setprecision;
using std::setfill;

void generate_master(vector<receipt>&);
void report(vector<receipt>&, string, string);
string getmonthstring(int);

#endif /* REPORTS_H */
