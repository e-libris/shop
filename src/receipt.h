#ifndef RECEIPT_H
#define RECEIPT_H

#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <fstream>
#include <sstream>
#include "item.h"

using std::vector;
using std::ostream;
using std::istream;
using std::string;
using std::stringstream;
using std::cout;
using std::endl;
using std::setw;
using std::right;
using std::left;
using std::to_string;
using std::ifstream;

class receipt	{
	
	private:
		friend ostream& operator<<(ostream&, const receipt&);
		friend istream& operator>>(istream&, receipt&);
		friend bool operator==(receipt&, receipt&);

		
	public:
		receipt();			
		receipt(int,int,int);
        ~receipt();
		
		vector<item> receiptvec;
		int month,day,year;
		string date,fdate;
		string total, tax, savings;
		string cashier;
		int num_items;
		
		//item* getitem(unsigned int);
		
       // vector<int> cat_totals;
        int cat_totals[15];
		vector<item> top_five;
		vector<item> bottom_five;

		void additem(string);
		void topandbottom(vector<item>);
		void print_top();
		void print_bottom();
		//bool price_comp(item&, item&);
		
		//void printitem(unsigned int);
		void printtotal();
		void print();
		
        size_t size();
		
		
		void clear();
			
	
};


#endif /* RECEIPT_H */
		
		/*
		struct item	{
			string	code;			
			string	name;			
			int		qty;
			int		price;
			int		wasprice;
			string	rate;
			bool	sale;
			int		category;
			
			item(string code, string name, int qty, int price, 
				 int wasprice, string rate, bool sale, int category):
				 		   
				 code(code), name(name), qty(qty), price(price),
				 wasprice(wasprice), rate(rate), sale(sale), category(category) 
			{}
		
			void printitem(){
				string s = to_string(price);				
				s.length()==2 ? s="0."+s : s.insert(s.length()-2, ".");
				string s2 = to_string(wasprice);
				if(s2.length()==2)
					s2 = "0." + s2;
				else if(s2.length()>2)
					s2 = s2.insert(s2.length()-2, ".");
				cout << setw(15) << left;
				
				code[0]=='*' ? cout << code.substr(1) : cout << code;
				
				cout << setw(18) << left << name
					 << setw(3) << right << qty 
					 << setw(7) << right << s 
					 << setw(5);
				sale ? cout << "Y" << setw(7) << s2 
				     : cout << "N" << setw(7) << "n/a";
				
				cout << setw(5) << category 
					 << endl;
			}
				
				
				//code << '\t' << name << '\t' << qty  << '\t' << price << '\t' 
				//	 << wasprice << '\t' << rate << '\t' << sale << '\t' << category << endl;}
		};
		*/
		/*
		vector<item> receiptvec;
		int month,day,year;
		string date,fdate;
		string total, tax, savings;
		string cashier;
		*/
