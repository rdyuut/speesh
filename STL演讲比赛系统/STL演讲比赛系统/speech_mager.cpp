#include"speech_mager.h"
void myprint(int val) {            //for_each ʹ�õķº���
	cout << val << "  ";
}

speech_mager::speech_mager() {    //���캯��
	//��ʼ������
	this->initspeech();
	//����12��ѡ��
	this->createpeople();
	//��ȡ��ʷ��¼
	//this->loadrecord();
}

void speech_mager::show_menu() {
	cout << "*****************************************" << endl;
	cout << "************��ӭ�μ��ݽ�����*************" << endl;
	cout << "************1. ��ʼ�ݽ����� *************" << endl;
	cout << "************2. �鿴�����¼ *************" << endl;
	cout << "************3. ��������¼ *************" << endl;
	cout << "************0. �˳�����ϵͳ *************" << endl;
	cout << "*****************************************" << endl;
	cout << endl;
}

//�˳�����
void speech_mager::exit_system() {
	cout << "��ӭ�´�ʹ��" << endl;
	system("pause");
	exit(0);
}

//��ʼ������
void speech_mager::initspeech() {
	this->v1.clear();       //������    this->v1.clear()
	this->v2.clear();
	this->victory.clear();
	this->m_recode.clear();
	m_index = 1;
}

//����ѡ��
void speech_mager::createpeople() {
	string nameseed = "ABCDEFGHIJKL";
	for (int i = 0; i < nameseed.size(); i++) {
		string name = "ѡ��";
		name += nameseed[i];

		speaker sp;
		sp.m_name = name;
		//�����ֵ÷ָ�ֵ
		for (int j = 0; j < 2; j++) {
			sp.m_score[j] = 0;
			//����ѡ�ֱ�ŷ���v1����
		}
		v1.push_back(i + 10001);
		this->m_speaker.insert(make_pair(i + 10001, sp));//map<int, speaker>m_speaker;
	}
}
//��ʼ����
void speech_mager::startspeech() {

	//��һ�ֱ���
	
	   //1. ��ǩ
	this->speechDraw();
	   //2.����
	this->speechContest();
	   //3����ʾ�������
	this->showscore();
	//�ڶ��ֱ���
	m_index++;
	   //1. ��ǩ
	this->speechDraw();
	   //2.����
	this->speechContest();
	   
	   //3����ʾ�������
	this->showscore();
	   //4 .����������ļ�
	this->saverecord();

	cout << "������������" << endl;
	system("pause");
	system("cls");

}

     //��ǩ
void speech_mager::speechDraw() {
	cout << "��" << m_index << "��ѡ�ֿ�ʼ��ǩ" << endl;
	cout << "------------------------" << endl;
	cout << "��ǩ˳������" << endl;
	if (m_index == 1) {
		random_shuffle(v1.begin(), v1.end());
		for_each(v1.begin(), v1.end(), myprint);               //����
		cout << endl;
	}
	else {
		random_shuffle(v2.begin(), v2.end());            
		for_each(v2.begin(), v2.end(), myprint);                  //����
		cout << endl;
	}
	cout << "---------------------------" << endl;
	system("pause");
}

//����
void speech_mager::speechContest() {
	cout << "��" << m_index << "������ʽ��ʼ" << endl;

	multimap<double, int, greater<double>>groupScore;      //���С��ɼ�
	int num = 0;     //��¼��Ա����  6��һ��

	vector<int>v_Src;
	if (m_index == 1) {
		v_Src = v1;
	}
	else {
		v_Src = v2;
	}
	//��������ѡ��
	for (vector<int>::iterator it = v_Src.begin(); it != v_Src.end(); it++) {
		num++;
		//��ί���
		deque<double>d;
		for (int i = 0; i < 10; i++) {
			double score = (rand() % 401 + 600) / 10.f;
			//cout << score << "\t";
			d.push_back(score);            //������������������
		}
		//cout << endl;
		sort(d.begin(), d.end(),greater<double>());        //�Ӵ�С����
		d.pop_front();       //ȥ����߷�
		d.pop_back();        //ȥ����ͷ�
		double sum = accumulate(d.begin(), d.end(), 0.0f);       //�ɼ��ܺ�
		double ave = sum / double(d.size());                  //ÿ���˵�ƽ���ɼ�

		//��ӡƽ����

		//cout << "��ţ�" << *it << "������" << this->m_speaker[*it].m_name << "ƽ���ɼ���" << ave;
		//cout << endl;
		//��ave����map����
		m_speaker[*it].m_score[this->m_index - 1] = ave;
		//����ֳɼ�����groupscore
		groupScore.insert(make_pair(ave, *it));         //*it   ���
		//ÿ6��ȡ��ǰ����
		if (num % 6 == 0) {
			cout << "��" << num / 6 << "��ĳɼ�����" << endl;

			for (multimap<double, int>::iterator it = groupScore.begin();           
				it != groupScore.end() ; it++) {
				cout << "��ţ�" << (*it).second<<"    " << "������" << this->m_speaker[it->second].m_name <<"    "
					"����ƽ���ɼ���" << m_speaker[it->second].m_score[m_index-1] << endl;
			}
			//ȡ��ǰ����
			int count = 0;
			for (multimap<double, int>::iterator it = groupScore.begin();            //count��Ŀ����Ϊ��ֻ���ǰ����
				it != groupScore.end() && count < 3; count++, it++) {
				if (this->m_index == 1) {          //��һ��
					v2.push_back(it->second);
				}
				else {
					victory.push_back(it->second);
				}
			}

			groupScore.clear();            //С���������
			cout << endl;
		}

	}

	cout << "--------------��" << this->m_index << "�����------------" << endl;
	system("pause");
}

//��ʾ�÷�
void speech_mager::showscore() {
	cout << "---------��" << m_index << "�ֽ�����ѡ����Ϣ" << endl;
	vector<int>v;
	if (m_index == 1) {
		v = v2;
	}
	else {
		v = victory;
	}

	for (vector<int>::iterator it = v.begin(); it != v.end(); it++) {
		cout << "���" << *it << "  " << "������" << m_speaker[*it].m_name << 
			"    " << "�ɼ�" << m_speaker[*it].m_score[m_index-1] << endl;
	}

	//cout << endl;
	system("pause");
	system("cls");
	this->show_menu();
}

//���������¼
void speech_mager::saverecord() {
	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app);   //��׷�ӵķ�ʽд

	//��ÿ��ѡ�ֵ����ݴ����ļ���      ��project��ͬĿ¼
	for (vector<int>::iterator it = victory.begin(); it != victory.end(); it++)
	{
		ofs << *it << "," << m_speaker[*it].m_score[1] << ",";
	}
	ofs << endl;
	ofs.close();
	cout << "�ļ��ѱ���" << endl;
}

//��ȡ��¼
void speech_mager::loadrecord() {
	ifstream ifs("speech.csv", ios::in);   //���ļ�
	if (!ifs.is_open()) {
		this->fileisempty = true;
		cout << "�ļ�������" << endl;
		ifs.close();
		return;
	}
	//�ļ����
	char ch;
	ifs >> ch;
	if (ifs.eof()) {
		cout << "�ļ�Ϊ��" << endl;
		this->fileisempty = true;
		ifs.close();
		return;
	}
	//�ļ���Ϊ��
	this->fileisempty = false;
	ifs.putback(ch);       //�������ch����
	string data;
	int index = 1;        //�ڼ������
	while (ifs >> data) {
		vector<string>v;         //���ڴ��temp��ֵ  
		//cout << data << endl;;
		int pos = -1;//���ڲ��ҡ�����
		int start = 0;
	
		

		while (true) {
			pos = data.find(",", start);
			if (pos == -1) {
				break;   
			}
			string temp = data.substr(start, pos - start);     //��ȡ�ַ���
			v.push_back(temp);
			start = pos + 1;
		}
		//map<int, vector<string>>m_recode;
		m_recode.insert((make_pair(index, v)));
		index++;
		
	}
	ifs.close();
	for (map<int, vector<string>>::iterator op = m_recode.begin(); op != m_recode.end(); op++) {
		cout << "��" << op->first << "��"<<"\n"
			<< "�ھ���ţ�" << op->second[0] << "�ɼ�Ϊ: " << op->second[1]<<"\n"
			<< "�Ǿ���ţ�" << op->second[2] << "�ɼ�Ϊ: " << op->second[3]<<"\n"
			<< "������ţ�" << op->second[4] << "�ɼ�Ϊ: " << op->second[5] << endl;
	}
	system("pause");
	system("cls");

}

//����ļ�
void speech_mager::clearrecord() {
	cout << "׼����գ�" << endl;
	int ack;
	cout << "ȷ���밴1��ȡ����2" << endl;
	cin >> ack;
	if (ack == 1) {
		//ios::trunc  ������ڣ�ɾ���ļ��ؽ�
		ofstream ofs("speech.csv", ios::trunc);
		ofs.close();
		//��ʼ������
		this->initspeech();
		//����12��ѡ��
		this->createpeople();
		//��ȡ��ʷ��¼
		this->loadrecord();
		cout << "��ճɹ�" << endl;
	}
	system("pause");
	system("cls");
}
	//��������
speech_mager::~speech_mager() {
	
}



