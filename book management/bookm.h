#ifndef BOOKM_H_
#define BOOKM_H_

#include<string>
#include<list>

using namespace std;

class User
{
    private:
        int type;//3系统管理员（1名） 2 图书管理员 1普通读者
        char name[20];//用string会出现问题！！！
        char code[20];
    public:
        ~User();
        User();
        User(char* name_u,char* code_u,int type_u);
        void set_user();
        void show_user();
        //void change_code();
        int gettype(){return type;}
        string getname(){return name;}
        string getcode(){return code;}
        bool log_first();
        friend class User_control;//user_control的所有函数都可以访问user的私有数据
};//不用友元类也可以，需要多编几个get函数cin>>u.gettype可以吗,不可以，还是有存在必要

class User_control:public User
{
    private:
        list<User>listu;
        int n;
    public:
        User_control();
        User_control(int n_u);
        ~User_control();
        void input_from_keybord();
        void change_user();
        void read_from_file_to_list(string filename);
        void show_list();
        void write_to_file(string filename);
        bool log(User &u);
        void write_to_file_noapp(string filename);
        void modify();
        void delete_li();
        void change_code_li();
        void register_u();

};

class Reader
{
    private:
        int id;
        char reader_name[20];
        char unit[20];
        long long phone;
        int number_have;
        int number_borrowed;
    public:
        Reader();
        Reader(long id_r,char* name_r,char* unit_r,long phone_r,int number_have_r,int number_borrowed_r);
        ~Reader();
        void set_reader();
        void show_reader();
        bool friend operator<(Reader &r1,Reader &r2);
        friend class Reader_control;
        friend class Book_control;


};

class Reader_control:public Reader
{
    private:
        list<Reader>listr;
        int n;
    public:
        Reader_control();
        Reader_control(int n_r);
        ~Reader_control();
        void input_from_keybord_r();
        void read_from_file_to_list_r(string filename);
        void write_to_file_r(string filename);
        void write_to_file_noapp_r(string filename);
        void show_list_r();
        void modify_r();
        void delete_li_r();
        void find_r();
        void sort_r();
        friend class Book_control;



};

class Index_num
{
    private:
        int record_book_in;//记录号
        int num_book_in;//书号
    public:
        Index_num();
        ~Index_num();
        void show_index_num();
        friend class Book_control;

};

/*class Index_num_control
{
    private:
        list<Index_num> listn_i;
    public:
        Index_num_control();
        ~Index_num_control();

};*/

class Index_bookname
{
    private:
        char book_name_in[20];
        int p1_in;
        int len1;
    public:
        Index_bookname();
        ~Index_bookname();
        void show_index_bookname();
        char* get_boin(){return book_name_in;};
        friend class Book_control;
};
/*
class Index_bookname_control
{
    private:
        list<Index_bookname> listb_i;
    public:
        Index_bookname_control();
        ~Index_bookname_control();

};*/

class Index_aurthor
{
    private:
        char author_in[20];
        int p2_in;
        int len2;
    public:
        Index_aurthor();
        ~Index_aurthor();
        void show_index_authorname();
        char* get_auin(){return author_in;};
        friend class Book_control;
};
/*
class Index_aurthor_control
{
    private:
        list<Index_aurthor> lista_i;
    public:
        Index_aurthor_control();
        ~Index_aurthor_control();

};
*/
class Index_publish
{
    private:
        char publish_in[20];
        int p3_in;
        int len3;
    public:
        Index_publish();
        ~Index_publish();
        char* get_puin(){return publish_in;};
        void show_index_publishname();
        friend class Book_control;

};
/*
class Index_publish_control
{
    private:
        list<Index_publish> listp_i;
    public:
        Index_publish_control();
        ~Index_publish_control();

};
*/
class Book
{
    private:
        int record;//记录号
        int num_book;//书号
        char book_name[20];
        char author_name[20];
        char publish_name[20];//出版社名字
        int num_have;//藏书量
        int num_borrow;//借出数
        int p1;
        int p2;
        int p3;
    public:
        Book();
        //Book(int record_b,int num_book_b,)
        ~Book();
        void input_book();
        void show_book();
        void show_book_all();
        bool friend operator<(Book &b1,Book &b2);
        int get_record(){return record;};
        char* get_book_name(){return book_name;};
        char* get_author_name(){return author_name;};
        char* get_publish_name(){return publish_name;};
        friend class Book_control;

};

class BR_book
{
    private:
        int num_reader;
        int num_book_br;
        int month_b;
        int day_b;
        int month_r;
        int day_r;
    public:
        BR_book();
        ~BR_book();
        friend class Book_control;

};

class Book_control
{
    private:
        list<Book> listb;
        int num;//记录号
        list<Index_num> listn_i;//记录号索引
        list<Index_bookname> listb_i;//书名索引
        list<Index_aurthor> lista_i;//作者索引
        list<Index_publish> listp_i;//出版社索引
        list<BR_book>listbr;//读者借还书信息
        //list<Reader>listr;
    public:
        Book_control();
        ~Book_control();
        void input_book();//在输入时判断并改变指针写入文件
        void input_to_list(Book &b);//创建不同文件，往单个文件添加b
        //void input_bookin_from_keybord();
        void write_to_bookfile();
        void write_to_index_num();
        void write_to_index_bona();
        void write_to_index_auna();
        void write_to_index_puna();
        void write_to_bookfile_noapp();
        void write_to_index_num_noapp();
        void write_to_index_bona_noapp();
        void write_to_index_auna_noapp();
        void write_to_index_puna_noapp();
        void write_to_num_noapp();
        void read_from_num();
        void read_from_bookfile();
        void read_from_index_num();
        void read_from_index_bona();
        void read_from_index_auna();
        void read_from_index_puna();
        void Read_all();
        void show_filein();
        void show_brfile();
        void find_book_num();
        void find_book_name();
        void find_author_name();
        void find_publish_name();
        void collect_bona();
        void collect_auna();
        void collect_puna();
        void modify();
        //void read_from_reader();
        //void write_to_readerf();
        void borrow();
        void return_b();
        void read_from_brfile();
        //void write_to_bookfile_noapp_pushback();





};


void menu_log();
void menu_log_first();
void menu_main();
void menu_usermanage();
void menu_modifyuser();
void menu_readermanage();
void menu_modifyreader();
void menu_bookmanagement();
void menu_find_book();
void menu_collection();
void menu_modifybook();
void menu_book_circulate();

#endif // BOOKM_H_
