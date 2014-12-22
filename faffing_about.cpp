#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
using namespace std;

enum status { KO, Poisoned /*more to come for sure.*/ };

class player
{
private:
	int strength, hitPoints;
	string charName;
	status playerStatus;

	void knockOut()
	{
		if (getHP() < 0)
		{
			hitPoints = 0;
		}
		if (getHP() == 0)
		{
			setStatus(KO);
			cout << charName << " has died\n";
		}
	}

public:
	~player() {};
	player(string initName){ charName = initName; };
	player(string initName, int initStr)
	{
		charName = initName;
		strength = initStr;
	}
	player(string initName, int initStr, int initHitPoints)
	{
		charName = initName;
		strength = initStr;
		hitPoints = initHitPoints;
	}
	status getStatus()
	{
		return playerStatus;
	}
	void setStatus(status newStatus)
	{
		playerStatus = newStatus;
	}

	void setName(string newName)
	{
		charName = newName;
	}
	string getName()
	{
		return charName;
	}
	int getStr()
	{
		return strength;
	}
	void setStr(int newStr)
	{
		strength = newStr;
	}
	int getHP()
	{
		return hitPoints;
	}
	void getHP(bool pretty)
	{
		if (pretty == 1)
		{
			cout << getName() << " has " << getHP() << " hit points\n";
		}
	}
	void setHP(int newHP)
	{
		hitPoints = newHP;
		knockOut();
	}
	void getStats()
	{
		cout << "Name:\t" << getName() << endl;
		cout << "\tHit Points: " << getHP() << endl;
		cout << "\tStrength: " << getStr() << endl;
		cout << "\tStatus: " << getStatus() << "\n\n";
	}
};

class duel
{
	/*
	 * Ideally this will be a (singleton?) mediator class.
	 * Let's see how it goes.
	 */

private:
	int getRandom(int multiplier)
	{
		//int var = ;
		return rand() % multiplier;
	}
public:
	duel(){ srand(time(NULL)); };
	~duel(){};
	void attack(player &attacker, player &defender)
	{
		//do stuff. Attacky like.
		if (attacker.getHP() > 0 && defender.getHP() > 0)
		{
			int attackVal = getRandom(attacker.getStr());
			cout << "\nAttacker " << attacker.getName() << " hits " << defender.getName() << " for " << attackVal << " HP\n\n";
			defender.setHP(defender.getHP() - attackVal);
			/*if (defender.getHP() <= 0)
			{
				defender.knockOut();
			}*/
			attacker.getHP(1);
			defender.getHP(1);
		}
	}
	void battle(player &p1, player &p2)
	{
		// To the death!
		string winner;

		while (p1.getHP() > 0 && p2.getHP() > 0)
		{
			attack(p1, p2);
			attack(p2, p1);
		}
		if (p1.getHP() > 0){
			winner = p1.getName();
		}
		else if (p2.getHP() > 0)
		{
			winner = p2.getName();
		}
		cout << "The winner is: " << winner << endl;
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