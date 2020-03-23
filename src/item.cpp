#include "item.h"

using std::cout;
using std::setw;
using std::left;
using std::right;
using std::endl;
using std::ifstream;
using std::stringstream;

item::item(string cod, string nam, int q, int prc, 
		   int wasp, string rat, bool sal, int cat):
				
		   code(cod), name(nam), qty(q), price(prc),
		   wasprice(wasp), rate(rat), sale(sal), category(cat)	{ 
			   
			   
		   set_category_name(cat);   
		   }
item::~item(){}

string item::getname()		{ return name; }
int	   item::getcategory()	{ return category; }
int    item::getprice()		{ return price; }

void item::set_category_name(int c)	{
	string line;
    ifstream f("../aaa_shop/data/categories.txt");
	stringstream ss;
	// clear here?
	while(getline(f, line))	{
		ss.clear();
		ss.str("");
		ss<<line;
		getline(ss, line, ',');
		if(stoi(line)==c)	{
			getline(ss, line, ',');
			categoryname=line;
			break;
		}
		else;
		
	}
	
}
/*
void item::setname(string s)	{ name = s; }
void item::setcategory(int n)	{ category = n; }
void item::setcode(string s)	{ code = s; }
void item::setprice(size_t n)	{ price = n; }
void item::setqty(size_t q)		{ qty = q; }
*/
void item::print() { 
	
	string s = to_string(price);
	string t = to_string(wasprice);
	
	if(s.length()==1)
		s = "0.0" + s;
	if(t.length()==1)
		t = "0.0" + t;
	
	if(s.length()==2)	
		s = "0." + s;
	else	
		s = s.substr(0, s.length()-2) + "." + s.substr(s.length()-2, 2);
	if(sale && wasprice != 0)
		t = t.substr(0, t.length()-2) + "." + t.substr(t.length()-2, 2);

	
	cout << setw(18) << left << name 
		 << setw(15) << left << code
		 << setw(2) << right << qty 
		 << setw(8) << right << s;
		 
		 
		 sale ? cout << setw(3) << "Y" << setw(8) << right << t 
			  : cout << setw(3) << "N" << setw(8) << right << "n/a";
		 cout << setw(6)  << right << category;
		 cout << setw(20) << right << categoryname;
		 
		 cout <<  endl; 
}
