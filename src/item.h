#ifndef ITEM_H
#define ITEM_H

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>

using std::string;
using std::to_string;

class item	{
	
	private:

	public:
        item(string, string, int, int, int, string, bool, int);			// default constructor.  initializes to zero
        //item(string, string, int, int, int);                          // alternate constructor.
        ~item();
	
		string code;
		string name;
		int	   qty;
		int	   price;
		int	   wasprice;
		string rate;
		bool   sale;
        size_t category;
		string categoryname;
		
		string getname();			
		int getcategory();		
		int    getprice();
		
		void set_category_name(int);
	
		
		/*
		void setname(string);		
		void setcategory(int);
		void setcode(string);
		void setprice(size_t);
		void setqty(size_t);
		*/
		void print();				// print item object
	
};


#endif /* ITEM_H */
