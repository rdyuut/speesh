#include<iostream>
using namespace std;
#include "speech_mager.h"
int main() {
	srand((unsigned int)time(NULL));
	speech_mager sm;

	//for (map<int, speaker>::iterator it = sm.m_speaker.begin(); it != sm.m_speaker.end();it++) {
	//	cout << (*it).first << "        " << (*it).second.m_name << "          " << (*it).second.m_score[0] << endl;
	//}
	//
	int choice;
	
	while (true) {
		sm.show_menu();               //展示菜单
		cout << "请输入对应功能：" << "";
		cin >> choice;
		switch (choice)
		{
		case 1:                 //开始演讲比赛
			sm.startspeech();
				break;
		case 2:                //查看往届记录
			sm.loadrecord();
			break;
		case 3:               //清空往届记录
			sm.clearrecord();
			break;
		case 0:               //退出比赛系统
			sm.exit_system();
			break;
		default:
			system("cls");
			break;
		}
	}
	system("pause");
	return 0;
}