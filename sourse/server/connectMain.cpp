#include <iostream>
#include <cstring>
#include "connectDB.cpp"

using namespace std;

int main() {
    cout << "Hello, World!" << endl;
    try {
        // DB연결 객체 생성
        sql::Driver* driver = sql::mariadb::get_driver_instance();
        // 연결할 DB의 특정 IP, DB를 정의 (mariaDB localhost is '3306')
        sql::SQLString url("jdbc:mariadb://localhost:3306/LIBRARY");
        // 연결할 DB를 사용할 유저를 정의
        sql::Properties properties({{"user", "USER"}, {"password", "1234"}});
        // 객체에 값을 통하여 연결을 시도
        std::unique_ptr<sql::Connection> conn(driver->connect(url, properties));

        showTasks(conn);

        FILE * fp = fopen("/home/lms/github/LMS_Project_05/data/Library_data.csv", "rt");

        char str[100000];
        char *jmNum;
        char *title;
        char *author;
        char *publisher;
        int stock;

        while(fgets(str,sizeof(str),fp))
        {
            strtok(str, ",");
            strtok(NULL, ",");
            strtok(NULL, ",");
            jmNum = strtok(NULL, ",");
            cout << "jmNum: " << jmNum << endl;
            title = strtok(NULL, ",");
            cout << "title: " << title << endl;
            author = strtok(NULL, ",");
            cout << "author: " << author << endl;
            publisher = strtok(NULL, ",");
            cout << "publisher: " << publisher << endl;
            strtok(NULL, "\n");
            addTask(conn, jmNum, title, author, publisher);
        }
        
        // addTask(conn, "등록번호", "제목", "작가", "출판사");
        
        // updateTask(conn, "Tom", true);
        // deleteTask(conn, "None");
        std::cout << "-------------------------------" << std::endl;
        showTasks(conn);


    // 연결 실패시 오류 발생
    } catch(sql::SQLException& e) {
        std::cerr << "Error Connecting to MariaDB Platform: " << e.what() << std::endl;
        // 프로그램 비정상 종료
        return 1;
    }

    return 0;
}