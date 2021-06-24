//These are the files used in this project(made by IRTAZA, JAWAD AND YAZAAN)
//activationrecord.txt includes status of each book in form of 0 (not presnt) and 1(presnt)
//allbooks.txt includes names of all books present in library,librarian can add or remove the book from this list
//dataofbooks.txt includes authors of the books which are present in the book list available in library
//alldata.txt includes the usernames and passwords of every new user who first time sign-up
//allowordecline.txt includes the data for the granting permissions of issue the book(0 means book available,1 means book issuing permission need from librarian,2 means book is issued by librarian and again 0 means book is returned to library)further username who want to issue the book and that bookname is also saved in this file in same row
#include<iostream>
#include<string>
#include<fstream>
using namespace std;
class book {

private:
    char* name;
    char* author;
    bool status;

public:
    book()
    {
        name = nullptr;
        author = nullptr;

    }
    void createnewactivation(int* arr, int totalbooks)
    {
        ofstream off("activationrecord.txt");

        for (int i = 0; i < totalbooks; i++)
        {
            off << arr[i];
            off << endl;
        }


    }

    void showstatus(int& c, char* nameofbook, int totalbooks, int& co)
    {
        fstream in("dataofbooks.txt");
        ifstream activation("activationrecord.txt");
        ifstream copy("activationrecord.txt");
        //   char* a=new char;//for author name accessing from file named(dataofbooks.txt)
        char* b = new char[40];
        //tring a;

        int* arr = new int[totalbooks];
        for (int i = 0; i < totalbooks; i++)
        {
            copy >> arr[i];
        }

        for (int i = 0; i < totalbooks; i++)
        {
            if (i == c)
            {
                name = nameofbook;

                in.getline(b, 40);
                this->author = b;
                activation >> this->status;
                arr[i] = this->status;

                if (this->status == 0 || this->status == 1)
                {

                    if (co == 1 && this->status == true)
                    {
                        cout << endl << " Book is Available : ) " << endl;
                        cout << "Name of book: " << name << endl;
                        cout << endl << "Author is: " << this->author << endl;

                        arr[i] = 0;
                        createnewactivation(arr, totalbooks);
                        break;
                    }
                    else if (co == 1 && this->status == false)
                    {
                        arr[i] = 0;
                        createnewactivation(arr, totalbooks);
                        cout << endl << "Book is Unavailable : / " << endl;
                        break;
                    }
                    else if (co == 2 && this->status == false)
                    {

                        arr[i] = 1;
                        createnewactivation(arr, totalbooks);

                        break;
                    }
                    else if (co == 2 && this->status == true)
                    {
                        cout << endl << "Book is already returned you cant return it." << endl;
                        return;
                    }


                }

            }
            else
            {
                in.getline(b, 40);
                activation >> status;
            }
        }
    }
};
class user {

private:
    char** name;
    char** password;

    int i;

public:
    book** uniquenumberofbook;
    user()
    {
        name = nullptr;
        password = nullptr;
        uniquenumberofbook = nullptr;
        i = 0;
        name = new char* [100];
        password = new char* [100];
    }
    void checkwhilebookisavailableornot(char* issuebook, int& co)
    {
        uniquenumberofbook = new book * [20];

        int i=0;
		int c = 0;
		int f=0;
        char* a = new char[40];
        ifstream inn("allbooks.txt");
        for (f = 0; !inn.eof(); f++)
        {
            string temp;
            getline(inn, temp);
        }
        ifstream d("allbooks.txt");
        while (!d.eof())
        {
            i = 0;

            d.getline(a, 40);


            uniquenumberofbook[c] = new book[strlen(a)];
            for (int k = 0; k < strlen(a); k++)
            {
                if (issuebook[k] == a[k])
                {
                    i++;
                }
                if (i == strlen(a))
                {
                    uniquenumberofbook[c]->showstatus(c, issuebook, f, co);
                    //showstatus();
                }


            }
            c++;
        }




    }
    void showoptions(char* currentuser)
    {

        int co = 0;
        char** base = new char* [1];
        base[0] = new char[30];
        cout << endl << "-----------------------------WELCOME TO USER PANEL----------------------------" << endl;

        ifstream inputdata("allowordecline.txt");

        int k; char* requesteduser = new char[30];

        inputdata >> k;

        inputdata >> requesteduser;


        char nameofbook[30];
        inputdata >> nameofbook;
        int counter = 0;
        if (strlen(currentuser) == strlen(requesteduser))
        {
            for (int i = 0; i < strlen(currentuser); i++)
            {
                if (currentuser[i] == requesteduser[i])
                {
                    counter++;
                }
            }

        }

        if (counter == strlen(currentuser))
        {
            if (k == 2)
            {
                co = 1;
                cout << nameofbook << " has been issued to you by librarian";
                checkwhilebookisavailableornot(nameofbook, co);
				cout<<"for others NOW "<<endl<<endl<<endl;
            }
        }


        cout << "Enter 1 to issue a book." << endl;

        cout << "Enter 2 to return a book." << endl;
		
        cout << "Enter 3 to exit the Panel:)" << endl;
        cin >> co;
        if (co == 1 || co == 2)
        {
            
			int a;
            ifstream all("allowordecline.txt");
            all >> a;
           /* all >> requesteduser;
            all >> nameofbook;
			*/

            if (co == 1)
            {
				ifstream act("activationrecord.txt"); 
				ifstream objectiss("allbooks.txt");
				int booksavailablestatus;
				 for (int i = 0; !objectiss.eof(); i++)
					{
						if (i == 0)
							cout << "=================AVAILABLE BOOKS ARE========================" << endl;
						act >> booksavailablestatus;
						if (booksavailablestatus == 1)
						{
							string get;
							getline(objectiss, get);
							cout << get << endl;;        
						}
						if (booksavailablestatus == 0)
						{
							string extra;
							getline(objectiss, extra);
						}
					}
				cout << "PLEASE--Enter the Name of the book which You want to issue!" << endl;
				char* issuebook = new char[40];
				cin.ignore();
				cin.getline(issuebook, 40);
				cout << endl;
				cout << issuebook << endl;
				ofstream allowance("allowordecline.txt");
                allowance << co;
                allowance << " ";
                allowance << currentuser;
                allowance << " ";
                allowance << issuebook;
                cout << endl << "Your request has sent to the librarian, Please wait for his response. ";
                return;
            }
            //yeh functionality tab perform ho jab file me librarian allow krde
            else if (co == 2 && a == 2)
            {
				cout << "PLEASE--Enter the Name of the book which You want to Return (important point is that book should be already issued to you)!!" << endl;
				cout<<"Enter here:\t\t\t";
				char* returnbook = new char[40];
				cin.ignore();
				cin.getline(returnbook, 40);
				cout << endl;
				cout << returnbook << endl;
                ofstream allowance("allowordecline.txt");
                int zero;
                zero = 0;
                allowance << zero << " ";
                allowance << currentuser;
                allowance << " ";
                allowance << returnbook;
                checkwhilebookisavailableornot(returnbook, co);
                cout << endl << returnbook << " has returned successfully!!!!" << endl;
                return;

            }
            //obj.uniquenumberofbook;
            //issue a book
        }
		else
		if(co==3)
		{
			cout<<"PANEL LEFT!HAVE NICE DAY DEAR:)"<<endl;
		}
        else
        {
            cout << endl << "This was not the correct number to press!SO HAVE NICE DAY!!!BETTER LUCK NEXT TIME:)" << endl;
            return;
        }


    }


    bool signinuser(char*& name)
    {
        cout << endl << "\t\t\tLogging-IN of User" << endl;
        ifstream obj("alldata.txt");//ifstream used here to check the list of the alldata.txt file and finding the exact matched user name and password

        name = new char[30];//allocation of user name entered by the user during logging in at run time
        char* password = new char[30];//allocation of password entered by the user during logging in at the run time
        char* namecpy = new char[30];//allocation of the user name which is present in the record of registered user names and passwords OR (alldata.txt)File
        char* passcpy = new char[30];//allocation of the user password which is present in the record of registered user names and passwords OR (alldata.txt)File


        int temp = 1;//when temp=1,I have used bool ture and when temp=0 I have used bool false

        int N;//size of registered names present in the (alldata.txt) file
        int P;//size of registered passwords present in the (alldata.txt) file


        cout << "Enter name:\t\t\t";
        cin >> name;
        int n = strlen(name);//length of username taken by user at runtime for putting delimeter(\0)..U can also see in next line
        name[n++] = '\0';

        cout << "Enter password:\t\t\t";
        cin >> password;
        int p = strlen(password);//length of paswrd taken by user at runtime for putting delimeter(\0)..U can also see in next line
        password[p++] = '\0';

        cout << "================================================================================" << endl << endl;

      

        while (!obj.eof())//means if file is not empty further yet
        {
            temp = 1;//every time bool will become true in start because we have to check all lines of registred names and paswrds

            obj >> namecpy;
            N = strlen(namecpy);
            namecpy[N++] = '\0';
           

            obj >> passcpy;
            P = strlen(passcpy);
            passcpy[P++] = '\0';
           
            int i;
            for (i = 0; i < N; i++)
            {
                if (name[i] != namecpy[i])
                {
                    temp = 0;
                }
            }

            int k;
            for (k = 0; k < P; k++)
            {
                if (password[k] != passcpy[k])
                {
                    temp = 0;
                }
            }

            cout << endl;
            if (temp == 1)
            {
                return true;
            }

        }
        return false;
    }

    void enterdatainfile(char** nameof, char** passof, fstream& data)
    {

        data << *nameof;
        data << " ";
        data << *passof;
        data << endl;

    }
    void registeryourself(fstream& data)
    {
        //====================NAME--ENTERING======================================

        cout << "\t\t\t Registering of User" << endl;
        cout << "============================================================================" << endl;
        cout << "Enter Login User name:\t\t";
        char* a;
        a = new char[30];
        cin >> a;
        int l = strlen(a);

        name[i] = new char[l];

        for (int k = 0; k < l; k++)
        {
            name[i][k] = a[k];
        }
        name[i][l] = '\0';
        cout << endl << name[i] << endl;


        //===================PASSWORD--ENTERING======================================

        cout << "Enter Login PASSWORD:\t\t";
        char* passwordofuser;

        passwordofuser = new char[30];
        cin >> passwordofuser;

        int lengthofenteredpassword;

        lengthofenteredpassword = strlen(passwordofuser);

        password[i] = new char[lengthofenteredpassword];

        int k;

        for (k = 0; k < lengthofenteredpassword; k++)
        {
            password[i][k] = passwordofuser[k];
        }
        password[i][k] = '\0';

        cout << endl << password[i] << endl;
        //i++;
        enterdatainfile(name, password, data);


    }
};
class librarian {

private:
    char** name;
    char** password;
    user** userlist;
    book** books;
    int j;

public:
    librarian()
    {
        userlist = nullptr;
        books = nullptr;
        name = nullptr;
        password = nullptr;
        j = 0;
        name = new char* [1];
        password = new char* [1];

    }
    void showoptionstolibrarian()
    {
        int a;
        cout << "Press 1 to add book." << endl;
        cout << "Press 2 to remove a book." << endl;
        cout << "Press 3 to edit a book." << endl;
        cout << "Press Any other button else 1,2,3 to Quit,Successfully." << endl;
        cin >> a;
        if (a == 1)
        {
            char* newbook = new char[40];
            cin.ignore();//just to ignore errors
            cin.getline(newbook, 40);
            fstream obj("allbooks.txt", ios::app);
            obj << endl << newbook;

            char* author = new char[40];
            cin.getline(author, 40);
            fstream objforauthor("dataofbooks.txt", ios::app);
            objforauthor << endl << author;

            ifstream newobj("allbooks.txt");

            int x;
            for (x = 0; !newobj.eof(); x++)
            {
                string b;
                getline(newobj, b);
                //just to catch the new counter of total books
            }
            cout << endl;
            cout << "x is now " << x << endl;
            ifstream off("activationrecord.txt");
            int* aem;
            aem = new int[x];

            for (int f = 0; f < x - 1; f++)
            {
                off >> aem[f];
            }
            aem[x - 1] = 0;
            ofstream ok("activationrecord.txt");

            for (int i = 0; i < x; i++)
            {

                ok << aem[i];
                ok << endl;
            }




            //fstream app("activationrecord.txt",ios::app);
            //pp<<a;

            //process in working
            //linking with book class and functions will be made in book class which were accessed by two d array present in the private area of librarian and in the function of book class,we will easily access to private area of book class
        }
        else
            if (a == 2)
            {
                //process in working
                //remove book
                cout << "Enter the name of book which you want to remove:\t\t\t";
                char* newbook = new char[40];
                cin.ignore();//just to ignore errors
                cin.getline(newbook, 40);
                cout << endl;
                ifstream newobj("allbooks.txt");

                int x;
                int linecatcher;
                int cheq = 0;
                for (x = 0; !newobj.eof(); x++)
                {
                    char* bookname = new char[50];
                    newobj.getline(bookname, 50);
                    cout << "book name is " << endl;
                    cout << bookname << endl;
                    if (strlen(bookname) == strlen(newbook))
                    {
                        for (int i = 0; i < strlen(bookname); i++)
                        {
                            if (bookname[i] == newbook[i])
                            {
                                cheq++;
                            }
                        }

                    }

                    if (cheq == strlen(bookname))
                    {
                        linecatcher = x;
                        break;
                    }
                    //just to catch the new counter of total books
                }

                ifstream newone("allbooks.txt");

                int totalbooks;
                for (totalbooks = 0; !newone.eof(); totalbooks++)
                {
                    char* waste = new char[50];
                    //cin.ignore();
                    newone.getline(waste, 50);
                    //just to catch the new counter of total books
                }


                ifstream objectis("allbooks.txt");

                int lines = 0;
                int reallines = 0;

                char** afterremovingarrayis = new char* [totalbooks - 1];
                while (!objectis.eof())
                {
                    if (lines == linecatcher)
                    {
                        string removetheline;
                        getline(objectis, removetheline);
                        lines++;
                    }
                    if (lines != linecatcher)
                    {
                        afterremovingarrayis[reallines] = new char[50];
                        objectis.getline(afterremovingarrayis[reallines], 50);
                        reallines++;
                        lines++;
                    }
                }


                ofstream abc("allbooks.txt");
                for (int i = 0; i < totalbooks - 1; i++)
                {
                    if (i != totalbooks - 2)
                    {
                        abc << afterremovingarrayis[i] << endl;
                    }
                    if (i == totalbooks - 2)
                    {
                        abc << afterremovingarrayis[i];
                    }
                }



                //==================================================================================

                ifstream object1("dataofbooks.txt");

                lines = 0;
                reallines = 0;

                char** afterremovingarrayis1 = new char* [totalbooks - 1];
                while (!object1.eof())
                {
                    if (lines == linecatcher)
                    {
                        string removetheline1;
                        getline(object1, removetheline1);
                        lines++;
                    }
                    if (lines != linecatcher)
                    {
                        afterremovingarrayis1[reallines] = new char[50];
                        object1.getline(afterremovingarrayis1[reallines], 50);
                        reallines++;
                        lines++;
                    }
                }


                ofstream xyz("dataofbooks.txt");
                for (int i = 0; i < totalbooks - 1; i++)
                {
                    if (i != totalbooks - 2)
                    {
                        xyz << afterremovingarrayis1[i] << endl;
                    }
                    if (i == totalbooks - 2)
                    {
                        xyz << afterremovingarrayis1[i];
                    }
                }

                //=================================================================================================
                int counter;
                counter = 0;
                ifstream objforactivation("activationrecord.txt");
                char* activationlist = new char[totalbooks - 1];
                for (int i = 0; !objforactivation.eof(); i++)
                {
                    if (i == linecatcher)
                    {
                        string extra2;
                        getline(objforactivation, extra2);
                    }
                    if (i != linecatcher)
                    {
                        objforactivation >> activationlist[counter];
                        counter++;
                    }
                }

                ofstream output("activationrecord.txt");
                for (int i = 0; i < totalbooks - 1; i++)
                {
                    if (i != totalbooks - 2)
                    {
                        output << activationlist[i] << endl;
                    }
                    if (i == totalbooks - 2)
                    {
                        output << activationlist[i];
                    }
                }


            }
            else
                if (a == 3)
                {


                    cout << "Enter the name of book whose author you want to edit:\t\t\t";
                    char* newbook = new char[40];
                    cin.ignore();//just to ignore errors
                    cin.getline(newbook, 40);
                    cout << endl;
                    ifstream authorfile("allbooks.txt");

                    int x;
                    int linecatcher;
                    int cheq = 0;
                    for (x = 0; !authorfile.eof(); x++)
                    {
                        char* bookname = new char[50];
                        authorfile.getline(bookname, 50);
                        cout << "book name is " << endl;
                        cout << bookname << endl;
                        if (strlen(bookname) == strlen(newbook))
                        {
                            for (int i = 0; i < strlen(bookname); i++)
                            {
                                if (bookname[i] == newbook[i])
                                {
                                    cheq++;
                                }
                            }

                        }

                        if (cheq == strlen(bookname))
                        {
                            linecatcher = x;
                            break;
                        }
                        //just to catch the new counter of total books
                    }

                    ifstream newone("dataofbooks.txt");

                    int totalbooks;
                    for (totalbooks = 0; !newone.eof(); totalbooks++)
                    {
                        char* waste = new char[50];
                        //cin.ignore();
                        newone.getline(waste, 50);
                        //just to catch the new counter of total books
                    }

                    ifstream objectis("dataofbooks.txt");

                    int reallines;
                    reallines = 0;

                    char** arrayis = new char* [totalbooks];
                    while (!objectis.eof())
                    {
                        if (reallines == linecatcher)
                        {
                            cout << "Edit authors here:\t\t\t";
                            arrayis[reallines] = new char[50];
                            string extra;
                            getline(objectis, extra);
                            cin.ignore();
                            cin.getline(arrayis[reallines], 50);
                            reallines++;
                        }
                        if (reallines != linecatcher)
                        {
                            arrayis[reallines] = new char[50];
                            objectis.getline(arrayis[reallines], 50);
                            reallines++;
                        }
                    }


                    ofstream abc("dataofbooks.txt");
                    for (int i = 0; i < totalbooks; i++)
                    {
                        if (i != totalbooks - 1)
                        {
                            abc << arrayis[i] << endl;
                        }
                        if (i == totalbooks - 1)
                        {
                            abc << arrayis[i];
                        }
                    }

                }
                else
                {
                    cout << "Panel left Successfully,HAVE NICE DAY :)" << endl;
                }




    }
    /*
    void updateactivationrecord(ifstream& newobj,ifstream& off,ofstream& ok,string& bookname)
    {

    }*/
    void signinlibrarian()
    {
        //==============NAME--ENTERING===========================================
        cout << endl << "\t\t\tSign---in of the LIBRARIAN" << endl;
        cout << "============================================================================" << endl;
        cout << "Enter login user name:\t\t";
        char* nameoflibrarian;
        nameoflibrarian = new char[30];
        cin >> nameoflibrarian;

        int lengthofenteredname = strlen(nameoflibrarian);

        name[j] = new char[lengthofenteredname];
        int x;

        for (x = 0; x < lengthofenteredname; x++)
        {
            name[j][x] = nameoflibrarian[x];
        }
        name[j][x] = '\0';

        cout << endl << name[j] << endl;


        //================PASS-WORD ENTERING====================================
        char* passwordoflibrarian;
        cout << "Enter login PASS--WORD:\t\t";
        passwordoflibrarian = new char[30];
        cin >> passwordoflibrarian;
        int lengthofenteredpassword;
        lengthofenteredpassword = strlen(passwordoflibrarian);
        password[j] = new char[lengthofenteredpassword];
        int k;
        for (k = 0; k < lengthofenteredpassword; k++)
        {
            password[j][k] = passwordoflibrarian[k];
        }
        password[j][k] = '\0';
        cout << endl << password[j] << endl;

        //opening file for pending requests
//2d array append ifstream ofstream sb use krna h taak record bna rhy

        ifstream openfile("allowordecline.txt");
        openfile >> k;
        if (k == 1)
        {
            string name;
            string bookname;
            //checking whether book name is present
            //checking whether its activation record is present or not
            cout << "Hello man, Somme requests are here,please check them out" << endl;
            openfile >> name;
            openfile >> bookname;
            cout << name << " has requested to take the book named " << bookname << endl;
            cout << "Enter 1 to accept and 2 to decline" << endl;
            cin >> k;
            if (k == 1)
            {

                ofstream hmm("allowordecline.txt");
                hmm << 2 << " " << name << " " << bookname;


                //to update activation record

                ifstream newobj("allbooks.txt");
                int x;
                int matchedline;
                for (x = 0; !newobj.eof(); x++)
                {
                    string b;
                    getline(newobj, b);
                    if (b == bookname)
                    {
                        matchedline = x;
                    }
                    //just to catch
                }
                cout << endl;
                //=========================================================================================
                ifstream off("activationrecord.txt");

                int* aem;
                aem = new int[x];

                for (int f = 0; f < x; f++)
                {
                    off >> aem[f];
                }
                aem[matchedline] = 0;
                //=========================================================================================
                ofstream ok("activationrecord.txt");
                for (int i = 0; i < x; i++)
                {

                    ok << aem[i];
                    ok << endl;
                }


            }

        }

    }
};

int typeofperson()
{
    cout <<endl<< "        =============================LIBRARY PANEL===============================" << endl;
    cout <<endl<< "Enter '1' If you are a User. " << endl << "Enter '2' If you are Librarian. " << endl;
    cout << "Now Who Are You? ";
    int enterednum;
    cin >> enterednum;
    cout << "================================================================================" << endl << endl;
    return enterednum;
    

}

void main()
{
    char* name = nullptr;
    fstream data("alldata.txt", ios::app);
    //fstream is to input and output file simultaneously and  ios::app is for
    //entering values without losing previous values
    user obj;
    librarian holder;

    int choice = typeofperson();
    if (choice == 1)
    {
        int c;
        cout << "If you want to register,then Press 1. " << endl << "If you already have an account,then Press 2." << endl;
        cout << endl << endl << " Enter your chocie: ";
        cin >> c;
        if (c == 1)
        {
            obj.registeryourself(data);
        }
        else if (c == 2)
        {
            if (obj.signinuser(name) == false)
            {
                cout << endl << "Your entered credentials are incorrect!!.";
            }
            else
            {

                obj.showoptions(name);
                cout << endl << "===============SUCCESSFULL================" << endl;
            }
        }
    }
    else if (choice == 2)
    {
        cout << endl << "\t\t\t LIBRARIAN PANEL" << endl;
        holder.signinlibrarian();
        holder.showoptionstolibrarian();
    }
    else
    {
        cout << endl << "Panel don't exist because you have entered wrong number :) " << endl;
        return;
    }
    system("pause");

}
