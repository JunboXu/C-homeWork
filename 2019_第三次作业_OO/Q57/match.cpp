#include<iostream>
#include<string>
#include<vector>
#include<Windows.h>
#include<fstream>

using namespace std;

void getTest() {
	string input;
	ofstream myout("F:\\match.txt", ios::app);
	while (getline(cin, input))
	{
		myout << input << endl;
	}
	cin >> input;
	myout << "done" << endl;
	myout.close();
}

class Role {
protected:
	int hp;
	int atk;
	bool alive;
	string name;
	bool alreadyUsed = false;
public:
	string getName() {
		return this->name;
	}
	Role(int h,int at){
		this->atk = at;
		this->hp = h;
		this->alive = true;
	}
	virtual void power()=0;
	void subHp(int at) {
		this->hp -= at;
	}
	int getHp() {
		return this->hp;
	}
	int getAtk() {
		return this->atk;
	}
	bool getAlive() {
		return this->alive;
	}
	bool setDeath() {
		this->alive = false;
		return this->alive;
	}
	void setAlreadyUsed() {
		this->alreadyUsed = true;
	}
	bool getAlreadyUsed() {
		return this->alreadyUsed;
	}
	void addHp(int i) {
		this->hp += i;
		this->setAlreadyUsed();
	}
};

class Warrior :public Role {
public:
	Warrior() :Role(12, 2) {
		name = "Warrior";
	};
	
	void power() {
			if (this->alive){
				this->hp += 1;
			}
	}
};

class Magician:public Role {
public:
	Magician():Role(2, 6) { name = "Magician"; };
	void power() {
		if (this->alive)
		{
			if (!this->alreadyUsed)
			{
			}
		}
	}
	void addHp(int i) {
		if (this->alive)
		{
			if (!this->alreadyUsed)
			{
				this->hp += i;
			}
		}
	}

};

class Leader :public Role {
public:
	Leader() :Role(6, 6) { name = "Leader"; };
	void power() {
		if (this->alive)
		{
			this->atk+=1;
		}
	}

};

void getReady(vector<Role*> &l1, vector<Role*> &l2,int num) {
	Role *role;
	for (int i = 0; i < num; i++)
	{
		int roleId;
		cin >> roleId;
		switch (roleId)
		{
		case 1:
			role = new Warrior();
			break;
		case 2:
			role = new Magician();
			break;
		case 3:
			role = new Leader();
			break;
		default:
			break;
		}
		l1.push_back(role);
	}
	for (int i = 0; i < num; i++)
	{
		int roleId;
		cin >> roleId;
		switch (roleId)
		{
		case 1:
			role = new Warrior();
			break;
		case 2:
			role = new Magician();
			break;
		case 3:
			role = new Leader();
			break;
		default:
			break;
		}
		l2.push_back(role);
	}
}

int battle(Role *x, Role *y) {
	int res = 0;//res=1:x胜利；res=2则y胜利；res=3则平局；
	while (x->getAlive()&&y->getAlive())
	{
		x->subHp(y->getAtk());
		y->subHp(x->getAtk());
		if (x->getName() == "Magician")
		{
			if (!x->getAlreadyUsed())
			{
				//x->power()
				x->addHp(y->getAtk());
			}
		}
		if (y->getName() == "Magician")
		{
			if (!y->getAlreadyUsed())
			{
				//y->power();
				y->addHp(x->getAtk());
			}
		}
		if ((x->getHp()<=0)||(y->getHp()<=0))//死了至少一个
		{
			if ((x->getHp()<=0)&&(y->getHp()>0))
			{
				x->setDeath();
				if ((y->getName() == "Warrior") || (y->getName() == "Leader"))
				{
					y->power();
				}
				if (y->getName() == "Magician")
				{
					if (!y->getAlreadyUsed()) {
						//y->power();
						y->addHp(x->getAtk());
					}
				}
				res = 2;
			}
			if ((y->getHp()<=0)&&(x->getHp()>0))
			{
				y->setDeath();
				if ((x->getName() == "Warrior") || (x->getName() == "Leader"))
				{
					x->power();
				}
				if (x->getName() == "Magician")
				{
					//x->power();
					if (!x->getAlreadyUsed())
					{
						x->addHp(y->getAtk());
					}
				}
				res = 1;
			}
			if ((x->getHp() <= 0)&& (y->getHp() <= 0))
			{
				x->setDeath();
				y->setDeath();
				res = 3;
			}
		}
		else//都没死，游戏继续；//需要判断是否发动技能
		{
			if ((x->getName()=="Warrior")|| (x->getName() == "Leader"))
			{
				x->power();
			}
			if ((y->getName() == "Warrior") || (y->getName() == "Leader"))
			{
				y->power();
			}
			if (x->getName() == "Magician")
			{
				if (!x->getAlreadyUsed())
				{
					//x->power()
					x->addHp(y->getAtk());
				}
			}
			if (y->getName() == "Magician")
			{
				if (!y->getAlreadyUsed())
				{
					//y->power();
					y->addHp(x->getAtk());
				}
			}
			x->setAlreadyUsed();
			y->setAlreadyUsed();
		}
	}
	return res;
}


void start() {
	vector<Role*> l1;
	vector<Role*> l2;
	int num;
	bool over = false;
	cin >> num;
	getReady(l1, l2,num);
	//for (int i = 0; i < num; i++)
	//{
	//	cout << "L1["<<i<<"]:"<<l1[i]->getName() << endl;
	//	cout << "L2[" << i << "]:" << l2[i]->getName() << endl;
	//}
	//cout << "ready" << endl;
	int a = 0; int b = 0;
	while (true)
	{
		Role* x = l1[a];
		Role* y = l2[b];
		int battleResult=battle(x, y);
		if (battleResult==1)
		{
			b++;
			if (b<num)
			{
				continue;
			}
			
		}
		else if (battleResult==2)
		{
			a++;
			if (a <num)
			{
				continue;
			}
		}
		else if(battleResult==3)
		{
			a++;
			b++;
			if ((b < num)&&(a<num))
			{
				continue;
			}
		}
		if ((a>=num)||(b>=num))
		{
			if (a<num)
			{
				for (int i = 0; i < num; i++) {
					if (l1[i]->getAlive())
					{
						cout << l1[i]->getName() << " " << l1[i]->getAtk() << " " << l1[i]->getHp() << endl;
					}
				}
			}
			else if (b < num)
			{
				for (int i = 0; i < num; i++) {
					if (l2[i]->getAlive())
					{
						cout << l2[i]->getName() << " " << l2[i]->getAtk() << " " << l2[i]->getHp() << endl;
					}
				}
			}
			else if ((a == num) && (b == num)) {
				cout << "All Dead";
			}
			break;
		}
		else {
			cout << "All Dead" ;
			break;
		}
	}
}


int main() {
	start();
	//getTest();
	//Sleep(1000);
	//system("PAUSE");
	return 0;


}