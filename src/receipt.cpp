/****************************************************
 * 
 * todo:
 * 	add addition/subtraction/editing of items
 * 		update total
 * 	calculate percentage of each category (food/household)
 * 	calculate top 10/bottom 10 items in terms of money spent
 * 	add a get current date bit of code to date entry portion
 * 
 ****************************************************/

#include <algorithm>
#include "receipt.h"
#include "item.h"

using std::to_string;
using std::right;
using std::cout;
using std::setw;
using std::endl;
using std::sort;
using std::greater;
using std::fill;

#define underline "\033[4m"
#define nounderline "\033[0m"

// NOTE: >> operator turns fields with decimals into ints without decimals
//		    when inserting(<<), we convert back to string, so put the '.' back
//			in the right spot.  consider not going back and forth, or creating
//			a simple function to do this quickly and clearly, instead of 
//			encumbering the insertion operator with string handling.
ostream& operator<<(ostream& os, const receipt& r)	{
	string tmp;
	os << "0," << r.fdate << "," << r.cashier << endl;
	for(size_t i=0; i<r.receiptvec.size(); i++)	{
		os << "1," << r.receiptvec[i].code << "," << r.receiptvec[i].name << "," 
		   << to_string(r.receiptvec[i].qty) << ",";
		 
		tmp = to_string(r.receiptvec[i].price);
		tmp = tmp.substr(0, tmp.length()-2) + "." + tmp.substr(tmp.length()-2);
		
		os << tmp << ",";
		   
		if(r.receiptvec[i].wasprice == 0)	{
			os << "NULL,";
		}
		else	{
			tmp = to_string(r.receiptvec[i].wasprice);
			tmp = tmp.substr(0, tmp.length()-2) + "." + tmp.substr(tmp.length()-2);
			os << tmp << ",";
		}
		os << r.receiptvec[i].rate << endl;
	}
	os << "7," << r.savings << "," << r.tax << "," << r.total << endl;
	return os;	
}
istream& operator>>(istream& is, receipt& r)	{
	if(r.receiptvec.empty())	{
		string s;
		while(getline(is, s))
			r.additem(s);
	}
	return is;
}

bool operator==(receipt& l, receipt& r)	{
	return l.date == r.date;
}

receipt::receipt()	{ 
	month	= day = year = 0;
	date	= "000000";
	fdate	= "00/00/00";
	total	= "";
    //cat_totals = vector<int>(15,0);
    //for(int i = 0; i < 15; i++)
    //   cat_totals.push_back(0);
    fill(cat_totals, cat_totals+15, '\0');

	num_items = 0;
}


receipt::receipt(int m, int d, int y)	{
	month	= m;
	day  	= d;
	year	= y;
	date 	= to_string(y)+to_string(m)+to_string(d);
	fdate 	= to_string(m)+"/"+to_string(d)+"/"+to_string(y);
	total 	= "";
}

receipt::~receipt(){}

void receipt::additem(string s)	{
	stringstream ss(s);
	switch(s[0])	{
		case '0':
			getline(ss, s, ',');
			getline(ss, fdate, ',');
			getline(ss, cashier);
			date = "20" + fdate.substr(6) 
						+ fdate.substr(0,2) 
						+ fdate.substr(3,2);
						
			break;
		case '7':
			getline(ss, s, ',');
			getline(ss, savings, ',');
			getline(ss, tax, ',');
			getline(ss, total);	
			topandbottom((*this).receiptvec);
			break;	
		default:
			string code, name, rate;
            int qty, price, wasprice, category;
			bool sale;
			getline(ss, s, ',');
			getline(ss, code, ',');
			getline(ss, name, ',');
			getline(ss, s, ',');
			qty = stoi(s);
			
			getline(ss, s, ',');
			//cout << "first erase" << endl;
			s.erase(s.length()-3, 1);
			//cout << "after" << endl;
			price = stoi(s);
			getline(ss, s, ',');
			if(s=="NULL")	{
				wasprice = 0;
			}
			else	{
				s.erase(s.length()-3, 1);
				wasprice = stoi(s);
			}
			getline(ss, rate, ',');
			getline(ss, s);
            category = stoi(s);
            cat_totals[category]++;
			
			code[0]=='*' ? sale = true : sale = false;
			
			receiptvec.push_back(item(code, name, qty, price, wasprice, rate, sale, category));
	}
}

size_t receipt::size() { return receiptvec.size(); }

void receipt::printtotal()	{
	cout << setw(40) << right << "TOTAL:" << setw(24) << total << endl;
}
                
void receipt::print()	{
	
	cout << "************************************************************************************" << endl;
	cout << "  date: " << fdate << "                                                  cashier: " << cashier << endl;
	cout << "************************************************************************************" << endl;
	cout << underline <<  "  # NAME              CODE          QTY   PRICE  S     WAS   CAT            CATEGORY" 
	     << nounderline << endl;
	
	for(size_t i = 0; i < receiptvec.size(); i++)	{
		if((i+1)%10==0)	{
			cout << underline << setw(3) << right << i+1 << " ";
			receiptvec[i].print();
			cout << nounderline;
		}
		else	{
			cout << setw(3) << right << i+1 << " ";
			receiptvec[i].print();
		}
	}
	cout << "\n\n";
	this->printtotal();
	cout << "\n";
}

void receipt::clear()	{
	receiptvec.clear();
    //cat_totals.clear();
    //cat_totals = vector<int>(15,0);
    //for(auto x : cat_totals) { x = 0; }
	top_five.clear();
	bottom_five.clear();
	month	= day = year = 0;
	date	= "000000";
	fdate	= "00/00/00";
	total	= "";
	num_items = 0;
}

void receipt::topandbottom(vector<item> v)	{

	sort(v.begin(), v.end(), 
		 [](const item& l, const item& r) { return l.price < r.price; });
		 
	for(size_t i = 0; i < 5; i++)
		bottom_five.push_back(v[i]);
	for(size_t i = v.size()-5; i < v.size(); i++)
		top_five.push_back(v[i]);
	sort(top_five.begin(), top_five.end(),
		 [](const item& l, const item& r) { return l.price > r.price; });	
}

// repeated code.  consolidate?
void receipt::print_top()	{
	cout << "TOP FIVE BY COST" << endl;
	for(size_t i = 0; i < 80; i++)	{ cout << "*"; } cout << endl;
	for(auto& i : top_five)
		i.print();
}

void receipt::print_bottom()	{
	cout << "BOTTOM FIVE BY COST" << endl;
	for(size_t i = 0; i < 80; i++)	{ cout << "*"; } cout << endl;
	for(auto& i : bottom_five)
		i.print();
}
