#include <iostream>
#include <cstring>
#include <mariadb/conncpp.hpp>

using namespace std;
using namespace sql;

class Database
{
    private:
        /* data */
    public:
        string searchResult;
        int resultCount;
        sql::Driver* driver;
        sql::ResultSet *res;
        unique_ptr<sql::Connection> conn;
        void showTasks(unique_ptr<sql::Connection> &conn); // SELECT문 실행 함수
        void showSelectedTasks(unique_ptr<sql::Connection> &conn, string BOOKNAME); // SELECT문 실행 함수 2
        void openDB(string user_input);
};

void Database::showTasks(unique_ptr<sql::Connection> &conn) {
    try {
        // createStaemet 객체 생성
        unique_ptr<sql::Statement> stmnt(conn->createStatement());
        // 쿼리를 실행
        sql::ResultSet *res = stmnt->executeQuery("select * from BOOKINFO");
        // 반복문을 통해서 내부의 값을 반환
        while (res->next()) {
            cout << "연번: " << res->getInt(1);
            // cout << ", 소장도서관: " << res->getString(2);
            // cout << ", 자료실명: " << res->getString(3);
            cout << ", 등록번호: " << res->getString(4);
            cout << ", 도서명: " << res->getString(5);
            cout << ", 저자: " << res->getString(6);
            cout << ", 출판사: " << res->getString(7);
            // cout << ", 출판연도: " << res->getInt(8);
            cout << ", 청구기호: " << res->getString(9);
            // cout << ", 데이터기준일자: " << res->getString(10);
            cout << ", 재고량: " << res->getInt(11) << endl;
        }
    // 실패시 오류 메세지 반환
    } catch(sql::SQLException& e){
      cerr << "Error selecting tasks: " << e.what() << endl;
   }
}

void Database::showSelectedTasks(unique_ptr<sql::Connection> &conn, string BOOKNAME) {
    try {
        // PreparedStatement 객체 생성
        unique_ptr<sql::Statement> stmnt(conn->createStatement());
        // 쿼리 실행
        string str =  "select BOOKNAME from BOOKINFO where BOOKNAME like '%" + BOOKNAME + "%'"; 
        res = stmnt->executeQuery(str);
        // 객체에 값을 전달
        int i = 0;
        while (res->next()) {
            searchResult += res->getString(1) + "\n";
            i++;
        }
        resultCount = i;
        // cout << searchResult << endl;
        // cout << "-------------------------------" << endl;
        // cout << BOOKNAME << " 검색 결과입니다." << endl;
        // cout << "총 " << resultCount << "건" << endl;
        // 객체의 내부 함수를 이용하여 쿼리를 실행

    // 실패시 오류 메세지 반환
    } catch(sql::SQLException& e){
      cerr << "Error selecting tasks: " << e.what() << endl;
   }
}

void Database::openDB(string user_input)
{
    cout << "Hello, World!" << endl;
    try {
        // DB연결 객체 생성
        driver = sql::mariadb::get_driver_instance();
        // 연결할 DB의 특정 IP, DB를 정의 (mariaDB localhost is '3306')
        sql::SQLString url("jdbc:mariadb://localhost:3306/LIBRARY");
        // 연결할 DB를 사용할 유저를 정의
        sql::Properties properties({{"user", "USER"}, {"password", "1234"}});
        // 객체에 값을 통하여 연결을 시도
        unique_ptr<sql::Connection> conn(driver->connect(url, properties));
        // showTasks(conn);
        cout << "-------------------------------" << endl;
    
    while (1)
    {
        if (user_input == "q" || user_input == "Q")
        {
            break;
        }
        showSelectedTasks(conn, user_input);
        return;
    }
    }
    // 연결 실패시 오류 발생
    catch(sql::SQLException& e) {
        cerr << "Error Connecting to MariaDB Platform: " << e.what() << endl;
        // 프로그램 비정상 종료
        return;
    }
}

// int main()
// {
//     Database dat;
//     string user_input;

//     cout << "입력해라 : ";
//     cin >> user_input;
//     dat.openDB(user_input);
//     return 0;
// }