#include <Windows.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "DxLib.h"

//�摜�ԍ�
#define WALL  2
#define SPACE 3
#define PLAYER 5
#define BOX 0
#define BOX_ON_GOAL 1
#define GOAL 11

#define WIDTH 11 
#define HEIGHT 11 


const int Width = 32;
const int Height = 32;

const int Num = 14;
const int LineNum = 7;
const int ColumnNum = 2;

const enum {
	Wall = -1,
	Space,

	Player,

	Box,
	RedBox,
	GreenBox,

	Goal,
	RedGoal,
	GreenGoal,

	BoxOnGoal,

	Ice,

	Button1,
	Button2,

	Door1 = 15,
	Door2,



	Block = 32,

	Val = 16,

	Up = 8,
	Down = 2,
	Left = 4,
	Right = 6
};

class Level
{
public:
	Level();
	~Level();
	void displayLevel();
	void loadLevel();
private:
	std::vector<std::vector<char>> map;
	int handle[256];//�摜�̃n���h��
};

Level::Level()
{
	//�摜�𕪊�
	LoadDivGraph("field.png", Num, LineNum, ColumnNum, Width, Height, handle);
}

Level::~Level()
{
}
//���[�h�����}�b�v��\��
void Level::displayLevel() {
	for (int y = 0; y < map.size(); y++) {
		for (int x = 0; x < map[y].size(); x++) {
			switch (map[y][x])
			{
			case '#': {
				DrawRotaGraph(Block * x + Val, Block * y + Val, 1, 0, handle[WALL], TRUE);
				break;
			}
			case ' ': {
				DrawRotaGraph(Block * x + Val, Block * y + Val, 1, 0, handle[SPACE], TRUE);
				break;
			}
			case '@': {
				DrawRotaGraph(Block * x + Val, Block * y + Val, 1, 0, handle[SPACE], TRUE);
				DrawRotaGraph(Block * x + Val, Block * y + Val, 1, 0, handle[PLAYER], TRUE);
				break;
			}
			case '+': {
				DrawRotaGraph(Block * x + Val, Block * y + Val, 1, 0, handle[GOAL], TRUE);
				DrawRotaGraph(Block * x + Val, Block * y + Val, 1, 0, handle[PLAYER], TRUE);
				break;
			}
			case '.': {
				DrawRotaGraph(Block * x + Val, Block * y + Val, 1, 0, handle[GOAL], TRUE);
				break;
			}
			case '$': {
				DrawRotaGraph(Block * x + Val, Block * y + Val, 1, 0, handle[BOX], TRUE);
				break;
			}
			case '*': {
				DrawRotaGraph(Block * x + Val, Block * y + Val, 1, 0, handle[BOX_ON_GOAL], TRUE);
				break;
			}
			default:
				break;
			}
		}
	}
}
//�e�L�X�g���烌�x�������[�h
void Level::loadLevel() {
	std::ifstream ifs("map.txt");
	std:: string str; //��s��ǂݍ��܂���p
	if (ifs.fail()) {
		std::cerr << "���s" << std::endl;
		return;
	}
	for (int y = 0; y < HEIGHT;y++) {
		std::vector<char> line; //�����s��ǂݍ��܂���p�̔z��
		getline(ifs, str);
		if (ifs.eof()) break;
		for (int i = 0; i < str.size(); i++) {
			line.push_back(str[i]);
		}
		map.push_back(line);
	}
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE); // �E�B���h�E���[�h�ɐݒ�
	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}

	if (ClearDrawScreen() != 0) {
		return -1;
	}
	if (ProcessMessage() != 0) {
		return -1;
	}
	SetMainWindowText("�q�ɔ�");
	Level level;
	level.loadLevel();
	level.displayLevel();

	if (ScreenFlip() != 0) {
		return -1;
	}

	WaitKey();				// �L�[���͑҂�

	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
}