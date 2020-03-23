#include <algorithm>
#include <string>
#include "receipt.h"
#include "item.h"

using std::stoi;

////////////////////////////////////////////////////////////////////////////////
// generate a vector of (all) receipts from the master receipt
////////////////////////////////////////////////////////////////////////////////
void generate_master(vector<receipt>& v)	{
    ifstream f("master.csv");
    //vector<receipt> v;
	
	receipt r;
	
	string line;
	
	while (getline(f, line))	{
		if (line[0] == '0')	{	// create a new receipt
			r.clear();
			r.additem(line);
		}
		else if (line[0] != '0' && line[0] != '7')	{
			r.additem(line);
			r.num_items++;
		}
		else if (line[0] == '7')	{
			r.additem(line);
			v.push_back(r);
		}
		else
			cout << "there was an error" << endl;
	}
	f.close();

    sort(v.begin(), v.end(),
        [](const auto& a, const auto& b)    {
            return stoi(a.date) < stoi(b.date);
        });

    //return v;
}

void report(vector<receipt>& v, string begin, string end)	{
	// get category names
	vector<string> cat_names;
    ifstream f("categories.txt");
	string line;
	stringstream ss;
	while(getline(f, line))	{
		ss.clear();
		ss.str("");
		ss<<line;
		getline(ss, line, ',');
		getline(ss, line, ',');
		cat_names.push_back(line);
	}
	
	const auto & first = find_if(v.begin(), v.end(),	
								[&](const receipt& r) { return r.date == begin; } );
	const auto & last = find_if(v.begin(), v.end(),	
								[&](const receipt& r) { return r.date == end; } );
	for_each(first, last+1, [](receipt& r) { r.print(); });
						

string getmonthstring(int m) {
    switch(m)   {
        case 1:
            return "Jan";
        case 2:
            return "Feb";
        case 3:
            return "Mar";
        case 4:
            return "Apr";
        case 5:
            return "May";
        case 6:
            return "Jun";
        case 7:
            return "Jul";
        case 8:
            return "Aug";
        case 9:
            return "Sep";
        case 10:
            return "Oct";
        case 11:
            return "Nov";
        case 12:
            return "Dec";
        default:
            return "ERR";
    }
}
