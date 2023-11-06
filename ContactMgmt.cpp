#include<iostream>
#include<conio.h>
#include<fstream>

using namespace std;

class Contact{
private: //global variables 
        char fName[50], lName[50], address[50], email[50];
        long long phoneNumber;

public:

        void createContact(){ //taking input from user for details 
            cout<<"Enter your first name: ";
            cin>>fName;
            cout<<"Enter your last name: ";
            cin>>lName;
            cout<<"Enter phone: ";
            cin>>phoneNumber;
            cout<<"Enter address: ";
            cin>>address;
            cout<<"Enter email: ";
            cin>>email;	 
        }

        void showContact(){ //displaying details of a particular contact 
            cout<<"Name: "<<fName<<" "<<lName<<endl;
            cout<<"Phone: "<<phoneNumber<<endl;
            cout<<"Address: "<<address<<endl;
            cout<<"Email: "<<email<<endl;	
        }

        void writeFile(){ //using fstream module to write data in file 
            char ch;
            ofstream f1;
            f1.open("CMS.dat", ios::binary | ios::app);

            do{
                createContact();
                f1.write(reinterpret_cast<char*>(this), sizeof(*this)); //using in-built functions 
                cout<<"Do you have any next data?(y/n)";
                cin>>ch;
            } while(ch == 'y');

            cout<<"Contact has been Successfully Created....";
            f1.close();
        }

        void readFile(){ //reading details from the file 
            ifstream f2;
            f2.open("CMS.dat", ios::binary);

            cout<<"\n================================\n";
		    cout<<"LIST OF CONTACTS";
		    cout<<"\n================================\n";

            while(!f2.eof()){ //eof -> end of the file user wants to read 
                if(f2.read(reinterpret_cast<char*>(this), sizeof(*this))){
                    showContact(); //displaying all contact details of all the persons from the file
                    cout<<"\n================================\n";
                }
            }
            f2.close();
        }

        void searchFile(){
            ifstream f3;
            long long phone; //searching any person through its phone number 

            cout<<"Enter phone no: "; //taking input 
            cin>>phone;
            f3.open("CMS.dat", ios::binary);

            while(!f3.eof()){ //eof -> end of the file user wants to read 
                if(f3.read(reinterpret_cast<char*>(this), sizeof(*this))){
                    if(phone == phoneNumber){ 
                        showContact(); //displaying contact detail of searched person 
                        return; 
                    }
                }
            }
            cout<<"\n\n No record not found";
            f3.close();
        }

        void deleteFile(){
            long long num;
            int flag = 0; //check whether contact is deleted or not 
            ofstream f4; // using both output & input stream to read and write a contact from the contacts 
            ifstream f5;

            f5.open("CMS.dat", ios::binary); //original file 
            f4.open("temp.dat", ios::binary); //temporary file for deleting any contact  

            cout<<"Enter phone no. to delete: ";
            cin>>num;

            while(!f5.eof()){ //eof -> end of the file user wants to read  
                if(f5.read(reinterpret_cast<char*>(this), sizeof(*this))){
                    if(phoneNumber != num){ // if phone number user wants to delete and entered one doesn't match then perform write operation in temporary file
                        f4.write(reinterpret_cast<char*>(this),sizeof(*this));
                    } else {
                        flag = 1;
                    }
                }
            }
            f5.close();
            f4.close();

            remove("CMS.dat"); //removing the original file 
            rename("temp.dat", "CMS.dat"); //get deleted & updated temporary file and rename it 

            flag == 1 ? 
            cout<<endl<<endl<<"\tContact Deleted...":
		    cout<<endl<<endl<<"\tContact Not Found...";
        }

        void editContact(){
            long long phone;
            fstream f6;

            cout<<"Edit contact";
            cout<<"\n===============================\n\n";
            cout<<"Enter the phone number to be edit: ";
            cin>>phone;

            f6.open("CMS.dat", ios::binary | ios::out | ios::in); //set both output stream & input stream as mode 

            while(!f6.eof()){ //eof -> end of the file user wants to read 
                if(f6.read(reinterpret_cast<char*>(this), sizeof(*this)));  //read the contact that user wants to edit 
                if(phoneNumber == phone){ //both phone number matches then call createContact to edit & get its last position to update the contact 
                    cout<<"Enter new record\n";
                    createContact();
                    int pos = -1 * sizeof(*this);
                    f6.seekp(pos, ios::cur);  //set current position 
                    f6.write(reinterpret_cast<char*>(this),sizeof(*this));  //write updated details and return 
                    cout<<endl<<endl<<"\t Contact Successfully Updated...";
                    return;
                }
            }
            cout <<"\n\n No record found";
            f6.close(); 
        }
};

int main () {
    system("cls");
	system("Color 4F"); // "Color XY", X - backgroung color, Y - text color

	cout<<"\n\n\n\n\n\n\n\n\t\t\t * WELCOME TO CONTACT MANAGEMENT SYSTEM *";
	getch();

	while(1) {
		Contact c1;
		int choice;

		system("cls");
		system("Color 03");

		cout<<"\nCONTACT MANAGEMENT SYSTEM";  //menu for contact management system 
        cout<<"\n\nMAIN MENU";
		cout<<"\n=====================\n";
        cout<<"[1] Add a new Contact\n";
        cout<<"[2] List all Contacts\n";
        cout<<"[3] Search for contact\n";
        cout<<"[4] Delete a Contact\n";
        cout<<"[5] Edit a Contact\n";
        cout<<"[0] Exit";
		cout<<"\n=====================\n";
        cout<<"Enter your choice: ";
        cin>>choice;

        switch (choice) {  //append all the methods to respective choices 
            case 1: 
                  c1.writeFile();
                  break;

            case 2:
                  c1.readFile();
                  break;

            case 3:
                  c1.searchFile();
                  break;

            case 4:
                 c1.deleteFile();
                 break;

            case 5:
                 c1.editContact();
                 break;    

            case 0:
                 cout<<"\n\n\n\t\t\tThank you for using CMS."<<endl<<endl;
                 exit(0);                         
                 break;

            default: 
                    continue;     
        }
        //if user wants to perform other actions then, 
        int opt;
        cout<<"\n\n..::Enter the Choice:\n[1] Main Menu\t\t[0] Exit\n";
		cin>>opt;

        switch(opt) {
            case 0:
                 cout<<"\n\n\n\t\t\tThank you for using CMS."<<endl<<endl;
                 exit(0);                         
                 break;

             default:
                    continue;    
        }

    }    

    return 0;
}