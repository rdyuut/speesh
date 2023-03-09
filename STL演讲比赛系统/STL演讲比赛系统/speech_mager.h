#pragma once
#include<iostream>
using namespace std;
#include<vector>
#include<map>
#include"speak.h"
#include<algorithm>
#include<deque>
#include<functional>
#include<numeric>
#include<fstream>
#include<ctime>

class speech_mager {
public:
	speech_mager();

	void show_menu();        //չʾ�˵�Ŀ¼
	void exit_system();       //�˳�ϵͳ

	~speech_mager();
	//��ʼ����Ա����
	void initspeech();
	//����ѡ��
	void createpeople(); 
	//��Ա����
	//��һ��ѡ��
	vector<int>v1;
	//�ڶ���ѡ��
	vector<int>v2;
	//����ʤ��ѡ��
	vector<int>victory;
	//��ű�źͶ�Ӧѡ��
	map<int, speaker>m_speaker;
	//��¼��������
	int m_index;
	//��ʼ����
	void startspeech();
	//��ʼ��ǩ
	void speechDraw();
	//����
	void speechContest();
	//��ʾ�÷�
	void showscore();
	//�����¼
	void saverecord();
	//�ж��ļ��Ƿ�Ϊ��
	bool fileisempty;
	// ��������¼������
	map<int, vector<string>>m_recode;
	//��ȡ��¼
	void loadrecord();
	//����ļ�
	void clearrecord();
};