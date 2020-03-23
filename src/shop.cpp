#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <map>

#include <filesystem>

#include "item.h"
#include "receipt.h"
#include "procreceipt.h"
#include "reports.h"

using namespace std;
namespace fs = std::filesystem;

int main(int argc, char **argv)	{
	
	vector<receipt> vec;
	generate_master(vec);
	for(auto& i : vec)
		cout << i.date << endl;
	
	report(vec, "20171007", "20190920");
	
	//report("a","b");
	
	/*
	for(auto& i : cat_names)
		cout << i << endl;
	*/
	//for(size_t i = 0; i < v[0].cat_totals.size(); i++)
	//	cout << "cat_totals[" << i << "]: " << v[0].cat_totals[i] << endl;
	
	
	
	
	//string 
	//for(auto i = v.begin(); i !
	
	/*
	ifstream f("/home/roger/stuff/prog/projects/shop/object/work/data/master.csv");
	vector<receipt> v;
	receipt r;
	
	string line;
	
	while (getline(f, line))	{
		if (line[0] == '0')	{	// create a new receipt
			r.clear();
			r.additem(line);
		}
		else if (line[0] != '0' && line[0] != '7')	{
			r.additem(line);
		}
		else if (line[0] == '7')	{
			r.additem(line);
			v.push_back(r);
		}
		else
			cout << "there was an error" << endl;
	}
	f.close();
	*/
/*
	for (unsigned int j = 0; j < v.size(); j++)	{
		v[j].print();
	}
*/
/*
	for(auto i : v)
		cout << i.fdate << "\t" << i.date << endl;
*/
//	cout << "DOING TOP / BOTTOM 5" << endl << endl;
/*	
	for(auto &i : v)	{
		for(auto &j : i.top_five)	{
			j.print();
		}
	}
*/	
	
	////////////////////////////////////////////////////////////////////////////
	// Load all the category names into a vector
	////////////////////////////////////////////////////////////////////////////
	/*
	vector<string> cats(15);
	f.open("/home/roger/stuff/prog/projects/shop/object/work/data/categories.txt");
	string num,name;
	stringstream ss;
	while(getline(f, line))	{
		ss.clear();
		ss.str("");
		ss<<line;
		getline(ss, num, ',');
		getline(ss, name, ',');
		cats[stoi(num)] = name;		
	}
	f.close();
	*/
	////////////////////////////////////////////////////////////////////////////
	
	// vector cats now contains the category names
	
	//for(size_t i = 0; i < cats.size(); i++)
	//	cout << cats[i] << endl;
		
	
	
	
	
	/*
	cout << "Category totals" << endl;
	for(size_t i = 0; i < v.size(); i++)	{
		for(size_t j = 0; j < v[i].cat_totals.size(); j++)	{
			cout << "cat_totals[" << j << "]: " << v[i].cat_totals[j] << endl;
			
		}
	}
	*/
	
	
	
	
	////////////////////////////////////////////////////////////////////////////
	// delete all the '"' chars from file
	////////////////////////////////////////////////////////////////////////////
/*
	string line;
	
	ifstream f("/home/roger/stuff/prog/projects/shop/object/work/data/items.db");
	ofstream o("/home/roger/stuff/prog/projects/shop/object/work/data/items_mod.db");
	while(getline(f, line))	{
		line.erase(std::remove(line.begin(), line.end(), '"'), line.end());
		o << line << endl;
	}
*/	
		
	
	////////////////////////////////////////////////////////////////////////////
	// Generate a master receipt of stacked receipts from a directory of 
	// receipt files
	////////////////////////////////////////////////////////////////////////////
	
	/*
	vector<string> asdf;
	string pathe = "/home/roger/stuff/prog/projects/shop/object/work/data/txts/large/";
	for (const auto & entry : fs::directory_iterator(pathe))	{
		//cout << entry.path() << endl;
		//asdf.push_back(entry.path().string().substr(2));
		//cout << fs::exists(entry.path().string()) << endl;
		asdf.push_back(entry.path().string());
	}
	
	sort(asdf.begin(), asdf.end());
	
	for(unsigned int i = 0; i < asdf.size(); i++)	{
		proc_receipt(asdf[i], "../data/master.csv", true);		
	}
	*/
	
	/*
	ifstream f("/home/roger/stuff/prog/projects/shop/object/work/data/master_receipt.csv");
	
	vector<receipt> v;
	receipt r;
	
	string line;
	int i = 0;
	while (getline(f, line))	{
		if (line[0] == '0')	{	// create a new receipt
			r.clear();
			r.additem(line);
			i++;
		}
		else if (line[0] != '0' && line[0] != '7')	{
			r.additem(line);
			i++;
		}
		else if (line[0] == '7')	{
			r.additem(line);
			v.push_back(r);
			i++;
		}
		else
			cout << "there was an error, i is: " << i << endl;
	}
	
	for (int j = 0; j < v.size(); j++)	{
		v[j].print();
	}
	*/
	
	

	//cout << rcpt.receiptvec[10].price << endl;
	
	////////////////////////////////////////////////////////////////////////////
	// read in the categories into a vector
	////////////////////////////////////////////////////////////////////////////
	/*
	string line;
	stringstream ss;
	vector<string> cat(14, "BLANK");	// change to accommodate any number of categories based on the category file
	
	ifstream f("/home/roger/stuff/prog/projects/shop/object/meijer receipts/categories.txt");
	
	int i = 1;
	while(getline(f,line))	{
		ss<<line;
		getline(ss, line, ',');
		getline(ss, line, ',');
		
		cat[i] = line;
		
		i++;
		ss.str("");
		ss.clear();	
	}
	*/
	////////////////////////////////////////////////////////////////////////////
	// end
	////////////////////////////////////////////////////////////////////////////	


	return 0;
}
