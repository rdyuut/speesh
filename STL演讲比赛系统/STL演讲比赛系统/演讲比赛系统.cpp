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
		sm.show_menu();               //չʾ�˵�
		cout << "�������Ӧ���ܣ�" << "";
		cin >> choice;
		switch (choice)
		{
		case 1:                 //��ʼ�ݽ�����
			sm.startspeech();
				break;
		case 2:                //�鿴�����¼
			sm.loadrecord();
			break;
		case 3:               //��������¼
			sm.clearrecord();
			break;
		case 0:               //�˳�����ϵͳ
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