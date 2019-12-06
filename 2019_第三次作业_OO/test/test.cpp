#include<stdio.h>
#include<vector>
#include<string>
#include<iostream>
using namespace std;
vector<string> split(string str, const string pattern) {
	str += pattern;
	string::size_type pos;
	vector<string> result;
	for (int i = 0; i < str.size(); i++) {
		pos = str.find(pattern, i);
		if (pos < str.size() && pos != str.npos) {
			string temp = str.substr(i, pos - i);
			result.push_back(temp);
			i = pos + pattern.size() - 1;
		}
	}
	return result;
};
bool stringEquals(const string string1, const string string2) {
	if (string1.size() != string2.size()) {
		return false;
	}
	else {
		for (int i = 0; i < string1.size(); i++) {
			if (string1[i] != string2[i]) {
				return false;
			}
		}
	}
	return true;
}
int stringToInt(string x) {
	string temp = x.substr(1, x.size() - 1);
	int no = stoi(temp);
	return no;
}
class Car {
protected:
	int pos;//雨天的起始位置信息
	int occupyLength;//占用长度
	int parkTime;//停车时长
	int waitTime;//等候时长
	float fee;//停车费;
	string id;//id
	int remainTime;//等候或停车的用时
public:
	void setPos(int po) { pos = po; };
	int getPos() { return pos; };
	string getId() { return id; };
	float getFee() { return fee; };
	//看是不是要移除队列，1的话出队列
	int getLength() { return occupyLength; };
	void decreaseTime() { remainTime--; };
	int getRemTime() { return remainTime; };
	void setRemainTime(int flag) {//设置剩余等待时间
		if (flag == 1) { remainTime = parkTime; }
		else
		{
			remainTime = waitTime;
		}
	};
};
class SCar :public Car {
public:
	//车长*2防止下一个1.5 其他没什么好解释的
	SCar(string no) { this->id = no; this->occupyLength = 2; this->parkTime = 3; this->waitTime = 1; this->fee = 1.5; };
};
class MCar :public Car {
public:
	//车长*2防止下一个1.5 其他没什么好解释的
	MCar(string no) { this->id = no; this->occupyLength = 3; this->parkTime = 2; this->waitTime = 2; this->fee = 3; };
};
class LCar :public Car {
public:
	//车长*2防止下一个1.5 其他没什么好解释的
	LCar(string no) { this->id = no; this->occupyLength = 4; this->parkTime = 1; this->waitTime = 3; this->fee = 4.5; };
};
class Sunny {
	float totalFee = 0.0;
	int totalLength;
	int pLength = 0;//已占用的长度
	int pNum = 0;
	vector<Car *> parkVect;
	int wNum = 0;//实际等待个数
	vector<Car *> waitVect;
public:
	Sunny(int size) { this->totalLength = size * 2; };
	//进入停车库，车辆停车倒计时开始，入栈，停车数量++，长度++
	void addPark(Car * car) {
		car->setRemainTime(1);
		parkVect.push_back(car);
		pNum++;
		pLength += car->getLength();
	};
	//进入等待队列，车辆等待倒计时开始，入栈，等待数量++
	void addWait(Car * car) {
		car->setRemainTime(2);
		waitVect.push_back(car);
		wNum++;
	};
	void flushPark(int pos) {//停车队列向前进位
		pLength -= parkVect[pos]->getLength();
		for (int i = pos; i < parkVect.size() - 1; i++) {
			parkVect[i] = parkVect[i + 1];
		}
		parkVect.pop_back();
		pNum--;
	};
	void flushWait(int pos) {//等待队列向前进位
		for (int i = pos; i < waitVect.size() - 1; i++) {
			waitVect[i] = waitVect[i + 1];
		}
		waitVect.pop_back();
		wNum--;
	};
	//在这个时间进行状态检查,删除都为0的车
	void checkState() {
		vector<int> pPos;
		vector<int>wPos;
		for (int i = 0; i < parkVect.size(); i++) {
			if (parkVect[i]->getRemTime() == 0) {//返回0说明不行了
				pPos.push_back(i);
				this->totalFee += parkVect[i]->getFee();
			}
		}
		for (int i = 0; i < waitVect.size(); i++) {
			if (waitVect[i]->getRemTime() == 0) {//返回0说明不行了
				wPos.push_back(i);
			}
		}
		while (pPos.size() != 0) {
			flushPark(pPos.back());
			pPos.pop_back();
		}
		while (wPos.size() != 0) {
			flushWait(wPos.back());
			wPos.pop_back();
		}
	}
	void allMoveOn() {
		for (auto ele : parkVect) {
			ele->decreaseTime();
		}
		for (auto ele : waitVect) {
			ele->decreaseTime();
		}
	}
	bool canAfford(int length) {
		return (this->pLength + length) <= this->totalLength;
	}
	//集成addPark和addWait，决定车辆直接加入停车库还是等待队列
	void addFunc(Car * car) {
		if (canAfford(car->getLength()) && (waitVect.size() == 0)) {
			addPark(car);
		}
		else {
			addWait(car);
		}
	}
	void printAllCar() {
		if ((parkVect.size() == 0) && (waitVect.size() == 0)) {
			return;
		}
		if (parkVect.size() == 0) {
			cout << "null" << endl;
			return;
		}
		for (int i = 0; i < parkVect.size(); i++) {
			cout << parkVect[i]->getId();
			if (i != parkVect.size() - 1) {
				cout << ' ';
			}
		}
		cout << endl;
	}
	void adjust() {
		if (waitVect.size() == 0) { return; }//为0说明不需要调整
		if (canAfford(waitVect[0]->getLength())) {
			addPark(waitVect[0]);
			flushWait(0);
		}

	}
	void start() {
		string command;
		getline(cin, command);
		while (!stringEquals(command, "end")) {
			vector<string> cmdPieces = split(command, " ");
			printAllCar();
			checkState();
			adjust();
			if (stringEquals(cmdPieces[1], "S")) {
				addFunc(new SCar(cmdPieces[2]));
			}
			else if (stringEquals(cmdPieces[1], "M")) {
				addFunc(new MCar(cmdPieces[2]));
			}
			else {
				addFunc(new LCar(cmdPieces[2]));
			}
			allMoveOn();
			getline(cin, command);
		}
		while ((parkVect.size() != 0) || (waitVect.size() != 0)) {
			printAllCar();
			checkState();
			adjust();
			allMoveOn();
		}
		cout << "null" << endl;
		cout << totalFee << endl;
		//system("pause");
	}
};
//雨天的话需要将pLength变成数组。这里采用占位法
class Rainy {
	float totalFee = 0.0;
	int* position;
	int size;
	vector<Car *> parkVect;
	vector<Car *> waitVect;
public:
	Rainy(int siz) {
		position = new int[siz * 2];
		size = siz;
		for (int i = 0; i < size * 2; i++) {
			position[i] = -1;
		}
	};
public:
	//占用postion数组中的位置，调整parkVect中的顺序
	void addPark(Car* car, int pos) {
		parkVect.push_back(car);
		for (int i = parkVect.size() - 2; i >= 0; i--) {
			if (parkVect[i]->getPos() > pos) {//说明在后面
				parkVect[i + 1] = parkVect[i];
				parkVect[i] = car;
			}
			else {
				break;
			}
		}
		car->setPos(pos);
		car->setRemainTime(1);
		int no = stringToInt(car->getId());
		for (int k = 0; k < car->getLength(); k++) {
			position[pos + k] = no;
		}
	}
	void addWait(Car* car) {
		car->setRemainTime(2); waitVect.push_back(car);
	}
	//干两件事，去掉他在postion中占用的位置，并且调整parkVect
	void flushPark(int posInParkVec) {
		Car * current = parkVect[posInParkVec];
		int begin = current->getPos();
		for (int i = 0; i < current->getLength(); i++) {
			position[begin + i] = -1;
		}
		for (int i = posInParkVec; i < parkVect.size() - 1; i++) {
			parkVect[i] = parkVect[i + 1];
		}
		parkVect.pop_back();
	};
	void flushWait(int pos) {
		for (int i = pos; i < waitVect.size() - 1; i++) {
			waitVect[i] = waitVect[i + 1];
		}
		waitVect.pop_back();
	}
	void checkState() {
		vector<int> pPos;
		vector<int>wPos;
		for (int i = 0; i < parkVect.size(); i++) {
			if (parkVect[i]->getRemTime() == 0) {//返回0说明不行了
				pPos.push_back(i);
				this->totalFee += parkVect[i]->getFee();
			}
		}
		for (int i = 0; i < waitVect.size(); i++) {
			if (waitVect[i]->getRemTime() == 0) {//返回0说明不行了
				wPos.push_back(i);
			}
		}
		while (pPos.size() != 0) {
			flushPark(pPos.back());
			pPos.pop_back();
		}
		while (wPos.size() != 0) {
			flushWait(wPos.back());
			wPos.pop_back();
		}
	}
	void allMoveOn() {
		for (auto ele : parkVect) {
			ele->decreaseTime();
		}
		for (auto ele : waitVect) {
			ele->decreaseTime();
		}
	}
	int canAfford(int cLength) {
		int lens = 0;
		for (int i = 0; i < size * 2; i++) {
			if (position[i] == -1) {
				lens++;
			}
			else {
				lens = 0;
			}
			if (lens >= cLength) {
				return (i + 1 - cLength);
			}
		}
		return -1;//免得和0混淆

	}
	void addFunc(Car * car) {
		int posit = canAfford(car->getLength());
		if ((posit != -1) && (waitVect.size() == 0)) {
			addPark(car, posit);
		}
		else {
			addWait(car);
		}
	}
	void printAllCar() {
		if ((parkVect.size() == 0) && (waitVect.size() == 0)) {
			return;
		}
		if (parkVect.size() == 0) {
			cout << "null" << endl;
			return;
		}
		for (int i = 0; i < parkVect.size(); i++) {
			cout << parkVect[i]->getId();
			if (i != parkVect.size() - 1) {
				cout << ' ';
			}
		}
		cout << endl;
	}
	void adjust() {
		if (waitVect.size() == 0) { return; }
		int pos = canAfford(waitVect[0]->getLength());
		while (pos != -1) {
			addPark(waitVect[0], pos);
			flushWait(0);
			if (waitVect.size() == 0) {
				break;
			}
			pos = canAfford(waitVect[0]->getLength());
		}
	}
	void start() {
		string command;
		getline(cin, command);
		while (!stringEquals(command, "end")) {
			vector<string> cmdPieces = split(command, " ");
			printAllCar();
			checkState();
			adjust();
			if (stringEquals(cmdPieces[1], "S")) {
				addFunc(new SCar(cmdPieces[2]));
			}
			else if (stringEquals(cmdPieces[1], "M")) {
				addFunc(new MCar(cmdPieces[2]));
			}
			else {
				addFunc(new LCar(cmdPieces[2]));
			}
			allMoveOn();
			getline(cin, command);
		}
		while ((parkVect.size() != 0) || (waitVect.size() != 0)) {
			printAllCar();
			checkState();
			adjust();
			allMoveOn();
		}
		cout << "null" << endl;
		cout << totalFee << endl;
		system("pause");
	}
};
int main() {
	string command;
	getline(cin, command);
	vector<string> pieces = split(command, " ");
	if (stringEquals(pieces[1], "sunny")) {
		Sunny* sun = new Sunny(stoi(pieces[0]));
		sun->start();
	}
	else {
		Rainy* rain = new Rainy(stoi(pieces[0]));
		rain->start();
	}
};