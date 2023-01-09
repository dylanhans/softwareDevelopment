

#pragma once

#include <string>
#include <vector>
using namespace std;

// The source filename for all the strings is hard coded.
const string SOURCE_FILE("InsultsSource.txt");

// The exception that is thrown if the source file cannot be read, or
// if the saved file cannot be created.
class FileException {
public:
	FileException(const string&);
	string what() const;
private:
	string message;
};

// This exception is thrown if the supplied number of insults is not between
// 1 and 10,000, inclusive
class NumInsultsOutOfBounds {
public:
	NumInsultsOutOfBounds(const string&);
	string what() const;
private:
	string message;
};

// The class that generates the insults in various ways.
class InsultGenerator {
public:
	InsultGenerator();						// An empty constructor.
	void initialize();						// Loads the attribute contents from the source file.
	string talkToMe() const;				// Returns a single insult.
	vector<string> generate(int) const;		// Returns a collection of insults, all different.
	void generateAndSave(string, int) const;// Generates and saves a collection of unique insults in alphabetical order.
private:
	int sourceSize;						// The number of lines in the source file.
	vector<string> part1;				// The phrases in the first column.
	vector<string> part2;				// The phrases in the second column.
	vector<string> part3;				// The phrases in the third column.
	int randInt(int) const;				// An internal method that generates a random integer below a supplied limit.
};

