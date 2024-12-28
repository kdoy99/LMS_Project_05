#include <iostream>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#define min '1'
#define max '3' 
using namespace std;

enum
{
    EM = 10,
    NM = 20,
    BM = 30
};

struct Book_Information
{
    char Book_Name[50];
    char Author[50];    // 작가
    char Publisher[50]; // 출판사
    int Book_Rental;
};

struct Member_Information
{
    char ID[20];
    char PW[50];
    char Name[20];
    char Residence[20]; // 거주지
    int PhoneNumber;
    int Grade;
    char Rental_Book[40];
};

void book_find(int *b_idx, Book_Information BI);
void login(Member_Information *MI, Book_Information *BI, int *m_idx, int *mt_idx);
char InputMenu();

int main(void)
{
    Book_Information BI[200];
    Member_Information MI[200];
    int m_idx = 0; // 고객 정보 저장
    int mt_idx = 0; // ID, Pw 구조체 배열에 넣을 때 사용할 변수
    int b_idx = -1; // 대여한 책 정보 저장
    char login_ID[20];
    login(MI, BI, &m_idx, &mt_idx);

    // 회원 등급 관리
    int EM, NM, BM;       // EM=Exellent Member, NM=Normal Member, BM=Black Member
    int Period = 0;       // 가입기간
    int Book_Return = 0;  // 책 반납
    int Overdue = 0;      // 연체
    int Overdue_Date = 0; // 연체일
    int Rental_Date = 0;  // 대여일

    while (1)
    {
        if (Period > 6 * 30 && Book_Return >= 10)
        {
            cout << "고객님의 등급이 우수회원으로 변경되었습니다.\n";
            MI[m_idx].Grade = EM;
        }
        else if (Overdue > 3 || Overdue_Date)
        {
            cout << "고객님의 등급이 블랙회원으로 변경되었습니다.\n";
            MI[m_idx].Grade = BM;
        }

        int Rental_count =0;
        for (int i = 0; i < Rental_count; i++)
            if (MI[m_idx].Grade == EM)
            {
                Overdue_Date = Rental_Date - 7;
                if (Overdue_Date > 0)
                    Overdue += 1;
            }
            else if (MI[m_idx].Grade == NM)
            {
                Overdue_Date = Rental_Date - 5;
                if (Overdue_Date > 0)
                    Overdue += 1;
            }
    }

    // 도서조회
    const char *booknames[5] = {"로빈슨크루소", "마시멜로이야기", "신데렐라", "백설공주", "일곱난쟁이"};
    char findbook[50];
    cout << "찾고 싶은 책 이름을 입력하세요: ";
    cin >> findbook;

    bool find = false;
    for (int i = 0; i < 5; i++)
    {
        if (strcmp(booknames[i], findbook) == 0)
        {
            find = true;
            break;
        }
    }
    if (find)
    {
        cout << "책을 찾았습니다: " << findbook << endl;
    }
    else
    {
        cout << "책을 찾을 수 없습니다." << endl;
    }

    // 대여 및 반납
}

void clrscr()
{
    system("clear");
}

char InputMenu()
{
    char num;
    while (1)
    {
        cin >> num;
        cin.ignore();
        if ((num >= min && num <= max) || 'q' == num)
        {
            return num;
        }
        else
        {
            cout << "잘못된 입력입니다. 다시 입력해 주세요 (" << min << " ~ " << max << ")" << endl;
        }
    }
}

// 도서 조회
void book_find(int *b_idx, Book_Information *BI)
{
    int i;
    char Find_Book;
    cin >> Find_Book;

    for (i = 0; i < *b_idx; i++)
    {
        if (Find_Book == BI->Book_Name[i])
        {
            cout << BI->Book_Name[i];
            cout << BI->Author[i];
            cout << BI->Publisher[i];
            return;
        }
    }
    cout << "찾고자 하는 책이 없습니다." << endl;
}

// 회원 정보 조회
void book_find(int *mt_idx, Member_Information *MI)
{
    int i;
    char Find_Member;
    cin >> Find_Member;

    for (i = 0; i < *mt_idx; i++)
    {
        if (strcmp(&Find_Member, MI[i].ID) == 0)
        {
            cout << MI->ID[i];
            cout << MI->Grade;
            cout << MI->Residence[i];
            cout << MI->Rental_Book[i];
            return;
        }
    }
    cout << "찾고자 하는 회원이 없습니다." << endl;
}

// 로그인
void login(Member_Information *MI, Book_Information *BI, int *m_idx, int *mt_idx)
{

    int login = 0;
    char Menu_Num = -1;
    int wrong_count = 0;
    char login_PW[20];
    char new_ID[20];
    char new_PW[20];
    char login_ID[20];
   
    while (1)
    {
        // 로그인 및 회원가입
        if (login == 0)
        {
            cout << "책사줘 도서관에 오신걸 환영합니다.\n";
            cout << "=============== MENU ===============\n";
            cout << "1. 로그인\n";
            cout << "2. 회원가입\n";
            cout << "3. 도서조회\n";
            cout << "====================================\n";

            Menu_Num = InputMenu();

            if (Menu_Num == '1')
            {
                cout << "로그인 할 ID를 입력해 주세요.\n";
                cin >> login_ID;
                cout << "로그인 할 PW를 입력해 주세요.\n";
                cin >> login_PW;

                bool login_success = false;
                for (int i = 0; i < *mt_idx; i++)
                {
                    if (strcmp(MI[i].ID, login_ID) == 0 && strcmp(MI[i].PW, login_PW) == 0)
                    {
                        cout << "로그인에 성공하였습니다.\n";
                        *m_idx = i;
                        login = 1;
                        login_success = true;
                        break;
                    }
                }

                if (!login_success)
                {
                    cout << "ID, PW를 다시 한번 확인해주세요.\n";
                    sleep(1);
                    wrong_count += 1;
                    if (wrong_count == 5)
                    {
                        cout << "비밀번호를 5회 틀렸습니다. 프로그램을 종료합니다.\n";
                        return;
                    }
                    continue;
                }
            }

            if (Menu_Num == '2')
            {
                cout << "회원가입 할 ID를 입력해주세요.\n";
                cin >> new_ID;
                cout << "사용할 비밀번호를 입력해주세요.\n";
                cin >> new_PW;

                bool SameID_Check = false;
                for(int i=0; i < *mt_idx; i++)
                {
                    if(strcmp(new_ID, MI[i].ID)==0){
                        cout << "중복된 아이디가 있습니다. 다른 아이디를 입력해주세요." << endl;
                        SameID_Check = true;
                        break;
                    }
                }
                
                if(!SameID_Check){
                    strcpy(MI[*mt_idx].ID, new_ID);
                    strcpy(MI[*mt_idx].PW, new_PW);
                    MI[*mt_idx].Grade = NM;
                    (*mt_idx)++;
                    cout << "회원가입이 완료되었습니다.";
                }
            }

            if (Menu_Num == '3')
                cout << "조회할 도서의 제목, 작가, 출판사를 입력해주세요.\n";
            // 도서 조회코드
        }

        if (login == 1)
        {
            cout << "책사줘 도서관에 오신걸 환영합니다.\n";
            cout << "=============== MENU ===============\n";
            cout << "현재 로그인 중인 ID\n"
                 << MI[*m_idx].ID;
            cout << endl;
            cout << "1. 로그아웃\n";
            cout << "2. 도서대여\n";
            cout << "3. 도서반납\n";
            cout << "====================================\n";

            Menu_Num = InputMenu();
            if (Menu_Num == '1')
            {
                cout << "로그아웃 하겠습니다.";
                login = 0;
                break;
            }
            else if (Menu_Num == '2')
            {
                cout << "대여할 도서의 제목과 작가, 출판사를 입력해주세요.";
                // 도서 대여 코드
            }
            else if (Menu_Num == '3')
            {
                cout << "반납할 도서의 제목과 작가, 출판사를 입력해주세요.";
                // 도서 반납 코드
            }
        }
    }
}