#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>
#include <sstream>
#include <cstdlib>

using namespace std;

vector<vector<string> > vector_object(const char *file_name) {
    ifstream fileName;
    fileName.open(file_name);
    string d;
    vector <string> myVec;
    vector<vector<string> > data;
    int i = 0;
    while (!fileName.eof()) {
       fileName >> d;
       stringstream ss(d);
       vector <string> myVec;
       string token;
       while (getline(ss, token, ',')) {
            myVec.push_back(token);
       }
       data.push_back(myVec);
       i += 1;
    }
    data.erase(data.end() - 1);
    return data;
}

void csv_create(const char *file_name, vector<vector<string> > data) {
    string str = "", temp = "";
    for (int i = 0; i < data.size(); ++i) {
        for (int j = 0; j < data[i].size(); ++j) {
            temp = data[i][j] + ",";
            str += temp;
        }
        str.erase(str.size() - 1, 1);
        str = str + '\n';
    }
    ifstream fin;
    ofstream fs;
    fs.open (file_name);
    fs << str;
    fs.close();
}

class Person{
protected:
    string name, dept, email, phone, semester, pass;
public:
    virtual void registration() = 0;
};

class Feedback {
public:
    void create_feedback() {
        ifstream fin;
        ofstream fs;
        fin.open("Feedback_form.csv", ios :: in);
        if (fin.is_open()) {
            fin.close();
        }
        fs.open ("Feedback_form.csv");
        string temp = "", token = "";
        for (int i = 0; i < 5; ++i) {
            cout << "Add Questions [" << i << "] : ";
            cin >> token;
            temp = temp + token +"\n";
            cout << endl;
        }
        fs << temp;
        fs.close();
    }
    void get_feedback(string rollno, string semester, string dept, string flag) {
        if (flag == "0") {
            cout << "You are not registered!\n";
            return;
        }
        vector <vector <string> > data = vector_object("Course_info.csv");
        cout << "Courses available are : \n";
        string op;
        for (int i = 0; i < data.size(); ++i) {
                if (semester == data[i][2] && dept == data[i][1]) {
                    //cout << data[i][0] << " " << data[i][3] ;
                    op = data[i][0];
                    cout << "\t\t\t" << op << "\t\t" << data[i][3] << endl;
                }
        }
        cout << endl;
        ofstream fs;
        int c;
        do {
            char code[10];
            cout << "Enter Course code : ";
            cin >> code;
            string feed = "", temp;
            int flag = 0,index;
            strcat(code, ".csv");
            vector <vector <string> > data = vector_object(code);
            for (int i = 0; i < data.size(); ++i) {
                    if (data[i][0] == rollno ) {
                        if( data[i][6] == "yes") {
                            flag = 1;
                            cout << "Already Submitted ...\n";
                            cout << "Do you want to continue (0/1) \n";
                            cin >> c;
                        }
                        else{cout<<"else";
                            index = i;

                            vector <vector <string> > que = vector_object("Feedback_form.csv");
                            cout << "Fill Feedback (1 to 5) : ";
                            for (int i = 0; i < que.size(); ++i) {
                                cout << que[i][0] << " : ";
                                cin >> temp;
                                data[index][i+1]=temp;
                            }
                            data[index][6]="yes";
                            csv_create(code, data);

                            cout << "Do you want to continue?(0/1)";
                            cin >> c;
                        }
                    }
            }
        } while(c != 0);
    }
};

void printLine(int N) {
    int count = 0;
    while (count++ < N) {
        cout << "_";
    }
    cout << endl;
}

class Student: public Person {

public:
    string rollno;
    void csv(string name, string rollno, string dept, string semester, string email, string phone, string pass) {
        string FILE_HEADER = "Name,RollNo,Dept,Semester,Email,Phone,Password,Flag";
        ifstream fin;
        ofstream fs;
        fin.open("Student_info.csv", ios :: in);
        if (fin.is_open()) {
            fin.close();
        } else {
            fs.open ("Student_info.csv", std::ios_base::app);
            fs << FILE_HEADER << endl;
            fs.close();
        }
        fs.open ("Student_info.csv", std::ios_base::app);
        fs << name << "," << rollno << "," << dept << "," << semester << "," << email << "," << phone << "," << pass << "," << "0" << endl;
        fs.close();
    }
    void registration(){
        char code[10];
        cout << "Enter Name : ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter RollNo : ";
        cin >> rollno;
        cout << "Enter Dept : ";
        cin >> dept;
        cout << "Enter Semester : ";
        cin >> semester;
        cout << "Enter Email : ";
        cin >> email;
        cout << "Enter Phone : ";
        cin >> phone;
        cout << "Enter Password : ";
        cin >> pass;
        csv(name, rollno, dept, semester, email, phone, pass);
        if (semester > "4") {
            vector <vector <string> > data = vector_object("Course_info.csv");
            cout << "optional Courses available in this semesters are : ";
            string op;
            cout << endl;
            for (int i = 0; i < data.size(); ++i) {
                    if (semester == data[i][2]) {
                        op = data[i][0];

                        cout << op << " " << data[i][3] << endl;
                    }
            }
            cout << endl;
            int ch;
            do {
                ofstream fs;
                cout << "Enter Course code : ";
                cin >> code;
                strcat(code, ".csv");
                fs.open (code, std::ios_base::app);
                fs << rollno << ",0,0,0,0,0,no" << endl;
                fs.close();
                cout << "Do you want to add more courses?(0/1) :";
                cin >> ch;
            } while (ch != 0);
        } else {
            vector <vector <string> > data = vector_object("Course_info.csv");
            cout << "Courses available in this semesters are : ";
            string op;
            cout << endl;
            for (int i = 0; i < data.size(); ++i) {
                    if (semester == data[i][2]) {
                        op = data[i][0];

                        cout << op << " " << data[i][3] << endl;
                    }
            }
            cout << endl;
            int ch;
            do {
                ofstream fs;
                cout << "Enter Course code : ";
                cin >> code;
                strcat(code, ".csv");
                vector <vector <string> > data = vector_object(code);
                for (int i = 0; i < data.size(); ++i) {
                    if (data[i][0] == rollno) {
                        cout << "Already registered!" << endl;
                    } else {
                        cout << "Registered " << endl;
                        fs.open (code, std::ios_base::app);
                        fs << rollno << ",0,0,0,0,0,no" << endl;
                        fs.close();
                    }
                }
                cout << "Do you want to register for more courses?(0/1) :";
                cin >> ch;
            } while (ch != 0);
        }
    }

    void display(){
        int line = 0;
        vector <vector <string> > data = vector_object("Student_info.csv");

        printLine(127);
        for (int i = 0; i < data.size(); ++i) {
            if (line == 1)
                printLine(127);
            for (int j = 0; j < data[i].size(); ++j) {
                if (i == 0) {
                    cout << data[i][j];
                    if (j == 4) {
                        cout << "                   |";
                    } else {
                        cout << "        |";
                    }
                } else {
                    if (j == 4) {
                        int elen = data[i][j].length();
                        cout << data[i][j];
                        while (elen <= 25) {
                            cout << " ";
                            elen++;
                        }
                        cout << "|";
                        continue;
                    }
                    if (j == 6) {
                        int p = data[i][j].length();
                        cout << data[i][j];
                        while (p <= 15) {
                            cout << " ";
                            ++p;
                        }
                        cout << "|";
                        continue;
                    }
                    if (j == 7) {
                        cout << data[i][j];
                        int M = 0;
                        while(M < 11) {
                            cout << " ";
                            M += 1;
                        }
                        cout << "|";
                        continue;
                    }
                    int len = data[i][j].length();
                    cout << data[i][j];
                    while (len <= 12) {
                        cout << " ";
                        len++;
                    }
                    cout << "|";
                    len = 0;
                }
            }
            if (line == 0) {
                cout << endl;
                printLine(127);
                line = 1;
            }
            cout << endl;
        }
        printLine(127);
        cout << endl;
    }

};

class Faculty: public Person {
    void csv(string name, string dept, string email, string phone) {
        string FILE_HEADER = "Name,Dept,Email,Phone";
        ifstream fin;
        ofstream fs;
        fin.open("Faculty_info.csv", ios :: in);
        if (fin.is_open()) {
            fin.close();
        } else {
            fs.open ("Faculty_info.csv", std::ios_base::app);
            fs << FILE_HEADER << endl;
            fs.close();
        }
        fs.open ("Faculty_info.csv", std::ios_base::app);
        fs << name << "," << dept << "," << email << "," << phone << endl;
        fs.close();
    }
public:
    void registration(){
        cout << "Enter Name : ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter Dept. : ";
        cin >> dept;
        cout << "Enter Email : ";
        cin >> email;
        cout << "Enter Phone : ";
        cin >> phone;
        csv(name, dept, email, phone);
    }
    void view_cources(string user_name) {
        vector <vector <string> > data = vector_object("Course_info.csv");
        for (int i = 0; i < data.size(); ++i) {
            if (data[i][3] == user_name) {
                cout << data[i][0] << " " << data[i][1] << " " << data[i][2] << endl;
            }
        }
    }

    void view_feedback(char *subject ,string user_name) {
        string sub=subject;
        strcat(subject, ".csv");
        vector <vector <string> > d = vector_object("Course_info.csv");
        for (int i = 0; i < d.size(); ++i) {
            if (d[i][0] == sub ){
                if( d[i][3] != user_name ){
                    cout << "Wrong Course Entered !!!\n";
                    return;
                }
                else {
                        float Average[6];
                        string temp;
                        int count = 0, submitted = 0, non_submitted = 0;
                        char c;
                        vector <vector <string> > data = vector_object(subject);
                        for (int k = 0; k < 5; ++k) {
                            for (int i = 1; i < data.size(); ++i) {
                                if (data[i][6] == "yes") {
                                    submitted++;
                                    temp = data[i][k + 1];
                                    c = temp[0];
                                    count = count + int(c) - 48;
                                } else {
                                    non_submitted++;
                                }
                            }
                            Average[k] = (float)count/submitted;
                            count = 0;
                        }
                        vector <vector <string> > sawal = vector_object("Feedback_form.csv");
                        printLine(25);
                        for (int i = 0; i < 5; ++i) {
                            cout << sawal[i][0] << "     :   " << Average[i] << endl;
                        }
                        submitted /=5;
                        non_submitted /=5;
                        cout << "Total Students : " << (submitted + non_submitted) << endl;
                        cout << "students submitted feedback : " << submitted << endl;
                        cout << "students not submitted feedback : " << non_submitted << endl;
                        return;

                }

            }
        }

    }

    void display(){
        vector <vector <string> > data = vector_object("Faculty_info.csv");
        printLine(70);
        int line = 0;
        for (int i = 0; i < data.size(); ++i) {
            if (line == 1) {
                printLine(70);
            }
            for (int j = 0; j < data[i].size(); ++j) {
                if (i == 0) {
                    cout << data[i][j];
                    if (j == 2) {
                        cout << "                     |";
                    } else {
                        cout << "         |";
                    }
                } else {
                    if (j == 2) {
                        int elen = data[i][j].length();
                        cout << data[i][j];
                        while (elen <= 25) {
                            cout << " ";
                            elen++;
                        }
                        cout << "|";
                        continue;
                    }
                    if (j == 3) {
                        int l = data[i][j].length();
                        cout << data[i][j];
                        while (l <= 13) {
                            cout << " ";
                            l++;
                        }
                        cout << "|";
                        continue;
                    }
                    int len = data[i][j].length();
                    cout << data[i][j];
                    while (len <= 12) {
                        cout << " ";
                        len++;
                    }
                    cout << "|";
                    len = 0;
                }
            }
            if (line == 0) {
                cout << endl;
                printLine(70);
                line = 1;
            }
            cout << endl;
        }
        printLine(70);
        cout << endl;
    }
    void courseOffer(string instructor) {
        int choice;
        do {
            string sem;
            string d;
            cout << "Enter semseter : ";
            cin >> sem;
            cout << "Enter Department : ";
            cin >> d;
            char course[10];
            cout << "Enter Course Name : ";
            cin >> course;
            ofstream fp;
            strcat(course, ".csv");
            fp.open (course);
            ofstream fs;
            ifstream fin;
            if (fp.is_open()) {
                string FILE_HEADER = "RollNo,Q1,Q2,Q3,Q4,Q5,Submit";
                fp << FILE_HEADER << endl;
                fp.close();
            }
            int flag;
            if (sem < "5") {
                vector <vector <string> > data = vector_object("Student_info.csv");
                vector <vector <string> > c = vector_object(course);
                for (int i = 0; i < data.size(); ++i) {
                    flag = 0;
                    if (data[i][3] == sem && data[i][2] == d) {
                        for (int k = 0; k < c.size(); ++k) {
                            if (c[k][0] == data[i][1]) {
                                flag = 1;
                            }
                        }
                        if (flag != 1) {
                            fp.open (course, std::ios_base::app);
                            fp << data[i][1] << ",0,0,0,0,0,no" << endl;
                            fp.close();
                        }
                    }
                }
            }
            string FILE_HEADER = "CourseName,Dept,Semester,Instructor";
            fin.open("Course_info.csv", ios :: in);
            if (fin.is_open()) {
                fin.close();
            } else {
                fs.open ("Course_info.csv", std::ios_base::app);
                fs << FILE_HEADER << endl;
                fs.close();
            }
            fs.open ("Course_info.csv", std::ios_base::app);
            fs << course << "," << d << "," << sem << "," << instructor << endl;
            fs.close();

            cout << "Do you want to add more courses(0/1)?";
            cin >> choice;
        } while(choice != 0);
    }

};

class Login {
public:
    void login(int choice);
};

void Login :: login(int choice) {
    string user_name, password;
    cout << "\t\t User Name : ";
    cin.ignore();
    getline(cin, user_name);
    cout << "\t\t Password : ";
    cin >> password;
    if (choice == 1) {
        vector <vector <string> > data = vector_object("Student_info.csv");
        for (int i = 0; i < data.size(); ++i) {
            if (data[i][0] == user_name) {
                cout << password << endl;
                if (data[i][6] == password) {
                    cout << "success!\n";
                    Feedback fb;
                    fb.get_feedback(data[i][1], data[i][3], data[i][2], data[i][7]);
                } else {
                    cout << "Failure!\n";
                }
            }
        }
    } else {
        vector <vector <string> > data = vector_object("Faculty_info.csv");
        for (int i = 0; i < data.size(); ++i) {
            if (data[i][0] == user_name) {
                if (data[i][1] == password) {
                    cout << "success!\n";
                    Faculty f;
                    f.view_cources(user_name);
                    int type;
                    cout << "1 - VIEW FEEDBACK\n";
                    cout << "2 - ADD COURSE\n";
                    cout << "Enter your choice : ";
                    cin >> type;
                    char cs[10];
                    if (type == 1) {
                        cout << "Display feedback of course? ";
                        cin >> cs;
                        f.view_feedback(cs,user_name);
                    } else {
                        f.courseOffer(user_name);
                    }
                } else {
                    cout << "Failure!\n";
                }
            }
        }
    }
}

class Admin {
public:
    void manage() {
        Student s;
        s.display();
        int c;
        string rollno;
        do {
            cout << "Enter RollNo : ";
            cin >> rollno;
            int i;
            string yes_no;
            vector <vector <string> > data = vector_object("Student_info.csv");
            for (i = 0; i < data.size(); ++i) {
                if (data[i][1] == rollno) {
                    cout << "\nRegister this rollno(0/1)? ";
                    cin >> yes_no;
                    data[i][7] = yes_no;
                    break;
                }
            }
            if (i == data.size()) {
                cout << "No such rollno exist!\n";
            }
            cout << "Do you want to register more students?(0/1)";
            cin >> c;
            csv_create("Student_info.csv", data);
        } while(c != 0);
    }
};

class Menu {
public:
    void display() {
        int choice, type;
        do {
            cout << "\n\t\t\tINDIAN INSTITUTE OF INFORMATION TECHNOLOGY-DHARWAD\n\n";
            cout << "\t\t\t1 - ADMIN\n";
            cout << "\t\t\t2 - STUDENT\n";
            cout << "\t\t\t3 - FACULTY\n";
            cout << "\t\t\t4 - EXIT\n\n";
            cout << "\t\t\tEnter your choice : ";
            cin >> choice;
            if (choice == 1) {
                do {
                    cout << "\t\t\t1 - STUDENT\n";
                    cout << "\t\t\t2 - FACULTY\n";
                    cout << "\t\t\t3 - FEEDBACK\n";
                    cout << "\t\t\t4 - MANAGE\n";
                    cout << "\t\t\t5 - EXIT\n\n";
                    cout << "\t\t\tEnter your choice : ";
                    cin >> type;
                    if (type == 1) {
                        Student s;
                        s.display();
                    } else if (type == 2) {
                        Faculty f;
                        f.display();
                    }
                    else if (type == 3) {
                        Feedback fb;
                        fb.create_feedback();
                    } else if (type == 4) {
                        Admin a;
                        a.manage();
                    } else if(type == 5)
                        system("clear");
                    else {
                        cout << "Invalid Selection!\n";
                    }
                } while(type != 5);
            } else if (choice == 2) {
                do {
                    cout << "\t\t\t1 - REGISTER\n";
                    cout << "\t\t\t2 - LOGIN\n";
                    cout << "\t\t\t3 - EXIT\n\n";
                    cout << "\t\t\tEnter your choice : ";
                    cin >> type;
                    if (type == 1) {
                        Student s;
                        s.registration();
                    } else if (type == 2) {
                        Login l;
                        l.login(1);
                    }else if (type == 3)
                        system("clear");
                    else {
                        cout << "Invalid Selection!\n";
                    }
                } while (type != 3);
            } else if (choice == 3) {
                do {
                    cout << "\t\t\t1 - REGISTER\n";
                    cout << "\t\t\t2 - LOGIN\n";
                    cout << "\t\t\t3 - EXIT\n\n";
                    cout << "\t\t\tEnter your choice : ";
                    cin >> type;
                    if (type == 1) {
                        Faculty f;
                        f.registration();
                    } else if (type == 2) {
                        Login l;
                        l.login(2);
                    } else if (type == 3)
                        system("clear");
                    else {
                        cout << "Invalid Selection!\n";
                    }
                } while (type != 3);
            }else if (choice == 4)
                system("clear");
            else {
                cout << "Invalid Selection!\n";
            }
        } while(choice != 4);
    }
};

void init() {
    ifstream fin;
    ofstream fs;
    fin.open("Student_info.csv", ios :: in);
    if (fin.is_open()) {
        fin.close();
    } else {
        fs.open ("Student_info.csv");
        fs.close();
    }
    fin.open("Course_info.csv", ios :: in);
    if (fin.is_open()) {
        fin.close();
    } else {
        fs.open ("Course_info.csv");
        fs.close();
    }
    fin.open("Faculty_info.csv", ios :: in);
    if (fin.is_open()) {
        fin.close();
    } else {
        fs.open ("Faculty_info.csv");
        fs.close();
    }
}

int main(){
    init();
    Menu m;
    m.display();
    return 0;
}
