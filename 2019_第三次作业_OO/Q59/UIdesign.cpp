#include<iostream>
#include<string>
#include<vector>
#include<fstream>

using namespace std;

vector<string> split(string input, string seperator) {
	vector<string> res;
	string cutPart = input + seperator;
	int firstPosition;
	while ((firstPosition=cutPart.find(seperator))!=-1)
	{
		res.push_back(cutPart.substr(0, firstPosition));
		cutPart = cutPart.substr(firstPosition + seperator.length());
	}
	return res;
}

void getTest() {
	string input;
	ofstream myout("F:\\UIdesign.txt", ios::app);
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

class Polygon {
private:
	int ploygonId;
	string bianhao;
	double gary;
	int type;		//1:普通矩形;2:反色矩形；3：单红色矩形；
	int r;
	int g;
	int b;
	int rgb[3];
	vector<string> group;
public:
	void addGroup(string g) {
		group.push_back(g);
	}
	bool hasTargetGroup(string tg) {
		bool res=false;
		for (int i = 0; i < this->group.size(); i++)
		{
			if (group[i]==tg)
			{
				res = true;
				break;
			}
		}
		return res;
	}
	Polygon() {
		setRGB(0, 0, 0);
		this->gary = (this->r*0.299 + this->g*0.587 + this->b*0.114);
	}
	void setType(int i) {
		this->type = i;
	}
	int getType() {
		return this->type;
	}
	int* getRGB() {
		return rgb;
	}
	void setRGB(int x, int y, int z) {
		this->rgb[0] = x;
		this->rgb[1] = y;
		this->rgb[2] = z;
		this->r = x;
		this->g = y;
		this->b = z;
		setGary();
	}
	int getPloygonId() {
		return this->ploygonId;
	}
	void setPloygonId(int id) {
		this->ploygonId = id;
		setBianhao();
	}
	void setBianhao() {
		this->bianhao = "P" + to_string(this->getPloygonId());
	}
	string getBianhao() {
		return this->bianhao;
	}
	double getGary() {
		return this->gary;
	}
	void setGary() {
		this->gary = (this->r*0.299 + this->g*0.587 + this->b*0.114);
	}
};

void add(vector<Polygon*>& polygonList, vector<string> instructionList) {
	int type=0;//1:普通矩形;2:反色矩形；3：单红色矩形；
	Polygon *p=new Polygon();
	if (instructionList[1] =="normal" )
	{
		type = 1;
	}
	else if (instructionList[1] =="single" )
	{
		type = 3;
	}
	else if (instructionList[1] == "reverse") {
		type = 2;
	}
	p->setType(type);//设置类型
	string pId = instructionList[2];
	p->setPloygonId(stoi(pId.substr(1,pId.length())));//设置id以及编号
	p->setRGB(0, 0, 0);//题目中说：反色矩形和单红色矩形初始都为黑色
	polygonList.push_back(p);
}

void set(vector<Polygon*>& polygonList, vector<string> instructionList) {
	string tbianhao = instructionList[1];	
	if (tbianhao.at(0)=='P')
	{
		//int tId = stoi(tbianhao.substr(1, tbianhao.length() - 1));
		//Polygon *p;
		for (int i = 0; i < polygonList.size(); i++)
		{
			if (polygonList[i]->getBianhao() == tbianhao)
			{
				//p = polygonList[i];
				int r = stoi(instructionList[2]);
				int g = stoi(instructionList[3]);
				int b = stoi(instructionList[4]);
				//p->setRGB(r, g, b);
				if (polygonList[i]->getType() == 1)
				{
					polygonList[i]->setRGB(r, g, b);
				}
				else if (polygonList[i]->getType() == 2) {
					polygonList[i]->setRGB(255 - r, 255 - g, 255 - b);
				}
				else {
					polygonList[i]->setRGB(r, 0, 0);
				}
				break;
			}
		}
	}
	else if (tbianhao.at(0) == 'G')
	{
		string Tg = tbianhao;
		for (int i = 0; i < polygonList.size(); i++)
		{
			if (polygonList[i]->hasTargetGroup(tbianhao))
			{
				int r = stoi(instructionList[2]);
				int g = stoi(instructionList[3]);
				int b = stoi(instructionList[4]);
				if (polygonList[i]->getType() == 1)
				{
					polygonList[i]->setRGB(r, g, b);
				}
				else if (polygonList[i]->getType() == 2) {
					polygonList[i]->setRGB(255 - r, 255 - g, 255 - b);
				}
				else {
					polygonList[i]->setRGB(r, 0, 0);
				}
				break;
			}
		}
	}

}




void group(vector<Polygon*>& polygonList, vector<string> instructionList) {
	int n = stoi(instructionList[1]);
	string groupId = instructionList[2 + n];
	vector<string> poNameToGroup;
	for (int i = 0; i < n; i++)
	{
		int positon = i + 2;
		poNameToGroup.push_back(instructionList[positon]);
	}
	for (int i = 0; i < n; i++) {
		string name = poNameToGroup[i];
		for (int i = 0; i <polygonList.size() ; i++)
		{
			if (polygonList[i]->getBianhao()==name)
			{
				polygonList[i]->addGroup(groupId);
			}
		}
	}
}

void handleInstruction(vector<Polygon*>& PolygonList, string instruction) {
	int operationCode = 0;//1:add,2:group,3:set
	vector<string> instructionList=split(instruction," ");
	if (instructionList[0]=="Add")
	{
		operationCode = 1;
	}
	else if(instructionList[0] == "Group")
	{
		operationCode = 2;
	}
	else if(instructionList[0] == "Set"){
		operationCode = 3;
	}
	switch (operationCode)
	{
	case 1:
		add(PolygonList, instructionList);
		break;
	case 3:
		set(PolygonList, instructionList);
		break;
	case 2:
		group(PolygonList, instructionList);
		break;
	default:
		break;
	}
}
vector<Polygon*> normalOutPut(vector<Polygon*>& polygonList) {
	for (int i = 0; i < polygonList.size()-1; i++)
	{
		for (int j = 0; j < polygonList.size()-1-i; j++)
		{
			if (polygonList[j]->getPloygonId() > polygonList[j + 1]->getPloygonId()) {
				Polygon *temP = new Polygon();
				temP = polygonList[j];
				polygonList[j] = polygonList[j + 1];
				polygonList[j + 1] = temP;
			}
		}
	}
	return polygonList;
}

vector<Polygon*> garyOutPut(vector<Polygon*>& polygonList) {
	for (int i = 0; i < polygonList.size() - 1; i++)
	{
		for (int j = 0; j < polygonList.size() - 1 - i; j++)
		{
			if (polygonList[j]->getGary() > polygonList[j + 1]->getGary()) {
				Polygon *temP = new Polygon();
				temP = polygonList[j];
				polygonList[j] = polygonList[j + 1];
				polygonList[j + 1] = temP;
			}
			else if (polygonList[j]->getGary() > polygonList[j + 1]->getGary()) {
				if (polygonList[j]->getPloygonId() > polygonList[j + 1]->getPloygonId()) {
					Polygon *temP = new Polygon();
					temP = polygonList[j];
					polygonList[j] = polygonList[j + 1];
					polygonList[j + 1] = temP;
				}
			}
		}
	}
	return polygonList;
}

void start() {
	int n;
	vector<Polygon*> polygonList;
	vector<Polygon*> resToOut;
	cin >> n;
	getchar();
	string instruction;
	for (int i = 0; i < n; i++)
	{
		getline(cin,instruction);
		handleInstruction(polygonList,instruction);
	}
	string outPutType;
	cin >> outPutType;
	if (outPutType=="Normal")
	{
		normalOutPut(polygonList);
		for (int i = 0; i < polygonList.size(); i++)
		{
			cout << polygonList[i]->getBianhao() << " " << polygonList[i]->getRGB()[0] << " " << polygonList[i]->getRGB()[1] << " " << polygonList[i]->getRGB()[2] << endl;
		}
	}
	else if (outPutType=="Gray")
	{
		resToOut=normalOutPut(polygonList);
		garyOutPut(resToOut);
		for (int i = 0; i < resToOut.size(); i++)
		{
			cout << resToOut[i]->getBianhao() << " " << resToOut[i]->getRGB()[0] << " " << resToOut[i]->getRGB()[1] << " " << resToOut[i]->getRGB()[2] << endl;
		}
	}
}

int main() {
	start();
	//getTest();
	system("PAUSE");
	return 0;
}