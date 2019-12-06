#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<map>

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
void getTest() {
	string input;
	ofstream myout("F:\\plane.txt", ios::app);
	int i = 1;
	while (getline(cin, input))
	{
		myout << input << endl;
	}
	cin >> input;
	myout << "第" << i << "个用例：" << "done" << endl;
	i++;
	myout.close();
}

class Plane {
protected:
	int takeOffTime;//起飞用时
	int takeOffShiKe;//起飞时刻
	int taskTime;//任务用时
	int landTime;//降落用时
	int landShiKe;//降落时刻
	int priority;//优先级
	int id;//编号
	string type;//类型
	//int type;//0:战斗机，1：运输机，2：直升机
	//string typeDescription;


public:
	Plane(int i,string t) {
		if (type=="helicopter")
		{
			this->takeOffTime = 1;
			this->taskTime = 0;
			this->landTime = 1;
			this->priority = 3;
		}
		else if (type=="battleplane")
		{
			this->takeOffTime = 2;
			this->taskTime = 0;
			this->landTime = 2;
			this -> priority = 2; 
		}
		else if (type=="transportplane")
		{
			this->takeOffTime = 3;
			this->taskTime = 0;
			this->landTime = 3;
			this->priority = 1;
		}
		this->type = t;
		this->id = i;
	}
	int getTakeOffTime() {
		return this->takeOffTime;
	}
	int getTakeOffShiKe() {
		return this->takeOffShiKe;
	}
	int getTaskTime() {
		return this->taskTime;
	}
	int getLandTime() {
		return this->landTime;
	}
	int getLandShiKe() {
		return this->landShiKe;
	}
	int getId() {
		return this->id;
	}
	string getType() {
		return this->type;
	}
	int getPriority() {
		return this->priority;
	}
	void setTakeOffShiKe(int i) {
		this->takeOffShiKe = i;
	}
	void setLandTime(int i) {
		this->landShiKe = i + this->landTime;
	}
	void setTTLTime(int x,int y,int z){
		this->takeOffTime = x;
		this->taskTime = y;
		this->landTime = z;
	}
	void normalPrint() {
		cout << "p" << id << " " << type << " " << takeOffTime << " " << taskTime << " " << landTime << endl;
	}
	void schedulePrint() {
		cout << "P" << id << " " << takeOffShiKe << " " << landShiKe << endl;
	}

};


class Carrier {
private:
	int tick = 0;
	map<int, Plane*> allPlanes;
	vector<pair<Plane*, int>> arrivedPlaneList;
	vector<pair<Plane*, int>> landFirstPlaneList;
	vector<pair<Plane*, int>> takingOffPlaneList;
	vector<Plane*> landingPlaneList;
	vector<Plane*> taskingPlaneList;
public:
	void set(int id, int takeOffT, int taskT, int landT) {
		allPlanes[id]->setTTLTime(takeOffT, taskT, landT);
	}
	void add(int id, string type) {
		allPlanes[id] = new Plane(id, type);
	}
	void printPlanes(string instruction) {
		if (instruction=="normal")
		{
			map<int, Plane*>::iterator itr = allPlanes.begin();
			while (itr!=allPlanes.end())
			{
				itr->second->normalPrint();
				itr++;
			}
		}
		else if (instruction=="schedule")
		{
			vector<Plane*>::iterator itr = landingPlaneList.begin();
			while (itr!=landingPlaneList.end())
			{
				(*itr)->schedulePrint();
				itr++;
			}
		}
	}
	void join(int id, int tick) {
		vector<pair<Plane*, int>>::iterator itr = takingOffPlaneList.begin();
		Plane* planeToTakeOff = allPlanes[id];
		Plane* tempP;
		while (itr!=takingOffPlaneList.end())
		{
			tempP = itr->first;
			if (tick>itr->second)
			{
				itr++;
				continue;
			}
			else if (tick==itr->second)
			{
				if (planeToTakeOff->getPriority()>tempP->getPriority())
				{
					takingOffPlaneList.insert(itr, pair<Plane*, int>(planeToTakeOff, tick));
					return;
				}
				if (planeToTakeOff->getPriority()==tempP->getPriority())
				{
					if (planeToTakeOff->getId()<tempP->getId())
					{
						takingOffPlaneList.insert(itr, pair<Plane*, int>(planeToTakeOff, tick));
						return;
					}
				}
			}
			else{
				takingOffPlaneList.insert(itr, pair<Plane*, int>(planeToTakeOff, tick));
				return;
			}
			itr++;
		}
		takingOffPlaneList.push_back(pair<Plane*, int>(planeToTakeOff, tick));
	}
	void landfirst(int id, int tick) {
		landFirstPlaneList.push_back(pair<Plane*, int>(allPlanes[id], tick));
	}
	void addArrivedList(Plane* pl, int takeOffT) {
		vector<pair<Plane*, int>>::iterator itr = arrivedPlaneList.begin();
		Plane* tempP;
		takeOffT += pl->getTakeOffTime() + pl->getTaskTime();
		while (itr!=arrivedPlaneList.end())
		{
			tempP = itr->first;
			if (takeOffT<itr->second)
			{
				arrivedPlaneList.insert(itr, pair<Plane*, int>(pl, takeOffT));
				return;
			}
			else if (takeOffT==itr->second)
			{
				if (pl->getPriority()<tempP->getPriority())
				{
					arrivedPlaneList.insert(itr, pair<Plane*, int>(pl, takeOffT));
					return;
				}
				else if (pl->getPriority()>=tempP->getPriority()&&pl->getId()<tempP->getId())
				{
					arrivedPlaneList.insert(itr, pair<Plane*, int>(pl, takeOffT));
					return;
				}
			}
			itr++;
		}
		arrivedPlaneList.push_back(pair<Plane*, int>(pl, takeOffT));
	}
	void takeAwayArrivedPlane(Plane * p) {
		for (int i = 0; i < this->arrivedPlaneList.size(); i++)
		{
			if (this->arrivedPlaneList[i].first->getId()==p->getId())
			{
				arrivedPlaneList.erase(arrivedPlaneList.begin() + i);
				break;
			}
		}
	}

	void cal() {
		int t_p = 0;
		int arrived_p = 0;
		pair<Plane*, int>* takingOffItr;
		pair<Plane*, int>* arrivedItr;
		do {
			for (int itr=landFirstPlaneList.size()-1;  itr>=0; itr--)
			{
				if (landFirstPlaneList[itr].second<=tick)
				{
					landFirstPlaneList[itr].first->setLandTime(tick);
					landingPlaneList.push_back(landFirstPlaneList[itr].first);
					tick += landFirstPlaneList[itr].first->getTakeOffTime();
					takeAwayArrivedPlane(landFirstPlaneList[itr].first);
					landFirstPlaneList.erase(landFirstPlaneList.begin() + itr);
					break;
				}
			}
			if (t_p<takingOffPlaneList.size())
			{
				takingOffItr = &takingOffPlaneList[t_p];
				if (takingOffItr->second<=tick)
				{
					takingOffItr->first->setTakeOffShiKe(tick);
					addArrivedList(takingOffItr->first, tick);
					tick += takingOffItr->first->getTakeOffTime();
					t_p++;
					continue;
				}
			}
			else if (arrived_p<arrivedPlaneList.size())
			{
				arrivedItr = &arrivedPlaneList[arrived_p];
				if (arrivedItr->second<=tick)
				{
					arrivedItr->first->setLandTime(tick);
					landingPlaneList.push_back(arrivedItr->first);
					tick += arrivedItr->first->getLandTime();
					arrived_p++;
					continue;
				}
			}
			tick ++;
		} while (t_p < takingOffPlaneList.size() || arrived_p < arrivedPlaneList.size());
	}

	//vector<Plane*> getPlaneList() {
	//	return this->planeList;
	//}
	//void addPlane(Plane* p) {
	//	this->planeList.push_back(p);
	//}
	//Plane * findPlaneByBianhao(string bianhao) {
	//	vector<Plane *>list =this->planeList;
	//	for (int i = 0; i < list.size(); i++)
	//	{
	//		if (list[i]->getBianhao() == bianhao)
	//		{
	//			return list[i];
	//		}
	//	}
	//}
	//void add(int type, int id, string des) {
	//	switch (type)
	//	{
	//	case 0: {
	//		BattlePlane *p = new BattlePlane();
	//		p->setId(id);
	//		p->setDescription(des);
	//		this->addPlane(p);
	//		break;
	//	}
	//	case 1: {
	//		TransportPlane *p = new TransportPlane();
	//		p->setId(id);
	//		p->setDescription(des);
	//		this->addPlane(p);
	//		break;
	//	}
	//	case 2:
	//	{
	//		Helicopter *p = new Helicopter();
	//		p->setId(id);
	//		p->setDescription(des);
	//		this->addPlane(p);
	//		break;
	//	}
	//	default:
	//		break;
	//	}
	//}
	//void set(int x, int y, int z, string bianhao) {
	//	Plane * p = this->findPlaneByBianhao(bianhao);
	//	p->setTTLTime(x, y, z);
	//}
	//void join(string bianhao, int shike) {}
};

//void handleInstruction(Carrier & c,string instruction) {
//	vector<string> instructionItem = split(instruction, " ");
//	if (instructionItem[0]=="add")
//	{
//		int type;
//		string planeType = instructionItem[1];
//		if (planeType=="battleplane")
//		{
//			type = 0;
//		}
//		else if (planeType == "transportplane")
//		{
//			type = 1;
//		}
//		else if (planeType == "helicopter") {
//			type = 2;
//		}
//
//		string des = instructionItem[2];
//		int id = stoi(des.substr(1, des.length() - 1));
//		c.add(type, id,planeType);
//	}
//	else if (instructionItem[0]=="set")
//	{
//		string bh = instructionItem[1];
//		int x = stoi(instructionItem[2]);
//		int y= stoi(instructionItem[3]);
//		int z = stoi(instructionItem[4]);
//		c.set(x, y, z, bh);
//	}
//	else if (instructionItem[0]=="join")
//	{
//		string bh = instructionItem[1];
//		int shike = stoi(instructionItem[2]);
//		c.join(bh, shike);
//	}
//	else if (instructionItem[0]=="landfirst")
//	{
//
//	}
//}
//
//vector<Plane*> normalOutPut(Carrier& c) {
//	vector<Plane*> list = c.getPlaneList();
//	for (int i = 0; i < list.size() - 1; i++)
//	{
//		for (int j = 0; j < list.size() - 1 - i; j++)
//		{
//			if (list[j]->getId() > list[j + 1]->getId()) {
//				Plane *temP = new Plane();
//				temP = list[j];
//				list[j] = list[j + 1];
//				list[j + 1] = temP;
//			}
//		}
//	}
//	return list;
//}
void start() {
	int n;
	cin >> n;
	getchar();
	string instructionItem;
	vector<string> instruction;
	Carrier c;
	for (int i = 0; i < n; i++)
	{
		int id = 0;
		getline(cin, instructionItem);
		instruction = split(instructionItem, " ");
		if (instruction[0]=="add")
		{
			c.add(stoi(instruction[2].substr(1)), instruction[1]);
		}
		else if (instruction[0]=="set")
		{
			c.set(stoi(instruction[1].substr(1)),stoi(instruction[2]), stoi(instruction[3]), stoi(instruction[4]));
		}
		else if (instruction[0] == "join")
		{
			c.join(stoi(instruction[1].substr(1)), stoi(instruction[2]));
		}
		else if (instruction[0] == "landfirst")
		{
			c.landfirst(stoi(instruction[2].substr(1)), stoi(instruction[1]));
		}
		else if (instruction[0]=="normal")
		{
			break;
		}
		else if(instruction[0]=="schedule"){
			break;
		}
	}
	c.cal();
	c.printPlanes(instruction[0]);

}

int main() {
	//getTest();

	start();
	system("PAUSE");
	return 0;
}