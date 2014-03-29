#ifndef _MINTERM_CPP
#define _MINTERM_CPP

#include <iostream>
#include <iomanip>
#include <cmath>
#include <algorithm>
#include <string>
#include <vector>

#include "rice/Class.hpp"
#include "rice/Data_Type.hpp"
#include "rice/Array.hpp"
#include "rice/Hash.hpp"

using namespace std;
using namespace Rice;

/* Minterm.h */
class minterm
{
	public:
		minterm(); //Empty constructor. 
		minterm (int v); //Constructor with number of variables.
		minterm (int, int); //Constructor with number of variables and an order.
		void setVal(int); //Setting the integer value (order).
		void setLen(int); //Setting the number of variables.

		int getVal(); //Getting the value of the minterm.
		int getVal(int); //Overloaded getVal for multiple values minterms.
		int getLen(); //Getting the length of the minterm.
		int getOnes(); //Getting the number of ones.
		int NumOfCom(); //Number of combined minterms.

		bool valExist(int); //Checking the existentce of a minterm.

		string getValB(); //Getting the binary value of the minterm.

		bool adjacent (minterm); //Checkin if the two minterms are adjacent.
		
		minterm combine(minterm&); //Minterms combining.

		bool compareImp(minterm); //Implicants comparison.

		void setPrime(bool); //Modifying prime flag.
		void setEssential (bool);
		bool isPrime(); //Retrieving prime flag.
		bool isEssential();


		friend bool operator==(minterm a, minterm min);
		friend bool operator!=(minterm a, minterm min);
		friend bool operator<=(minterm a, minterm min);
		friend bool operator>=(minterm a, minterm min);
		friend bool operator>(minterm a, minterm min);
		friend bool operator<(minterm a, minterm min);

	private:
		string val; //Minterm value.

		vector <int> m; //Minterms orders.
		int n; //Number of variables.

		bool valid; //Minterm validity.

		int ones; //Number of ones in val.

		bool prime; //Prime flag.
		bool essential; //Essential flag.

		void updateOnes (); //Count the one's in the values.
		void addVal(int); //Add val for multiple input.
};

ostream &operator<< (ostream &out, minterm min);

bool operator==(int a, minterm min);
bool operator==(minterm min, int a);


bool operator!=(int a, minterm min);
bool operator!=(minterm min, int a);


bool operator<=(int a, minterm min);
bool operator<=(minterm min, int a);


bool operator>=(int a, minterm min);
bool operator>=(minterm min ,int a);


bool operator<(int a, minterm min);
bool operator<(minterm min, int a);


bool operator>(int a, minterm min);
bool operator>(minterm min, int a);

/* Minterm.cpp */
string toBin (int dec) //Decimal to Binary converter.
{
	if (dec == 0) return "0";
	if (dec == 1) return "1";

	if (dec % 2 == 0)
	return toBin(dec / 2) + "0";
	else
	return toBin(dec / 2) + "1";
}

minterm::minterm()
{
n = 0;
valid = 0;
prime = 1;
essential = 0;
}

void minterm::setVal(int v)
{
m.assign(1, v);
if (v > (pow((double)2, n) - 1)) //Checking value validty.
{
val = '-1'; 
valid = 0;
cout << "Invalid minterm entry." << endl;
return;
}

valid = 1;

val = toBin(v); //Assigning minterm value.

int l = val.length();

for (int i = 0; i < (n - l); i++) //0's extension.
{
val.insert(0, "0");
}
updateOnes();
}

void minterm::addVal(int v)
{
if (v > (pow((double)2, n) - 1)) //Checking value validty.
{
val = '-1'; 
valid = 0;
cout << "Invalid minterm entry." << endl;
return;
}
m.push_back(v);
sort (m.begin(), m.end());
}

void minterm::setLen(int k) {n = k;}

minterm::minterm(int k)
{
setLen (k);
for (int i = 0; i < n; i++)
{
val = val + '0';
}
m.assign(1, 0);
valid = 1;
prime = 1;
essential = 0;
}

minterm::minterm(int k, int v)
{
n = k;
essential = 0;
setVal(v);

}

int minterm::getVal()
{
return m[0];
}

int minterm::getVal(int v)
{
if (v < m.size())
return m[v];
return -1;
}

int minterm::getLen()
{
return n;
}

int minterm::getOnes()
{
return ones;
}

string minterm::getValB()
{
return val;
}

int minterm::NumOfCom()
{
return m.size();
}

ostream &operator<< (ostream &out, minterm min)
{
out << min.getVal();
for (int i = 1; i < min.NumOfCom(); i++)
out << ", " << min.getVal(i);
out << "  " << min.getValB();
return out;
}

bool minterm::isEssential(){return essential;}


bool minterm::adjacent(minterm x)
{
int diff = 0;
if (getLen() != x.getLen())
return 0;
for (int i = 0; i < getLen(); i++)
{
if (val[i] != x.getValB().at(i))
diff ++;
}

if (diff != 1)
return 0;

return 1;
}

minterm minterm::combine(minterm &par)
{
minterm result = *this;
if (adjacent (par))
{
result.setPrime(1);
for (int i = 0; i < par.m.size(); i++)
{
if (!result.valExist(par.m[i]))
result.addVal(par.m[i]);
}

for (int i = 0; i < getLen(); i++)
{
if (val[i] != par.val[i])
{
result.val[i] = '-';
}

}
prime = 0;
par.prime = 0;
}
else
cout << "Warning: attempting to combine non-adjacent elements, the second parameter was rejected." << endl;
return result;
}

bool minterm::valExist(int a)
{
for (int i = 0; i < m.size(); i++)
if (m[i] == a)
return 1;
return 0;
}

void minterm::updateOnes()
{
ones = 0;
for (int i = 0; i < val.length(); i++)
if (val.at(i) == '1')
ones++;
}

void minterm::setPrime(bool value) {prime = value;}

void minterm::setEssential (bool value) {essential = value;}

bool minterm::isPrime() {return prime;}

bool operator==(int a, minterm min) {return (a == min.getVal());}
bool operator==(minterm min, int a) {return (a == min.getVal());}
bool operator==(minterm a, minterm min) {return (a.val == min.val);}

bool operator!=(int a, minterm min) {return (a != min.getVal());}
bool operator!=(minterm min, int a) {return (a != min.getVal());}
bool operator!=(minterm a, minterm min) {return (a.val != min.val);}

bool operator<=(int a, minterm min) {return (a <= min.getVal());}
bool operator<=(minterm min, int a) {return (min.getVal() <= a);}
bool operator<=(minterm a, minterm min) {return (a.val <= min.val);}

bool operator>=(int a, minterm min){return (a >= min.getVal());}
bool operator>=(minterm min ,int a) {return (min.getVal() >= a);}
bool operator>=(minterm a, minterm min) {return (a.val >= min.val);}

bool operator<(int a, minterm min){return (a < min.getVal());}
bool operator<(minterm min, int a) {return (min.getVal() < a);}
bool operator<(minterm a, minterm min) {return (a.val < min.val);}

bool operator>(int a, minterm min) {return (a > min.getVal());}
bool operator>(minterm min, int a) {return (min.getVal() > a);}
bool operator>(minterm a, minterm min) {return (a.val > min.val);}

/* Quine McClusky Implementation (Main.cpp) */
bool mintExist(vector <minterm> vect, minterm min)
{
	for (int i = 0; i < vect.size(); i++)
		if (vect[i] == min)
			return 1;

	return 0;
}

string printSop(vector <minterm> mins)
{
	stringstream ss;
	bool isOne = false;
	if (mins.empty()) return "";
	
	string temp;


	if (mins.size() == 1)
		if (mins[0].NumOfCom() == pow(double(2), mins[0].getLen()))
		{
			ss << "1";
			isOne = true;
		}
	
	if(!isOne) {
		for (int i = 0; i < mins.size(); i++)
		{
			temp = mins[i].getValB();
			for (int j = 0; j < temp.length(); j++)
			{
				if (temp.at(j) == '0')
					ss << char (65 + j) <<"'";
				else
				 if (temp.at(j) == '1')
					 ss << char (65 + j);
			}
			if (i != mins.size() - 1)
				ss << " + ";
		}
	}

	string s;
	getline(ss, s);
	return s;
}


vector <minterm> MinimumCover (vector <minterm> mins, vector <minterm> primes)
{
	vector <vector <minterm> > AndOr;
	vector <vector <minterm> > temp; 
	vector <minterm> result;
	vector <vector<minterm> > expansion;


	int min_size; //Size of smalles implicant.
	string literalsCounter(""); //To Count the literals of implicants.

	if (mins.empty())
		return mins;

	int divider;

	AndOr.resize(mins.size());
	
	for (int i = 0; i < mins.size(); i++) //BuildingExpression.
		for (int j = 0; j < primes.size(); j++)
			if (primes[j].valExist(mins[i].getVal()))
				AndOr[i].push_back(primes[j]);

	expansion.resize (AndOr[0].size());
	for (int i = 1; i < AndOr.size(); i++)
		expansion.resize(expansion.size() * AndOr[i].size());
	
	
	divider = expansion.size();
	for (int i = 0; i < AndOr.size(); i++) //Expanding.
	{	if (AndOr[i].size() != 0) divider /= AndOr[i].size(); else cout <<"Attempting to divide by zero!" << endl;
		for (int j = 0; j < AndOr[i].size(); j++)
		{ 

			for (int l = j*divider; l < expansion.size(); l++)				
			{
				if (! mintExist(expansion[l], AndOr[i][j]))
					expansion[l].push_back(AndOr[i][j]);
				if ((l+1) % divider == 0) {l += divider;}
			} 
		}
	}

	
	for (int i = 0; i < expansion.size(); i++) //Eliminating repeated terms.
		{ 
			for (int j = i + 1; j < expansion.size(); j++)
			{
				if (expansion[i] == expansion[j])
				{ 
					expansion.erase(expansion.begin() + j);
					j--;
				}
				
			} 
		}


	bool subset;

	for (int i = 0; i < expansion.size(); i++) //Applying X + XY = X.
		for (int j = 0; j < expansion.size(); j++)
		{
			if (i == j) continue;

			subset = 1;
			for (int k = 0; k < expansion[i].size(); k++)
				if (find (expansion[j].begin(), expansion[j].end(), expansion[i][k]) == expansion[j].end())
					subset = 0;

			if (subset)
			{
				if (j < i)
					i--;
				expansion.erase(expansion.begin() + j);
				j--;
			}

		}


					


	min_size = expansion[0].size();

	for (int i = 1; i < expansion.size(); i++) //Getting the smallest implicants combination.
	{
		if (expansion[i].size() < min_size)
			min_size = expansion[i].size();
	}

	


	for (int i = 0; i < expansion.size(); i++)
	{
		if (expansion[i].size() == min_size)
			temp.push_back(expansion[i]);
	}


	
	min_size = 9999999;
	int x;

	for (int i = 0; i < temp.size(); i++) //Getting the implicant with the smallest number of literals.
	{
		x = 0;
		literalsCounter = "";

		for (int j = 0; j < temp[i].size(); j++)
			literalsCounter += temp[i][j].getValB();

		for (int j = 0; j < literalsCounter.size(); j++)
			{
				if ((literalsCounter.at(j) == '1') || (literalsCounter.at(j) == '0'))
					x++;
			}

		if (x < min_size)
			{
				result.clear();
				result = temp[i];
			}
	}

	
	return result;
}

Hash Optimize (Array rb_mins, Array rb_dcs)
{
	vector <minterm> mins, dcs;
	Hash output, h_cols, h_iterations;

	int highest_minterm = 0, n = 0;
	
	for (size_t i = 0; i < rb_mins.size(); ++i)
		highest_minterm = highest_minterm < from_ruby<int>(rb_mins[i]) ? from_ruby<int>(rb_mins[i]) : highest_minterm;

	for (size_t i = 0; i < rb_dcs.size(); ++i)
		highest_minterm = highest_minterm < from_ruby<int>(rb_dcs[i]) ? from_ruby<int>(rb_dcs[i]) : highest_minterm;
	
	if (log(highest_minterm)/log(2.0) ==  ceil(log(highest_minterm)/log(2.0)))
		n = ceil(log(highest_minterm)/log(2.0)) + 1; 
	else
		n = ceil(log(highest_minterm)/log(2.0));

	cout << "Size : " << rb_mins.size() << endl;
	mins.resize(rb_mins.size());
	for (size_t i = 0; i < rb_mins.size(); ++i) {
		mins[i].setLen(n);
		mins[i].setVal(from_ruby<int>(rb_mins[i]));
	}

	cout << "Size : " << rb_dcs.size() << endl;
	dcs.resize(rb_dcs.size());
	for (size_t i = 0; i < rb_dcs.size(); ++i) {
		dcs[i].setLen(n);
		dcs[i].setVal(from_ruby<int>(rb_dcs[i]));
	}

	if (!dcs.empty()) sort (dcs.begin(), dcs.end());
	sort (mins.begin(), mins.end());


	vector <vector<vector<minterm> > > implicants; //3D implicants vector (Coloumn, 1's group, implicants).
	vector <minterm> temp;
	vector <minterm> prime; //Prime implicants.
	vector <minterm> e_prime; //Essential prime implicants.
	vector <vector<char> > chart; //Chart array.
	vector <minterm> minterms_reduced; //Minterms after elimimnations. 
	vector <minterm> primes_reduced; //Prime implicants after eliminations.
	vector <minterm> covers; //Minimum cover.

	stringstream out;

	/* New Code */
	int count, x;

	int iterations = 0;
	bool re_itr = 1, ess_flag = 0, col_flag = 0, row_flag = 0;

	

	if (mins.empty()) return output; //Checking for empty argument.

	
	implicants.resize(mins[0].getLen() + 1); //Adding coloumns.
	for (int i = 0; i < implicants.size(); i++) //Dividing coloumns to 1's groups.
		implicants[i].resize(mins[0].getLen() + 1);


	temp.resize(mins.size() + dcs.size());
	merge (mins.begin(), mins.end(), dcs.begin(), dcs.end(), temp.begin()); //Merging minterms and don-t cares.

	

	for (vector<minterm>::iterator it = temp.begin(); it != temp.end(); it++) //Filling minterms coloumn.
	{
		implicants[0][it -> getOnes()].push_back(*it);			
	}
		
	out << "Constructing implicants:" << endl << endl;
	//***********Building the coloumns************
		
	for (int i = 0; i < (implicants.size() - 1); i++) //Looping through coloumns.
		for (int j = 0; j < (implicants[i].size() - 1); j++) //Looping through 1's groups.
			for (int k = 0; k < implicants [i][j].size(); k++) //Looping through minterms of the first 1's group.
				for (int m = 0; m < implicants[i][j + 1].size(); m++) //Looping through minterms of the second 1's group.
					if (implicants[i][j][k].adjacent(implicants [i][j + 1][m]))
					{
						temp[0] = implicants[i][j][k].combine(implicants [i][j + 1][m]);
						if (!mintExist(implicants[i + 1][temp[0].getOnes()] , temp[0]))
						{
							implicants[i + 1][temp[0].getOnes()].push_back(temp[0]);
							out << "Combining " << implicants[i][j][k].getValB() << " and " << implicants [i][j + 1][m].getValB() << endl << "Resulted implicant: " << temp[0] << endl; 				
						}
					}

	out << endl << endl;
	
	//***********Printing coloumns****************
	for (int i = 0; i < implicants.size(); i++)
	{	
		Array arr_col;

			cout << endl << "Column " << i << endl;
			for (int j = 0; j < implicants [i].size(); j++)
			{
				if (!implicants[i][j].empty())
				{
					cout << ".............." << endl;
					for (int k = 0; k < implicants [i][j].size(); k++)
					{	
						stringstream ss;
						ss << implicants [i][j][k];
						cout << implicants [i][j][k];
						if (implicants [i][j][k].isPrime())
						{
							ss << "*";
							cout << "*";
							if(!mintExist(prime, implicants [i][j][k]))
								prime.push_back (implicants [i][j][k]);
						}
						ss << endl;
						cout << endl;
						string im;
						getline(ss, im);
						arr_col.push(im);
					}
				}
			}

			h_cols[i] = arr_col;
	}
	cout << endl << "-------------------------------------------" << endl;

	cout << endl << "Prime implicants: "; 
	output[String("pi")] = printSop(prime);
	cout << endl; //Printing prime implicants as SOP.
	
	//Copying minterms and primes to their reduction vectors.
	primes_reduced.assign(prime.begin(), prime.end());
	minterms_reduced.assign(mins.begin(), mins.end());

	//*******************Building Chart**************
	cout << endl << "-------------------------------------------" << endl;
	Array arr_chart;
	stringstream ss; 
	for (int i = 0; i < prime.size(); i++)
	{
		ss << "," << right << prime[i].getValB();
	}
	cout << endl;
	string s; getline(ss, s); ss.clear();
	arr_chart.push(s);

	chart.resize(mins.size());

	for (int i = 0; i < mins.size(); i++)
	{
		chart[i].resize(prime.size());
	}

	for (int i = 0; i < mins.size(); i++)
	{

		ss << mins[i];
		for (int j = 0; j < prime.size(); j++)
		{
			chart[i][j] = prime[j].valExist(mins[i].getVal())? '1' : '0';
			ss << "," << right<< chart [i] [j];
		}
		ss << endl;
		getline(ss,s); ss.clear();
		arr_chart.push(s);
	}
	output[String("chart")] = arr_chart;

	while (re_itr)
	{	
		Hash itr;
		re_itr = 0;
		cout << endl << "           Iteration #" << ++iterations << endl << endl;
		out << endl << "Iteration # " << iterations << ":" << endl << endl << endl;
		e_prime.clear();
		//********Searching for essential prime implicants************
		out << "Detecting essential prime implicants: " << endl << endl;
		cout << endl << "-------------------------------------------" << endl;
		cout << endl << "Essential prime implicants: " << endl;

		Array arr_epi;

		for (int i = 0; i < minterms_reduced.size(); i++)
		{
			count = 0;
			for (int j = 0; j < primes_reduced.size(); j++)
				if (primes_reduced[j].valExist(minterms_reduced[i].getVal()))
				{
					count++;
					x = j;
				}
			if (count == 1)
			{
				primes_reduced[x].setEssential(1);
				ess_flag = 1;
				if (!mintExist(e_prime, primes_reduced[x]))
				{
					e_prime.push_back(primes_reduced[x]);
					stringstream ss;
					out << "Detected " << primes_reduced[x].getValB() << endl;
					ss << primes_reduced[x] << endl;
					cout << primes_reduced[x] << endl;
					string s; getline(ss, s);
					arr_epi.push(s);
				}
			}
		}

		itr[String("essential_pi")] = arr_epi;


		if (!ess_flag)
			{
				cout <<"No essential prime implicants detected for this iteration." << endl;
				out << "No essential prime implicants in iteration #" << iterations << endl;
			}

		out << endl << endl;
	
		//*********************Eliminating essential primes**************
	
		out << endl << "Eliminating essential prime implicants and covered minterms: " << endl << endl;
		for (vector<minterm>::iterator it = primes_reduced.begin(); it != primes_reduced.end();) //Eliminating essential primes.
		{
			if ((*it).isEssential())
			{
				if (!mintExist(covers, *it))
				{
					out << "Eliminating essential implicant " << it -> getValB() << endl << "Eliminating covered minterms: ";
					covers.push_back (*it);
					for (vector<minterm>::iterator it2 = minterms_reduced.begin(); it2 != minterms_reduced.end();) //Eliminating minterms covered by this implicant.
					{
						if ((*it).valExist((*it2).getVal()))
						{
							out << it2 -> getVal() << " ";
							it2 = minterms_reduced.erase(it2);
						}
						else
						{
							it2++;
						}
					}
					out << endl;
					it = primes_reduced.erase(it);
				}
			}
			else
				it++;
		}

		if (ess_flag)
		{
			//Rebuilding the chart:
			cout << endl << "-------------------------------------------" << endl;
			cout << "Chart after eliminating essential primes: " << endl;

			Array arr_chart_after_epi;
			chart.clear();

			if(minterms_reduced.size() != 0) {
				for (int i = 0; i < primes_reduced.size(); i++)
				{
					ss << "," << right << primes_reduced[i].getValB();
				}
				ss << endl; getline(ss, s); ss.clear();
				arr_chart_after_epi.push(s);


				chart.resize(minterms_reduced.size());
		
				for (int i = 0; i < minterms_reduced.size(); i++)
				{
					chart[i].resize(primes_reduced.size());
				}

				for (int i = 0; i < minterms_reduced.size(); i++)
				{
					ss << minterms_reduced[i];
					for (int j = 0; j < primes_reduced.size(); j++)
					{
						chart[i][j] = primes_reduced[j].valExist(minterms_reduced[i].getVal())? '1' : '0';
						ss << "," << right<< chart [i] [j];
					}
					ss << endl; getline(ss, s); ss.clear();
					arr_chart_after_epi.push(s);
				}
				itr[String("chart_after_epi")] = arr_chart_after_epi;
			}


			e_prime.clear();

			cout << endl << "-------------------------------------------" << endl;
		}

		ess_flag = 0;

		//*********************Eliminating dominant rows*****************
		bool eliminated = 1;
		bool dominant;
		out << endl << endl << "Eliminating dominant rows (minterms): " << endl << endl;
		while (eliminated)
		{
			eliminated = 0;
			for (int i = 0; i < minterms_reduced.size(); i++)
				for (int j = 0; j < minterms_reduced.size(); j++)
				{
					if (i == j) continue;
					dominant = 1;
					for (int k = 0; k < primes_reduced.size(); k++)
						if (primes_reduced[k].valExist(minterms_reduced[i].getVal()))
							if (!primes_reduced[k].valExist(minterms_reduced[j].getVal()))
								dominant = 0;
					if (dominant)
					{
						out <<"Eliminating minterm " << minterms_reduced[j].getVal() << " dominated by minterm " << minterms_reduced[i].getVal() << endl << endl;
						row_flag = 1;
						re_itr = 1;
						if (j < i)
							i--;
						minterms_reduced.erase(minterms_reduced.begin() + j);
						j--;
						eliminated = 1;
					}
				}
		}

		if (row_flag)
		{
			//Rebuilding the chart:
			cout << endl << "-------------------------------------------" << endl;
			cout << "Chart after eliminating dominant rows: " << endl;

			Array arr_chart_after_dr;
			chart.clear();

			if(minterms_reduced.size() != 0) { 
				for (int i = 0; i < primes_reduced.size(); i++)
				{
					ss << "," << right << primes_reduced[i].getValB();
				}
				ss << endl; getline(ss,s); ss.clear();
				arr_chart_after_dr.push(s);

				chart.resize(minterms_reduced.size());
		
				for (int i = 0; i < minterms_reduced.size(); i++)
				{
					chart[i].resize(primes_reduced.size());
				}

				for (int i = 0; i < minterms_reduced.size(); i++)
				{
					ss << minterms_reduced[i];
					for (int j = 0; j < primes_reduced.size(); j++)
					{
						chart[i][j] = primes_reduced[j].valExist(minterms_reduced[i].getVal())? '1' : '0';
						ss << "," << right<< chart [i] [j];
					}
					ss << endl; getline(ss,s); ss.clear();
					arr_chart_after_dr.push(s);
				}

				itr[String("chart_after_dr")] = arr_chart_after_dr;
			}

			cout << endl << "-------------------------------------------" << endl;
		}
		else
		{
			cout << endl << "-------------------------------------------" << endl
				<< "No dominant rows in this iteration." << endl << "-------------------------------------------" << endl;
			out << "No dominant rows in iteration #" << iterations << endl;
		}
		row_flag = 0;
		out << endl << endl;

		//*********************Eliminating dominant coloumns*****************
		eliminated = 1;
		out << endl << endl << "Eliminating dominant coloumns (implicants): " << endl << endl;

		while (eliminated)
		{
			eliminated = 0;
			for (int i = 0; i < primes_reduced.size(); i++)
				for (int j = 0; j < primes_reduced.size(); j++)
				{
					if (i == j) continue;
					dominant = 1;
					for (int k = 0; k < primes_reduced[j].NumOfCom(); k++)
						if (!primes_reduced[i].valExist(primes_reduced[j].getVal(k)))
							for (int l = 0; l <minterms_reduced.size(); l++)
								if (minterms_reduced[l].valExist(primes_reduced[j].getVal(k)))
									dominant = 0;

					if (dominant)
					{
						out << "Eliminating implicant " << primes_reduced[j].getValB() << " dominated by " <<  primes_reduced[i].getValB() << endl << endl;
						if (j < i)
							i--;
						col_flag = 1;
						re_itr = 1;
						primes_reduced.erase(primes_reduced.begin() + j);
						j--;
						eliminated = 1;
					}
				}

		}

		if (col_flag)
		{
			//Rebuilding the chart:
			cout << endl << "-------------------------------------------" << endl;
			cout << "Chart after eliminating dominant columns: " << endl;
			
			Array arr_chart_after_dc;
			chart.clear();

			if(minterms_reduced.size() != 0) {
				for (int i = 0; i < primes_reduced.size(); i++)
				{
					ss << "," << right << primes_reduced[i].getValB();
				}
				ss << endl; getline(ss,s); ss.clear();
				arr_chart_after_dc.push(s);

				chart.resize(minterms_reduced.size());
		
				for (int i = 0; i < minterms_reduced.size(); i++)
				{
					chart[i].resize(primes_reduced.size());
				}

				for (int i = 0; i < minterms_reduced.size(); i++)
				{
					ss << minterms_reduced[i];
					for (int j = 0; j < primes_reduced.size(); j++)
					{
						chart[i][j] = primes_reduced[j].valExist(minterms_reduced[i].getVal())? '1' : '0';
						ss << "," << right<< chart [i] [j];
					}
					ss << endl; getline(ss,s); ss.clear();
					arr_chart_after_dc.push(s);
				}

				itr[String("chart_after_dc")] = arr_chart_after_dc;
			}

			cout << endl << "-------------------------------------------" << endl;
		}
		else
		{
			cout << endl << "-------------------------------------------" << endl
				<< "No dominant columns in this iteration." << endl << "-------------------------------------------" << endl;
			out << "No dominant columns in iteration #" << iterations << endl;
		}
		col_flag = 0;
		out << endl << endl;

		h_iterations[iterations] = itr;
	}

	char prompt =' ';
	const unsigned long overload = 16777216;

	int req;
	
	count = 1;

	for (int i = 0; i < minterms_reduced.size(); i++)
	{
		req = 0;
		for (int j = 0; j < primes_reduced.size(); j++)
			if (primes_reduced[j].valExist(minterms_reduced[i].getVal()))
				req++;
		count *= req;
	}

	x = 0;

	cout << "Computing the final cover.." << endl;
	out << "Computing the final cover";
	if (minterms_reduced.size() != 1)
	{
		if (count > overload)
		{
			cout << "Warning: Computing the final cover requires high computation power and might take long time."
				<< endl << "Do you want to compute a random minimum cover? (Y = Yes. Otherwise = Procceed anyway). ";
			cin >> prompt;
		}

		out << " using Petrick's method.." << endl;
		temp = MinimumCover(minterms_reduced, primes_reduced);

		// if (toupper(prompt) == 'Y')
		// {
		// 	while (!minterms_reduced.empty())
		// 	{
		// 		out << " with lower calculations.." << endl;
		// 		temp.push_back(primes_reduced[x]);
		// 		for (int i = 0; i < minterms_reduced.size(); i++)
		// 			if (primes_reduced[x].valExist(minterms_reduced[i].getVal()))
		// 			{
		// 				minterms_reduced.erase(minterms_reduced.begin() + i);
		// 				i--;
		// 			}
		// 		x++;
		// 	}
		// }
		// else
		// {
		// 	out << " using Petrick's method.." << endl;
		// 	temp = MinimumCover(minterms_reduced, primes_reduced);
		// }
	}
	else
	{temp.resize(1); temp [0] = primes_reduced[0]; out << ".." << endl;}

	for (int i = 0; i < temp.size(); i++)
		covers.push_back(temp[i]);

	out << "Final cover implicants are: ";
	for (int i = 0; i < covers.size(); i++)
	{
		out << covers[i].getValB(); if (i < covers.size() - 1) out << " & ";
	}
	out << endl << endl;

	cout << "Reduced function: "; printSop(covers); cout << endl;
	output[String("reduced_function")] = printSop(covers); 
	cout << endl;

	output[String("columns")] = h_cols;
	output[String("iterations")] = h_iterations;
	
	Array arr_log;
	while(getline(out, s)) {
		if(s != "")
			arr_log.push(s);
	}
	output[String("log")] = arr_log;

	// cout << endl << endl << "------Optimzation log-------" << endl << endl << out.str();

	/* Old Cde */
	// int count;

	// bool eliminated = 1;
	
	// if (mins.empty()) return output; //Checking for empty argument.


	// implicants.resize(mins[0].getLen() + 1); //Adding coloumns.
	// for (int i = 0; i < implicants.size(); i++) //Dividing coloumns to 1's groups.
	// 	implicants[i].resize(mins[0].getLen() + 1);

	

	// temp.resize(mins.size() + dcs.size());
	// merge (mins.begin(), mins.end(), dcs.begin(), dcs.end(), temp.begin()); //Merging minterms and don-t cares.

	

	// 	for (vector<minterm>::iterator it = temp.begin(); it != temp.end(); it++) //Filling minterms coloumn.
	// 		{
	// 			implicants[0][it -> getOnes()].push_back(*it);			
	// 		}
		

	// //***********Building the coloumns************
		
	// for (int i = 0; i < (implicants.size() - 1); i++) //Looping through coloumns.
	// 	for (int j = 0; j < (implicants[i].size() - 1); j++) //Looping through 1's groups.
	// 		for (int k = 0; k < implicants [i][j].size(); k++) //Looping through minterms of the first 1's group.
	// 			for (int m = 0; m < implicants[i][j + 1].size(); m++) //Looping through minterms of the second 1's group.
	// 				if (implicants[i][j][k].adjacent(implicants [i][j + 1][m]))
	// 				{
	// 					temp[0] = implicants[i][j][k].combine(implicants [i][j + 1][m]);
	// 					if (!mintExist(implicants[i + 1][temp[0].getOnes()] , temp[0]))
	// 						implicants[i + 1][temp[0].getOnes()].push_back(temp[0]);
	// 				}

	
	
	// //***********Printing coloumns****************
	// for (int i = 0; i < implicants.size(); i++)
	// {	
	// 	Array arr_col;

	// 		cout << endl << "Column " << i << endl;
	// 		for (int j = 0; j < implicants [i].size(); j++)
	// 		{
	// 			if (!implicants[i][j].empty())
	// 			{
	// 				cout << ".............." << endl;
	// 				for (int k = 0; k < implicants [i][j].size(); k++)
	// 				{	
	// 					stringstream ss;
	// 					ss << implicants [i][j][k];
	// 					cout << implicants [i][j][k];
	// 					if (implicants [i][j][k].isPrime())
	// 					{
	// 						ss << "*";
	// 						cout << "*";
	// 						if(!mintExist(prime, implicants [i][j][k]))
	// 							prime.push_back (implicants [i][j][k]);
	// 					}
	// 					ss << endl;
	// 					cout << endl;
	// 					string im;
	// 					getline(ss, im);
	// 					arr_col.push(im);
	// 				}
	// 			}
	// 		}

	// 		h_cols[i] = arr_col;
	// }
	// cout << endl << "-------------------------------------------" << endl;

	// cout << endl << "Prime implicants: "; 
	// output[String("pi")] = printSop(prime);
	// cout << endl; //Printing prime implicants as SOP.

	

	// //********Searching for essential prime implicants************
	// cout << endl << "-------------------------------------------" << endl;
	// cout << endl << "Essential prime implicants: " << endl;
	// int x;
	// Array arr_epi;
	// for (int i = 0; i < mins.size(); i++)
	// {
	// 	count = 0;
	// 	for (int j = 0; j < prime.size(); j++)
	// 		if (prime[j].valExist(mins[i].getVal()))
	// 		{
	// 			count++;
	// 			x = j;
	// 		}
	// 	if (count == 1)
	// 	{
	// 		prime[x].setEssential(1);
	// 		if (!mintExist(e_prime, temp[0]))
	// 		{
	// 			e_prime.push_back(prime[x]);
	// 			stringstream ss;
	// 			ss << prime[x] << endl;
	// 			cout << prime[x] << endl;
	// 			string s; getline(ss, s);
	// 			arr_epi.push(s);
	// 		}
	// 	}
	// }
	// output[String("essential_pi")] = arr_epi;

	// //*******************************************************************
	
	// //Copying minterms and primes to their reduction vectors.
	// primes_reduced.assign(prime.begin(), prime.end());
	// minterms_reduced.assign(mins.begin(), mins.end());

	// //*******************Building Chart**************
	// cout << endl << "-------------------------------------------" << endl;
	// Array arr_chart;
	// stringstream ss; 
	// for (int i = 0; i < prime.size(); i++)
	// {
	// 	ss << "," << right << prime[i].getValB();
	// }
	// cout << endl;
	// string s; getline(ss, s); ss.clear();
	// arr_chart.push(s);

	// chart.resize(mins.size());
	
	// for (int i = 0; i < mins.size(); i++)
	// {
	// 	chart[i].resize(prime.size());
	// }

	// for (int i = 0; i < mins.size(); i++)
	// {

	// 	ss << mins[i];
	// 	for (int j = 0; j < prime.size(); j++)
	// 	{
	// 		chart[i][j] = prime[j].valExist(mins[i].getVal())? '1' : '0';
	// 		ss << "," << right<< chart [i] [j];
	// 	}
	// 	ss << endl;
	// 	getline(ss,s); ss.clear();
	// 	arr_chart.push(s);
	// }
	// output[String("chart")] = arr_chart;

	// cout << endl << "-------------------------------------------" << endl;
	
	// //*********************Eliminating essential primes**************
	
	// for (vector<minterm>::iterator it = primes_reduced.begin(); it != primes_reduced.end();) //Eliminating essential primes.
	// {
	// 	if ((*it).isEssential())
	// 	{
	// 		if (!mintExist(covers, *it))
	// 		{
	// 			covers.push_back (*it);
	// 			for (vector<minterm>::iterator it2 = minterms_reduced.begin(); it2 != minterms_reduced.end();) //Eliminating minterms covered by this implicant.
	// 			{
	// 				if ((*it).valExist((*it2).getVal()))
	// 				{
	// 					it2 = minterms_reduced.erase(it2);
	// 				}
	// 				else
	// 				{
	// 					it2++;
	// 				}
	// 			}
	// 			it = primes_reduced.erase(it);
	// 		}
	// 	}
	// 	else
	// 		it++;
	// }

	// //Rebuilding the chart:
	// cout << endl << "-------------------------------------------" << endl;
	// cout << "Chart after eliminating essential primes: " << endl;

	// Array arr_chart_after_epi;

	// chart.clear();

	// for (int i = 0; i < primes_reduced.size(); i++)
	// 	{
	// 		ss << "," << right << primes_reduced[i].getValB();
	// 	}
	// ss << endl; getline(ss, s); ss.clear();
	// arr_chart_after_epi.push(s);

	// chart.resize(minterms_reduced.size());
	
	// for (int i = 0; i < minterms_reduced.size(); i++)
	// {
	// 	chart[i].resize(primes_reduced.size());
	// }

	// for (int i = 0; i < minterms_reduced.size(); i++)
	// {
	// 	ss << minterms_reduced[i];
	// 	for (int j = 0; j < primes_reduced.size(); j++)
	// 	{
	// 		chart[i][j] = primes_reduced[j].valExist(minterms_reduced[i].getVal())? '1' : '0';
	// 		ss << "," << right<< chart [i] [j];
	// 	}
	// 	ss << endl; getline(ss, s); ss.clear();
	// 	arr_chart_after_epi.push(s);
	// }
	// output[String("chart_after_epi")] = arr_chart_after_epi;

	// cout << endl << "-------------------------------------------" << endl;

	// //*********************Eliminating dominant rows*****************

	// bool dominant;
	// while (eliminated)
	// {
	// 	eliminated = 0;
	// 	for (vector<minterm>::iterator it = minterms_reduced.begin(); it != minterms_reduced.end();) //Eliminating minterms covered by all implicants (dominant rows).
	// 	{
	// 		dominant = 1;
	// 		for(int i = 0; i < primes_reduced.size(); i++)
	// 		{
	// 			if (!primes_reduced[i].valExist((*it).getVal()))
	// 				dominant = 0;
	// 		}

	// 		if (dominant && minterms_reduced.size() != 1)
	// 			{it = minterms_reduced.erase(it); eliminated = 1;}
	// 		else
	// 			it ++;
	// 	}
	// }

	// //Rebuilding the chart:
	// cout << endl << "-------------------------------------------" << endl;
	// cout << "Chart after eliminating dominant rows: " << endl;

	// Array arr_chart_after_dr;

	// chart.clear();

	// for (int i = 0; i < primes_reduced.size(); i++)
	// 	{
	// 		ss << "," << right << primes_reduced[i].getValB();
	// 	}
	// ss << endl; getline(ss,s); ss.clear();
	// arr_chart_after_dr.push(s);

	// chart.resize(minterms_reduced.size());
	
	// for (int i = 0; i < minterms_reduced.size(); i++)
	// {
	// 	chart[i].resize(primes_reduced.size());
	// }

	// for (int i = 0; i < minterms_reduced.size(); i++)
	// {
	// 	ss << minterms_reduced[i];
	// 	for (int j = 0; j < primes_reduced.size(); j++)
	// 	{
	// 		chart[i][j] = primes_reduced[j].valExist(minterms_reduced[i].getVal())? '1' : '0';
	// 		ss << "," << right<< chart [i] [j];
	// 	}
	// 	ss << endl; getline(ss,s); ss.clear();
	// 	arr_chart_after_dr.push(s);
	// }

	// output[String("chart_after_dr")] = arr_chart_after_dr;

	// cout << endl << "-------------------------------------------" << endl;

	// cout << "Computing the final cover.." << endl;
	
	// temp = MinimumCover(minterms_reduced, primes_reduced);

	// for (int i = 0; i < temp.size(); i++)
	// 	covers.push_back(temp[i]);

	// cout << "Reduced function: "; 
	// output[String("reduced_function")] = printSop(covers); 
	// cout << endl;

	// output[String("columns")] = h_cols;
	return output;
}

extern "C" void Init_minterm()
{
	Class quine_ = define_class("Quine").define_method("optimize", &Optimize);
}
#endif