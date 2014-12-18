#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
using namespace std;


class player
{
private:
	int strength, hitPoints;
	string charName;

public:
	~player() {};
	player(string initName){ charName = initName; };
	player(string initName, int initStr){
		charName = initName;
		strength = initStr;
	}
	player(string initName, int initStr, int initHitPoints){
		charName = initName;
		strength = initStr;
		hitPoints = initHitPoints;
	}

	void setName(string newName){
		charName = newName;
	}
	string getName(){
		return charName;
	}
	int getStr(){
		return strength;
	}
	void setStr(int newStr){
		strength = newStr;
	}
	int getHP(){
		return hitPoints;
	}
	void setHitPoints(int newHP){
		hitPoints = newHP;
	}

};

class duel
	/*
	* Ideally this will be a (singleton?) mediator class.
	* Let's see how it goes.
	*/
{
private:

public:
	duel(){ srand(time(NULL)); };
	~duel(){};
	void attack(player attacker, player defender){
		//do stuff. Atacky like.
	}
	int getRandom(int mult){
		int var = rand() % mult;
		return var;
	}
};

int main()
{
	player c1("Cloud", 100, 9999);
	cout << "Player name: " << c1.getName() << endl;
	cout << "\tHit Points: " << c1.getHP() << endl;
	cout << "\tStrength: " << c1.getStr() << endl;

	duel duel;
	cout << duel.getRandom(100);



	cin.get();

	return 0;
}