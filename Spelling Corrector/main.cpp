#include <iostream>
#include <stdio.h>

#include "SpellingCorrector.h"

using namespace std;

SpellingCorrector corrector;

int main()
{
	corrector.Load("big.txt");
	cout<<corrector.Correct("Monlth")<<endl;
	return 0;
}