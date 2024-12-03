#include <bits/stdc++.h>
using namespace std;
class user;
class student;
class teacher;
class course;
class theory;
class practice;
class comprehensive;

int neededTheoryScore = 3;
int neededPracticeScore = 3;


class user {
public:
	string ID;
	string password;
public:
	user(string id = "NULL", string passw = "nopassword") {
		ID = id;
		password = passw;
	}
	virtual void read(fstream& f) {
		cout << "��ERROR�������麯��" << endl;
		exit(1);
	}
	virtual void save(fstream& f) {
	}
};

//1�û��� 2���� 3ѧ������
class student : public user {
public:
	string stuName;
	int courseNum;
	set<string> MyCourses;	//ѧϰ�� �γ̱��
	student(string ID = "NULL", string password = "nopassword", string stuname = "NULL") : user(ID, password) {
		stuName = stuname;
		courseNum = 0;
	}
	void print();
	
	void printMyCoures();
	
	void read(fstream& f);
	
	void save(fstream& f);
};

class teacher : public user {
public:
	//set<string> MyCourses;	//���ڵ� �γ���
	teacher(string ID = "NULL", string password = "nopassword") : user(ID, password) {

	}
	void print() {
		cout << "�û�����" << ID << "\t���룺" << password << endl;
	}
	void read(fstream& f) {
		/*if (!f) {
			cout << "�������·������" << endl;
			return;
		}*/
		f >> ID >> password;
	}
	void save(fstream& f) {
		f << ID << " " << password << endl;
	}
};

const int maxStuNum = 50;	//ÿ���γ̶�ֻ����50��

class course {
public:
	int type; // �����ж���ʲô���͵Ŀγ�
	string name;
	string courseNum;	//�γ̱��
	int score;			//ѧ��
	string time;		//�Ͽ�ʱ��
	int curStuNum;	//��ǰ���� ���������Ϊ50
public:
	course(string Name = "NULL", string courseN = "NULL", int Score = -1, string Time = "00:00") {
		name = Name;
		courseNum = courseN;
		score = Score;
		time = Time;
		curStuNum = 0;	//��ʼ������0��
		type = 0;
	}
	virtual void print() {
		//cout << "[ ERROR ]-�������麯��" << endl;
		cout << "������" << name << "\t��ţ�" << courseNum << "\t�ڿ�ʱ�䣺" << time << "\tѧ�֣�" << score << endl;
		//exit(1);
	}
	virtual void read(fstream& f) {

	}
	virtual void save(fstream& f) {

	}
};

class theory : virtual public course {	//���ۿ�
public:
	string book;	//�̲�
	theory(string Name = "NULL", string courseN = "NULL", int Score = -1, string Time = "00:00", string bk = "NULL") : course(Name, courseN, Score, Time), book(bk){
		type = 1;	//���ۿ�
	}
	void print() {
		cout << " <���ۿ�> ";
		course::print();
		cout << "\t�̲ģ�" << book << "\t<" << curStuNum << "/" << maxStuNum << ">" << endl;
	}
	void read(fstream& f) {
		f >> name >> courseNum >> score >> time >> curStuNum >> book;
	}
	void save(fstream& f) {
		f << type << " " << name << " " << courseNum << " " << score << " " << time << " " << curStuNum << " " << book << endl;
	}
};

class practice : virtual public course {	//ʵ���
public:
	string environment;	//��������
	practice(string Name = "NULL", string courseN = "NULL", int Score = -1, string Time = "00:00", string emt = "NULL") : course(Name, courseN, Score, Time), environment(emt) {
		type = 2;	//ʵ���
	}
	void print() {
		cout << " <ʵ���> ";
		course::print();
		cout << "\tʵ�黷����" << environment << "\t<" << curStuNum << "/" << maxStuNum << ">" << endl;
	}
	void read(fstream& f) {
		f >> name >> courseNum >> score >> time >> curStuNum >> environment;
	}
	void save(fstream& f) {
		f << type << " " << name << " " << courseNum << " " << score << " " << time << " " << curStuNum << " " << environment << endl;
	}
};

class comprehensive : public theory, public practice {
public:
	comprehensive(string Name = "NULL", string courseN = "NULL", int Score = -1, string Time = "00:00", string bk = "NULL", string emt = "NULL") : theory(Name, courseN, Score, Time, bk), practice(Name, courseN, Score, Time, emt), course(Name, courseN, Score, Time) {
		type = 3;	//�ۺ�
	};
	void print() {
		//cout << " <�ۺϿ�> " << "������" << name << "\t��ţ�" << courseNum << "\tѧ�֣�" << score << "\t�ڿ�ʱ�䣺" << time << "\t�̲ģ�" << book << "\tʵ�黷����" << environment << endl;
		cout << " <�ۺϿ�> ";
		course::print();
		cout << "\t�̲ģ�" << book << "\tʵ�黷����" << environment << "\t<" << curStuNum << "/" << maxStuNum << ">" << endl;
	}
	void read(fstream& f) {
		f >> name >> courseNum >> score >> time >> curStuNum >> book >> environment;
	}
	void save(fstream& f) {
		f << type << " " << name << " " << courseNum << " " << score << " " << time << " " << curStuNum << " " << book << " " << environment << endl;
	}
};

map<string, student> TheStudentMap;
map<string, teacher> TheTeacherMap;
map<string, course*> TheCourseMap;

void student::printMyCoures() {
	cout << "\t�װ��� " << stuName << " �㵱ǰһ��ѧϰ�� " << MyCourses.size() << " ���γ̣�" << endl;
	if (MyCourses.size() == 0) {
		cout << "\tNULL" << endl;
	}
	else {
		set<string>::iterator it;
		int i;
		for (i = 0, it = MyCourses.begin(); it != MyCourses.end();i++, it++) {
			cout << "\t[" << i + 1 << "]" << *it << "\t" << TheCourseMap.find(*it)->second->name << endl;
		}
	}
}

void student :: read(fstream& f) {
	/*if (!f) {
		cout << "�������·������" << endl;
		return;
	}*/
	f >> ID >> password >> stuName >> courseNum;
	string temp;
	for (int i = 0; i < courseNum; i++) {
		f >> temp;
		MyCourses.insert(temp);		//������ǿγ̱��
		TheCourseMap.find(temp)->second->curStuNum++;
	}
}

void student::save(fstream& f) {
	f << ID << " " << password << " " << stuName << " " << courseNum << " ";
	string temp;
	set<string> ::iterator it;
	for (it = MyCourses.begin(); it != MyCourses.end(); it ++) {
		f << *it << " ";
	}
	f << endl;
}


void student :: print() {
	cout << "ѧ�ţ�" << ID << "\t���룺" << password << "\t������" << stuName << endl;
	cout << "\tѧϰ��" << MyCourses.size() << "���γ̣�" << endl;
	if (MyCourses.size() == 0) {
		cout << "\tNULL" << endl;
	}
	else {
		set<string>::iterator it;
		int i;
		for (i = 0, it = MyCourses.begin(); it != MyCourses.end();i++, it++) {
			cout << "\t[" << i + 1 << "]" << *it << "\t" << TheCourseMap.find(*it)->second->name << endl;
		}
	}
}


int choice(int begin, int end);	//����ָ����Χ��int
void mainManue();
void adminManue();
void studentManue();
teacher& password_tea();
student& password_stu();
void tea_ManageStudent();
void tea_ManageCourse();
void addCourse();
void tea_SystemSetting();

//void read(string path_stu = "student.txt", string path_tea = "teacher.txt", string path_course = "course.txt");

//void stu_ViewCourse();
//void courseChoosen();	//ѡ��

void read(string path_stu = "student.txt", string path_tea = "teacher.txt", string path_course = "course.txt") {
	fstream f(path_course);
	if (!f) {
		//while (1) {
			cout << "*·�����󣬿γ̵���ʧ�ܡ�" << endl;
			//cout << "*������γ��ļ�·����";
			//if (f)
		//}
		
	}
	while (f.peek() != EOF) {
		int c;
		f >> c;
		switch (c) {
		case 1: {
			theory* temp = new theory;
			temp->read(f);
			TheCourseMap.insert(pair<string, course*>{temp->courseNum, temp});
			cout << "��ϵͳ���á�";
			temp->print();
			break;
		}
		case 2: {
			practice* temp = new practice;
			temp->read(f);
			TheCourseMap.insert(pair<string, course*>{temp->courseNum, temp});
			cout << "��ϵͳ���á�";
			temp->print();
			break;
		}
		case 3:
			comprehensive* temp = new comprehensive;
			temp->read(f);
			TheCourseMap.insert(pair<string, course*>{temp->courseNum, temp});
			cout << "��ϵͳ���á�";
			temp->print();
			break;
		}
	}
	f.close();
	
	f.open(path_stu, ios::in);
	if (!f) {
		cout << "*·������ѧ������ʧ�ܡ�" << endl;
	}
	while (f.peek() != EOF) {
		student* temp = new student;
		temp->read(f);
		TheStudentMap.insert(pair<string, student>{temp->ID, *temp});
		cout << "��ϵͳ���á�";
		temp->print();
	}
	f.close();
	
	f.open(path_tea, ios::in);
	if (!f) {
		cout << "*·��������ʦ����ʧ�ܡ�" << endl;
	}
	while (f.peek() != EOF) {
		teacher* temp = new teacher;
		temp->read(f);
		TheTeacherMap.insert(pair<string, teacher>{temp->ID, * temp});
		cout << "��ϵͳ���á�";
		temp->print();
	}
	f.close();

	
	cout << "��ϵͳ���á�ϵͳ�������" << endl;
}

void save(string path_stu = "student_out.txt", string path_tea = "teacher_out.txt", string path_course = "course_out.txt") {
	fstream f(path_course);
	f.open(path_course, ios::out);
	/*if (!f) {
		cout << "*·�����󣬿γ̵���ʧ�ܡ�" << endl;
		return;
	}*/
	map<string, course*> ::iterator it;
	for (it = TheCourseMap.begin(); it != TheCourseMap.end(); it++) {
		it->second->save(f);
	}

	f.close();

	f.open(path_tea, ios::out);
	/*if (!f) {
		cout << "*·������ѧ������ʧ�ܡ�" << endl;
		return;
	}*/
	map<string, teacher> ::iterator it_t;
	for (it_t = TheTeacherMap.begin(); it_t != TheTeacherMap.end(); it_t++) {
		it_t->second.save(f);
	}
	f.close();

	f.open(path_stu, ios::out);
	map<string, student> ::iterator it_s;
	for (it_s = TheStudentMap.begin(); it_s != TheStudentMap.end(); it_s++) {
		it_s->second.save(f);
	}
	f.close();


	cout << "������" << endl;
}

int main() {
	student stu("stu001", "123456", "����");
	TheStudentMap.insert(pair<string, student>{stu.ID, stu});
	teacher admin("admin", "123456");
	TheTeacherMap.insert(pair<string, teacher>{admin.ID, admin});	//��ʼ������ ֮�����Ҳ����
	theory the1("����", "gs2021", 3, "8:00", "����1");
	theory the2("c++", "cpp2021", 3, "10:00", "c++�α�");
	TheCourseMap.insert(pair<string, course*>{the1.courseNum, & the1});
	TheCourseMap.insert(pair<string, course*>{the2.courseNum, & the2});
	mainManue();
	cout << "�Ƿ���Ҫ���Ϊ�ļ���\n\
* 1) ��\n\
* 2����" << endl;
	int num(choice(1, 2));
	if (num == 1) {
		save();
	}
	return 0;
}

int choice(int begin = 1, int end = 1) {
	int c;
	while (1) {
		cin >> c;
		if (!cin.fail() && c >= begin && c <= end) {
			cin.get();
			return c;
		}
		cout << "���������������������롣" << endl;
		cin.clear();
		cin.get();
	}
}

void mainManue() {
	int loop = 1;
	while (loop) {
		cout << "*��ӭ��ʹ��xnuϵͳ*\n\
* 1) ����Ա\n\
* 2��ѧ��\n\
* 3���˳�ϵͳ\n\
* ��ѡ���¼�û�����[1 - 3]:" << endl;
		int choice(::choice(1,3));
		switch (choice) {
		case 1:
			adminManue();
			break;
		case 2:
			studentManue();
			break;
		case 3:
			cout << "��л����ʹ�ã�\n" << endl;
			loop = 0;
			break;
		}
	}
}

teacher notfound_t;
student notfound_s;		//Ĭ�϶��ǿյ� ��ͳһ��notfound ���Ǻ�����

teacher& password_tea() {
	string id;
	cout << "�����������û�����";
	cin >> id;
	if (TheTeacherMap.find(id) != TheTeacherMap.end()) {
		cout << "���������룺";
		string pw;
		cin >> pw;
		if (TheTeacherMap[id].password == pw) {
			cout << "����¼�ɹ���" << endl;
			return TheTeacherMap[id];
		}
	}
	return notfound_t;
}

student& password_stu() {
	string id;
	cout << "�����������û�����";
	cin >> id;
	if (TheStudentMap.find(id) != TheStudentMap.end()) {
		cout << "���������룺";
		string pw;
		cin >> pw;
		if (TheStudentMap[id].password == pw) {
			cout << "����¼�ɹ���" << endl;
			return TheStudentMap[id];
		}
	}
	return notfound_s;
}

void adminManue() {
	teacher &tea(password_tea());
	if (tea.ID == "NULL") {		//���û���ҵ����˳�
		cout << "������������" << endl;
		return;
	}
	int loop = 1;
	while (loop) {
		cout << "*��ӭ�� " << tea.ID << " �����Ľ�ɫ�ǹ���Ա���������¹���Ȩ�ޣ�\n\
*1��ѧ������\n\
*2���γ̹���\n\
*3��ϵͳ����\n\
*4��ͳ�Ʒ���\n\
*5���˳�\n\
*����������[1-5]��" << endl;
		int choice(::choice(1,5));
		switch (choice) {
		case 1:
			tea_ManageStudent();
			break;
		case 2:
			tea_ManageCourse();
			break;
		case 3:
			tea_SystemSetting();
			break;
		case 4:	{
			cout << "*��ӭʹ��ͳ�Ʒ������ܡ�" << endl;
			map<string, course*> ::iterator it;
			int i;

			cout << "  * Courses *" << endl;
			if (TheCourseMap.begin() == TheCourseMap.end()) {
				cout << "*��Ǹ����û���κογ̡�" << endl;
			}
			else {
				cout << "*һ����" << TheCourseMap.size() << "�ſγ̡�" << endl;
				for (i = 1, it = TheCourseMap.begin(); it != TheCourseMap.end(); it++, i++) {
					cout << "[" << i << "]";
					it->second->print();
				}
			}

			cout << "\n  * Teacher *" << endl;
			if (TheTeacherMap.begin() == TheTeacherMap.end()) {
				cout << "*��Ǹ����û���κι���Ա��" << endl;
			}
			else {
				i = 1;
				cout << "*һ����" << TheTeacherMap.size() << "������Ա��" << endl;
				//map<string, teacher> ::iterator t;
				for (auto t : TheTeacherMap) {
				//for (t = TheTeacherMap.begin(); t != TheTeacherMap.end(); t++) {
					cout << "[" << i << "]\t";
					t.second.print();
					i++;
				}
			}

			cout << "\n  * Student *" << endl;
			if (TheStudentMap.begin() == TheStudentMap.end()) {
				cout << "*��Ǹ����û���κ�ѧ����" << endl;
			}
			else {
				i = 1;
				//map<string, student> ::iterator s;
				cout << "*һ����" << TheStudentMap.size() << "��ѧ����" << endl;
				for (auto s : TheStudentMap) {
				//for (s = TheStudentMap.begin(); s != TheStudentMap.end(); s++) {
					cout << "[" << i << "]\tID��" << endl;
					//s->second.print();
					s.second.print();
					i++;
				}
			}
			break;
		}
			break;
		case 5:
			loop = 0;
			break;
		}
	}
}

void tea_ManageStudent() {
	int loop = 1;
	while (loop) {
		cout << "*ѧ������������¹���Ȩ�ޣ�\n\
*1�����ѧ��\n\
*2��ɾ��ѧ��\n\
*3���鿴ѧ���б�\n\
*4���˳�\n\
*����������[1-4]��" << endl;
		int choice(::choice(1,4));
		switch (choice) {
		case 1: {
			cout << "*��ӭʹ�����ѧ�����ܡ�";
			string id, password, name;
			cout << "\n�������û���������ѧ�ţ�";
			cin >> id;
			cout << "\n�������û������������룺";
			cin >> password;
			cout << "\n�������û������������ƣ�";
			cin >> name;
			student temp(id, password, name);
			TheStudentMap[id] = temp;
			cout << "\n�������û���ѧ�������" << endl;
			break;
		}
		case 2: {
			cout << "*��ӭʹ��ɾ��ѧ�����ܡ�";
			string id;
			cout << "\n��ɾ���û���������ѧ�ţ�";
			cin >> id;
			if (TheStudentMap.find(id) == TheStudentMap.end()) {
				cout << "\n��ɾ���û���ɾ��ʧ�ܣ�û�����ѧ����" << endl;
				break;
			}
			TheStudentMap.erase(id);
			break;
		}
		case 3: {
			cout << "*��ӭʹ�ò鿴ѧ���б��ܡ�" << endl;
			map<string, student> ::iterator it;
			for (it = TheStudentMap.begin(); it != TheStudentMap.end(); it++) {
				it->second.print();
			}
			break;
		}
		case 4:
			loop = 0;
			break;
		}
	}
}

void tea_ManageCourse() {
	int loop = 1;
	while (loop) {
		cout << "*��ӭ����γ̹���ģ�顭\n\
* 1�����ӿγ�\n\
* 2���γ��б�\n\
* 3��ɾ���γ�\n\
* 4��������һ��\n\
* ����������[1 - 4]��" << endl;
		int choice(::choice(1,4));
		switch (choice) {
		case 1:
			addCourse();
			break;
		case 2: {
			cout << "*��ӭʹ�ò鿴�γ��б��ܡ�" << endl;
			map<string, course*> ::iterator it;
			int i;
			if (TheCourseMap.begin() == TheCourseMap.end()) {
				cout << "*��Ǹ����û���κογ̡�" << endl;
				break;
			}
			cout << "*һ����" << TheCourseMap.size() << "�ſγ̡�" << endl;
			for (i = 1, it = TheCourseMap.begin(); it != TheCourseMap.end(); it++, i++) {
				cout << "[" << i << "]";
				it->second->print();
			}
			break;
		}
		case 3: {
			cout << "*��ӭʹ��ɾ���γ̹��ܡ�" << endl;
			cout << "��ɾ���γ̡�������γ̱�ţ�";
			//map<string, course*> ::iterator it;
			string cnum;
			cin >> cnum;
			cin.get();	//���ջس�
			if (!TheCourseMap.erase(cnum)) {
				cout << "��ɾ���γ̡�ɾ��ʧ�ܣ�û������γ̡�" << endl;
				break;
			}
			cout << "��ɾ���γ̡�ɾ���ɹ���" << endl;
			break;
		}
		case 4:
			loop = 0;
			break;
		}
	}
}



void tea_SystemSetting() {
	int loop = 1;
	while (loop) {
		cout << "*��ӭ����ϵͳ����ģ�顭\n\
* 1�������ļ�����\n\
* 2������ѧ������ѡ�����ۿε�ѧ����\n\
* 3������ѧ������ѡ��ʵ��ε�ѧ����\n\
* 4��������һ��\n\
* ����������[1 - 4]��" << endl;
		int choice(::choice(1, 4));
		switch (choice) {
		case 1:
			read();
			break;
		case 2: {
			cout << "��ϵͳ���á����������ۿα��޵�ѧ������";
			int score;
			while (1) {
				cin >> score;
				if (!cin.fail()) {
					cin.get();
					break;
				}
				cout << "��ϵͳ���á����������������������롣" << endl;
				cin.clear();
				cin.get();
			}
			neededTheoryScore = score;
			cout << "��ϵͳ���á����óɹ�" << endl;
			cout << "��ϵͳ���á�ѧ������ѡ�����ۿε�ѧ����Ϊ��" << neededTheoryScore << endl;
			break;
		}
		case 3: {
			cout << "��ϵͳ���á�������ʵ��α��޵�ѧ������";
			int score;
			while (1) {
				cin >> score;
				if (!cin.fail()) {
					cin.get();
					break;
				}
				cout << "��ϵͳ���á����������������������롣" << endl;
				cin.clear();
				cin.get();
			}
			neededPracticeScore = score;
			cout << "��ϵͳ���á����óɹ�" << endl;
			cout << "��ϵͳ���á�ѧ������ѡ��ʵ��ε�ѧ����Ϊ��" << neededTheoryScore << endl;
			break;
		}
		case 4:
			loop = 0;
			break;
		}
	}
}


void addCourse() {
	int loop = 1;
	cout << "*��ӭʹ�����ӿγ̹��ܣ�ϵͳ�γ����Ͱ���\n\
* 1�����ۿ�\n\
* 2��ʵ���\n\
* 3������ʵ���\n\
�����ӿγ̡���ѡ��γ�����[1 - 3]��" << endl;
	int choice(::choice(1,3));
	string cnum, cname, ctime, cbook, cdiscribe;
	int cscore;
	cout << "�����ӿγ̡�������γ̱�ţ�";
	cin >> cnum;
	cout << "�����ӿγ̡�������γ����ƣ�";
	cin >> cname;
	cout << "�����ӿγ̡�������γ�ѧ�֣�";
	cin >> cscore;
	cout << "�����ӿγ̡��������Ͽ�ʱ�䣺";
	cin >> ctime;
	switch (choice) {
	case 1: {
		cout << "�����ӿγ̡��������Ͽν̲ģ�";
		cin >> cbook;
		theory* temp = new theory(cname, cnum, cscore, ctime, cbook);
		TheCourseMap.insert(pair<string, course*>{temp->name, temp});
		break;
	}
	case 2: {
		cout << "�����ӿγ̡�������ʵ�黷��������";
		cin >> cdiscribe;
		practice *temp = new practice(cname, cnum, cscore, ctime, cdiscribe);
		TheCourseMap.insert(pair<string, course*>{temp->name, temp});
		break;
	}
	case 3: {
		cout << "�����ӿγ̡��������Ͽν̲ģ�";
		cin >> cbook;
		cout << "�����ӿγ̡�������ʵ�黷��������";
		cin >> cdiscribe;
		comprehensive * temp = new comprehensive(cname, cnum, cscore, ctime, cbook, cdiscribe);
		TheCourseMap.insert(pair<string, course*>{temp->name, temp});
		break;
	}
	}
	cout << "�����ӿγ̡��γ�����ӡ�" << endl;
}

void studentManue() {
	student& stu(password_stu());
	if (stu.ID == "NULL") {		//���û���ҵ����˳�
		cout << "������������" << endl;
		return;
	}
	
	int loop = 1;
	while (loop) {
		cout << "*��ӭ�� " << stu.ID << " �����Ľ�ɫ��ѧ�����������¹���Ȩ�ޣ�\n\
*1������γ�\n\
*2����ѡ�γ�\n\
*3��ѡ��\n\
*4���˿�\n\
*5���˳�\n\
*����������[1-5]��" << endl;
		int ch(choice(1,5));
		switch (ch) {
		case 1: {
			map<string, course*> ::iterator it;
			int i;
			if (TheCourseMap.begin() == TheCourseMap.end()) {
				cout << "*��Ǹ����û���κογ̡�" << endl;
				break;
			}
			for (i = 1, it = TheCourseMap.begin(); it != TheCourseMap.end(); it++, i++) {
				cout << "[" << i << "]";
				it->second->print();
			}
			break;
		}
		case 2: {
			stu.printMyCoures();
			break;
		}
		case 3: {
			cout << "*��ӭʹ��ѡ�ι��ܡ�" << endl;
			cout << "��ѡ�ι��򡿿γ̵�ѧ��Ϊ1~3��ѧ��" << endl;
			cout << "��ѡ�ι���ÿѧ�����޵����ۿ�ѧ��Ϊ��" << neededTheoryScore << endl;
			cout << "��ѡ�ι���ÿѧ�����޵�ʵ���ѧ��Ϊ��" << neededPracticeScore << endl;
			cout << "��ѡ�ι�������ѧ�ֺ󽫲��ܹ���ѡ��" << endl << endl;
			cout << "��ѡ�Ρ�ѡ��֮ǰ����ϸ�Ķ�ѡ�ι���" << endl;
			set<string> ::iterator it;
			//int myScore = 0;
			int myTheoryScore = 0;
			int myPracticeScore = 0;
			for (it = stu.MyCourses.begin(); it != stu.MyCourses.end(); it++) {
				if (TheCourseMap.find(*it)->second->type == 1 || TheCourseMap.find(*it)->second->type == 3) {
					myTheoryScore += TheCourseMap.find(*it)->second->score;
				}
				if (TheCourseMap.find(*it)->second->type == 2 || TheCourseMap.find(*it)->second->type == 3) {
					myPracticeScore += TheCourseMap.find(*it)->second->score;
				}
			}

			cout << "��ѡ�Ρ�������ۿ��Ѿ�����<" << myTheoryScore << "/" << neededTheoryScore << ">ѧ��";
			if (myTheoryScore >= neededTheoryScore) {
				cout << "��������ѡ���ۿΡ�" << endl;
			}
			else {
				cout << endl;
			}
			cout << "��ѡ�Ρ����ʵ����Ѿ�����<" << myPracticeScore << "/" << neededPracticeScore << ">ѧ��";
			if (myPracticeScore >= neededPracticeScore) {
				cout << "��������ѡʵ��Ρ�" << endl;
			}
			else {
				cout << endl;
			}
			if (myTheoryScore >= neededTheoryScore && myPracticeScore >= neededPracticeScore) {
				break;
			}
			///////////////////////////////////////////////////////////////////�˴���û���� ֮����Ҫ ���ۿ������������ֻ����ʵ��� �������˾�ֱ�ӽ���
			cout << "��ѡ�Ρ�����������ѡ�γ̵Ŀγ̴��ţ�";
			string temp;
			cin >> temp;
			if (TheCourseMap.find(temp) == TheCourseMap.end()) {
				cout << "��ѡ�Ρ�û�����ſΣ������������롣" << endl;
				break;
			}
			if (stu.MyCourses.find(temp) != stu.MyCourses.end()) {
				cout << "��ѡ�Ρ����Ѿ�ѡ�� " << temp << " �������ظ�ѡ�Ρ�" << endl;
				break;
			}
			if ((TheCourseMap.find(temp)->second->type == 1 || TheCourseMap.find(temp)->second->type == 3) && myTheoryScore >= neededTheoryScore) {
				cout << "��ѡ�Ρ����޵����ۿ�ѧ��������������ѡ���ۿ�" << endl;
			}
			if ((TheCourseMap.find(temp)->second->type == 2 || TheCourseMap.find(temp)->second->type == 3) && myPracticeScore >= neededPracticeScore) {
				cout << "��ѡ�Ρ����޵�ʵ���ѧ��������������ѡʵ���" << endl;
			}

			stu.MyCourses.insert(temp);
			TheCourseMap.find(temp)->second->curStuNum++;	//�ڿγ�����������
			cout << "��ѡ�Ρ�ѡ�γɹ�" << endl;
			stu.printMyCoures();
			break;
		}
		case 4: {
			cout << "*��ӭʹ���˿ι��ܡ�" << endl;
			cout << "���˿Ρ�������γ̱�ţ�";
			string temp;
			cin >> temp;
			if (stu.MyCourses.find(temp) == stu.MyCourses.end()) {
				cout << "���˿Ρ�ɾ��ʧ�ܣ���û��ѡ���ſγ̡�" << endl;
				break;
			}
			cout << "���˿Ρ�Ҫ�˵��ÿγ���" << endl;
			TheCourseMap.find(temp)->second->print();
			cout << "*1����" << endl;
			cout << "*2����" << endl;
			if (choice(1, 2) == 2) {
				cout << "���˿Ρ��˿�ʧ��" << endl;
				break;
			}
			stu.MyCourses.erase(temp);
			TheCourseMap.find(temp)->second->curStuNum--;	//�ڿγ��м�������
			cout << "���˿Ρ��˿γɹ�" << endl;
			stu.printMyCoures();
			break;
		}
		case 5:
			loop = 0;
			break;
		}
	}
}
