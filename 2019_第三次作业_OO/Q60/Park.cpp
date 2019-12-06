#include<iostream>
#include<string>
#include<fstream>
#include<vector>

using namespace std;

vector<string> split(string input, string seperator) {
	vector<string> res;
	string cutPart = input + seperator;
	int firstPosition;
	while ((firstPosition = cutPart.find(seperator)) != -1)
	{
		res.push_back(cutPart.substr(0, firstPosition));
		cutPart = cutPart.substr(firstPosition + seperator.length());
	}
	return res;
}

class Car {
protected:
	int arriveTime;//到达时刻
	int type;//0代表S车；1代表M车；2代表L车；
	string biaohao;
	double carLen;
	int parkTime;
	int waitTime;
	double fee;
	int remainTime;
	int departTime;
	int position;//Rain 起始位置
public:
	Car(double carLe, int parkT, int waitT, double fe) {
		this->carLen = carLe;
		this->parkTime =parkT;
		this->waitTime = waitT;
		this->fee = fe;
		this->departTime = this->arriveTime + waitT;
	}
	Car() {
		this->carLen = 0;
		this->parkTime = 0;
		this->waitTime = 0;
		this->fee = 0;
	}
	int getPosition() {
		return this->position;
	}
	void setPosition(int p) {
		this->position = p;
	}
	void decreaseTime() { this->remainTime--; }
	int getRemainTime() {
		return this->remainTime;
	}
	void setRemainTime(int i) {
		if (i==1)
		{
			this->remainTime = parkTime;
		}
		else {
			remainTime = waitTime;
		}
	}
	int getDepartTime() {
		return this->departTime;
	}
	int getArriveTime() {
		return this->arriveTime;
	}
	void setArriveTime(int i) {
		this->arriveTime = i;
		this->departTime = this->arriveTime + this->parkTime;
	}
	void setBiaohao(string bh) {
		this->biaohao = bh;
	}
	string getBiaohao() {
		return this->biaohao;
	}
	int getType() {
		return this->type;
	}
	double getCarLen() {
		return this->carLen;
	}
	int getParkTime() {
		return this->parkTime;
	}
	int getWaitTime() {
		return this->waitTime;
	}
	double getFee() {
		return this->fee;
	}
};

class Scar:public Car {
public:
	Scar() :Car(1, 3, 1, 1.5) {
		this->type = 0;
	}
};

class Mcar :public Car {
public:
	Mcar() :Car(1.5, 2, 2, 3) {
		this->type = 1;
	}
};

class Lcar :public Car {
public:
	Lcar() :Car(2, 1, 3, 4.5) {
		this->type = 2;
	}
};

class ParkLot {
private:
	vector<Car*> waitCarList;
	vector<Car*> successParkedList;
	double alreadyOccupyLen;
	int parkUnitNum;
	int waitListLen;
	double totalFeeSunny=0;
public:
	double getTotalFee() {
		return this->totalFeeSunny;
	}
	vector<Car*> getSuccessParkedList() {
		return this->successParkedList;
	}
	int getWaitListLen(){
		return this->waitListLen;
	}
	vector<Car*> getWaitCarList() {
		return this->waitCarList;
	}
	int getParkUnitNum() {
		return this->parkUnitNum;
	}
	void setParkUnitNum(int i){
		this->parkUnitNum = i;
	}
	void addCarToWaitList(Car* c) {
		c->setRemainTime(2);
		waitListLen++;
		this->waitCarList.push_back(c);
	}
	void addCarToSuccessParkedList(Car *c) {
		c->setRemainTime(1);
		this->successParkedList.push_back(c);
		this->alreadyOccupyLen += c->getCarLen();
	}
	void flushPark(int position) {//停车队列往前走；
		this->alreadyOccupyLen -= successParkedList[position]->getCarLen();
		for (int i = position; i < successParkedList.size()-1; i++)
		{
			successParkedList[i] = successParkedList[i + 1];
		}
		successParkedList.pop_back();
	}
	void flushWait(int position) {
		for (int i = position; i < waitCarList.size()-1; i++)
		{
			waitCarList[i] = waitCarList[i + 1];
		}
		waitCarList.pop_back();
	}//等待队列往前走
	void moveOn() {
		for (int i = 0; i < this->waitCarList.size(); i++)
		{
			waitCarList[i]->decreaseTime();
		}
		for (int i = 0; i < this->successParkedList.size(); i++)
		{
			successParkedList[i]->decreaseTime();
		}
	}
	void addFunction(Car * c) {
		if (canIn(c)&&(this->waitCarList.size()==0))//当该车进来时，如果可以停车场可容纳，并且前面没有等待的，则可以进入
		{
			addCarToSuccessParkedList(c);
		}
		else {
			addCarToWaitList(c);
		}
	}
	bool canIn(Car* c) {
		if (c->getCarLen()+this->alreadyOccupyLen<=this->parkUnitNum)
		{
			return true;
		}
		else { return false; }
	}
	void printAll() {
		if ((this->successParkedList.size() == 0) && (this->waitCarList.size() == 0))
		{
			return;
		}
		if ((this->successParkedList.size()==0))
		{
			cout << "null" << endl;
			return;
		}
		for (int i = 0; i < this->successParkedList.size(); i++)
		{
			cout << successParkedList[i]->getBiaohao();
			if (i!=successParkedList.size()-1)
			{
				cout << " ";
			}
		}
		cout << endl;
	}
	void checkIfTakeOut() {
		vector<int> park;
		vector<int> wait;
		for (int i = 0; i < this->successParkedList.size(); i++)
		{
			if (successParkedList[i]->getRemainTime()==0)
			{
				park.push_back(i);
				this->totalFeeSunny += successParkedList[i]->getFee();
			}
		}
		for (int i = 0; i < this->waitCarList.size(); i++)
		{
			if (waitCarList[i]->getRemainTime()==0)
			{
				wait.push_back(i);
			}
		}
		while (park.size() != 0) 
		{
			flushPark(park.back());
			park.pop_back();
		}
		while (wait.size()!=0)
		{
			flushWait(wait.back());
			wait.pop_back();
		}
	}
	void adjust() {
		if (waitCarList.size()==0)
		{
			return;
		}
		if (canIn(waitCarList[0]))
		{
			addCarToSuccessParkedList(waitCarList[0]);
			flushWait(0);
		}
	}
};

class RainnyParkLot {
private:
	double totalFee = 0;
	int size;
	int* position;
	vector<Car *> successParkedCarList;
	vector<Car *> waitList;
public:
	RainnyParkLot(int s) {
		position = new int[s * 2];//消除小数影响
		size = s;
		for (int i = 0; i < s * 2; i++)
		{
			position[i] = -1;
		}
	}
	double getTotalFee() {
		return this->totalFee;
	}
	vector<Car *> getSuccessParkedCarList(){
		return this->successParkedCarList;
	}
	vector<Car *> getWaitList() {
		return this->waitList;
	}
	void addPark(Car* c, int pos) {
		successParkedCarList.push_back(c);
		for (int i = successParkedCarList.size()-2;i>=0;i--)
		{
			if (successParkedCarList[i]->getPosition()>pos)
			{
				successParkedCarList[i + 1] = successParkedCarList[i];
				successParkedCarList[i] = c;
			}
			else { 
				break; 
			}
		}
		c->setPosition(pos);
		c->setRemainTime(1);
		int id = stoi(c->getBiaohao().substr(1, c->getBiaohao().length() - 1));
		for (int j = 0; j < c->getCarLen(); j++)
		{
			this->position[pos + j] = id;
		}
	}

	void addWait(Car * c) {
		c->setRemainTime(2);
		this->waitList.push_back(c);
	}

	void moveOn() {
		for (int i = 0; i < this->successParkedCarList.size(); i++)
		{
			this->successParkedCarList[i]->decreaseTime();
		}
		for (int i = 0; i < this->waitList.size(); i++)
		{
			this->waitList[i]->decreaseTime();
		}
	}

	void flushPark(int positionP) {
		Car *c = successParkedCarList[positionP];
		int start = c->getPosition();
		for (int i = 0; i < c->getCarLen(); i++)
		{
			this->position[start + i] = -1;
		}
		for (int i = positionP; i < successParkedCarList.size()-1; i++)
		{
			successParkedCarList[i] = successParkedCarList[i + 1];
		}
		successParkedCarList.pop_back();
	}

	void flushWait(int position) {
		for (int i = position; i <waitList.size()-1 ; i++)
		{
			waitList[i] = waitList[i + 1];
		}
		waitList.pop_back();
	}

	void checkIfTakeOut() {
		vector<int> park;
		vector<int> wait;
		for (int i = 0; i < this->successParkedCarList.size(); i++)
		{
			if (successParkedCarList[i]->getRemainTime()==0)
			{
				park.push_back(i);
				this->totalFee += successParkedCarList[i]->getFee();
			}
		}
		for (int  i = 0; i < waitList.size(); i++)
		{
			if (waitList[i]->getRemainTime()==0)
			{
				wait.push_back(i);
			}
		}
		while (park.size()!=0)
		{
			flushPark(park.back());
			park.pop_back();
		}
		while (wait.size() != 0) {
			flushWait(wait.back());
			wait.pop_back();
		}
	}

	void printAll() {

		if ((this->successParkedCarList.size()==0)&&(this->waitList.size()==0))
		{
			return;
		}	
		if (successParkedCarList.size() == 0)
		{
			cout << "null"<<endl;
			return;
		}
		for (int i = 0; i < successParkedCarList.size(); i++)
		{
			cout << successParkedCarList[i]->getBiaohao();
			if (i!=successParkedCarList.size()-1)
			{
				cout << " ";
			}
		}
		cout << endl;
	}
	int canIn(Car *c) {
		int carLen = c->getCarLen();
		int lens = 0;
		for (int i = 0; i < (this->size)*2; i++)
		{
			if (this->position[i]==-1)
			{
				lens++;
			}
			else {
				lens = 0;
			}
			if (lens>=carLen)
			{
				int res = i + 1 - carLen;
				return res;
			}
		}
		return -1;
	}
	void adjust() {
		if (waitList.size()==0)
		{
			return;
		}
		int po = canIn(waitList[0]);
		while (po!=-1)
		{
			addPark(waitList[0], po);
			flushWait(0);
			if (waitList.size()==0)
			{
				break;
			}
			po = canIn(waitList[0]);
		}
	}
	void addFunction(Car *c) {
		int p = canIn(c);
		if ((p!=-1)&&(waitList.size()==0))
		{
			this->addPark(c, p);
		}
		else {
			addWait(c);
		}
	}
};
void start() {
	int n;
	string tianqi;
	cin >> n >> tianqi;
	ParkLot *pt = new ParkLot();
	RainnyParkLot *Rainnylot = new RainnyParkLot(n);
	pt->setParkUnitNum(n);
	string instruction;
	if (tianqi=="sunny")
	{
		getline(cin, instruction);
		while (instruction!="end")
		{
			pt->printAll();
			pt->checkIfTakeOut();
			pt->adjust();
			vector<string> instructionItem = split(instruction, " ");
			if (instructionItem[0] == "in")
			{
				string type = instructionItem[1];
				string bianhao = instructionItem[2];
				//int arriveT = pt->getWaitListLen()+1;
				if (type == "S")
				{
					Scar* s = new Scar();
					//s->setArriveTime(arriveT);
					s->setBiaohao(bianhao);
					pt->addFunction(s);
				}
				else if (type == "M")
				{
					Mcar* m = new Mcar();
					m->setBiaohao(bianhao);
					//m->setArriveTime(arriveT);
					pt->addFunction(m);
				}
				else if (type == "L")
				{
					Lcar* l = new Lcar();
					l->setBiaohao(bianhao);
					//l->setArriveTime(arriveT);
					pt->addFunction(l);
				}
			}
			pt->moveOn();
			getline(cin, instruction);
		}
		while ((pt->getSuccessParkedList().size()!=0)||(pt->getWaitCarList().size()!=0))
		{
			pt->printAll();
			pt->checkIfTakeOut();
			pt->adjust();
			pt->moveOn();
		}
		cout << "null" << endl;
		cout << pt->getTotalFee() << endl;
		//dealWithWaitList()
	}
	else if (tianqi == "rainy")
	{
		getline(cin, instruction);
		while (instruction != "end")
		{
			vector<string> instructionItem = split(instruction, " ");
			Rainnylot->printAll();
			Rainnylot->checkIfTakeOut();
			Rainnylot->adjust();
			
			if (instructionItem[0] == "in")
			{
				string type = instructionItem[1];
				string bianhao = instructionItem[2];
				//int arriveT = pt->getWaitListLen()+1;
				if (type == "S")
				{
					Scar* s = new Scar();
					//s->setArriveTime(arriveT);
					s->setBiaohao(bianhao);
					Rainnylot->addFunction(s);
				}
				else if (type == "M")
				{
					Mcar* m = new Mcar();
					m->setBiaohao(bianhao);
					//m->setArriveTime(arriveT);
					Rainnylot->addFunction(m);
				}
				else if (type == "L")
				{
					Lcar* l = new Lcar();
					l->setBiaohao(bianhao);
					//l->setArriveTime(arriveT);
					Rainnylot->addFunction(l);
				}
			}
			Rainnylot->moveOn();
			getline(cin, instruction);
		}
		while ((Rainnylot->getSuccessParkedCarList().size() != 0) || (Rainnylot->getWaitList().size() != 0))
		{
			Rainnylot->printAll();
			Rainnylot->checkIfTakeOut();
			Rainnylot->adjust();
			Rainnylot->moveOn();
		}
		cout << "null" << endl;
		cout << Rainnylot->getTotalFee() << endl;
		//dealWithWaitList()
	}
}

int main() {
	start();
	system("PAUSE");
	return 0;
}