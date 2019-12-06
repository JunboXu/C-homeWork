#include<iostream>
#include<string>
#include<fstream>

using namespace std;

void getTest() {
	string input;
	ofstream myout("F:\\chess.txt", ios::app);
	while (getline(cin,input))
	{
		myout << input << endl;
	}
	cin >> input;
	myout << "done" << endl;
	myout.close();
}

class ChessBoard {
protected:
	int sideLen;
	string board[100][100];
public:
	ChessBoard(int n){
		sideLen = n;
	}
	void setSideLen(int i) {
		sideLen = i;
	}
	void setBoardLocation(int x,int y,string type) {
		board[x][y] = type;
	}
	int checkWin(int m,string type) {
		int res = 0;//1:成功,0: 未成功
		int count = 0;
		//横向判定
		for (int i = 0; i < sideLen; i++)
		{
			for (int j = 0; j < sideLen; j++)
			{
				int position = j;
				if (board[i][position]== type)
				{
					count = 1;
					while ((position -1)>=0)//当前位置左边判定
					{
						position--;
						if (board[i][position] == type) {
							count++;
							if (count==m)
							{
								return 1;//横向，当前位置左边成功,直接返回
							}
							else {
								continue;//连续但是未达到m数量
							}
						}
						else {
							break;//左边不是的话就不连续了，直接跳过，开始看右边
						}
					}
					position = j;
					while ((position +1)<=(sideLen-1))//当前位置右边判定
					{
						position++;
						if (board[i][position] == type) {
							count++;
							if (count == m)
							{
								return 1;
							}
							else {
								continue;
							}
						}
						else {
							count = 0;
							break;
						}
					}
				
				}
				else {
					count = 0;
					continue;
				}
			}
		}
		//竖向判定
		count = 0;
		for (int i = 0; i < sideLen; i++)
		{
			for (int j = 0; j < sideLen; j++)
			{
				int position = j;
				if (board[position][i] == type)
				{
					count = 1;
					while ((position - 1) >= 0)
					{
						position--;
						if (board[position][i] == type) {
							count++;
							if (count == m)
							{
								return 1;//竖向，当前位置上面成功
							
							}
							else {
								continue;//连续但是未达到m数量
							}
						}
						else {
							break;//上面不是的话就不连续了，直接跳过，进入到下面
						}
					}
					position = j;
					while ((position + 1) <= (sideLen - 1))
					{
						position++;
						if (board[position][i] == type) {
							count++;
							if (count == m)
							{
								return 1;
							}
							else {
								continue;
							}
						}
						else {
							count = 0;
							break;
						}
					}
				}
				else {
					count = 0;
					continue;
				}
			}
		}
		//左上右下斜向判定
		count = 0;
		for (int i = 0; i < sideLen; i++)
		{
			for (int j = 0; j < sideLen; j++)
			{
				int positionH = i;
				int positionL = j;
				int position = i;
				if (board[positionH][positionL] == type)
				{
					count = 1;
					while (((positionH - 1) >= 0)&& ((positionL - 1) >= 0))
					{
						positionH--;
						positionL--;
						if (board[positionH][positionL] == type) {
							count++;
							if (count == m)
							{
								return 1;
							}
							else {
								continue;//连续但是未达到m数量
							}
						}
						else {
							break;//左边不是的话就不连续了，直接跳过
						}
					}
					positionH = i;
					positionL = j;
					while (((positionH + 1) <= (sideLen - 1))&&(positionL + 1) <= (sideLen - 1))
					{
						positionH++;
						positionL++;
						if (board[positionH][positionL] == type) {
							count++;
							if (count == m)
							{
								return 1;
							}
							else {
								continue;
							}
						}
						else {
							count = 0;
							break;
						}
					}
				}
				else {
					count = 0;
					continue;
				}

			}
		}
		//右上左下斜向判定	
		count = 0;
		for (int i = 0; i < sideLen; i++)
		{
			for (int j = 0; j < sideLen; j++)
			{
				int positionH = i;
				int positionL = j;
				int position = i;
				if (board[positionH][positionL] == type)
				{
					count = 1;
					while (((positionH - 1) >= 0) && ((positionL + 1) <= (sideLen-1)))
					{
						positionH--;
						positionL++;
						if (board[positionH][positionL] == type) {
							count++;
							if (count == m)
							{
								return 1;
							}
							else {
								continue;//连续但是未达到m数量
							}
						}
						else {
							break;//右上不是的话就不连续了，直接跳过
						}
					}
					positionH = i;
					positionL = j;
					while (((positionH + 1) <= (sideLen - 1)) && ((positionL - 1) >= 0))
					{
						positionH++;
						positionL--;
						if (board[positionH][positionL] == type) {
							count++;
							if (count == m)
							{
								return 1;
							}
							else {
								continue;
							}
						}
						else {
							count = 0;
							break;
						}
					}
				}
				else {
					count = 0;
					continue;
				}

			}
		}
		return res;
}

};

class Chess {
public:
	Chess(string type) {
		name = type;
	}
protected:
	string name;
};


void start() {
	int sideLen, m;
	cin >> sideLen >> m;

	ChessBoard *board = new ChessBoard(sideLen);
	int roundCount = 0;
	int flag = 0;//0:表示“O”的回合,1表示“X回合”
	string type = "O";
	while (true)
	{
		int positionH, positionL;
		cin >> positionH >> positionL;
		if (m == 1)
		{
			cout << "O Success";
			return;
		}
		if (flag%2==0)
		{
			type = "O";
		}
		else {
			type = "X";
		}
		board->setBoardLocation(positionH, positionL, type);
		if ((roundCount<m-1))
		{

		}
		else {
			int result = board->checkWin(m, type);
			if (result == 1)
			{
				cout << type << " Success" << endl;
				return;
			}
			else if (roundCount == m*m) {
				cout << "Dogfall" << endl;
				return;
			}
		}
		roundCount++;
		flag++;

	}
}

int main() {
	//getTest();
	start();
	//system("PAUSE");
	return 0;
}