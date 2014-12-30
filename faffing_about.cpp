#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
using namespace std;



class Player
{
private:

	enum status { KO, Poisoned /*more to come for sure.*/ };
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
			cout << this->getStatus() << endl;
		}
	}

public:
	~Player() {};
	Player(string initName){ charName = initName; };
	Player(string initName, int initStr)
	{
		charName = initName;
		strength = initStr;
	}
	Player(string initName, int initStr, int initHitPoints)
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
		this->hitPoints = newHP;
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

class Team
{
private:
	int teamHP = 0, teamSize;
	string teamName;
	Player *members[];

public:
	~Team() {};
	Team(string newName, Player * newMembers[], int newSize)
	{
		teamName = newName;
		teamSize = newSize;
		for (int i = 0; i < teamSize; i++)
		{
			members[i] = newMembers[i];
			teamHP += members[i]->getHP();
		}
	}
	Team(string newName, Player *p1, Player *p2)
	{
		teamName = newName;
		teamSize = 2;
		members[0] = p1;
		members[1] = p2;
		for (int i = 0; i < teamSize; i++)
		{
			teamHP += members[i]->getHP();
		}
	}
	Team(string newName, Player *p1, Player *p2, Player *p3)
	{
		teamName = newName;
		teamSize = 3;
		members[0] = p1;
		members[1] = p2;
		members[2] = p3;
		for (int i = 0; i < teamSize; i++)
		{
			teamHP += members[i]->getHP();
		}
	}

	string getTeamName()
	{
		return teamName;
	}

	void printNames()
	{
		// List each member name
		cout << endl;
		for (int i = 0; i < teamSize; i++)
		{
			cout << teamName << "[" << i << "] is: " << members[i]->getName() << endl;
		}
		cout << endl;
	}
	int getSize()
	{
		return teamSize;
	}
	int getTeamHP()
	{
		resetTeamHP();
		return teamHP;
	}
	Player* randomPlayer()
	{
		Player *randPlayer;
		if (getTeamHP() > 0)
		{
			do
			{				
				randPlayer = this->members[rand() % teamSize];
			} while (randPlayer->getHP() == 0);
			return randPlayer;
		}
	}
	Player* getPlayer(int i)
	{
		return members[i];
	}
	void resetTeamHP()
	{
		teamHP = 0;
		for (int i = 0; i < teamSize; i++)
		{
			teamHP += members[i]->getHP();
		}
	}
};

class Battle
{
	/*
	 * Ideally this will be a (singleton?) mediator class.
	 * Let's see how it goes.
	 */

private:
	Battle(){ srand(time(NULL)); };
	int getRandom(int multiplier)
	{
		//int var = ;
		return rand() % multiplier;
	}
public:

	//static duel* newDuel();


	Battle & newBattle()
	{
		static Battle *globalBattle = new Battle();
		return *globalBattle;
	}
	~Battle(){};
	void attack(Player &attacker, Player &defender)
	{
		//do stuff. Attacky like.
		if (attacker.getHP() > 0 && defender.getHP() > 0)
		{
			int attackVal = getRandom(attacker.getStr());
			cout << "\n\tAttacker " << attacker.getName() << " hits " << defender.getName() << " for " << attackVal << " HP\n";
			defender.setHP(defender.getHP() - attackVal);
			attacker.getHP(1);
			defender.getHP(1);
		}
	}
	void duel(Player &p1, Player &p2)
	{
		// To the death!
		string winner;

		cout << p1.getName() << " Vs. " << p2.getName() << " battle to the death" << endl;

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

	void teamBattle(Team &t1, Team &t2)
	{
		// Allow two teams to battle.  Each team gets a turn,
		// during which each member attacks a random member of 
		// the other team. Hopefully.
		
		while (t1.getTeamHP() > 0 && t2.getTeamHP() > 0)
		{
			for (int i = 0; i < t1.getSize(); i++)
				{
					if (t2.getTeamHP() > 0)
					{
						attack(*t1.getPlayer(i), *t2.randomPlayer());
					}
				}
			
				for (int i = 0; i < t2.getSize(); i++)
				{
					if (t1.getTeamHP() > 0)
					{
						attack(*t2.getPlayer(i), *t1.randomPlayer());
					}
				}
			}
		cout << "\nEnding stats:" << endl;
		cout << t2.getTeamName() << "'s health: " << t2.getTeamHP() << endl;
		cout << t1.getTeamName() << "'s health: " << t1.getTeamHP() << endl;
	}
};


int main()
{
	Battle battle = battle.newBattle();
	Player * pArrTeam1[3];
	
	pArrTeam1[0] = new Player("Cloud", 100, 200);
	pArrTeam1[1] = new Player("Yuffie", 80, 200);
	pArrTeam1[2] = new Player("Red13", 90, 200);
	
	Team *pTeam1 = new Team("Main Characters", pArrTeam1, 3);
	pTeam1->printNames();
	cout << pTeam1->getTeamHP() << endl;
		
	Team *pTeam2 = new Team("Another team", new Player("Sephiroth", 50, 200), new Player("Jenova", 60, 200), new Player("Hojo", 55, 200));
		
	battle.teamBattle(*pTeam1, *pTeam2);
	
	cout << "\nBattle complete, press enter to quit" << endl;
	cin.get();

	return 0;
}