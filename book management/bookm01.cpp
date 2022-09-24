#include<iostream>
#include"bookm.h"
#include<string>
#include<list>
#include<fstream>
#include<conio.h>
#include<cstring>
#include<cstdlib>
#include<iomanip>
#include<algorithm>//list用不了算法头文件的sort
#include<functional>

using namespace std;

User::User()//如果不编写默认构造，还会有问题吗
{
    strcpy(name,"no name");
    strcpy(code,"no code");;//code="000";,默认长度与这个有关！改成char了就没关了应该
    type=0;
}

User::User(char name_u[],char code_u[],int type_u)
{
   strcpy(name,name_u);
   strcpy(code,code_u);
    type=type_u;
}

void User::set_user()
{

    cin>>type;
    cin>>name;
    cin>>code;
}

/*void User::change_code()
{
    //先不写输入原密码
    cout<<"请输入更改后的密码"<<endl;
    cin>>code;
}*/

void User::show_user()
{
    cout<<setw(4)<<type<<setw(14)<<name<<setw(8)<<code<<endl;
}

bool User::log_first()
{
   // string name_first="20210694";
    char code_first[]="qazwsx";
    code[7]={'\0'};
    /*cout<<"用户名:";
    cin>>name;*/
    cout<<"密码 :";
    //cin.get();
    int i=0;
    int n=3;
    char ch;
    /*do{
         while(i<6&&code[i]!='\r')
        {
            code[i]=getch();
            if(code[i]=='\b')
                {
                    cout<<'\b'<<" "<<'\b';
                    i--;
                }
             else
             {
                 cout<<"*";
                 //cout<<code[i];
                 i++;
             }
        }
        code[i]='\0';
        cout<<code.length();//是因为我的构造函数length是三吗
        for(j=0;j<code.length();j++)
        {
            cout<<code[j]<<" ";
        }
        cout<<code;*/
        while(n--)
    {
        for(i=0;(ch=getch())!='\r'&&i<6;)
        {
            code[i]=ch;
            if(code[i]=='\b')
            {
                cout<<'\b'<<" "<<'\b';
                i--;
            }
            else
            {
                cout<<"*";
                i++;
            }
        }
        code[i]='\0';
        if(strcmp(code_first,code)==0)//if(!((name_first.compare(name))&&(code_first.compare(code))))//!直接用==也可以判断
        {
            type=3;//系统管理员
            strcpy(name,"20210694");
            cout<<endl<<"恭喜！密码输入成功！欢迎系统管理员！"<<endl;
            return true;
        }
        else
        {
            cout<<endl<<"密码错误，请再次输入"<<endl;
            cout<<"您还有"<<n<<"次机会"<<endl;
        }
     }

    return false;

}

User::~User()
{

}

User_control::User_control()
{
    listu.resize(0);
    n=0;
}
User_control::User_control(int n_u)
{
    n=n_u;
    listu.resize(n);
}

User_control::~User_control()
{

}

void User_control::input_from_keybord()
{
    User u;
    u.set_user();
    listu.push_front(u);
    n++;
}

void User_control::register_u()
{
    User u;
    ofstream fout("用户信息.dat",ios::out|ios::app|ios::binary);
    cout<<"请选择用户类型（1.普通读者 2.图书管理员 )"<<endl;
    cin>>u.type;
    //while()其他情况
    cout<<"请设置用户名"<<endl;
    cin>>u.name;
    cout<<"请设置密码"<<endl;
    cin>>u.code;
    fout.write(reinterpret_cast<char*>(&u),sizeof(User));
    fout.close();


}

void User_control::read_from_file_to_list(string filename)
{
    User u;
    ifstream fin;
    fin.open(filename.c_str(),ios::in|ios::binary);
    while(fin)
    {
        fin.read(reinterpret_cast<char*>(&u),sizeof(User));
        listu.push_front(u);
    }
    listu.pop_front();
    fin.close();
}

void User_control::show_list()
{
   cout<<setw(4)<<"用户类型"<<setw(8)<<"用户名"<<setw(12)<<"用户密码"<<endl;
    list<User>::iterator up;
    up=listu.begin();
    do
    {
        up->show_user();
        up++;
    }
    while(up!=listu.end());
    listu.clear();//清理一下显示才好
}

 void User_control:: write_to_file(string filename)
 {
     int num;
     User u;
     ofstream fout(filename.c_str(),ios::out|ios::app|ios::binary);
     cout<<"请输入添加用户的个数"<<endl;
     cin>>num;
      cout<<"请输入用户信息（eg 1 lili 23456h）"<<endl;
     int i;
     for(i=0;i<num;i++)
     {
         input_from_keybord();
     }
     list<User>::iterator ulp;
     for(ulp=listu.begin();ulp!=listu.end();ulp++)//!采用二进制读写更方便
     {
         u=*ulp;
         fout.write(reinterpret_cast<char*>(&u),sizeof(User));
        // fout<<ulp->gettype()<<" "<<ulp->getname()<<" "<<ulp->getcode()<<endl;//txt用write可以吗
     }
     fout.close();

 }

 void User_control::write_to_file_noapp(string filename)//不追加全覆盖
 {
     User u;
     ofstream fout(filename.c_str(),ios::binary|ios::out|ios::trunc);
     list<User>::iterator ulp;
     for(ulp=listu.begin();ulp!=listu.end();ulp++)
     {
         n++;
         u=*ulp;
         fout.write(reinterpret_cast<char*>(&u),sizeof(User));
     }
     fout.close();

 }

 void User_control::modify()
 {
     char name2[20];
     int flag=0;
     int choice;
     int flag1=1;
     read_from_file_to_list("用户信息.dat");
     cout<<"请输入您想要修改用户的用户名"<<endl;
     cin>>name2;
     list<User>::iterator ulp;
     for(ulp=listu.begin();ulp!=listu.end();ulp++)
     {
         if(strcmp(name2,ulp->name)==0)
         {
             flag=1;
             while(flag1)
             {
                 //cout<<"g"<<endl;
                 system("cls");
                 menu_modifyuser();
                 cin>>choice;
                 switch(choice)
                 {
                 case 1:
                    {
                        cout<<"请输入修改后的用户名"<<endl;
                        cin>>ulp->name;
                        system("pause");
                        break;
                    }
                 case 2:
                    {
                        cout<<"请输入修改后的密码"<<endl;
                        cin>>ulp->code;
                        system("pause");
                        break;
                    }
                 case 3:
                   {
                       cout<<"请输入修改后的用户类型（1系统管理员 2图书管理员 3普通读者）"<<endl;
                       cin>>ulp->type;
                       system("pause");
                       break;
                   }
                 case 4:
                    {
                        flag1=0;
                        //system("pause");
                        break;
                    }
                default:
                    {
                        cout<<"请输入正确数字"<<endl;
                        system("pause");
                        break;
                    }

                 }
             }
         }
     }
     if(flag)
     {
         write_to_file_noapp("用户信息.dat");
     }
     else
     {
         cout<<"未查询到此用户！"<<endl;
         listu.clear();
     }
 }

 void User_control::delete_li()
 {
     char name3[20];
     int flag=0;
     read_from_file_to_list("用户信息.dat");
     cout<<"请输入您想要删除用户的用户名"<<endl;
     cin>>name3;
     list<User>::iterator ulp;
     for(ulp=listu.begin();ulp!=listu.end();++ulp)//所有容器做erase时都有可能使迭代器失效
     {
         if(strcmp(name3,ulp->name)==0)
         {
             flag=1;
             //list<User>::iterator ulp2;
             //ulp2=ulp++;//不是指针的复制，不指向同一位置
             listu.erase(ulp++);//！要有一个备份
         }
     }
     if(flag)
     {
         write_to_file_noapp("用户信息.dat");
     }
     else
     {
         cout<<"未查询到该用户"<<endl;
         listu.clear();
     }
 }

 void User_control::change_code_li()
 {
        char code2[20];
        int flag=0;
        read_from_file_to_list("用户信息.dat");
        cout<<"请输入用户原密码"<<endl;
        cin>>code2;
        list<User>::iterator ulp;
        for(ulp=listu.begin();ulp!=listu.end();ulp++)
        {
            if(strcmp(code2,ulp->code)==0)
            {
                flag=1;
                cout<<"请输入修改后的密码"<<endl;
                cin>>ulp->code;
            }
        }
        if(flag)
        {
            write_to_file_noapp("用户信息.dat");
        }
        else
        {
            cout<<"原密码输入有误！无法正常修改"<<endl;
            listu.clear();//!清一下才好使！
        }
        listu.clear();
 }

 bool User_control::log(User &u)
{
    read_from_file_to_list("用户信息.dat");
    char name1[20],code1[20];
    cout<<"请输入用户名"<<endl;
    cin>>name1;
    cout<<"请输入密码"<<endl;
    getchar();
    int n=3;
    int i;
    char ch;
    while(n--)
    {
        for(i=0;(ch=getch())!='\r'&&i<6;)
        {
            code1[i]=ch;
            if(code1[i]=='\b')
            {
                cout<<'\b'<<" "<<'\b';
                i--;
            }
            else
            {
                cout<<"*";
                i++;
            }
        }
        code1[i]='\0';
        list<User>::iterator ulp;
        for(ulp=listu.begin();ulp!=listu.end();ulp++)
        {
            if(strcmp(name1,ulp->name)==0&&strcmp(code1,ulp->code)==0)
            {
                    type=ulp->type;
                    u=*ulp;
                    cout<<endl<<"登录成功"<<endl;
                    //system("pause");
                    return true;
            }
        }
        cout<<endl<<"用户名与密码不匹配，您还有"<<n<<"次机会"<<endl;
        //cout<<"请依次输入用户名及密码"<<endl;
        //getchar();
    }
    return false;

}

Reader::Reader()
{
    id=000000;
    strcpy(reader_name,"no name");
    strcpy(unit,"no unit");
    phone=00000000;
    number_have=0;
    number_borrowed=0;
}

Reader::Reader(long id_r,char* name_r,char* unit_r,long phone_r,int number_have_r,int number_borrowed_r)
{
    id=id_r;
    strcpy(reader_name,name_r);
    strcpy(unit,unit_r);
    phone=phone_r;
    number_have=number_have_r;
    number_borrowed=number_borrowed_r;
}

Reader::~Reader()
{

}

void Reader::set_reader()
{
    cin>>id>>reader_name>>unit>>phone>>number_have>>number_borrowed;
}

void Reader::show_reader()
{
    cout<<setiosflags(ios::left)<<setw(8)<<id<<setw(10)<<reader_name<<setw(10)<<unit<<setw(14)<<phone<<setw(10)<<number_have<<setw(5)<<number_borrowed<<endl;
}

/*bool operator<(Reader &r1,Reader &r2)
{
    if(strcmp(r1.reader_name,r2.reader_name)==-1)
    {
        return true;
    }
    else
    {
        return false;
    }
}*/

Reader_control::Reader_control()
{
    n=0;
    listr.resize(0);
}

Reader_control::Reader_control(int n_r)
{
    n=n_r;
    listr.resize(n_r);
}

Reader_control::~Reader_control()
{

}

void Reader_control::input_from_keybord_r()
{
    Reader r;
    r.set_reader();
    listr.push_front(r);
    n++;
}

void Reader_control::read_from_file_to_list_r(string filename)
{
    Reader r;
    ifstream fin;
    fin.open(filename.c_str(),ios::in|ios::binary);
    while(fin)
    {
        fin.read(reinterpret_cast<char*>(&r),sizeof(Reader));
        listr.push_front(r);
    }
    listr.pop_front();
    fin.close();
}

void Reader_control:: write_to_file_r(string filename)
 {
     int num;
     Reader r;
     ofstream fout(filename.c_str(),ios::out|ios::app|ios::binary);
     cout<<"请输入添加读者的个数"<<endl;
     cin>>num;
      cout<<"请输入读者信息（eg 1000 孙欣 计软学院 18846333700 10 4）"<<endl;
     int i;
     for(i=0;i<num;i++)
     {
         input_from_keybord_r();
     }
     list<Reader>::iterator rlp;
     for(rlp=listr.begin();rlp!=listr.end();rlp++)
     {
         r=*rlp;
         fout.write(reinterpret_cast<char*>(&r),sizeof(Reader));
     }
     fout.close();

 }

 void Reader_control::write_to_file_noapp_r(string filename)//不追加全覆盖
 {
     Reader r;
     ofstream fout(filename.c_str(),ios::binary|ios::out|ios::trunc);
     list<Reader>::iterator rlp;
     for(rlp=listr.begin();rlp!=listr.end();rlp++)
     {
         n++;
         r=*rlp;
         fout.write(reinterpret_cast<char*>(&r),sizeof(Reader));
     }
     fout.close();

 }

 void Reader_control::show_list_r()
 {
     cout<<"读者号"<<setw(10)<<"读者姓名"<<setw(10)<<"读者单位"<<setw(10)<<"联系方式"<<setw(14)<<"可借书数"<<setw(10)<<"已借书数"<<endl;
     list<Reader>::iterator rp;
    rp=listr.begin();
    do
    {
        rp->show_reader();
        rp++;
    }
    while(rp!=listr.end());
    listr.clear();//清理一下显示才好

 }

 void Reader_control::modify_r()
 {
     long id2;
     int flag=0;
     int choice;

     read_from_file_to_list_r("读者信息.dat");
     cout<<"请输入您想要修改读者的读者号"<<endl;
     cin>>id2;
     list<Reader>::iterator rlp;
     for(rlp=listr.begin();rlp!=listr.end();rlp++)
     {
         if(id2==rlp->id)
         {
             flag=1;
             int flag1=1;
             while(flag1)
             {
                 //cout<<"g"<<endl;
                 system("cls");
                 menu_modifyreader();
                 cin>>choice;
                 switch(choice)
                 {
                 case 1:
                    {
                        cout<<"请输入修改后的读者号"<<endl;
                        cin>>rlp->id;
                        system("pause");
                        break;
                    }
                 case 2:
                    {
                        cout<<"请输入修改后的读者名"<<endl;
                        cin>>rlp->reader_name;
                        system("pause");
                        break;
                    }
                 case 3:
                   {
                       cout<<"请输入修改后的读者单位"<<endl;
                       cin>>rlp->unit;
                       system("pause");
                       break;
                   }
                 case 4:
                    {
                        cout<<"请输入修改后的联系方式"<<endl;
                        cin>>rlp->phone;
                        system("pause");
                        break;
                    }
                 case 5:
                    {
                        cout<<"请输入修改后的可借书数"<<endl;
                        cin>>rlp->number_have;
                        system("pause");
                        break;
                    }
                 case 6:
                    {
                        cout<<"请输入修改后的已借书数"<<endl;
                        cin>>rlp->number_borrowed;
                        system("pause");
                        break;

                    }
                 case 7:
                    {
                        flag1=0;
                        //system("pause");
                        break;
                    }
                    default:
                    {
                        cout<<"请输入正确数字"<<endl;
                        system("pause");
                        break;
                    }
                 }
             }
         }
     }
     if(flag==1)
     {
         write_to_file_noapp_r("读者信息.dat");
     }
     else if(flag==0)
     {
         cout<<"未查询到此读者！"<<endl;
         listr.clear();
     }
     listr.clear();
 }

void Reader_control::delete_li_r()
 {
     long id_r;
     int flag=0;
     read_from_file_to_list_r("读者信息.dat");
     cout<<"请输入您想要删除读者的读者号"<<endl;
     cin>>id_r;
     list<Reader>::iterator rlp;
     for(rlp=listr.begin();rlp!=listr.end();++rlp)//所有容器做erase时都有可能使迭代器失效
     {
         if(rlp->id==id_r)
         {
             flag=1;
             //list<User>::iterator ulp2;
             //ulp2=ulp++;//不是指针的复制，不指向同一位置
             listr.erase(rlp++);//！要有一个备份
         }
     }
     if(flag==1)
     {
         write_to_file_noapp_r("读者信息.dat");
     }
     else if(flag==0)
     {
         cout<<"未查询到该读者"<<endl;
         listr.clear();
     }
 }

 void Reader_control::find_r()
 {
     read_from_file_to_list_r("读者信息.dat");
     long id_r;
     int flag=0;
     cout<<"请输入您想查询的读者的读者号"<<endl;
     cin>>id_r;
     list<Reader>::iterator rlp;
     for(rlp=listr.begin();rlp!=listr.end();rlp++)
     {
         if(id_r==rlp->id)
         {
             flag=1;
             cout<<rlp->id<<" "<<rlp->reader_name<<" "<<rlp->unit<<" "<<rlp->phone<<" "<<rlp->number_have<<" "<<rlp->number_borrowed<<endl;
         }
     }
     if(flag==0)
     {
          cout<<"未查询到该读者"<<endl;
     }
     listr.clear();
 }

 bool operator<(Reader &r1,Reader &r2)
 {
     if(strcmp(r1.reader_name,r2.reader_name)<0)
     {
         return true;
     }
     else if(strcmp(r1.reader_name,r2.reader_name)>0)
     {
         return false;
     }
     //如果有同名怎么办呢？

 }

 void Reader_control::sort_r()
 {
     listr.sort();//list不支持随机访问，用不了算法里的sort
 }

 Index_num::Index_num()
 {
     record_book_in=0;
     num_book_in=0;
 }

 Index_num::~Index_num()
 {

 }

 void Index_num::show_index_num()
 {
     cout<<setw(32)<<record_book_in<<setw(8)<<num_book_in<<endl;
 }
 /*Index_num_control::Index_num_control()
 {
     listn_i.resize(0);
 }

 Index_num_control::~Index_num_control()
 {

 }*/

 Index_bookname::Index_bookname()
 {
     strcpy(book_name_in,"no name");
     p1_in=0;
     len1=1;
 }

 Index_bookname::~Index_bookname()
 {

 }

 void Index_bookname::show_index_bookname()
 {
     cout<<setiosflags(ios::left)<<setw(20)<<book_name_in<<setw(22)<<p1_in<<setw(16)<<len1<<endl;
 }
 /*Index_bookname_control::Index_bookname_control()
 {
     listb_i.resize(0);
 }

 Index_bookname_control::~Index_bookname_control()
 {

 }*/

 Index_aurthor::Index_aurthor()
 {
     strcpy(author_in,"no name");
     p2_in=0;
     len2=1;
 }

 Index_aurthor::~Index_aurthor()
 {

 }

 void Index_aurthor::show_index_authorname()
 {
     cout<<setiosflags(ios::left)<<setw(20)<<author_in<<setw(22)<<p2_in<<setw(16)<<len2<<endl;
 }

 /*Index_aurthor_control::Index_aurthor_control()
 {
     lista_i.resize(0);
 }

 Index_aurthor_control::~Index_aurthor_control()
 {

 }*/

 Index_publish::Index_publish()
 {
     strcpy(publish_in,"no name");
     p3_in=0;
     len3=1;
 }

 Index_publish::~Index_publish()
 {

 }

 void Index_publish::show_index_publishname()
 {
     cout<<setiosflags(ios::left)<<setw(20)<<publish_in<<setw(22)<<p3_in<<setw(16)<<len3<<endl;
 }

 /*Index_publish_control::Index_publish_control()
 {
     listp_i.resize(0);
 }

 Index_publish_control::~Index_publish_control()
 {

 }*/

 Book::Book()
 {
     record=0;
     num_book=0000;
     strcpy(book_name,"no name");
     strcpy(author_name,"no name");
     strcpy(publish_name,"no name");
     num_have=0;
     num_borrow=0;
     p1=0;
     p2=0;
     p3=0;
 }

 Book::~Book()
 {

 }

 void Book::input_book()
{
    cin>>num_book>>book_name>>author_name>>publish_name>>num_have>>num_borrow;
}

bool operator<(Book &b1,Book &b2)
{
    if(b1.record<b2.record)
    {
        return true;
    }
    else if(b1.record>b2.record)
    {
        return false;
    }
}

void Book::show_book_all()
{
    cout<<setiosflags(ios::left)<<setw(8)<<record<<setw(6)<<num_book<<setw(12)<<book_name<<setw(8)<<author_name<<setw(12)<<publish_name<<setw(10)<<num_have<<setw(8)<<num_borrow<<setw(6)<<p1<<setw(7)<<p2<<setw(6)<<p3<<endl;
}

BR_book::BR_book()
{
    month_b=month_r=day_b=day_r=0;
    num_reader=0;
    num_book_br=0;
}

BR_book::~BR_book()
{

}

 Book_control::Book_control()
 {
     num=0;
     listb.resize(0);
     listn_i.resize(0);
     listb_i.resize(0);
     lista_i.resize(0);
     listp_i.resize(0);
     listbr.resize(0);
    // listr.resize(0);
 }

 Book_control::~Book_control()
 {

 }

 void Book_control::write_to_bookfile()
 {
     Book b;
     ofstream fout("图书信息.dat",ios::out|ios::binary|ios::app);
     list<Book>::iterator blp;
     for(blp=listb.begin();blp!=listb.end();blp++)
     {
         b=*blp;
         fout.write(reinterpret_cast<char*>(&b),sizeof(Book));
     }
     fout.close();
 }

 void Book_control::write_to_bookfile_noapp()
 {
     Book b;
     ofstream fout("图书信息.dat",ios::out|ios::binary|ios::trunc);
     list<Book>::iterator blp;
     for(blp=listb.begin();blp!=listb.end();blp++)
     {
         b=*blp;
         fout.write(reinterpret_cast<char*>(&b),sizeof(Book));
     }
     fout.close();
 }

 void Book_control::write_to_index_num()
 {
     Index_num in;
     ofstream fout("书号检索.dat",ios::out|ios::binary|ios::app);
     list<Index_num>::iterator inp;
     for(inp=listn_i.begin();inp!=listn_i.end();inp++)
     {
         in=*inp;
         fout.write(reinterpret_cast<char*>(&in),sizeof(Index_num));
     }
     fout.close();
 }

 void Book_control::write_to_index_num_noapp()
 {
     Index_num in;
     ofstream fout("书号检索.dat",ios::out|ios::binary|ios::trunc);
     list<Index_num>::iterator inp;
     for(inp=listn_i.begin();inp!=listn_i.end();inp++)
     {
         in=*inp;
         fout.write(reinterpret_cast<char*>(&in),sizeof(Index_num));
     }
     fout.close();
 }

 void Book_control::write_to_index_bona()
 {
     Index_bookname ib;
     ofstream fout("书名检索.dat",ios::out|ios::binary|ios::app);
     list<Index_bookname>::iterator ibp;
     for(ibp=listb_i.begin();ibp!=listb_i.end();ibp++)
     {
         ib=*ibp;
         fout.write(reinterpret_cast<char*>(&ib),sizeof(Index_bookname));
     }
     fout.close();
 }

 void Book_control::write_to_index_bona_noapp()
 {
     Index_bookname ib;
     ofstream fout("书名检索.dat",ios::out|ios::binary|ios::trunc);
     list<Index_bookname>::iterator ibp;
     for(ibp=listb_i.begin();ibp!=listb_i.end();ibp++)
     {
         ib=*ibp;
         fout.write(reinterpret_cast<char*>(&ib),sizeof(Index_bookname));
     }
     fout.close();
 }

 void Book_control::write_to_index_auna()
 {
     Index_aurthor ia;
     ofstream fout("作者名检索.dat",ios::out|ios::binary|ios::app);
     list<Index_aurthor>::iterator iap;
     for(iap=lista_i.begin();iap!=lista_i.end();iap++)
     {
         ia=*iap;
         fout.write(reinterpret_cast<char*>(&ia),sizeof(Index_aurthor));
     }
     fout.close();
 }

 void Book_control::write_to_index_auna_noapp()
 {
     Index_aurthor ia;
     ofstream fout("作者名检索.dat",ios::out|ios::binary|ios::trunc);
     list<Index_aurthor>::iterator iap;
     for(iap=lista_i.begin();iap!=lista_i.end();iap++)
     {
         ia=*iap;
         fout.write(reinterpret_cast<char*>(&ia),sizeof(Index_aurthor));
     }
     fout.close();
 }

 void Book_control::write_to_index_puna()
 {
     Index_publish ip;
     ofstream fout("出版社检索.dat",ios::out|ios::binary|ios::app);
     list<Index_publish>::iterator ipp;
     for(ipp=listp_i.begin();ipp!=listp_i.end();ipp++)
     {
         ip=*ipp;
         fout.write(reinterpret_cast<char*>(&ip),sizeof(Index_publish));
     }
     fout.close();
 }

 void Book_control::write_to_index_puna_noapp()
 {
     Index_publish ip;
     ofstream fout("出版社检索.dat",ios::out|ios::binary|ios::trunc);
     list<Index_publish>::iterator ipp;
     for(ipp=listp_i.begin();ipp!=listp_i.end();ipp++)
     {
         ip=*ipp;
         fout.write(reinterpret_cast<char*>(&ip),sizeof(Index_publish));
     }
     fout.close();
 }

 void Book_control::write_to_num_noapp()
 {
     ofstream fout("书籍总数.dat",ios::out|ios::binary|ios::trunc);
     fout.write(reinterpret_cast<char*>(&num),sizeof(int));
     fout.close();
 }

 void Book_control::read_from_num()
 {
     int num_t;
     ifstream fin("书籍总数.dat",ios::in|ios::binary);
     while(fin)
     {
         fin.read(reinterpret_cast<char*>(&num_t),sizeof(int));
     }
     num=num_t;
 }

/* void Book_control::write_to_bookfile_noapp()
 {
     Book b;
     ofstream fout("图书信息.dat",ios::out|ios::binary|ios::trunc);
     list<Book>::iterator blp;
     for(blp=listb.begin();blp!=listb.end();blp++)
     {
         b=*blp;
         fout.write(reinterpret_cast<char*>(&b),sizeof(Book));
     }
     fout.close();
 }

 void Book_control::write_to_index_num_noapp()
 {
     Index_num in;
     ofstream fout("书号检索.dat",ios::out|ios::binary|ios::trunc);
     list<Index_num>::iterator inp;
     for(inp=listn_i.begin();inp!=listn_i.end();inp++)
     {
         in=*inp;
         fout.write(reinterpret_cast<char*>(&in),sizeof(Index_num));
     }
     fout.close();
 }

 void Book_control::write_to_index_bona_noapp()
 {
     Index_bookname ib;
     ofstream fout("书名检索.dat",ios::out|ios::binary|ios::trunc);
     list<Index_bookname>::iterator ibp;
     for(ibp=listb_i.begin();ibp!=listb_i.end();ibp++)
     {
         ib=*ibp;
         fout.write(reinterpret_cast<char*>(&ib),sizeof(Index_bookname));
     }
     fout.close();
 }

 void Book_control::write_to_index_auna_noapp()
 {
     Index_aurthor ia;
     ofstream fout("作者名检索.dat",ios::out|ios::binary|ios::trunc);
     list<Index_aurthor>::iterator iap;
     for(iap=lista_i.begin();iap!=lista_i.end();iap++)
     {
         ia=*iap;
         fout.write(reinterpret_cast<char*>(&ia),sizeof(Index_aurthor));
     }
     fout.close();
 }

 void Book_control::write_to_index_puna_noapp()
 {
     Index_publish ip;
     ofstream fout("出版社检索.dat",ios::out|ios::binary|ios::trunc);
     list<Index_publish>::iterator ipp;
     for(ipp=listp_i.begin();ipp!=listp_i.end();ipp++)
     {
         ip=*ipp;
         fout.write(reinterpret_cast<char*>(&ip),sizeof(Index_publish));
     }
     fout.close();
 }
 /*void input_bookin_from_keybord()
 {
     Book b;

 }*/

 void Book_control::input_to_list(Book &b)//判断是哪个，加到对应的指针上，改变指针
 {
        b.p1=b.p2=b.p3=0;
        int flag=1;//判断输入书籍是否重复,重复了就不用push front了
        list<Book>::iterator blp1;
        for(blp1=listb.begin();blp1!=listb.end();blp1++)
        {
            if(blp1->num_book==b.num_book&&strcmp(blp1->book_name,b.book_name)==0&&strcmp(blp1->author_name,b.author_name)==0&&strcmp(blp1->publish_name,b.publish_name)==0)
            {
                blp1->num_have+=b.num_have;
                blp1->num_borrow+=b.num_borrow;
                blp1->record=b.record;
                flag=0;
            }
        }
        if(flag)//填写主文件三个指针
        {
            num++;
            b.record=num;//b.getrecord()=num;
            list<Book>::iterator blp;
            for(blp=listb.begin();blp!=listb.end();blp++)
            {
                if(strcmp(blp->book_name,b.book_name)==0)//书名相同时，指针1改变
                {
                        b.p1=blp->record;//blp->getrecord(),不用友元类也可以
                        break;//找到了我就跳出来，不然会变成最小的那个，那后面的怎么变化呢？
                }
            }
             for(blp=listb.begin();blp!=listb.end();blp++)//!分三个循环写就不会跳出后为0.我真厉害！
             {
                  if(strcmp(blp->author_name,b.author_name)==0)//作者名相同时，指针2改变
                {
                      b.p2=blp->record;
                      break;
                }
             }
             for(blp=listb.begin();blp!=listb.end();blp++)
             {

                if(strcmp(blp->publish_name,b.publish_name)==0)//出版社名字相同时，指针3改变
                {
                    b.p3=blp->record;
                    break;
                }
             }

             listb.push_front(b);//改完一个，将数据存进去，等下一个数据进来判断的时候会循环到它
        }
        /*list<Book>::iterator it;
        cout<<"****************************************************"<<endl;
        for(it=listb.begin();it!=listb.end();it++)
        {

            it->show_book_all();


        }
         cout<<"****************************************************"<<endl;*/
        int flag2=1;//用其判断是否原来有数据
        Index_num in;
        list<Index_num>::iterator inp;
        for(inp=listn_i.begin();inp!=listn_i.end();inp++)
        {
            if(inp->num_book_in==b.num_book)
            {
                flag2=0;
                inp->record_book_in=b.record;//书号相同，记录号不变
            }
        }
        if(flag2)
        {
            in.num_book_in=b.num_book;
            in.record_book_in=b.record;
            listn_i.push_front(in);
        }
        int flag3=1;
        Index_bookname ib;
        list<Index_bookname>::iterator ibp;
        for(ibp=listb_i.begin();ibp!=listb_i.end();ibp++)
        {
            if(strcmp(ibp->book_name_in,b.book_name)==0)
            {
                ibp->p1_in=b.record;
                ibp->len1=ibp->len1+1;
                flag3=0;
            }
        }
        if(flag3)
        {
            strcpy(ib.book_name_in,b.book_name);
            ib.p1_in=b.record;
            listb_i.push_front(ib);
        }
        int flag4=1;
        Index_aurthor ia;
        list<Index_aurthor>::iterator iap;
        for(iap=lista_i.begin();iap!=lista_i.end();iap++)
        {
            if(strcmp(iap->author_in,b.author_name)==0)
            {
                iap->p2_in=b.record;
                iap->len2=iap->len2+1;
                flag4=0;
            }
        }
        if(flag4)
        {
            strcpy(ia.author_in,b.author_name);
            ia.p2_in=b.record;
            lista_i.push_front(ia);
        }
        int flag5=1;
        Index_publish ip;
        list<Index_publish>::iterator ipp;
        for(ipp=listp_i.begin();ipp!=listp_i.end();ipp++)
        {
            if(strcmp(ipp->publish_in,b.publish_name)==0)
            {
                ipp->p3_in=b.record;
                ipp->len3=ipp->len3+1;
                flag5=0;
            }
        }
        if(flag5)
        {
            strcpy(ip.publish_in,b.publish_name);
            ip.p3_in=b.record;
            listp_i.push_front(ip);
        }





 }

 void Book_control::input_book()//键盘输入一个，去验证一圈指针，然后再输入到文件里面
 {
        int n;
        Book b;
        cout<<"请输入您想要输入图书的数量"<<endl;
        cin>>n;
        int i;
        cout<<"请输入图书信息（eg 1109 程序设计 赵鹏 清华大学 9 1 ）"<<endl;
        for(i=0;i<n;i++)
        {
            b.input_book();
            input_to_list(b);//改指针
           // listb.push_front(b);//数据存在list里
        }
           write_to_num_noapp();
           write_to_bookfile_noapp();
            write_to_index_num_noapp();
            write_to_index_bona_noapp();
            write_to_index_auna_noapp();
            write_to_index_puna_noapp();
        //数据写到文件里
 }

 void Book_control::read_from_bookfile()
 {
     Book b;
     ifstream fin("图书信息.dat",ios::in|ios::binary);
     while(fin)
     {
         fin.read(reinterpret_cast<char*>(&b),sizeof(Book));
         listb.push_front(b);
     }
     listb.pop_front();
     fin.close();
 }

 void Book_control::read_from_index_num()
 {
     Index_num in;
     ifstream fin("书号检索.dat",ios::in|ios::binary);
     while(fin)
     {
         fin.read(reinterpret_cast<char*>(&in),sizeof(Index_num));
         listn_i.push_front(in);
     }
     listn_i.pop_front();
     fin.close();
 }

 void Book_control::read_from_index_bona()
 {
     Index_bookname ib;
     ifstream fin("书名检索.dat",ios::in|ios::binary);
     while(fin)
     {
         fin.read(reinterpret_cast<char*>(&ib),sizeof(Index_bookname));
         listb_i.push_front(ib);
     }
     listb_i.pop_front();
     fin.close();
 }

 void Book_control::read_from_index_auna()
 {
     Index_aurthor ia;
     ifstream fin("作者名检索.dat",ios::in|ios::binary);
     while(fin)
     {
         fin.read(reinterpret_cast<char*>(&ia),sizeof(Index_aurthor));
         lista_i.push_front(ia);
     }
     lista_i.pop_front();
     fin.close();
 }

 void Book_control::read_from_index_puna()
 {
     Index_publish ip;
     ifstream fin("出版社检索.dat",ios::in|ios::binary);
     while(fin)
     {
         fin.read(reinterpret_cast<char*>(&ip),sizeof(Index_publish));
         listp_i.push_front(ip);
     }
     listp_i.pop_front();
     fin.close();
 }

 void Book_control::find_book_num()
 {

     read_from_bookfile();
     read_from_index_num();
     int x;
     int flag=0;
     cout<<"请输入您想查询的图书的书号"<<endl;
     cin>>x;
     list<Index_num>::iterator inp;
     //cout<<"结果如下"<<endl;
     for(inp=listn_i.begin();inp!=listn_i.end();inp++)
     {
         if(x==inp->num_book_in)
         {
             list<Book>::iterator lbp;
             for(lbp=listb.begin();lbp!=listb.end();lbp++)
             {
                 if(inp->record_book_in==lbp->record)
                 {
                     cout<<lbp->record<<" "<<lbp->num_book<<" "<<lbp->get_book_name()<<" "<<lbp->get_author_name()<<" "<<lbp->get_publish_name()<<" "<<lbp->num_have<<" "<<lbp->num_borrow<<endl;
                 }
             }
             flag=1;
             //break;
         }
     }
     if(flag==0)
     {
         cout<<"未查询到该书号"<<endl;
     }
     listn_i.clear();
     listb.clear();
 }

 void Book_control::find_author_name()
 {

     read_from_bookfile();
     read_from_index_auna();
     char name[20];
     int flag=0;
     int temp;
     cout<<"请输入您想查询的图书的作者名"<<endl;
     cin>>name;
     list<Index_aurthor>::iterator iap;
     for(iap=lista_i.begin();iap!=lista_i.end();iap++)
     {
         if(strcmp(name,iap->author_in)==0)
         {
             temp=iap->p2_in;
             while(temp!=0)//当指针不为空，一直输出
             {
                 list<Book>::iterator lbp;
             for(lbp=listb.begin();lbp!=listb.end();lbp++)
             {
                 if(temp==lbp->record)
                 {
                     cout<<lbp->record<<" "<<lbp->num_book<<" "<<lbp->get_book_name()<<" "<<lbp->get_author_name()<<" "<<lbp->get_publish_name()<<" "<<lbp->num_have<<" "<<lbp->num_borrow<<endl;
                     temp=lbp->p2;//指针赋值一下，方便输出后面的信息
                     //break;
                 }
             }
             }
             flag=1;
             //break;
         }
     }
     if(flag==0)
     {
         cout<<"未查询到该作者名"<<endl;
     }
     lista_i.clear();
     listb.clear();
 }

 void Book_control::find_publish_name()//用len是不是也可以，有时间试一下
 {

     read_from_bookfile();
     read_from_index_puna();
     char name[20];
     int flag=0;
     int temp;
     cout<<"请输入您想查询的图书的出版社名"<<endl;
     cin>>name;
     list<Index_publish>::iterator ipp;
     for(ipp=listp_i.begin();ipp!=listp_i.end();ipp++)
     {
         if(strcmp(name,ipp->publish_in)==0)
         {
             temp=ipp->p3_in;
             while(temp!=0)//当指针不为空，一直输出
             {
                 list<Book>::iterator lbp;
             for(lbp=listb.begin();lbp!=listb.end();lbp++)
             {
                 if(temp==lbp->record)
                 {
                     cout<<lbp->record<<" "<<lbp->num_book<<" "<<lbp->get_book_name()<<" "<<lbp->get_author_name()<<" "<<lbp->get_publish_name()<<" "<<lbp->num_have<<" "<<lbp->num_borrow<<endl;
                     temp=lbp->p3;//指针赋值一下，方便输出后面的信息
                     //break;
                 }
             }
             }
             flag=1;
             //break;
         }
     }
     if(flag==0)
     {
         cout<<"未查询到该出版社名"<<endl;
     }
     listp_i.clear();
     listb.clear();
 }

 void Book_control::find_book_name()
 {

     read_from_bookfile();
     read_from_index_bona();
     char name[20];
     int flag=0;
     int temp;
     cout<<"请输入您想查询的图书的书名"<<endl;
     cin>>name;
     list<Index_bookname>::iterator ibp;
     for(ibp=listb_i.begin();ibp!=listb_i.end();ibp++)
     {
         if(strcmp(name,ibp->book_name_in)==0)
         {
             temp=ibp->p1_in;
             while(temp!=0)//当指针不为空，一直输出
             {
                 list<Book>::iterator lbp;
             for(lbp=listb.begin();lbp!=listb.end();lbp++)
             {
                 if(temp==lbp->record)
                 {
                     cout<<lbp->record<<" "<<lbp->num_book<<" "<<lbp->get_book_name()<<" "<<lbp->get_author_name()<<" "<<lbp->get_publish_name()<<" "<<lbp->num_have<<" "<<lbp->num_borrow<<endl;
                     temp=lbp->p1;//指针赋值一下，方便输出后面的信息
                     //break;
                 }
             }
             }
             flag=1;
             //break;
         }
     }
     if(flag==0)
     {
         cout<<"未查询到该书名"<<endl;
     }
     listb_i.clear();
     listb.clear();
 }

 void Book_control::show_filein()
 {
     listb.sort();
     list<Book>::iterator lbp;
     cout<<"******************************图书主文件******************************************"<<endl;
     cout<<"记录号"<<"  "<<"书号"<<"   "<<"书名"<<"       "<<"作者"<<"    "<<"出版社"<<"    "<<"藏书量"<<"   "<<"借出数"<<"   "<<"指针1"<<"  "<<"指针2"<<"  "<<"指针3"<<endl;
     for(lbp=listb.begin();lbp!=listb.end();lbp++)
     {
         lbp->show_book_all();
     }
     listb.clear();
     cout<<"*******************************书号索引文件**************************************"<<endl;
     cout<<setw(32)<<"记录号"<<setw(8)<<"书号"<<endl;
     list<Index_num>::iterator inp;
     for(inp=listn_i.begin();inp!=listn_i.end();inp++)
     {
         inp->show_index_num();
     }
     listn_i.clear();
      cout<<"*******************************书名索引文件**************************************"<<endl;
     cout<<setw(18)<<"书名"<<setw(22)<<"链头指针"<<setw(18)<<"长度"<<endl;
     list<Index_bookname>::iterator ibp;
     for(ibp=listb_i.begin();ibp!=listb_i.end();ibp++)
     {
         ibp->show_index_bookname();
     }
     listb_i.clear();
      cout<<"*******************************作者名索引文件**************************************"<<endl;
     cout<<setw(18)<<"作者"<<setw(22)<<"链头指针"<<setw(18)<<"长度"<<endl;
     list<Index_aurthor>::iterator iap;
     for(iap=lista_i.begin();iap!=lista_i.end();iap++)
     {
         iap->show_index_authorname();
     }
     lista_i.clear();
      cout<<"*******************************出版社名索引文件**************************************"<<endl;
     cout<<setw(18)<<"出版社"<<setw(22)<<"链头指针"<<setw(18)<<"长度"<<endl;
     list<Index_publish>::iterator ipp;
     for(ipp=listp_i.begin();ipp!=listp_i.end();ipp++)
     {
         ipp->show_index_publishname();
     }
     listp_i.clear();
     cout<<"图书总种类量为："<<num<<endl;
 }

 void Book_control::collect_bona()
 {
     read_from_index_bona();
     list<Index_bookname>::iterator ibp;
     for(ibp=listb_i.begin();ibp!=listb_i.end();ibp++)
     {
         cout<<ibp->get_boin()<<":"<<ibp->len1<<"种类型"<<endl;
     }
 }

 void Book_control::collect_auna()
 {
     read_from_index_auna();
     list<Index_aurthor>::iterator iap;
     for(iap=lista_i.begin();iap!=lista_i.end();iap++)
     {
         cout<<iap->get_auin()<<":"<<iap->len2<<"种类型"<<endl;
     }
 }

 void Book_control::collect_puna()
 {
     read_from_index_puna();
     list<Index_publish>::iterator ipp;
     for(ipp=listp_i.begin();ipp!=listp_i.end();ipp++)
     {
         cout<<ipp->get_puin()<<":"<<ipp->len3<<"种类型"<<endl;
     }
 }

 void Book_control::modify()//修改完之后需要再重新排指针，再写到文件里
 {
     Read_all();
     read_from_num();
     int flag1=0;
     int num_b;
     char name_b[20];
     char name_a[20];
     char name_p[20];
     cout<<"请输入要修改书籍的书号，书名，作者名及出版社"<<endl;
     cin>>num_b>>name_b>>name_a>>name_p;
     list<Book>::iterator lbp;
     for(lbp=listb.begin();lbp!=listb.end();lbp++)
     {
         if(lbp->num_book==num_b&&strcmp(lbp->book_name,name_b)==0&&strcmp(lbp->author_name,name_a)==0&&strcmp(lbp->publish_name,name_p)==0)
         {
                flag1=1;
                int flag2=1;
                while(flag2)
                {
                    system("cls");
                    menu_modifybook();
                    int c;
                    cin>>c;
                    switch(c)
                    {
                    case 1:
                        {
                            cout<<"请输入修改后的书号"<<endl;
                            list<Index_num>::iterator inp;
                            for(inp=listn_i.begin();inp!=listn_i.end();inp++)
                            {
                                if(lbp->num_book==inp->num_book_in)
                                {
                                    cin>>lbp->num_book;
                                    inp->num_book_in=lbp->num_book;
                                   // break;
                                }
                            }
                            system("pause");
                            break;
                        }
                    case 2:
                        {
                            char t[20];
                            cout<<"请输入修改后的书名"<<endl;
                            list<Index_bookname>::iterator ibp;
                            for(ibp=listb_i.begin();ibp!=listb_i.end();ibp++)
                            {
                                if(strcmp(lbp->book_name,ibp->book_name_in)==0)
                                {
                                    cin>>t;
                                    strcpy(lbp->book_name,t);
                                    //break;
                                }
                            }
                            system("pause");
                            break;
                        }
                    case 3:
                        {
                            char t[20];
                            cout<<"请输入修改后的作者名"<<endl;
                            list<Index_aurthor>::iterator iap;
                            for(iap=lista_i.begin();iap!=lista_i.end();iap++)
                            {
                                if(strcmp(lbp->author_name,iap->author_in)==0)
                                {
                                    cin>>t;
                                    strcpy(lbp->author_name,t);
                                    //break;
                                }
                            }
                            system("pause");
                            break;
                        }
                    case 4:
                        {
                            char t[20];
                            cout<<"请输入修改后的出版社名"<<endl;
                            list<Index_publish>::iterator ipp;
                            for(ipp=listp_i.begin();ipp!=listp_i.end();ipp++)
                            {
                                if(strcmp(lbp->publish_name,ipp->publish_in)==0)
                                {
                                    cin>>t;
                                    strcpy(lbp->publish_name,t);
                                    //break;
                                }
                            }
                            system("pause");
                            break;
                        }
                    case 5:
                        {
                            cout<<"请输入修改后的藏书量"<<endl;
                            cin>>lbp->num_have;
                            system("pause");
                            break;
                        }
                    case 6:
                        {
                            cout<<"请输入修改后的借出量"<<endl;
                            cin>>lbp->num_borrow;
                            system("pause");
                            break;
                        }
                    case 7:
                        {
                            flag2=0;
                            break;
                        }
                    default:
                    {
                        cout<<"请输入正确数字"<<endl;
                        system("pause");
                        break;
                    }
                    }
                }
         }
     }
     if(flag1==0)
     {
         cout<<"未寻找到该书籍"<<endl;
         lista_i.clear();
         listb.clear();
         listbr.clear();
         listb_i.clear();
         listn_i.clear();
         listp_i.clear();
         num=0;
     }
     else if(flag1==1)
     {
         //cout<<"he"<<endl;
         int count=0;
         list<Book>temp;
         list<Book>::iterator lbp;
         for(lbp=listb.begin();lbp!=listb.end();lbp++,count++)
         {
             //cout<<num;
             if(count>=0&&count<=(num+1))//num+1 !num出现问题，从文件读取后，num原来加加，写入文件后消失
             {
                 //cout<<"he"<<endl;
                 temp.push_back(*lbp);//要pshuback顺序才是正确的
             }
         }
         list<Book>::iterator lbp2;
         for(lbp2=temp.begin();lbp2!=temp.end();lbp2++)
         {
             lbp2->p1=lbp2->p2=lbp2->p3=0;

         }
        /* list<Book>::iterator lbp4;
         for(lbp4=temp.begin();lbp4!=temp.end();lbp4++)
         {
             lbp4->show_book_all();

         }*/
             listb.clear();
             listn_i.clear();
             listb_i.clear();
             lista_i.clear();
             listp_i.clear();
             num=0;
         list<Book>::iterator lbp3;
         for(lbp3=temp.begin();lbp3!=temp.end();lbp3++)
         {

             input_to_list(*lbp3);

         }
            write_to_bookfile_noapp();
            write_to_index_num_noapp();
            write_to_index_bona_noapp();
            write_to_index_auna_noapp();
            write_to_index_puna_noapp();

     }
 }

 void Book_control::Read_all()
 {
     read_from_bookfile();
     read_from_index_num();
     read_from_index_bona();
     read_from_index_auna();
     read_from_index_puna();

 }

 /*void Book_control::read_from_reader()
 {

 }*/

 void Book_control::borrow()
 {
    Reader_control rc;
    rc.read_from_file_to_list_r("读者信息.dat");
    Book_control bc;
    bc.read_from_bookfile();
    bc.read_from_index_num();
    BR_book br1;
    int flag1=0;
    int flag2=0;
    cout<<"请输入读者号"<<endl;
    cin>>br1.num_reader;
    for(list<Reader>::iterator rlp=rc.listr.begin();rlp!=rc.listr.end();rlp++)
    {
        if(br1.num_reader==rlp->id)
        {
            cout<<"读者号合法"<<endl;
            if(rlp->number_have>rlp->number_borrowed)
            {
                cout<<"该读者的借阅量有余额，可以进行借阅"<<endl;
                //rlp->number_borrowed++;
                flag2=1;
            }
            flag1=1;
            break;
        }
    }
    if(flag1==0)
    {
        cout<<"未找到该读者"<<endl;
    }
    if(flag2==0&&flag1!=0)
    {
        cout<<"此读者借阅量已用完，无法进行借阅"<<endl;
    }
    else if(flag1==1&&flag2==1)
    {
        int flag3;
        flag3=0;
        cout<<"请输入要借阅的书号"<<endl;
        cin>>br1.num_book_br;
        for(list<Index_num>::iterator inp=bc.listn_i.begin();inp!=bc.listn_i.end();inp++)
        {
            if(br1.num_book_br==inp->num_book_in)
            {
                cout<<"该书籍号合法"<<endl;
                flag3=1;
                break;
            }

        }
        //cout<<flag3<<endl;
        if(flag3==0)
        {

            cout<<"未查询到此书号，其为非法书号"<<endl;
           // return;
        }
        else if(flag3==1)
        {
            int flag4=1;
            for(list<Book>::iterator lbp=bc.listb.begin();lbp!=bc.listb.end();lbp++)
            {
                if(br1.num_book_br==lbp->num_book)
                {
                    if(lbp->num_have>lbp->num_borrow)
                    {
                        lbp->num_borrow++;
                        cout<<"该读者成功借阅书籍一本"<<endl;
                        break;
                    }
                    else
                    {
                        cout<<"此书的可借数量不足，无法借阅"<<endl;
                        flag4=0;
                        break;

                    }
                }
            }
            bc.write_to_bookfile_noapp();
            if(flag4==1)
            {
                for(list<Reader>::iterator rlp=rc.listr.begin();rlp!=rc.listr.end();rlp++)
            {
                if(rlp->id==br1.num_reader_br)
                {
                    rlp->number_borrowed++;
                }
            }
            rc.write_to_file_noapp_r("读者信息.dat");
            cout<<"请输入借书日期（eg 6 7）"<<endl;
            cin>>br1.month_b>>br1.day_b;
            ofstream fout("借还书文件.dat",ios::out|ios::binary|ios::app);
            fout.write(reinterpret_cast<char*>(&br1),sizeof(BR_book));
            fout.close();
            }

        }

    }

 }

 void Book_control::return_b()
 {
    int flag1=0;
    BR_book br;
    Book_control bc2;
    Reader_control rc;
    cout<<"请输入读者号"<<endl;
    cin>>br.num_reader;
    rc.read_from_file_to_list_r("读者信息.dat");
    bc2.read_from_brfile();
    bc2.read_from_index_num();
    bc2.read_from_bookfile();
    for(list<Reader>::iterator lrp=rc.listr.begin(); lrp!=rc.listr.end(); lrp++)
    {
        if(lrp->id==br.num_reader)
        {
            cout<<"此读者为合法读者"<<endl;
            flag1=1;
            break;
        }
    }
    if(flag1==0)
    {
        cout<<"此读者为非法读者"<<endl;
    }
    else if(flag1==1)
    {
        int flag2=0;
        for(list<BR_book>::iterator brp=bc2.listbr.begin(); brp!=bc2.listbr.end(); brp++)
        {
            if(brp->num_reader==br.num_reader)
            {
                cout<<"该读者在借还书文件中存在"<<endl;
                flag2=1;
                break;
            }
        }
        if(flag2==0)
        {
            cout<<"此读者不存在于借还书文件中"<<endl;
        }
        else if(flag2==1)
        {
            int flag3=0;
            cout<<"请输入书号"<<endl;
            cin>>br.num_book_br;
            for(list<BR_book>::iterator brp=bc2.listbr.begin(); brp!=bc2.listbr.end(); brp++)
            {
                if(brp->num_book_br==br.num_book_br)
                {
                    cout<<"该书籍在借还书文件中存在"<<endl;
                    flag3=1;
                    break;
                }
            }
            if(flag3==0)
            {
                cout<<"此书籍不存在于借还书文件中"<<endl;
            }
            else if(flag3==1)
            {
                int flag4=0;
                for(list<Index_num>::iterator inp=bc2.listn_i.begin(); inp!=bc2.listn_i.end(); inp++)
                {
                    if(br.num_book_br==inp->num_book_in)
                    {
                        cout<<"该书籍号合法"<<endl;
                        flag4=1;
                        break;
                    }

                }
                if(flag4==0)
                {
                    cout<<"该书籍号不合法"<<endl;
                }
                else if(flag4==1)
                {
                    for(list<Book>::iterator lbp=bc2.listb.begin(); lbp!=bc2.listb.end(); lbp++)
                    {
                       // cout<<"g"<<endl;
                        if(br.num_book_br==lbp->num_book)
                        {
                            if(lbp->num_borrow!=0)
                            {
                                lbp->num_borrow--;
                                cout<<"该读者成功归还书籍一本"<<endl;
                                bc2.write_to_bookfile_noapp();
                                break;
                            }
                            else
                            {
                                cout<<"此书籍并没有被借出！"<<endl;
                            }


                        }
                    }

                    for(list<Reader>::iterator rlp=rc.listr.begin(); rlp!=rc.listr.end(); rlp++)
                    {
                        if(rlp->id==br.num_book_br)
                        {
                            rlp->number_borrowed--;
                        }
                    }
                    rc.write_to_file_noapp_r("读者信息.dat");

                    cout<<"请输入还书日期（月/日）"<<endl;
                    cin>>br.month_r>>br.day_r;
                    for(list<BR_book>::iterator brp=bc2.listbr.begin();brp!=bc2.listbr.end();brp++)
                    {
                        if(brp->num_reader==br.num_reader&&brp->num_book_br==br.num_book_br)
                        {
                            brp->month_r=br.month_r;
                            brp->day_r=br.day_r;
                            break;
                        }
                    }
                    BR_book br2;
                    ofstream fout("借还书文件.dat",ios::out|ios::binary|ios::trunc);
                    for(list<BR_book>::iterator brp=bc2.listbr.begin();brp!=bc2.listbr.end();brp++)
                    {
                        br2=*brp;
                        fout.write(reinterpret_cast<char*>(&br2),sizeof(BR_book));
                    }
                    fout.close();
                }
            }

        }
    }




 }
 void Book_control::read_from_brfile()
 {
     BR_book br;
     ifstream fin("借还书文件.dat",ios::in|ios::binary);
     while(fin)
     {
         fin.read(reinterpret_cast<char*>(&br),sizeof(BR_book));
         listbr.push_front(br);
     }
     listbr.pop_front();
     fin.close();

 }

 void Book_control::show_brfile()
 {
     read_from_brfile();
     cout<<"结果如下（日期为0则代表未还书）"<<endl;
     cout<<"读者号   书号   借书日期（月/日） 还书日期（月/日）"<<endl;
     for(list<BR_book>::iterator brp=listbr.begin();brp!=listbr.end();brp++)
     {
         cout<<brp->num_reader<<"     "<<brp->num_book_br<<"   "<<brp->month_b<<"月"<<brp->day_b<<"日                 "<<brp->month_r<<"月"<<brp->day_r<<"日"<<endl;
     }
     listbr.clear();
 }

void menu_log()
{
    cout<<"欢迎来到图书管理系统"<<endl;
    cout<<"1.登录"<<endl;
    cout<<"2.注册"<<endl;
    //cout<<"3.切换账号进行登录"<<endl;
    cout<<"3.退出程序"<<endl;
    cout<<"请选择数字 1 2 3 进行操作"<<endl;
}

void menu_log_first()
{
    cout<<"欢迎来到图书管理系统"<<endl;
    cout<<"经检测此次登录为图书馆系统激活，请系统管理员20210694进行激活操作"<<endl;
    cout<<"请输入信息进行登录（注意！若密码三次输入失败将会退出系统！）"<<endl;
    cout<<"用户名：20210694"<<endl;
}

void menu_main()
{
    cout<<"1.用户管理"<<endl;
    cout<<"2.读者管理"<<endl;
    cout<<"3.图书管理"<<endl;
    cout<<"4.图书流通管理"<<endl;
    cout<<"5.退出系统"<<endl;
    cout<<"请输入数字进行选择"<<endl;
}

void menu_usermanage()
{
    cout<<"1.用户信息输入"<<endl;
    cout<<"2.用户信息修改"<<endl;
    cout<<"3.用户信息删除"<<endl;
    cout<<"4.用户信息显示"<<endl;
    cout<<"5.用户密码修改"<<endl;
    cout<<"6.返回主菜单"<<endl;
    cout<<"请输出数字进行选择"<<endl;
}

void menu_modifyuser()
{
     cout<<"1.修改用户名"<<endl;
     cout<<"2.修改密码"<<endl;
     cout<<"3.修改用户类型"<<endl;
     cout<<"4.退出修改"<<endl;
     cout<<"请输入数字进行选择"<<endl;
}

void menu_readermanage()
{
    cout<<"1.读者信息输入"<<endl;
    cout<<"2.读者信息修改"<<endl;
    cout<<"3.读者信息删除"<<endl;
    cout<<"4.读者信息查询"<<endl;
    cout<<"5.读者信息显示（按姓氏排序）"<<endl;
    cout<<"6.返回主菜单"<<endl;
    cout<<"请输入数字进行选择"<<endl;
}

void menu_modifyreader()
{
     cout<<"1.修改读者号"<<endl;
     cout<<"2.修改读者名"<<endl;
     cout<<"3.修改读者单位"<<endl;
     cout<<"4.修改联系方式"<<endl;
     cout<<"5.修改可借书数"<<endl;
     cout<<"6.修改已借书数"<<endl;
     cout<<"7.退出修改"<<endl;
     cout<<"请输入数字进行选择"<<endl;
}

void menu_bookmanagement()
{
    cout<<"1.图书信息输入"<<endl;
    cout<<"2.图书信息修改"<<endl;
    cout<<"3.图书信息查询"<<endl;
    cout<<"4.汇总统计"<<endl;
    cout<<"5.显示图书文件及索引文件信息"<<endl;
    cout<<"6.返回主菜单"<<endl;
    cout<<"请输入数字进行选择"<<endl;
}

void menu_find_book()
{
    cout<<"1.按书号查询"<<endl;
    cout<<"2.按书名查询"<<endl;
    cout<<"3.按作者查询"<<endl;
    cout<<"4.按出版社查询"<<endl;
    cout<<"5.返回前置菜单"<<endl;
    cout<<"请输入数字进行选择"<<endl;
}

void menu_collection()
{
    cout<<"1.按书名进行统计"<<endl;
    cout<<"2.按作者名进行统计"<<endl;
    cout<<"3.按出版社名进行统计"<<endl;
    cout<<"4.退出汇总统计"<<endl;
    cout<<"请输入数字进行选择"<<endl;
}

void menu_modifybook()
{
    cout<<"1.修改书号"<<endl;
    cout<<"2.修改书名"<<endl;
    cout<<"3.修改作者名"<<endl;
    cout<<"4.修改出版社名"<<endl;
    cout<<"5.修改藏书量"<<endl;
    cout<<"6.修改借出量"<<endl;
    cout<<"7.退出修改"<<endl;
    cout<<"请输入数字进行选择"<<endl;
}

void menu_book_circulate()
{
    cout<<"1.借书处理"<<endl;
    cout<<"2.还书处理"<<endl;
    cout<<"3.显示借还书文件内容"<<endl;
    cout<<"4.返回主菜单"<<endl;
    cout<<"请输入数字进行选择"<<endl;
}
