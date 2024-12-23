// Includes
#include <iostream>
#include <mariadb/conncpp.hpp>

// DELETE문 실행 함수(등록번호를 이용한)
void deleteTask(std::unique_ptr<sql::Connection> &conn, std::string jmNum) {
    try {
        // PreparedStatement 객체 생성
        std::unique_ptr<sql::PreparedStatement> stmnt(conn->prepareStatement("delete from tasks where jmNum = ?"));
        // 객체에 값을 전달
        stmnt->setString(1, jmNum);
        // 객체의 내부 함수를 이용하여 쿼리를 실행
        stmnt->executeQuery();
    // 실패시 오류 메세지 반환
    } catch(sql::SQLException& e){
      std::cerr << "Error deleting task: " << e.what() << std::endl;
   }
}

// UPDATE문 실행 함수(등록번호를 이용하여 재고량을 바꿈)
void updateTask(std::unique_ptr<sql::Connection> &conn, std::string jmNum, int stock) {
    try {
        // PreparedStatement 객체 생성
        std::unique_ptr<sql::PreparedStatement> stmnt(conn->prepareStatement("update tasks set author = ? where jmNum = ?"));
        // 객체에 값을 전달
        stmnt->setInt(1, stock);
        stmnt->setString(2, jmNum);
        // 객체의 내부 함수를 이용하여 쿼리를 실행
        stmnt->executeQuery();
    // 실패시 오류 메세지 반환
    } catch(sql::SQLException& e){
      std::cerr << "Error updating task status: " << e.what() << std::endl;
   }
}

// Insert문 실행 함수
// 인자로 값을 넣는다. (id값은 AUTO_INCEREMENT이기 때문에 없어도 상관 없다.)
void addTask(std::unique_ptr<sql::Connection> &conn, std::string jmNum, std::string title, std::string author, std::string publisher) {
    try {
        // PreparedStatement 객체 생성
        std::unique_ptr<sql::PreparedStatement> stmnt(conn->prepareStatement("insert into tasks values (default, ?, ?, ?)"));
        // 객체에 값을 전달
        stmnt->setString(1, jmNum);
        stmnt->setString(2, title);
        stmnt->setString(3, author);
        stmnt->setString(4, publisher);
        // 객체의 내부 함수를 이용하여 쿼리를 실행
        stmnt->executeQuery();
    // 실패시 오류 메세지 반환
    } catch(sql::SQLException& e){
      std::cerr << "Error inserting new task: " << e.what() << std::endl;
   }
}

// SELECT문 실행 함수
void showTasks(std::unique_ptr<sql::Connection> &conn) {
    try {
        // createStaemet 객체 생성
        std::unique_ptr<sql::Statement> stmnt(conn->createStatement());
        // 쿼리를 실행
        sql::ResultSet *res = stmnt->executeQuery("select * from tasks");
        // 반복문을 통해서 내부의 값을 반환
        while (res->next()) {
            std::cout << "등록번호: " << res->getString(1);
            std::cout << ", 제목: " << res->getString(2);
            std::cout << ", 작가: " << res->getString(3);
            std::cout << ", 출판사: " << res->getString(4);\
        }
    // 실패시 오류 메세지 반환
    } catch(sql::SQLException& e){
      std::cerr << "Error selecting tasks: " << e.what() << std::endl;
   }
}

// int main() {
//     cout << "Hello, World!" << endl;
//     try {
//         // DB연결 객체 생성
//         sql::Driver* driver = sql::mariadb::get_driver_instance();
//         // 연결할 DB의 특정 IP, DB를 정의 (mariaDB localhost is '3306')
//         sql::SQLString url("jdbc:mariadb://localhost:3306/Library");
//         // 연결할 DB를 사용할 유저를 정의
//         sql::Properties properties({{"user", "USER"}, {"password", "1234"}});
//         // 객체에 값을 통하여 연결을 시도
//         std::unique_ptr<sql::Connection> conn(driver->connect(url, properties));

//         showTasks(conn);
//         // addTask(conn, "등록번호", "제목", "작가", "출판사");
//         addTask(conn, "Tom", 15, false);
//         addTask(conn, "None", 0, false);
//         updateTask(conn, "Tom", true);
//         deleteTask(conn, "None");
//         std::cout << "-------------------------------" << std::endl;
//         showTasks(conn);


//     // 연결 실패시 오류 발생
//     } catch(sql::SQLException& e) {
//         std::cerr << "Error Connecting to MariaDB Platform: " << e.what() << std::endl;
//         // 프로그램 비정상 종료
//         return 1;
//     }

//     return 0;
// }