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

	void show_menu();        //展示菜单目录
	void exit_system();       //退出系统

	~speech_mager();
	//初始化成员属性
	void initspeech();
	//创建选手
	void createpeople(); 
	//成员属性
	//第一轮选手
	vector<int>v1;
	//第二轮选手
	vector<int>v2;
	//最终胜利选手
	vector<int>victory;
	//存放编号和对应选手
	map<int, speaker>m_speaker;
	//记录比赛轮数
	int m_index;
	//开始比赛
	void startspeech();
	//开始抽签
	void speechDraw();
	//比赛
	void speechContest();
	//显示得分
	void showscore();
	//保存记录
	void saverecord();
	//判断文件是否为空
	bool fileisempty;
	// 存放往届记录的容器
	map<int, vector<string>>m_recode;
	//读取记录
	void loadrecord();
	//清空文件
	void clearrecord();
};