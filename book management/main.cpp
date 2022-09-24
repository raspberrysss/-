#include <iostream>
#include"bookm.h"
#include<string>
#include<list>
#include<fstream>
#include<cstdlib>
#include<cstring>
#include<conio.h>
#include<algorithm>

using namespace std;

int main(void)
{
   // char* file="用户信息.dat";有警告
    User u1,u2;
    User_control uc1,uc2,uc3,uc4,uc5,uc6,uc7,uc8;
    Reader_control rc1,rc2,rc3,rc4,rc5,rc6;
    Book_control bc1,bc2,bc3,bc4,bc5,bc6,bc71,bc72,bc73,bc8,bc9,bc10,bc11;
    ifstream fin("用户信息.dat",ios::in);
    if(!fin.is_open())//如果没有这个文件，就创建，继续接下来的操作
    {
    menu_log_first();
    if(u1.log_first())
    {
        system("pause");
        system("cls");
        cout<<"已成功激活图书管理系统"<<endl;
        cout<<"请系统管理员为程序写入基础用户文件与基础读者文件"<<endl;
        uc1.write_to_file("用户信息.dat");
        rc1.write_to_file_r("读者信息.dat");
        cout<<"已成功写入，用户信息写入信息如下"<<endl;
        uc1.show_list();
        cout<<"已成功写入，读者信息写入信息如下"<<endl;
        rc1.show_list_r();
        system("pause");
        cout<<"图书馆系统已被激活，欢迎使用！"<<endl;
        cout<<"请重启系统正常使用"<<endl;
        return 0;
        //system("pause");
        //system("cls");
    }
    else
    {
        cout<<"激活失败！强制退出程序！"<<endl;
        return 0;
    }
    }
    else if(fin.is_open())
    {
        //uc2.read_from_file_to_list("用户信息.dat");
        //uc2.show_list();
        int flag1=1;
        int choice1,choice2,choice3,choice4;
        while(flag1)
        {
            system("cls");
            menu_log();
            cin>>choice1;
            switch(choice1)
            {
              case 1:
            {
                  if(uc2.log(u2))
                {
                   int flag2=1;
                    if(u2.gettype()==1)
                    {
                        cout<<"欢迎用户"<<u2.getname()<<endl;
                    }
                    else if(u2.gettype()==2)
                    {
                        cout<<"欢迎图书管理员"<<u2.getname()<<endl;
                    }
                    else if(u2.gettype()==3)
                    {
                        cout<<"欢迎系统管理员"<<u2.getname()<<endl;
                    }
                  system("pause");
                  while(flag2)
                  {
                     system("cls");
                     menu_main();
                     cin>>choice2;
                     switch(choice2)
                     {

                     case 1:
                        {
                            int flag3=1;
                            while(flag3)
                            {
                                system("cls");
                                menu_usermanage();
                                cin>>choice3;
                                switch(choice3)
                                {
                                case 1:
                                    {
                                        if(u2.gettype()==3)
                                        {
                                             uc3.write_to_file("用户信息.dat");
                                        }
                                        else
                                        {
                                            cout<<"您没有操作此功能的权限"<<endl;
                                        }
                                        system("pause");
                                        break;
                                    }
                                case 2:
                                    {
                                        if(u2.gettype()==3)
                                        {
                                            uc4.modify();
                                        }
                                        else
                                        {
                                            cout<<"您没有操作此功能的权限"<<endl;
                                        }
                                        system("pause");
                                        break;
                                    }
                                case 3:
                                    {
                                            if(u2.gettype()==3)
                                            {
                                                uc5.delete_li();
                                            }
                                            else
                                            {
                                                cout<<"您没有操作此功能的权限"<<endl;
                                            }
                                            system("pause");
                                            break;
                                    }
                                case 4:
                                    {
                                        if(u2.gettype()==3)
                                        {
                                            uc6.read_from_file_to_list("用户信息.dat");
                                            cout<<"用户信息如下"<<endl;
                                            uc6.show_list();
                                        }
                                        else
                                        {
                                            cout<<"您没有操作此功能的权限"<<endl;
                                        }
                                        system("pause");
                                        break;
                                    }
                                case 5:
                                    {
                                        if(u2.gettype()==2)
                                        {
                                            cout<<"您没有操作此功能的权限"<<endl;
                                        }
                                        else
                                        {
                                            uc7.change_code_li();

                                        }
                                        system("pause");
                                        break;
                                    }
                                case 6:
                                    {
                                        flag3=0;
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
                            system("pause");
                            break;
                            }
                        case 2:
                        {
                            int flag4=1;
                            while(flag4)
                            {
                                system("cls");
                                menu_readermanage();
                                cin>>choice4;
                                switch(choice4)
                                {
                                case 1:
                                    {
                                        if(u2.gettype()==3)
                                        {
                                            rc2.write_to_file_r("读者信息.dat");
                                        }
                                        else
                                        {
                                            cout<<"您没有操作此功能的权限"<<endl;
                                        }
                                        system("pause");
                                        break;
                                    }
                                case 2:
                                    {   if(u2.gettype()==3)
                                        {
                                            rc3.modify_r();
                                        }

                                        else
                                        {
                                            cout<<"您没有操作此功能的权限"<<endl;
                                        }
                                        system("pause");
                                        break;
                                    }
                                case 3:
                                    {
                                        if(u2.gettype()==3)
                                        {
                                            rc4.delete_li_r();
                                        }
                                        else
                                        {
                                            cout<<"您没有操作此功能的权限"<<endl;
                                        }
                                        system("pause");
                                        break;
                                    }
                                case 4:
                                    {
                                        if(u2.gettype()==3)
                                        {
                                            rc5.find_r();
                                        }
                                        else
                                        {
                                            cout<<"您没有操作此功能的权限"<<endl;
                                        }
                                        system("pause");
                                        break;
                                    }
                                case 5:
                                    {
                                        if(u2.gettype()==3)
                                        {
                                            rc6.read_from_file_to_list_r("读者信息.dat");
                                            rc6.sort_r();
                                            rc6.show_list_r();//!仅显示未排序，测试其他
                                        }
                                        else
                                        {
                                            cout<<"您没有操作此功能的权限"<<endl;
                                        }
                                        system("pause");
                                        break;
                                    }
                                case 6:
                                    {
                                        flag4=0;
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
                             system("pause");
                             break;
                        }
                        case 3:
                        {
                            int flag5=1;
                            while(flag5)
                            {
                                system("cls");
                                menu_bookmanagement();
                                int choice5;
                                cin>>choice5;
                                switch(choice5)
                                {
                                case 1:
                                    {
                                        if(u2.gettype()!=2)
                                        {
                                            cout<<"您没有使用此功能的权限"<<endl;
                                        }
                                        else
                                        {
                                             bc1.input_book();
                                        //bc1.read_from_bookfile();
                                        //bc1.test();
                                        }

                                        system("pause");
                                        break;
                                    }
                                case 2:
                                    {
                                        if(u2.gettype()!=2)
                                        {
                                            cout<<"您没有使用此功能的权限"<<endl;
                                        }
                                        else
                                        {
                                            bc2.modify();
                                        }
                                       system("pause");
                                        break;
                                    }
                                case 3:
                                    {
                                        if(u2.gettype()==3)
                                        {
                                             cout<<"您没有使用此功能的权限"<<endl;
                                        }
                                        else
                                        {
                                            int flag6=1;
                                            while(flag6)
                                            {
                                                system("cls");
                                                menu_find_book();
                                                int choice6;
                                                cin>>choice6;
                                                switch(choice6)
                                                {
                                                case 1:
                                                    {
                                                        bc3.find_book_num();
                                                        system("pause");
                                                        break;
                                                    }
                                                case 2:
                                                    {
                                                        bc4.find_book_name();
                                                        system("pause");
                                                        break;
                                                    }
                                                case 3:
                                                    {
                                                        bc5.find_author_name();
                                                        system("pause");
                                                        break;
                                                    }
                                                case 4:
                                                    {
                                                        bc6.find_publish_name();
                                                        system("pause");
                                                        break;
                                                    }
                                                case 5:
                                                    {
                                                        flag6=0;
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
                                        system("pause");
                                        break;
                                    }
                                case 4:
                                    {
                                        if(u2.gettype()!=2)
                                        {
                                            cout<<"您没有操作此功能的权限"<<endl;
                                        }
                                        else
                                        {
                                            int flag7=1;
                                        while(flag7)
                                        {
                                            system("cls");
                                            menu_collection();
                                            int choice7;
                                            cin>>choice7;
                                            switch(choice7)
                                            {
                                            case 1:
                                                {
                                                    bc71.collect_bona();
                                                    system("pause");
                                                    break;
                                                }
                                            case 2:
                                                {
                                                    bc72.collect_auna();
                                                    system("pause");
                                                        break;
                                                }
                                            case 3:
                                                {
                                                    bc73.collect_puna();
                                                    system("pause");
                                                        break;
                                                }
                                            case 4:
                                                {
                                                    flag7=0;
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
                                        system("pause");
                                        break;
                                    }

                                case 5:
                                    {
                                        if(u2.gettype()!=2)
                                        {
                                            cout<<"您没有使用此功能的权限"<<endl;
                                        }
                                        else
                                        {

                                       // bc8.read_from_bookfile();
                                       // bc8.read_from_index_num();
                                        //bc8.read_from_index_bona();
                                        //bc8.read_from_index_auna();
                                        //bc8.read_from_index_puna();
                                        bc8.Read_all();
                                        bc8.read_from_num();
                                        bc8.show_filein();
                                        }
                                        system("pause");
                                        break;
                                    }
                                case 6:
                                    {
                                        flag5=0;
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

                             system("pause");
                             break;
                        }
                        case 4:
                        {
                           int flag8=1;
                           while(flag8)
                           {
                               system("cls");
                               menu_book_circulate();
                               int choice8;
                               cin>>choice8;
                               switch(choice8)
                               {
                               case 1:
                                {
                                    if(u2.gettype()!=2)
                                    {
                                        cout<<"您没有操作此功能的权限"<<endl;
                                    }
                                    else
                                    {
                                            bc9.borrow();
                                    }
                                    system("pause");
                                    break;
                                }
                               case 2:
                                {
                                    if(u2.gettype()!=2)
                                    {
                                        cout<<"您没有操作此功能的权限"<<endl;
                                    }
                                    else
                                    {
                                        bc10.return_b();
                                    }
                                    system("pause");
                                    break;
                                }
                               case 3:
                                {
                                    if(u2.gettype()!=2)
                                    {
                                        cout<<"您没有操作此功能的权限"<<endl;
                                    }
                                    else
                                    {
                                      bc11.show_brfile();
                                    }
                                    system("pause");
                                    break;
                                }
                               case 4:
                                {
                                    flag8=0;
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
                           system("pause");
                           break;
                        }
                        case 5:
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
                  else
                  {
                     cout<<"登录失败，请选择其他选项或重新尝试登录"<<endl;
                  }
                   system("pause");
                   break;
                  }
            case 2:
                {

                    uc8.register_u();
                    system("pause");
                    break;
                }
            case 3:
                {
                    flag1=0;
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




    return 0;
}
