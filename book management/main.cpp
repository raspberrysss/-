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
   // char* file="�û���Ϣ.dat";�о���
    User u1,u2;
    User_control uc1,uc2,uc3,uc4,uc5,uc6,uc7,uc8;
    Reader_control rc1,rc2,rc3,rc4,rc5,rc6;
    Book_control bc1,bc2,bc3,bc4,bc5,bc6,bc71,bc72,bc73,bc8,bc9,bc10,bc11;
    ifstream fin("�û���Ϣ.dat",ios::in);
    if(!fin.is_open())//���û������ļ����ʹ����������������Ĳ���
    {
    menu_log_first();
    if(u1.log_first())
    {
        system("pause");
        system("cls");
        cout<<"�ѳɹ�����ͼ�����ϵͳ"<<endl;
        cout<<"��ϵͳ����ԱΪ����д������û��ļ�����������ļ�"<<endl;
        uc1.write_to_file("�û���Ϣ.dat");
        rc1.write_to_file_r("������Ϣ.dat");
        cout<<"�ѳɹ�д�룬�û���Ϣд����Ϣ����"<<endl;
        uc1.show_list();
        cout<<"�ѳɹ�д�룬������Ϣд����Ϣ����"<<endl;
        rc1.show_list_r();
        system("pause");
        cout<<"ͼ���ϵͳ�ѱ������ӭʹ�ã�"<<endl;
        cout<<"������ϵͳ����ʹ��"<<endl;
        return 0;
        //system("pause");
        //system("cls");
    }
    else
    {
        cout<<"����ʧ�ܣ�ǿ���˳�����"<<endl;
        return 0;
    }
    }
    else if(fin.is_open())
    {
        //uc2.read_from_file_to_list("�û���Ϣ.dat");
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
                        cout<<"��ӭ�û�"<<u2.getname()<<endl;
                    }
                    else if(u2.gettype()==2)
                    {
                        cout<<"��ӭͼ�����Ա"<<u2.getname()<<endl;
                    }
                    else if(u2.gettype()==3)
                    {
                        cout<<"��ӭϵͳ����Ա"<<u2.getname()<<endl;
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
                                             uc3.write_to_file("�û���Ϣ.dat");
                                        }
                                        else
                                        {
                                            cout<<"��û�в����˹��ܵ�Ȩ��"<<endl;
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
                                            cout<<"��û�в����˹��ܵ�Ȩ��"<<endl;
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
                                                cout<<"��û�в����˹��ܵ�Ȩ��"<<endl;
                                            }
                                            system("pause");
                                            break;
                                    }
                                case 4:
                                    {
                                        if(u2.gettype()==3)
                                        {
                                            uc6.read_from_file_to_list("�û���Ϣ.dat");
                                            cout<<"�û���Ϣ����"<<endl;
                                            uc6.show_list();
                                        }
                                        else
                                        {
                                            cout<<"��û�в����˹��ܵ�Ȩ��"<<endl;
                                        }
                                        system("pause");
                                        break;
                                    }
                                case 5:
                                    {
                                        if(u2.gettype()==2)
                                        {
                                            cout<<"��û�в����˹��ܵ�Ȩ��"<<endl;
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
                                        cout<<"��������ȷ����"<<endl;
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
                                            rc2.write_to_file_r("������Ϣ.dat");
                                        }
                                        else
                                        {
                                            cout<<"��û�в����˹��ܵ�Ȩ��"<<endl;
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
                                            cout<<"��û�в����˹��ܵ�Ȩ��"<<endl;
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
                                            cout<<"��û�в����˹��ܵ�Ȩ��"<<endl;
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
                                            cout<<"��û�в����˹��ܵ�Ȩ��"<<endl;
                                        }
                                        system("pause");
                                        break;
                                    }
                                case 5:
                                    {
                                        if(u2.gettype()==3)
                                        {
                                            rc6.read_from_file_to_list_r("������Ϣ.dat");
                                            rc6.sort_r();
                                            rc6.show_list_r();//!����ʾδ���򣬲�������
                                        }
                                        else
                                        {
                                            cout<<"��û�в����˹��ܵ�Ȩ��"<<endl;
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
                                        cout<<"��������ȷ����"<<endl;
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
                                            cout<<"��û��ʹ�ô˹��ܵ�Ȩ��"<<endl;
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
                                            cout<<"��û��ʹ�ô˹��ܵ�Ȩ��"<<endl;
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
                                             cout<<"��û��ʹ�ô˹��ܵ�Ȩ��"<<endl;
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
                                        cout<<"��������ȷ����"<<endl;
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
                                            cout<<"��û�в����˹��ܵ�Ȩ��"<<endl;
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
                                        cout<<"��������ȷ����"<<endl;
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
                                            cout<<"��û��ʹ�ô˹��ܵ�Ȩ��"<<endl;
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
                                        cout<<"��������ȷ����"<<endl;
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
                                        cout<<"��û�в����˹��ܵ�Ȩ��"<<endl;
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
                                        cout<<"��û�в����˹��ܵ�Ȩ��"<<endl;
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
                                        cout<<"��û�в����˹��ܵ�Ȩ��"<<endl;
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
                                        cout<<"��������ȷ����"<<endl;
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
                    cout<<"��������ȷ����"<<endl;
                    system("pause");
                    break;
                  }
                        }

                     }
                  }
                  else
                  {
                     cout<<"��¼ʧ�ܣ���ѡ������ѡ������³��Ե�¼"<<endl;
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
                    cout<<"��������ȷ����"<<endl;
                    system("pause");
                    break;
                }

            }
        }


    }




    return 0;
}
