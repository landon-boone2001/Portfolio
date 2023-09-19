/*
hash_202.cpp
Landon Boone
This program will take a command line argument for a table size, function type, and a collision resolution type. Then, it will take in 
various arguments in order to Add to the hash table, find the total probes, find a value in the hash table, print the hash table, quit, and print commands.
Redone on 12/7/22
*/
#include "hash_202.hpp"
using namespace std;
#include <iostream>
#include <cstdio>
#include <sstream>
  
//creates the hash table, and initializes the collision function type and hash function type.
string Hash_202::Set_Up(size_t table_size, const std::string &fxn, const std::string &collision)
{
    //check if table already set up
	if (Keys.size() > 0){
		return "Hash table already set up" ;
	}
	//check for bad table size
	if (table_size < 1) {
		return "Bad table size";
	}
	//check for bad hash function
	if (fxn.compare("Last7") != 0 && fxn.compare("XOR") != 0) {
		return "Bad hash function";
	}
	if (fxn.compare("Last7") == 0){
		Fxn = 1;
	}
	if (fxn.compare("XOR") == 0){
		Fxn = 0;
	}
	//check for bad collision resolution strategy
	if (collision.compare("Linear") != 0 && collision.compare("Double") != 0) {
		return "Bad collision resolution strategy";
	}
	if (collision.compare("Double") == 0){
		Coll = 1;
	}
	if (collision.compare("Linear") == 0){
		Coll = 0;
	}
	//resize table (Keys & Vals vector) + initialize Nkeys to 0
	Keys.resize(table_size);
	Vals.resize(table_size);
	Nkeys = 0;

  (void) table_size;
  (void) fxn;
  (void) collision;

  return "";
}


//helper function to find the hex digits for a Last7 function
int getLast7(const string &key) {
	string toHex = "";
	stringstream hexer;
	int indexInput = 0;
	if (key.size() > 7) {
			for (int i = 0; i < 7; i++) {
				toHex += key[key.size()-7+i];
			}
		}
		else {
			toHex = key;
		}
	hexer << toHex;
	hexer >> hex >> indexInput;
	return indexInput;
}
//helper function to find the hex digits for a XOR function
int getXOR(const string &key) {
	int indexInput = 0;
	int tempIndexInput = 0;
	int offset = 0;
	int size = key.size();
	string toHex;
	stringstream hexer;
	if (size > 7) {
		while (size > 0) {
			if (size >= 7) {
				toHex = key.substr(offset, 7);
				hexer << hex << toHex;
				hexer >> indexInput;
				indexInput = indexInput ^ tempIndexInput;
				tempIndexInput = indexInput;
				size = size - 7;
				offset = offset + 7;
				hexer.clear();
			}
			else {
				toHex = key.substr(offset);
				hexer << hex << toHex;
				hexer >> indexInput;

				indexInput = indexInput ^ tempIndexInput;
				hexer.clear();	
				size = 0;
			}
		}
		return indexInput;
	}
	else {
		toHex = key.substr(offset);
		hexer << hex << toHex;
		hexer >> indexInput;
		indexInput = indexInput ^ tempIndexInput;
		hexer.clear();
	}

	return indexInput;
}
//adds a value to the hash table if possible.
string Hash_202::Add(const string &key, const string &val)
{
	//check if table not set up
	if (Keys.size() < 1) {
		return "Hash table not set up";
	}
	//check if empty string for key
	if (key.size() < 1) {
		return "Empty key";
	}
	//check if key not composed of hex digits
	for (int i = 0; i < key.size(); i++) {
		if ((int)key[i] > 102) {
			return "Bad key (not all hex digits)";
		}
	} 
	//check if empty string for val
	if (val.size() < 1) {
		return "Empty val";
	}
	//check if hash table is full
	int isFull = 0;
	for (int i = 0; i < Keys.size(); i++) {
		if (!Keys.at(i).empty()) {
			isFull++;
		}
	}
	if (isFull == Keys.size()) {
		return "Hash table full";
	}
	if(Find(key) != "") {
		return "Key already in the table";
	}
	int offset = 0;
	int index = 0;
	int newIndex = 0;
	int indexInput = 0;
	int offsetIndex = 0;
	int indexInputDouble = 0;
	if (Fxn == 1 ) {
		indexInput = getLast7(key);
	}

	if (Fxn == 0) {
		indexInput = getXOR(key);
	}
	
	index = indexInput % Keys.size();

	if (Coll == 1) {
		// if Fxn is XOR
		if (Fxn == 0) {
			indexInputDouble = getLast7(key);
			offset = indexInputDouble % Keys.size();
		}
		// if Fxn is Last7
		else if (Fxn == 1) {
			indexInputDouble = getXOR(key);
			offset = indexInputDouble % Keys.size();
		}
		if (offset == 0) {
				offset = 1;
		}
	}

	//insert into table
	if (Keys.at(index).empty()) {
			Keys.at(index) = key;
			Vals.at(index) = val;
	}
	//handle collisions
	//Linear
	else if (Coll == 0) {
		for (int i = 1; i < Keys.size(); i++) {
			newIndex = (indexInput + i) % Keys.size();
			if (Keys.at(newIndex).empty()) {
				Keys.at(newIndex) = key;
				Vals.at(newIndex) = val;
				break;
			}
			else if (i == Keys.size() -1) {
				return "Cannot insert key";
			}
		}
	}
	//Double 
	else if (Coll == 1) {
		for (int i = 1; i < Keys.size(); i++) {
			offsetIndex = (indexInput + offset*i) % Keys.size();
			if (Keys.at(offsetIndex).empty()) {
				Keys.at(offsetIndex) = key;
				Vals.at(offsetIndex) = val;
				break;
			}
			if (i == Keys.size() -1) {
				return "Cannot insert key";
			}
		}	
	}

	//increment Nkeys
	Nkeys++;

  (void) key;
  (void) val;
  return "";
}
//Finds a val in the hash table, adds Nprobes.
string Hash_202::Find(const string &key)
{

	//get index
	int offset;
	int index;
	int indexInput;
	int newIndex;
	int indexInputDouble;
	
	if (Fxn == 1 ) {
		indexInput = getLast7(key);
	}

	if (Fxn == 0) {
		indexInput = getXOR(key);
	}

	index = indexInput % Keys.size();

	if (Keys.at(index).compare(key) == 0) {
		return Vals.at(index);
	}
	
	if (Coll == 0) {
		for (int i = 1; i < Keys.size(); i++) {
			newIndex = (indexInput + i) % Keys.size();
			Nprobes++;
			if (Keys.at(newIndex).compare(key) == 0) {
				index = i;
				return Vals.at(newIndex);
				break;
			}		
		}
	}
	
	else if (Coll == 1) {
		// if Fxn is XOR
		if (Fxn == 0) {
			indexInputDouble = getLast7(key);
			offset = indexInputDouble % Keys.size();
		}
		// if Fxn is Last7
		else if (Fxn == 1) {
			indexInputDouble = getXOR(key);
			offset = indexInputDouble % Keys.size();
		}
		if (offset == 0) {
				offset = 1;
		}
		
	}

	if (Coll == 1) {
		for (int i = 1; i < Keys.size(); i++) {
			newIndex = (indexInput + offset*i) % Keys.size();
			Nprobes++;
			if (Keys.at(newIndex).compare(key) == 0) {
				return Vals.at(newIndex);
				break;
			}	
		}
	}
	//get probe increment
	//Nprobes = count
  (void) key;
  return "";
}
 
 //prints Hash table
void Hash_202::Print() const
{
  //if table has been set up
	if(Keys.size() != 0) {
		for(unsigned long int i = 0; i < Keys.size(); i++) {
			//print if not empty
			if(Keys.at(i) != "") 
				printf("%5lu %s %s\n", i, Keys.at(i).c_str(), Vals.at(i).c_str());
		}
	}
}
//finds the total amount of probes needed to traverse the hash table
size_t Hash_202::Total_Probes()
{
  	size_t sum = 0;
	
	if(Keys.size() != 0) {
		for(unsigned long int i = 0; i < Keys.size(); i++) {
			Nprobes = 0;
			if(Keys.at(i) != "") { //don't include empty strings
				Find(Keys.at(i));
				sum += Nprobes;
			}
		}
	}

  return sum;
}
