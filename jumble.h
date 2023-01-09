

#pragma once

#include <string>
using namespace std;

typedef char* charArrayPtr;

class BadJumbleException {
public:
	BadJumbleException(const string&);
	string& what();
private:
	string message;
};

class JumblePuzzle {
public:
	JumblePuzzle(const string&, const string&);
	JumblePuzzle(const JumblePuzzle&);
	~JumblePuzzle();
	JumblePuzzle& operator=(const JumblePuzzle&);
	int getSize() const;
	int getRowPos() const;
	int getColPos() const;
	char getDirection() const;
	int getDifficulty() const;
	charArrayPtr* getJumble() const;
private:
	int size;
	string hiddenString;
	charArrayPtr* jumble;
	int rowPos;
	int colPos;
	char direction;
	int difficultyLevel;	// 2, 3 or 4
	charArrayPtr* copyCharArray(const charArrayPtr*, const int) const;
	int getRandNum(int);
	void deleteCurrentJumble();
	void generateJumble();
};

