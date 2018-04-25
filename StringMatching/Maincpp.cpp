/*
Student Name: Jim Carrey and Jeff Daniels
Student ID: 1010101010
Operating System: {Windows[Version] / Linux[Version] / MacOSX}
Compile Status: {Compiling/Not Compiling} (Is your program successfully compiled?)
Execution Status: {Working/Not Working} (Is it working?)
Bonus Part: {Implemented/Not implemented} (Did you implement the bonus part?)
Comments: Please write your additional comments, if any, about your source code.
*/

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <cstdlib>
using namespace std;


unsigned int BruteForce(string);
unsigned int BruteForceEfficiency(string,string);
unsigned int BruteForceAverage(string,string);
unsigned int HorsePool(string);
unsigned int HorsePoolEfficiency(string,string);
unsigned int HorsePoolAverage(string,string);
void CompareBoth(string);
void AnalyzeAverage(string);
unsigned int allhorsecounter;
unsigned int allhorsetime;
unsigned int allbrutecounter;
unsigned int allbrutetime;
int main() {
	// read file to T
	string T;
	ifstream myfile;
	myfile.open("the_truman_show_script.txt");
	getline(myfile, T, (char)myfile.eof());
	//cout << T;
	myfile.close();
	// end of read file to T

	int choice = 0;
	do
	{
		cout << "MENU" << endl;
		cout << "(1) Brute-Force String Matching" << endl;
		cout << "(2) Horspool's String Matching" << endl;
		cout << "(3) Compare Brute-Force And Horspool' String Matching Algorithms" << endl;
		cout << "(4) Analyze The AverageCase Efficiencies" << endl;
		cout << "(5) Exit" << endl;
		cout << "Choice = ";
		cin >> choice;
		system("cls");
		switch (choice)
		{
		case 1:
		{
			int index = BruteForce(T);
			if (index >= 0)
			{
				cout << "Found At " << index << endl;
			}
			else
			{
				cout << "Not Found" << endl;
			}
			system("pause");
		
		}
		break;
		case 2:
		{
			int index = HorsePool(T);
			if (index >= 0)
			{
				cout << "Found At " << index << endl;
			}
			else
			{
				cout << "Not Found" << endl;
			}
			system("pause");

		}
		break;
		case 3:
		{
			CompareBoth(T); 
			system("pause");
		}
		break;
		case 4:
		{
			AnalyzeAverage(T);
			system("pause");
		}
			break;
		case 5:
			cout << "The Program Is Shutting Down..." << endl;
			break;
		default:
			cout << "Choose between 1-4" << endl;
			break;
		}
		system("cls");
	} while (choice != 5);

	system("pause");
	return 0;
}


unsigned int BruteForce(string T) {
	// input string
	string P;
	cout << "Brute Force Algorithm" << endl;
	cout << "Input A Pattern = ";
	cin.ignore(); // if it does not, it will fail 
	getline(cin, P); //standard input
	unsigned int i = 0;
	for (i = 0; i < (T.length() - P.length()); i++)
	{
		unsigned int j = 0;
		while (j < T.length() && P[j] == T[i + j])
		{
			j = j + 1;
		}
		if (j == P.length()) return i;
	}

	return -1;

}
unsigned int BruteForceEfficiency(string T, string P) {

	clock_t start = clock(); // efficiency time
	unsigned int counter = 0; // count basic operation
	unsigned int i = 0;
	for (i = 0; i < (T.length() - P.length()); i++)
	{
		counter++;
		unsigned int j = 0;
		while (j < T.length() && P[j] == T[i + j])
		{
			j = j + 1;
		}
		if (j == P.length())
		{
			int ms = (clock() - start) ;
			cout << "Found At " << i << " >> Brute Force Efficiency | " << " Second =" << ms << " Count= " << counter << endl;

			return i;
		}
	}
	int ms = (clock() - start);
	cout << "Not Found >> Brute Force Efficiency | " << " Second =" << ms << " Count= " << counter << endl;
	
	return -1;

}

//collects activity values globally
unsigned int BruteForceAverage(string T, string P) {

	clock_t start = clock(); // efficiency time
	unsigned int i = 0;
	for (i = 0; i < (T.length() - P.length()); i++)
	{
		unsigned int j = 0;
		allbrutecounter++;
		while (j < T.length() && P[j] == T[i + j])
		{
			j = j + 1;
		}
		if (j == P.length())
		{
			int ms = (clock() - start);
			allbrutetime += ms;
			return i;
		}
	}
	int ms = (clock() - start);
	allbrutetime += ms;
	return -1;

}



unsigned int HorsePool(string T) {
	// input string
	string P;
	cout << "HorsePool Algorithm" << endl;
	cout << "Input A Pattern = ";
	cin.ignore(); // if it does not, it will fail 
	getline(cin,P);


	//create table
	int const n = 256;
	int Table[n];
	int m = P.length();
	int i = 0;
	for (i = 0; i <= n - 1; i++)
	{
		Table[i] = m;
	}
	int j = 0;
	for (j = 0; j <= m - 2; j++)
	{
		int d = (int)P[j];
		Table[(int)P[j]] = m - 1 - j;
	}
	//end of table
	int n1 = T.length();
	i = m - 1;
	while (i < n1)
	{
		int k = 0;

		while (k < m && P[m - 1 - k] == T[i - k])
		{
			k = k + 1;
		}

		if (k == m)
		{
			return i - m + 1;
		}
		else
		{
			i = i + Table[T[i]];
		}

	}

	return -1;
}


unsigned int HorsePoolEfficiency(string T, string P) {

	//table
	int const n = 256;
	int Table[n];
	int m = P.length();
	int i = 0;
	for (i = 0; i <= n - 1; i++)
	{
		Table[i] = m;
	}
	int j = 0;
	for (j = 0; j <= m - 2; j++)
	{
		Table[(int)P[j]] = m - 1 - j;
	}
	//end of table

	clock_t start = clock(); // efficiency time
	unsigned int counter = 0; // count basic operation
	int n1 = T.length();
	i = m - 1;
	while (i < n1)
	{
		int k = 0;
		counter++; 
		while (k < m && P[m - 1 - k] == T[i - k])
		{
			k = k + 1;
		}

		if (k == m)
		{
			int ms = (clock() - start) ;
			cout << "Found At "<< i - m + 1 <<" >> HorsePool Efficiency | " << " Second =" << ms << " Count= " << counter << endl;

			return i - m + 1;
		}
		else
		{
			i = i + Table[T[i]];
		}

	}

	int ms = (clock() - start);
	cout << "Not Found >> HorsePool Efficiency | " << " Second =" << ms << " Count= " << counter << endl;


	return -1;
}

//collects activity values globally
unsigned int HorsePoolAverage(string T, string P) {
	

	//table
	int const n = 256;
	int Table[n];
	int m = P.length();
	int i = 0;
	for (i = 0; i <= n - 1; i++)
	{
		Table[i] = m;
	}
	int j = 0;
	for (j = 0; j <= m - 2; j++)
	{
		int d = (int)P[j];
		Table[(int)P[j]] = m - 1 - j;
	}
	//end of table

	clock_t start = clock(); // efficiency time
	int n1 = T.length();
	i = m - 1;
	while (i < n1)
	{
		int k = 0;
		allhorsecounter++;
		while (k < m && P[m - 1 - k] == T[i - k])
		{
			k = k + 1;
		}

		if (k == m)
		{
			int ms = (clock() - start);
			allhorsetime += ms;
			return i - m + 1;
		}
		else
		{
			i = i + Table[T[i]];
		}

	}
	int ms = (clock() - start);
	allhorsetime += ms;
	return -1;
}

void CompareBoth(string T) {
	// input string
	string P;
	cout << "Brute Force VS HorsePool Algorithm" << endl;
	cout << "Input A Pattern = ";
	cin.ignore(); // if it does not, it will fail
	getline(cin, P); //standard input

	BruteForceEfficiency(T,P);
	HorsePoolEfficiency(T,P);
	system("pause");
}

void AnalyzeAverage(string T)
{
	srand(time(NULL));

	string words[100];
	//random word production
	for (int i = 0; i < 100; i++)
	{
		int rlenght = (rand() % 3) + 5; //random length 3-7
		for (int m = 0; m < rlenght; m++)
		{
			int rchar = (rand() % 40) + 83;
			words[i] += (char)rchar;

		}

		cout << words[i] << endl;
	}

	allhorsecounter=0;
	allhorsetime=0;
	allbrutecounter=0;
	allbrutetime=0;
	//all the words are inserted in the algorithm
	for (int i = 0; i < 100; i++)
	{
		BruteForceAverage(T, words[i]);
		HorsePoolAverage(T, words[i]);
	}

	//average calculations
	unsigned int averagehorsecounter= allhorsecounter/100;
	unsigned int averagehorsetime=allhorsetime/100;
	unsigned int averagebrutecounter=allbrutecounter/100;
	unsigned int averagebrutetime=allbrutetime/100;

	cout << "BruteForce Average Efficiency Average | " << " Second =" << averagebrutetime << " Count= " << averagebrutecounter << endl;
	cout << "HorsePool Average Efficiency Average | " << " Second =" << averagehorsetime << " Count= " << averagehorsecounter << endl;
	

}
