// SortedDriver.cpp

// James Hoffman
//10/29/2017


#include "RandomUtilities.h"
#include "ContainerPrinting.h"
#include "winTimer.h"
#include <list>
#include <iostream>
#include <vector>
#include <algorithm>


using namespace std;


// post: a sorted vector of listSize random doubles from
//         the range minNum to maxNum has been returned.
vector<double>
getNums(size_t listSize, double minNum, double maxNum)
{
	vector<double> theList;
	for (size_t i = 0; i < listSize; ++i)
	{
		theList.push_back(randReal(minNum, maxNum));
	}

sort(begin(theList), end(theList));

return theList;
}


// post: a sorted list of numWords words of length
//         wordLength with characters chosen randomly from
//         alphabet has been returned.
list<string>
getWords(size_t numWords, size_t wordLength, string alphabet)
{
	list<string> theWords;
	for (size_t i = 0; i < numWords; ++i)
	{
		string word;
		for (size_t j = 0; j < wordLength; ++j)
		{
			word += alphabet.at(randInt(0, alphabet.size()));
		}
		theWords.push_back(word);
	}

	theWords.sort();

	return theWords;
}

//checks if negitive

void checkNegitive(double &a) {
	if (a < 0) {
		a = a *(-1);
	}
}

// pre:  number is not empty; 
//       number is sorted from smallest to largest
// post: The most isolated entry in number has been returned
double mostIsolated(vector<double> &number)
{
	int mostIsolatedLocation(0);
	double magnitude(0);
	for (int i(0); i < number.size(); i++) {
		if (i == 0) {
			//checks first 
			double tempH = number[i] - number[i + 1];
			//makes pos
			checkNegitive(tempH);
			if (tempH > magnitude) {
				magnitude = tempH;
				mostIsolatedLocation = i;
			}
		}
		else if (i == number.size() - 1) {
			//checks last
			double tempL = number[i] - number[i - 1];
			//makes pos
			checkNegitive(tempL);
			if (tempL > magnitude) {
				magnitude = tempL;
				mostIsolatedLocation = i;
			}
		}
		else {
			//checks evreything in the middle
			double tempL = number[i] - number[i - 1];
			double tempH = number[i] - number[i + 1];
			//makes pos
			checkNegitive(tempL);
			checkNegitive(tempH);
			if (tempL < tempH) {
				if (tempL > magnitude) {
					magnitude = tempL;
					mostIsolatedLocation = i;
				}
			}
			else if (tempH > magnitude) {
					magnitude = tempH;
					mostIsolatedLocation = i;
				}
		}
	}

	return number[mostIsolatedLocation];
}


// pre:  A and B are sorted.
// post: The number of strings in A that do not occur in B
//         has been returned.
int
unmatched(list<string> & A, list<string> & B)
{
	//setup
	int check(0);
	list<string>::iterator AList = A.begin();
	list<string>::iterator BList = B.begin();
	bool has = false;

	//for each item in A list do things
	for (AList; AList != A.end(); AList++) {
		//reset has so it does not just regester true for all
		has = false;
		//make sure we do not run out of data
		while (BList != B.end()){
			//if they are equal set has to true and leave loop
			if (*AList == *BList) {
				has = true;
				break;
			}
			//if B is greater get rid of front of B so we do not check it anymore
			else if (*AList < *BList) {
				B.pop_front();
				break; 
			}
			//if B is less then A increment B
			else if(*BList<*AList)
			BList++;
		}
		//keeps check of how many things f2f
		if (has == false) {
			check++;
		}
	}
	return check;
}


int
main()
{
	cout << "Find the most isolated number" << endl
		<< "-----------------------------" << endl << endl;
	while (true)
	{
		cout << "Enter size for numbers: ";
		int n = 0;
		cin >> n;
		if (n <= 0)
			break;
		cout << "Enter seed for rand: ";
		unsigned int seed;
		cin >> seed;
		srand(seed);

		// Construct a sorted list of numbers
		Timer get;
		get.start();
		vector<double> numbers = getNums(n, -n, n);
		get.stop();
		cout << "Constructed in " << get() << " seconds"
			<< endl;

		if (n < 10)
			cout << numbers << endl << endl;

		// Report a most isolated isolated number
		Timer time;
		time.start();
		double isolated = mostIsolated(numbers);
		time.stop();
		cout << "The most isolated number is "
			<< isolated << endl
			<< "calculated in " << time() << " seconds"
			<< endl << endl;
	}


	cout << endl << endl;
	cout << "Count the unmatched words" << endl
		<< "-------------------------" << endl << endl;
	while (true)
	{
		cout << "Enter size for words lists: ";
		int n = 0;
		cin >> n;
		if (n <= 0)
			break;
		cout << "Enter word length: ";
		int wordSize;
		cin >> wordSize;
		cout << "Enter alphabet: ";
		string alphabet;
		cin >> alphabet;

		cout << "Enter seed for rand: ";
		unsigned int seed;
		cin >> seed;
		srand(seed);

		// Construct two sorted vectors of words
		Timer get;
		get.start();
		list<string> A = getWords(n, wordSize, alphabet);
		list<string> B = getWords(n, wordSize, alphabet);
		get.stop();
		cout << "Constructed in " << get() << " seconds"
			<< endl;

		if (wordSize * n < 60)
		{
			cout << "A is: " << A << endl
				<< "B is: " << B << endl;
		}

		// Report the number of words in the first sorted list
		//   that are not in the second sorted list
		Timer time;
		time.start();
		int count = unmatched(A, B);
		time.stop();
		cout << count
			<< " words in A were not in B" << endl
			<< "calculated in " << time() << " seconds"
			<< endl << endl;
	}

	return 0;
}