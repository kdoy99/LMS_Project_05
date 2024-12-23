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

        // showTasks(conn);
        // addTask(conn, "등록번호", "제목", "작가", "출판사");
        // updateTask(conn, "Tom", true);
        // deleteTask(conn, "None");
        std::cout << "-------------------------------" << std::endl;

    while (1)
    {
        string input;
        cout << "책 제목 검색 (종료하려면 q): ";
        cin >> input;
        if (input == "q" || input == "Q")
        {
            break;
        }
        showSelectedTasks(conn, input);
    }

    // 연결 실패시 오류 발생
    } catch(sql::SQLException& e) {
        std::cerr << "Error Connecting to MariaDB Platform: " << e.what() << std::endl;
        // 프로그램 비정상 종료
        return 1;
    }

    return 0;
}