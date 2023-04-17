#include<iostream>
#include<fstream>
#include<sstream>
#include<string>

using namespace std;

int main ()
{
 int a, i=0;
 string text, old, password1, password2, pass, name, password0, age, user, word, word1;
 string creds[2], cp[2];
 
 cout<<"     Security System       "<<endl;
 cout<<"___________________________"<<endl<<endl;
 cout<<"|     1.REGISTER          |"<<endl;
 cout<<"|     2.LOGIN             |"<<endl;
 cout<<"|     3.CHANGE PASSWORD   |"<<endl;
 cout<<"|_____4.END PROGRAM_______|"<<endl<<endl;
  
 do {
    cout<<endl<<endl;
    cout<<"ENTER YOUR CHOICE:-";
    cin>>a;
    switch(a)
    {
        case 1:{
            cout<<"___________________________"<<endl<<endl;
            cout<<"|--------REGISTER---------|"<<endl;
            cout<<"|_________________________|"<<endl<<endl;
            cout<<"Enter username:- ";
            cin>>name;
            cout<<"Enter password:- ";
            cin>>password0;
            cout<<"Enter your age:- ";
            cin>>age;
            ofstream of1;
            of1.open("file.txt");
            if(of1.is_open()){
                of1<<name<<"\n";
                of1<<password0;
                cout<<"Registration sucessfull"<<endl; 
            }

            break;
        }
        case 2:{
            i=0;
            cout<<"___________________________"<<endl<<endl;
            cout<<"|--------LOGIN IN---------|"<<endl;
            cout<<"|_________________________|"<<endl<<endl;
            ifstream of2;
            of2.open("file.txt");
            cout<<"Enter username:- ";
            cin>>user;
            cout<<"Enter password:- ";
            cin>>pass;
            if(of2.is_open()){
                while(!of2.eof())
                {
                    while(getline(of2, text)){
                        istringstream iss(text);
                        iss>>word;
                        creds[i]=word;
                        i++;
                    }
                    if (user==creds[0]&& pass==creds[1]){
                        cout<<"----Login sucessfull------";
                        cout<<endl<<endl;
                        cout<<"    Details:    "<<endl;
                        cout<<"Username: "+name<<endl;
                        cout<<"Password: "+password0<<endl;
                        cout<<"Age: "+age<<endl;
                        }

                        else {
                            cout<<endl<<endl;
                            cout<<"Incorrect Credentials"<<endl;
                            cout<<"|     1. Press 2 to login again     |"<<endl;
                            cout<<"|     2. Press 3 to change password |"<<endl;
                            break;
                        }

                }
                
            }
            break;
        }
        case 3:{
            i=0;
           
            cout<<"|----CHANGE PASSSWORD-----|"<<endl;
           
            ifstream of0;
            of0.open("file.txt");
            cout<<"Enter the  old password:- ";
            cin>>old;
            if (of0.is_open())
            {
                while(!of0.eof())
                {
                    while(getline(of0, text))
                    {
                        istringstream iss(text);
                        iss>>word1;
                        cp[i]=word1;
                        i++;
                        
                        }
                        if(old==cp[1])
                        {
                            of0.close();
                            ofstream of1;
                            of1.open("file.txt");
                            if (of1.is_open())
                            {
                                cout<<"Enter new password:- ";
                                cin>>password1;
                                cout<<"Enter your password again:- ";
                                cin>>password2;

                                if(password1==password2)
                                {
                                    of1<<cp[0]<<"\n";
                                    of1<<password1;
                                    cout<<"Password changed sucessfully"<<endl;

                                }
                                else{
                                    of1<<cp[0]<<"\n"; 
                                    of1<<old;
                                    cout<<"Password do not match"<<endl;
                                    
                                }

                            }
                        }
                            else{
                                cout<<"Please enter a valid password"<<endl;
                              }  break;
                            
                        
                }
            }
            break;
        }
        case 4:{
            cout<<"      THANK YOU!     "<<endl;
            break;
        }
        default:
        {
        cout<<"Enter a valid choice ";
       
        }

        
    }
 }
while(a!=4);
return 0;

}