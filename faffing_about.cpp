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
	void getHP(int pretty){
		cout << getName() << " has " << getHP() << " hit points\n";
	}
	void setHitPoints(int newHP){
		hitPoints = newHP;
	}
	void getStats(){
		cout << "Name:\t" << getName() << endl;
		cout << "\tHit Points: " << getHP() << endl;
		cout << "\tStrength: " << getStr() << "\n\n";
	}

};

class duel
	/*
	* Ideally this will be a (singleton?) mediator class.
	* Let's see how it goes.
	*/
{
private:
	int getRandom(int multiplier){
		//int var = ;
		return rand() % multiplier;
	}
public:
	duel(){ srand(time(NULL)); };
	~duel(){};
	void attack(player &attacker, player &defender){
		//do stuff. Attacky like.
		int attackVal = getRandom(attacker.getStr());
		cout << "\nAttacker " << attacker.getName() << " hits " << defender.getName() << " for " << attackVal << " HP\n\n";
		defender.setHitPoints(defender.getHP() - attackVal);
		attacker.getHP(1);
		defender.getHP(1);
	}
	string battle(player &p1, player &p2){
		// To the death!
		string winner;

		while (p1.getHP() > 0 && p2.getHP() > 0){
			attack(p1, p2);
			attack(p2, p1);
		}
		if (p1.getHP() > 0){
			winner = p1.getName();
		}
		else if (p2.getHP() > 0){
			winner = p2.getName();
		}
		return winner;
	}
};

int main()
{
	player c1("Cloud", 100, 7777);
	player c2("Sephiroth", 50, 9999);
	c1.getStats();
	c2.getStats();
	duel duel;
	duel.battle(c1, c2);
	c1.getStats();
	c2.getStats();



	cin.get();

	return 0;
}