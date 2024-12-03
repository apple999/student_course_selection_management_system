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
		cout << "【ERROR】引用虚函数" << endl;
		exit(1);
	}
	virtual void save(fstream& f) {
	}
};

//1用户名 2密码 3学生姓名
class student : public user {
public:
	string stuName;
	int courseNum;
	set<string> MyCourses;	//学习的 课程编号
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
	//set<string> MyCourses;	//教授的 课程名
	teacher(string ID = "NULL", string password = "nopassword") : user(ID, password) {

	}
	void print() {
		cout << "用户名：" << ID << "\t密码：" << password << endl;
	}
	void read(fstream& f) {
		/*if (!f) {
			cout << "您输入的路径有误" << endl;
			return;
		}*/
		f >> ID >> password;
	}
	void save(fstream& f) {
		f << ID << " " << password << endl;
	}
};

const int maxStuNum = 50;	//每个课程都只能有50人

class course {
public:
	int type; // 用来判断是什么类型的课程
	string name;
	string courseNum;	//课程编号
	int score;			//学分
	string time;		//上课时间
	int curStuNum;	//当前人数 最大人数定为50
public:
	course(string Name = "NULL", string courseN = "NULL", int Score = -1, string Time = "00:00") {
		name = Name;
		courseNum = courseN;
		score = Score;
		time = Time;
		curStuNum = 0;	//初始人数是0人
		type = 0;
	}
	virtual void print() {
		//cout << "[ ERROR ]-访问了虚函数" << endl;
		cout << "课名：" << name << "\t编号：" << courseNum << "\t授课时间：" << time << "\t学分：" << score << endl;
		//exit(1);
	}
	virtual void read(fstream& f) {

	}
	virtual void save(fstream& f) {

	}
};

class theory : virtual public course {	//理论课
public:
	string book;	//教材
	theory(string Name = "NULL", string courseN = "NULL", int Score = -1, string Time = "00:00", string bk = "NULL") : course(Name, courseN, Score, Time), book(bk){
		type = 1;	//理论课
	}
	void print() {
		cout << " <理论课> ";
		course::print();
		cout << "\t教材：" << book << "\t<" << curStuNum << "/" << maxStuNum << ">" << endl;
	}
	void read(fstream& f) {
		f >> name >> courseNum >> score >> time >> curStuNum >> book;
	}
	void save(fstream& f) {
		f << type << " " << name << " " << courseNum << " " << score << " " << time << " " << curStuNum << " " << book << endl;
	}
};

class practice : virtual public course {	//实验课
public:
	string environment;	//环境描述
	practice(string Name = "NULL", string courseN = "NULL", int Score = -1, string Time = "00:00", string emt = "NULL") : course(Name, courseN, Score, Time), environment(emt) {
		type = 2;	//实验课
	}
	void print() {
		cout << " <实验课> ";
		course::print();
		cout << "\t实验环境：" << environment << "\t<" << curStuNum << "/" << maxStuNum << ">" << endl;
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
		type = 3;	//综合
	};
	void print() {
		//cout << " <综合课> " << "课名：" << name << "\t编号：" << courseNum << "\t学分：" << score << "\t授课时间：" << time << "\t教材：" << book << "\t实验环境：" << environment << endl;
		cout << " <综合课> ";
		course::print();
		cout << "\t教材：" << book << "\t实验环境：" << environment << "\t<" << curStuNum << "/" << maxStuNum << ">" << endl;
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
	cout << "\t亲爱的 " << stuName << " 你当前一共学习了 " << MyCourses.size() << " 个课程：" << endl;
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
		cout << "您输入的路径有误" << endl;
		return;
	}*/
	f >> ID >> password >> stuName >> courseNum;
	string temp;
	for (int i = 0; i < courseNum; i++) {
		f >> temp;
		MyCourses.insert(temp);		//存入的是课程编号
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
	cout << "学号：" << ID << "\t密码：" << password << "\t姓名：" << stuName << endl;
	cout << "\t学习了" << MyCourses.size() << "个课程：" << endl;
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


int choice(int begin, int end);	//返回指定范围的int
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
//void courseChoosen();	//选课

void read(string path_stu = "student.txt", string path_tea = "teacher.txt", string path_course = "course.txt") {
	fstream f(path_course);
	if (!f) {
		//while (1) {
			cout << "*路径错误，课程导入失败…" << endl;
			//cout << "*请输入课程文件路径：";
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
			cout << "【系统配置】";
			temp->print();
			break;
		}
		case 2: {
			practice* temp = new practice;
			temp->read(f);
			TheCourseMap.insert(pair<string, course*>{temp->courseNum, temp});
			cout << "【系统配置】";
			temp->print();
			break;
		}
		case 3:
			comprehensive* temp = new comprehensive;
			temp->read(f);
			TheCourseMap.insert(pair<string, course*>{temp->courseNum, temp});
			cout << "【系统配置】";
			temp->print();
			break;
		}
	}
	f.close();
	
	f.open(path_stu, ios::in);
	if (!f) {
		cout << "*路径错误，学生导入失败…" << endl;
	}
	while (f.peek() != EOF) {
		student* temp = new student;
		temp->read(f);
		TheStudentMap.insert(pair<string, student>{temp->ID, *temp});
		cout << "【系统配置】";
		temp->print();
	}
	f.close();
	
	f.open(path_tea, ios::in);
	if (!f) {
		cout << "*路径错误，老师导入失败…" << endl;
	}
	while (f.peek() != EOF) {
		teacher* temp = new teacher;
		temp->read(f);
		TheTeacherMap.insert(pair<string, teacher>{temp->ID, * temp});
		cout << "【系统配置】";
		temp->print();
	}
	f.close();

	
	cout << "【系统配置】系统配置完毕" << endl;
}

void save(string path_stu = "student_out.txt", string path_tea = "teacher_out.txt", string path_course = "course_out.txt") {
	fstream f(path_course);
	f.open(path_course, ios::out);
	/*if (!f) {
		cout << "*路径错误，课程导入失败…" << endl;
		return;
	}*/
	map<string, course*> ::iterator it;
	for (it = TheCourseMap.begin(); it != TheCourseMap.end(); it++) {
		it->second->save(f);
	}

	f.close();

	f.open(path_tea, ios::out);
	/*if (!f) {
		cout << "*路径错误，学生导入失败…" << endl;
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


	cout << "输出完毕" << endl;
}

int main() {
	student stu("stu001", "123456", "张三");
	TheStudentMap.insert(pair<string, student>{stu.ID, stu});
	teacher admin("admin", "123456");
	TheTeacherMap.insert(pair<string, teacher>{admin.ID, admin});	//初始化俩人 之后调试也方便
	theory the1("高数", "gs2021", 3, "8:00", "高数1");
	theory the2("c++", "cpp2021", 3, "10:00", "c++课本");
	TheCourseMap.insert(pair<string, course*>{the1.courseNum, & the1});
	TheCourseMap.insert(pair<string, course*>{the2.courseNum, & the2});
	mainManue();
	cout << "是否需要另存为文件：\n\
* 1) 是\n\
* 2）否" << endl;
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
		cout << "您的输入有误，请重新输入。" << endl;
		cin.clear();
		cin.get();
	}
}

void mainManue() {
	int loop = 1;
	while (loop) {
		cout << "*欢迎您使用xnu系统*\n\
* 1) 管理员\n\
* 2）学生\n\
* 3）退出系统\n\
* 请选择登录用户类型[1 - 3]:" << endl;
		int choice(::choice(1,3));
		switch (choice) {
		case 1:
			adminManue();
			break;
		case 2:
			studentManue();
			break;
		case 3:
			cout << "感谢您的使用！\n" << endl;
			loop = 0;
			break;
		}
	}
}

teacher notfound_t;
student notfound_s;		//默认都是空的 想统一用notfound 但是好像不行

teacher& password_tea() {
	string id;
	cout << "请输入您的用户名：";
	cin >> id;
	if (TheTeacherMap.find(id) != TheTeacherMap.end()) {
		cout << "请输入密码：";
		string pw;
		cin >> pw;
		if (TheTeacherMap[id].password == pw) {
			cout << "【登录成功】" << endl;
			return TheTeacherMap[id];
		}
	}
	return notfound_t;
}

student& password_stu() {
	string id;
	cout << "请输入您的用户名：";
	cin >> id;
	if (TheStudentMap.find(id) != TheStudentMap.end()) {
		cout << "请输入密码：";
		string pw;
		cin >> pw;
		if (TheStudentMap[id].password == pw) {
			cout << "【登录成功】" << endl;
			return TheStudentMap[id];
		}
	}
	return notfound_s;
}

void adminManue() {
	teacher &tea(password_tea());
	if (tea.ID == "NULL") {		//如果没有找到就退出
		cout << "您的输入有误" << endl;
		return;
	}
	int loop = 1;
	while (loop) {
		cout << "*欢迎您 " << tea.ID << " ，您的角色是管理员！具有如下功能权限：\n\
*1）学生管理\n\
*2）课程管理\n\
*3）系统配置\n\
*4）统计分析\n\
*5）退出\n\
*请输入命令[1-5]：" << endl;
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
			cout << "*欢迎使用统计分析功能…" << endl;
			map<string, course*> ::iterator it;
			int i;

			cout << "  * Courses *" << endl;
			if (TheCourseMap.begin() == TheCourseMap.end()) {
				cout << "*抱歉库中没有任何课程…" << endl;
			}
			else {
				cout << "*一共有" << TheCourseMap.size() << "门课程…" << endl;
				for (i = 1, it = TheCourseMap.begin(); it != TheCourseMap.end(); it++, i++) {
					cout << "[" << i << "]";
					it->second->print();
				}
			}

			cout << "\n  * Teacher *" << endl;
			if (TheTeacherMap.begin() == TheTeacherMap.end()) {
				cout << "*抱歉库中没有任何管理员…" << endl;
			}
			else {
				i = 1;
				cout << "*一共有" << TheTeacherMap.size() << "个管理员…" << endl;
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
				cout << "*抱歉库中没有任何学生…" << endl;
			}
			else {
				i = 1;
				//map<string, student> ::iterator s;
				cout << "*一共有" << TheStudentMap.size() << "个学生…" << endl;
				for (auto s : TheStudentMap) {
				//for (s = TheStudentMap.begin(); s != TheStudentMap.end(); s++) {
					cout << "[" << i << "]\tID：" << endl;
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
		cout << "*学生管理具有如下功能权限：\n\
*1）添加学生\n\
*2）删除学生\n\
*3）查看学生列表\n\
*4）退出\n\
*请输入命令[1-4]：" << endl;
		int choice(::choice(1,4));
		switch (choice) {
		case 1: {
			cout << "*欢迎使用添加学生功能…";
			string id, password, name;
			cout << "\n【增加用户】请输入学号：";
			cin >> id;
			cout << "\n【增加用户】请输入密码：";
			cin >> password;
			cout << "\n【增加用户】请输入名称：";
			cin >> name;
			student temp(id, password, name);
			TheStudentMap[id] = temp;
			cout << "\n【增加用户】学生已添加" << endl;
			break;
		}
		case 2: {
			cout << "*欢迎使用删除学生功能…";
			string id;
			cout << "\n【删除用户】请输入学号：";
			cin >> id;
			if (TheStudentMap.find(id) == TheStudentMap.end()) {
				cout << "\n【删除用户】删除失败，没有这个学生。" << endl;
				break;
			}
			TheStudentMap.erase(id);
			break;
		}
		case 3: {
			cout << "*欢迎使用查看学生列表功能…" << endl;
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
		cout << "*欢迎进入课程管理模块…\n\
* 1）增加课程\n\
* 2）课程列表\n\
* 3）删除课程\n\
* 4）返回上一级\n\
* 请输入命令[1 - 4]：" << endl;
		int choice(::choice(1,4));
		switch (choice) {
		case 1:
			addCourse();
			break;
		case 2: {
			cout << "*欢迎使用查看课程列表功能…" << endl;
			map<string, course*> ::iterator it;
			int i;
			if (TheCourseMap.begin() == TheCourseMap.end()) {
				cout << "*抱歉库中没有任何课程…" << endl;
				break;
			}
			cout << "*一共有" << TheCourseMap.size() << "门课程…" << endl;
			for (i = 1, it = TheCourseMap.begin(); it != TheCourseMap.end(); it++, i++) {
				cout << "[" << i << "]";
				it->second->print();
			}
			break;
		}
		case 3: {
			cout << "*欢迎使用删除课程功能…" << endl;
			cout << "【删除课程】请输入课程编号：";
			//map<string, course*> ::iterator it;
			string cnum;
			cin >> cnum;
			cin.get();	//吸收回车
			if (!TheCourseMap.erase(cnum)) {
				cout << "【删除课程】删除失败，没有这个课程。" << endl;
				break;
			}
			cout << "【删除课程】删除成功。" << endl;
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
		cout << "*欢迎进入系统配置模块…\n\
* 1）配置文件导入\n\
* 2）设置学生必须选修理论课的学分数\n\
* 3）设置学生必须选修实验课的学分数\n\
* 4）返回上一级\n\
* 请输入命令[1 - 4]：" << endl;
		int choice(::choice(1, 4));
		switch (choice) {
		case 1:
			read();
			break;
		case 2: {
			cout << "【系统配置】请输入理论课必修的学分数：";
			int score;
			while (1) {
				cin >> score;
				if (!cin.fail()) {
					cin.get();
					break;
				}
				cout << "【系统配置】您的输入有误，请重新输入。" << endl;
				cin.clear();
				cin.get();
			}
			neededTheoryScore = score;
			cout << "【系统配置】设置成功" << endl;
			cout << "【系统配置】学生必须选修理论课的学分数为：" << neededTheoryScore << endl;
			break;
		}
		case 3: {
			cout << "【系统配置】请输入实验课必修的学分数：";
			int score;
			while (1) {
				cin >> score;
				if (!cin.fail()) {
					cin.get();
					break;
				}
				cout << "【系统配置】您的输入有误，请重新输入。" << endl;
				cin.clear();
				cin.get();
			}
			neededPracticeScore = score;
			cout << "【系统配置】设置成功" << endl;
			cout << "【系统配置】学生必须选修实验课的学分数为：" << neededTheoryScore << endl;
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
	cout << "*欢迎使用增加课程功能，系统课程类型包括\n\
* 1）理论课\n\
* 2）实验课\n\
* 3）理论实验课\n\
【增加课程】请选择课程类型[1 - 3]：" << endl;
	int choice(::choice(1,3));
	string cnum, cname, ctime, cbook, cdiscribe;
	int cscore;
	cout << "【增加课程】请输入课程编号：";
	cin >> cnum;
	cout << "【增加课程】请输入课程名称：";
	cin >> cname;
	cout << "【增加课程】请输入课程学分：";
	cin >> cscore;
	cout << "【增加课程】请输入上课时间：";
	cin >> ctime;
	switch (choice) {
	case 1: {
		cout << "【增加课程】请输入上课教材：";
		cin >> cbook;
		theory* temp = new theory(cname, cnum, cscore, ctime, cbook);
		TheCourseMap.insert(pair<string, course*>{temp->name, temp});
		break;
	}
	case 2: {
		cout << "【增加课程】请输入实验环境描述：";
		cin >> cdiscribe;
		practice *temp = new practice(cname, cnum, cscore, ctime, cdiscribe);
		TheCourseMap.insert(pair<string, course*>{temp->name, temp});
		break;
	}
	case 3: {
		cout << "【增加课程】请输入上课教材：";
		cin >> cbook;
		cout << "【增加课程】请输入实验环境描述：";
		cin >> cdiscribe;
		comprehensive * temp = new comprehensive(cname, cnum, cscore, ctime, cbook, cdiscribe);
		TheCourseMap.insert(pair<string, course*>{temp->name, temp});
		break;
	}
	}
	cout << "【增加课程】课程已添加。" << endl;
}

void studentManue() {
	student& stu(password_stu());
	if (stu.ID == "NULL") {		//如果没有找到就退出
		cout << "您的输入有误" << endl;
		return;
	}
	
	int loop = 1;
	while (loop) {
		cout << "*欢迎您 " << stu.ID << " ，您的角色是学生！具有如下功能权限：\n\
*1）浏览课程\n\
*2）已选课程\n\
*3）选课\n\
*4）退课\n\
*5）退出\n\
*请输入命令[1-5]：" << endl;
		int ch(choice(1,5));
		switch (ch) {
		case 1: {
			map<string, course*> ::iterator it;
			int i;
			if (TheCourseMap.begin() == TheCourseMap.end()) {
				cout << "*抱歉库中没有任何课程…" << endl;
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
			cout << "*欢迎使用选课功能…" << endl;
			cout << "【选课规则】课程的学分为1~3个学分" << endl;
			cout << "【选课规则】每学生必修的理论课学分为：" << neededTheoryScore << endl;
			cout << "【选课规则】每学生必修的实验课学分为：" << neededPracticeScore << endl;
			cout << "【选课规则】修满学分后将不能够再选课" << endl << endl;
			cout << "【选课】选课之前请仔细阅读选课规则：" << endl;
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

			cout << "【选课】你的理论课已经修了<" << myTheoryScore << "/" << neededTheoryScore << ">学分";
			if (myTheoryScore >= neededTheoryScore) {
				cout << "，无需再选理论课。" << endl;
			}
			else {
				cout << endl;
			}
			cout << "【选课】你的实验课已经修了<" << myPracticeScore << "/" << neededPracticeScore << ">学分";
			if (myPracticeScore >= neededPracticeScore) {
				cout << "，无需再选实验课。" << endl;
			}
			else {
				cout << endl;
			}
			if (myTheoryScore >= neededTheoryScore && myPracticeScore >= neededPracticeScore) {
				break;
			}
			///////////////////////////////////////////////////////////////////此处还没改完 之后还需要 理论课修满的情况下只能修实验课 都修满了就直接结束
			cout << "【选课】请输入你想选课程的课程代号：";
			string temp;
			cin >> temp;
			if (TheCourseMap.find(temp) == TheCourseMap.end()) {
				cout << "【选课】没有这门课，请检查您的输入。" << endl;
				break;
			}
			if (stu.MyCourses.find(temp) != stu.MyCourses.end()) {
				cout << "【选课】你已经选过 " << temp << " ，请勿重复选课。" << endl;
				break;
			}
			if ((TheCourseMap.find(temp)->second->type == 1 || TheCourseMap.find(temp)->second->type == 3) && myTheoryScore >= neededTheoryScore) {
				cout << "【选课】您修的理论课学分已满，不可再选理论课" << endl;
			}
			if ((TheCourseMap.find(temp)->second->type == 2 || TheCourseMap.find(temp)->second->type == 3) && myPracticeScore >= neededPracticeScore) {
				cout << "【选课】您修的实验课学分已满，不可再选实验课" << endl;
			}

			stu.MyCourses.insert(temp);
			TheCourseMap.find(temp)->second->curStuNum++;	//在课程中增加人数
			cout << "【选课】选课成功" << endl;
			stu.printMyCoures();
			break;
		}
		case 4: {
			cout << "*欢迎使用退课功能…" << endl;
			cout << "【退课】请输入课程编号：";
			string temp;
			cin >> temp;
			if (stu.MyCourses.find(temp) == stu.MyCourses.end()) {
				cout << "【退课】删除失败，你没有选这门课程。" << endl;
				break;
			}
			cout << "【退课】要退掉该课程吗？" << endl;
			TheCourseMap.find(temp)->second->print();
			cout << "*1）是" << endl;
			cout << "*2）否" << endl;
			if (choice(1, 2) == 2) {
				cout << "【退课】退课失败" << endl;
				break;
			}
			stu.MyCourses.erase(temp);
			TheCourseMap.find(temp)->second->curStuNum--;	//在课程中减少人数
			cout << "【退课】退课成功" << endl;
			stu.printMyCoures();
			break;
		}
		case 5:
			loop = 0;
			break;
		}
	}
}
