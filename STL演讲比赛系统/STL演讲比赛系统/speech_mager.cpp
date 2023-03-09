#include"speech_mager.h"
void myprint(int val) {            //for_each 使用的仿函数
	cout << val << "  ";
}

speech_mager::speech_mager() {    //构造函数
	//初始化属性
	this->initspeech();
	//创建12名选手
	this->createpeople();
	//读取历史记录
	//this->loadrecord();
}

void speech_mager::show_menu() {
	cout << "*****************************************" << endl;
	cout << "************欢迎参加演讲比赛*************" << endl;
	cout << "************1. 开始演讲比赛 *************" << endl;
	cout << "************2. 查看往届记录 *************" << endl;
	cout << "************3. 清空往届记录 *************" << endl;
	cout << "************0. 退出比赛系统 *************" << endl;
	cout << "*****************************************" << endl;
	cout << endl;
}

//退出功能
void speech_mager::exit_system() {
	cout << "欢迎下次使用" << endl;
	system("pause");
	exit(0);
}

//初始化属性
void speech_mager::initspeech() {
	this->v1.clear();       //讲义上    this->v1.clear()
	this->v2.clear();
	this->victory.clear();
	this->m_recode.clear();
	m_index = 1;
}

//创建选手
void speech_mager::createpeople() {
	string nameseed = "ABCDEFGHIJKL";
	for (int i = 0; i < nameseed.size(); i++) {
		string name = "选手";
		name += nameseed[i];

		speaker sp;
		sp.m_name = name;
		//给两轮得分赋值
		for (int j = 0; j < 2; j++) {
			sp.m_score[j] = 0;
			//创建选手编号放入v1容器
		}
		v1.push_back(i + 10001);
		this->m_speaker.insert(make_pair(i + 10001, sp));//map<int, speaker>m_speaker;
	}
}
//开始比赛
void speech_mager::startspeech() {

	//第一轮比赛
	
	   //1. 抽签
	this->speechDraw();
	   //2.比赛
	this->speechContest();
	   //3，显示晋级结果
	this->showscore();
	//第二轮比赛
	m_index++;
	   //1. 抽签
	this->speechDraw();
	   //2.比赛
	this->speechContest();
	   
	   //3，显示晋级结果
	this->showscore();
	   //4 .保存分数到文件
	this->saverecord();

	cout << "本届比赛已完成" << endl;
	system("pause");
	system("cls");

}

     //抽签
void speech_mager::speechDraw() {
	cout << "第" << m_index << "轮选手开始抽签" << endl;
	cout << "------------------------" << endl;
	cout << "抽签顺序如下" << endl;
	if (m_index == 1) {
		random_shuffle(v1.begin(), v1.end());
		for_each(v1.begin(), v1.end(), myprint);               //遍历
		cout << endl;
	}
	else {
		random_shuffle(v2.begin(), v2.end());            
		for_each(v2.begin(), v2.end(), myprint);                  //遍历
		cout << endl;
	}
	cout << "---------------------------" << endl;
	system("pause");
}

//比赛
void speech_mager::speechContest() {
	cout << "第" << m_index << "比赛正式开始" << endl;

	multimap<double, int, greater<double>>groupScore;      //存放小组成绩
	int num = 0;     //记录人员个数  6人一组

	vector<int>v_Src;
	if (m_index == 1) {
		v_Src = v1;
	}
	else {
		v_Src = v2;
	}
	//遍历参赛选手
	for (vector<int>::iterator it = v_Src.begin(); it != v_Src.end(); it++) {
		num++;
		//评委打分
		deque<double>d;
		for (int i = 0; i < 10; i++) {
			double score = (rand() % 401 + 600) / 10.f;
			//cout << score << "\t";
			d.push_back(score);            //将分数放入打分容器中
		}
		//cout << endl;
		sort(d.begin(), d.end(),greater<double>());        //从大到小排序
		d.pop_front();       //去掉最高分
		d.pop_back();        //去除最低分
		double sum = accumulate(d.begin(), d.end(), 0.0f);       //成绩总和
		double ave = sum / double(d.size());                  //每个人的平均成绩

		//打印平均分

		//cout << "编号：" << *it << "姓名：" << this->m_speaker[*it].m_name << "平均成绩：" << ave;
		//cout << endl;
		//将ave放入map容器
		m_speaker[*it].m_score[this->m_index - 1] = ave;
		//将打分成绩放入groupscore
		groupScore.insert(make_pair(ave, *it));         //*it   编号
		//每6人取出前三名
		if (num % 6 == 0) {
			cout << "第" << num / 6 << "组的成绩如下" << endl;

			for (multimap<double, int>::iterator it = groupScore.begin();           
				it != groupScore.end() ; it++) {
				cout << "编号：" << (*it).second<<"    " << "姓名：" << this->m_speaker[it->second].m_name <<"    "
					"最后的平均成绩：" << m_speaker[it->second].m_score[m_index-1] << endl;
			}
			//取出前三名
			int count = 0;
			for (multimap<double, int>::iterator it = groupScore.begin();            //count的目的是为了只输出前三名
				it != groupScore.end() && count < 3; count++, it++) {
				if (this->m_index == 1) {          //第一轮
					v2.push_back(it->second);
				}
				else {
					victory.push_back(it->second);
				}
			}

			groupScore.clear();            //小组容器清空
			cout << endl;
		}

	}

	cout << "--------------第" << this->m_index << "轮完毕------------" << endl;
	system("pause");
}

//显示得分
void speech_mager::showscore() {
	cout << "---------第" << m_index << "轮晋级的选手信息" << endl;
	vector<int>v;
	if (m_index == 1) {
		v = v2;
	}
	else {
		v = victory;
	}

	for (vector<int>::iterator it = v.begin(); it != v.end(); it++) {
		cout << "编号" << *it << "  " << "姓名：" << m_speaker[*it].m_name << 
			"    " << "成绩" << m_speaker[*it].m_score[m_index-1] << endl;
	}

	//cout << endl;
	system("pause");
	system("cls");
	this->show_menu();
}

//保存分数记录
void speech_mager::saverecord() {
	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app);   //用追加的方式写

	//把每个选手的数据存在文件中      在project的同目录
	for (vector<int>::iterator it = victory.begin(); it != victory.end(); it++)
	{
		ofs << *it << "," << m_speaker[*it].m_score[1] << ",";
	}
	ofs << endl;
	ofs.close();
	cout << "文件已保留" << endl;
}

//读取记录
void speech_mager::loadrecord() {
	ifstream ifs("speech.csv", ios::in);   //读文件
	if (!ifs.is_open()) {
		this->fileisempty = true;
		cout << "文件不存在" << endl;
		ifs.close();
		return;
	}
	//文件清空
	char ch;
	ifs >> ch;
	if (ifs.eof()) {
		cout << "文件为空" << endl;
		this->fileisempty = true;
		ifs.close();
		return;
	}
	//文件不为空
	this->fileisempty = false;
	ifs.putback(ch);       //将上面的ch读出
	string data;
	int index = 1;        //第几届比赛
	while (ifs >> data) {
		vector<string>v;         //用于存放temp的值  
		//cout << data << endl;;
		int pos = -1;//用于查找“，”
		int start = 0;
	
		

		while (true) {
			pos = data.find(",", start);
			if (pos == -1) {
				break;   
			}
			string temp = data.substr(start, pos - start);     //截取字符串
			v.push_back(temp);
			start = pos + 1;
		}
		//map<int, vector<string>>m_recode;
		m_recode.insert((make_pair(index, v)));
		index++;
		
	}
	ifs.close();
	for (map<int, vector<string>>::iterator op = m_recode.begin(); op != m_recode.end(); op++) {
		cout << "第" << op->first << "届"<<"\n"
			<< "冠军编号：" << op->second[0] << "成绩为: " << op->second[1]<<"\n"
			<< "亚军编号：" << op->second[2] << "成绩为: " << op->second[3]<<"\n"
			<< "季军编号：" << op->second[4] << "成绩为: " << op->second[5] << endl;
	}
	system("pause");
	system("cls");

}

//清空文件
void speech_mager::clearrecord() {
	cout << "准备清空：" << endl;
	int ack;
	cout << "确认请按1，取消按2" << endl;
	cin >> ack;
	if (ack == 1) {
		//ios::trunc  如果存在，删除文件重建
		ofstream ofs("speech.csv", ios::trunc);
		ofs.close();
		//初始化属性
		this->initspeech();
		//创建12名选手
		this->createpeople();
		//读取历史记录
		this->loadrecord();
		cout << "清空成功" << endl;
	}
	system("pause");
	system("cls");
}
	//析构函数
speech_mager::~speech_mager() {
	
}



