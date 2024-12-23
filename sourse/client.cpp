#include <iostream>
#include <cstdlib>
#include <cstring>
#include <sys/socket.h>

using namespace std;
enum{EM = 10, NM = 20, BM = 30};

struct Book_Information
{
    char Book_Name[50];
    char Author[50];         // 작가
    char Publisher[50];      // 출판사
    int Book_Rental;
};

struct Member_Information
{
    char ID[20];
    int PW[20];
    char Name[20];
    char Residence[50]; //거주지
    int PhoneNumber;
    int Grade;
};


int main(void)
{
    Book_Information BI;
    Member_Information MI;
    // 로그인 및 회원가입


    // 회원 등급 관리
    int EM,NM,BM;    //EM=Exellent Member, NM=Normal Member, BM=Black Member
    int Period=0; //가입기간
    int Book_Return=0; //책 반납
    int Overdue=0; //연체
    int Overdue_Date=0; //연체일
    int Rental_Date=0; //대여일
    
    MI.Grade = NM;

    while(1)
    {
        if(Period > 6 * 30 && Book_Return >= 10)
            MI.Grade = EM;
        else if(Overdue > 3 || Overdue_Date )
            MI.Grade = BM;
        else
            MI.Grade = NM;


        if(MI.Grade == EM){
            Overdue_Date = Rental_Date -7;
            if(Overdue_Date > 0)
                Overdue +=1;
        }
        else if(MI.Grade == NM){
            Overdue_Date = Rental_Date -5;
            if(Overdue_Date > 0)
                Overdue +=1;
        }                
    }

    //도서조회


    //대여 및 반납
}