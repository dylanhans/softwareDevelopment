

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <cstdlib>
#include <time.h>

#include "insultgenerator_netid.h"

using namespace std;

FileException::FileException(const string& m) : message(m) {}
string FileException::what() const { return message; }

NumInsultsOutOfBounds::NumInsultsOutOfBounds(const string& m) : message(m) {}
string NumInsultsOutOfBounds::what() const { return message; }

InsultGenerator::InsultGenerator() : sourceSize(0) {
	srand(time(0));
} // end constructor

void InsultGenerator::initialize() {
	string phrase;
	ifstream fileIn(SOURCE_FILE);
	if (fileIn.fail()) {
		throw FileException("Insults source file: " + SOURCE_FILE + " cannot be read.");
		return;
	}
	sourceSize = 0;
	while (!fileIn.eof()) {
		fileIn >> phrase;
		part1.push_back(phrase);
		fileIn >> phrase;
		part2.push_back(phrase);
		fileIn >> phrase;
		part3.push_back(phrase);
		sourceSize++;
	}
	fileIn.close();
} // end load

int InsultGenerator::randInt(int upperLimit) const {
	return static_cast<int>(1.0 * upperLimit * rand() / RAND_MAX);
} // end randInt

string InsultGenerator::talkToMe() const {
	string insult("Thou ");
	insult += part1.at(randInt(sourceSize));
	insult += " " + part2.at(randInt(sourceSize)) + " ";
	insult += part3.at(randInt(sourceSize)) + "!";
	return insult;
} // end talkToMe

/*
 * This version of generate uses a 3D bool array to create the desired number of insults.
 * Each dimension corresponds to one of the source phrase sections.  If the value of
 * the array at this location is true, then it means "use this phrase at the
 * corresponding index location in the source phrase vector.  The advantage of this
 * algorithm is that it does not require any searching or sorting.  Since the phrases
 * are already in order, the desired number of phrases will be generated in order
 * automatically.
 */
vector<string> InsultGenerator::generate(int numInsults) const {
	int maxNumInsults(10000);
	if (numInsults < 1 || numInsults > maxNumInsults)
		throw NumInsultsOutOfBounds("Not a legal number of insults!");

	vector<string> insults;
	int count(0);
	int num1, num2, num3;
	string insult;
	bool boolArray[sourceSize][sourceSize][sourceSize];

	// Set each location in the 3D array to false to start with.
	for (num1 = 0; num1 < sourceSize; num1++)
		for (num2 = 0; num2 < sourceSize; num2++)
			for (num3 = 0; num3 < sourceSize; num3++)
				boolArray[num1][num2][num3] = false;

	// To generate the desired number of insults, generate three random numbers and
	// if the array location is not already set to true, set it to true, until
	// the desired number of array locations has been set.
	while (count < numInsults) {
		num1 = randInt(sourceSize);
		num2 = randInt(sourceSize);
		num3 = randInt(sourceSize);
		if (!boolArray[num1][num2][num3]) {
			boolArray[num1][num2][num3] = true;
			count++;
		} // end if
	} // end while

	// Create each insult using index locations and add them to a vector.  The collection
	// of insults will be in alphabetical order since the phrases are already in order.
	count = 0;
	for (num1 = 0; num1 < sourceSize && count < numInsults; num1++)
		for (num2 = 0; num2 < sourceSize && count < numInsults; num2++)
			for (num3 = 0; num3 < sourceSize && count < numInsults; num3++)
				if (boolArray[num1][num2][num3]) {
					insult = "Thou " + part1.at(num1) + " " + part2.at(num2) + " " + part3.at(num3) + "!";
					insults.push_back(insult);
					count++;
				} // end if
	return insults;
} // end generate

void InsultGenerator::generateAndSave(string filename, int numInsults) const {
	int count(0);
	int maxNumInsults(10000);
	if (numInsults < 1 || numInsults > maxNumInsults)
		throw NumInsultsOutOfBounds("Not a legal number of insults!");
	vector<string> insults(generate(numInsults));
	ofstream fileOut(filename);
	if (fileOut.fail()) {
		throw FileException("File: " + filename + " cannot be written.");
	}
	while (count < numInsults) {
		fileOut << insults[count] << endl;
		count++;
	}
	fileOut.close();
} // end generateAndSave
