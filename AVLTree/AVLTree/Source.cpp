#include <iostream>
#include "Tree.h"
#include <string>
#include <map>
using namespace std;



int main()
{
	map<string, string> tr;
	tr["a"]="a";
	tr["b"] = "b";
	tr["c"] = "c";
	tr["d"] = "d";
	tr["f"] = "f";
	tr["m"] = "m";
	tr["h"] = "h";
	tr["o"] = "o";
	tr["p"] = "p";
	tr["q"] = "q";
	tr["e"] = "e";
	
	for(auto it=tr.begin(); it!=tr.end(); ++it)
	{
		cout << it->first << endl;
	}

}