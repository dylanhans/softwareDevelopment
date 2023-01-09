
#include <string>
#include <cstdlib>
#include <ctime>
#include <iostream>

#include "jumble.h"

using namespace std;

// Exception thrown if attempt is made to create an illegal puzzle
BadJumbleException::BadJumbleException(const string& m) : message(m) {}
string& BadJumbleException::what() { return message; }

// Normal constructor
JumblePuzzle::JumblePuzzle(const string& hidden, const string& difficulty) : hiddenString(hidden) {
	int hiddenSize = hidden.length();
	if (hiddenSize > 10)
		throw BadJumbleException("Supplied string is too large.");
	if (hiddenSize < 3)
		throw BadJumbleException("Supplied string is too small.");

	// string is "just right!"
	char diff = difficulty.at(0);
	if (diff == 'e' || diff == 'E')
		difficultyLevel = 2;
	else if (diff == 'm' || diff == 'M')
		difficultyLevel = 3;
	else if (diff == 'h' || diff == 'H')
		difficultyLevel = 4;
	else
		throw BadJumbleException("Improper difficulty level.");

	size = hiddenSize * difficultyLevel;
	jumble = new charArrayPtr[size];
	for (int i = 0; i < size; i++)
		jumble[i] = new char[size];

	int seed = static_cast<int>(time(nullptr));
	srand(seed);

	generateJumble();
}

// Copy constructor
JumblePuzzle::JumblePuzzle(const JumblePuzzle& jp) {
	size = jp.getSize();
	jumble = copyCharArray(jp.getJumble(), size);
	// These are not really necessary, but they satisfy the pre-compiler
	rowPos = jp.getRowPos();
	colPos = jp.getColPos();
	direction = jp.getDirection();
	difficultyLevel = jp.getDifficulty();
	hiddenString = string(jp.hiddenString);
} // end copy constructor

// Overloaded assignment
JumblePuzzle& JumblePuzzle::operator=(const JumblePuzzle& jp) {
	if (this != &jp) {
		deleteCurrentJumble();
		size = jp.getSize();
		jumble = copyCharArray(jp.getJumble(), jp.getSize());
	}
	return *this;
} // end operator= overloading

// Destructor
JumblePuzzle::~JumblePuzzle() {
	deleteCurrentJumble();
}

// Accessors
int JumblePuzzle::getSize() const { return size; }

charArrayPtr* JumblePuzzle::getJumble() const {
	return copyCharArray(jumble, size);
}

int JumblePuzzle::getRowPos() const { return rowPos; }

int JumblePuzzle::getColPos() const { return colPos; }

char JumblePuzzle::getDirection() const { return direction; }

int JumblePuzzle::getDifficulty() const { return difficultyLevel; }

// Supporting, private member functions.
void JumblePuzzle::deleteCurrentJumble() {
	for (int i = 0; i < size; i++)
		delete[] jumble[i];
	delete[] jumble;
	jumble = nullptr;
}

charArrayPtr* JumblePuzzle::copyCharArray(const charArrayPtr* otherJumble, const int otherSize) const {
	int i, j;
	int sz = otherSize;
	charArrayPtr* puzzle = new charArrayPtr[sz];
	for (i = 0; i < sz; i++)
		puzzle[i] = new char[sz];
	for (i = 0; i < sz; i++)
		for (j = 0; j < sz; j++)
			puzzle[i][j] = otherJumble[i][j];
	return puzzle;
}

int JumblePuzzle::getRandNum(int max) { return rand() % max; }

void JumblePuzzle::generateJumble() {
	int row, col, stringPos;
	string directions("nesw");							// compass directions - no diagonals
	bool fits;
	for (row = 0; row < size; row++)
		for (col = 0; col < size; col++) {
			jumble[row][col] = 97 + getRandNum(26); 	// random letter between a and z
		}
	rowPos = getRandNum(size);
	colPos = getRandNum(size);
	int hiddenSize = size / difficultyLevel;
	jumble[rowPos][colPos] = hiddenString.at(0);
	// Place string at a random position in a random direction.  If it doesn't fit
	// just try another direction.  OK to leave some of the characters from the hidden
	// string in the jumble - it just makes it more difficult!
	do {
		fits = true;
		direction = directions.at(getRandNum(4));
		stringPos = 1;
		if (direction == 'n') {
			row = rowPos - 1;
			while (stringPos < hiddenSize && row >= 0) {
				jumble[row][colPos] = hiddenString.at(stringPos);
				row--;
				stringPos++;
			}
		}
		else if (direction == 'e') {
			col = colPos + 1;
			while (stringPos < hiddenSize && col < size) {
				jumble[rowPos][col] = hiddenString.at(stringPos);
				col++;
				stringPos++;
			}
		}
		else if (direction == 's') {
			row = rowPos + 1;
			while (stringPos < hiddenSize && row < size) {
				jumble[row][colPos] = hiddenString.at(stringPos);
				row++;
				stringPos++;
			}
		}
		else {
			col = colPos - 1;
			while (stringPos < hiddenSize && col >= 0) {
				jumble[rowPos][col] = hiddenString.at(stringPos);
				col--;
				stringPos++;
			}
		}
		if (stringPos < hiddenSize)
			fits = false;
	} while(!fits);
} // end generateJumble()


