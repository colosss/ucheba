#include <iostream>
#include <stdlib.h>


using namespace std;
struct Node{
    public:
    char data;
    Node *next;
    Node *parent;
    Node (char data){
        this -> data = data;
        this -> next = nullptr;
        this -> parent = nullptr;
    }
};

void AddAtBegin(Node*& head, char data){
    Node* newnd = new Node(data);
    if (head == nullptr){
        head = newnd;
        return;
    }
    newnd->next = head;
    head->parent=newnd;
    head=newnd;
}

void AddAtEnd(Node*& head,char data){
    Node* newnd = new Node(data);

    if (head == nullptr){
        head=newnd;
        return;
    }
    Node* temp = head;
    while (temp->next != nullptr){
        temp=temp->next;
    }
    temp->next = newnd;
    newnd->parent = temp;
}
void AddAtPosition(Node*& head, char data, int position){
    if(position<1){
        cout<<"Ne dopustimoe znachenie position"<<endl;
        return;
    }
    if(position==1){
        AddAtBegin(head, data);
        return;
    }

    Node* newnd = new Node(data);
    Node* temp = head;
    for (int i=1; temp !=nullptr && i<position-1; i++){
        temp=temp->next;
    }
    if (temp==nullptr){
        cout<<"Znachenie position vihodit za predeli kollichestva node"<<endl;
        return;
    }

    newnd->next=temp->next;
    newnd->parent=temp;

    if (temp->next !=nullptr){
        temp->next->parent = newnd;
    }
    temp->next=newnd;
}

void DeleteBegin(Node *& head){
    if (head == nullptr){
        cout<<"List uze pust"<<endl;
        return;
    }
    Node* temp = head;
    head = head->next;
    if (head!=nullptr){
        head->parent = nullptr;
    }
    delete temp;
}

void DeleteEnd(Node*& head){
    if (head == nullptr){
        cout<<"List uze pust"<<endl;
        return;
    }
    Node* temp= head;

    if (temp->next == nullptr){
        head=nullptr;
        delete temp;
        return;
    }

    while (temp->next!=nullptr){
        temp=temp->next;
    }
    temp->parent->next=nullptr;
    delete temp;
}

void DeleteAtPosition(Node*& head, int position){
    if (head == nullptr){
        cout<<"List uze pust"<<endl;
        return;
    }
    if(position<1){
        cout<<"Ne dopustimoe znachenie position"<<endl;
        return;
    }
    if(position==1){
        DeleteBegin(head);
        return;
    }
    Node* temp=head;
    for(int i =0; temp!=nullptr and i<position-1;i++){
        temp=temp->next;
    }
    if (temp==nullptr){
        cout<<"Znachenie position vihodit za predeli kollichestva node"<<endl;
        return;
    }
    if (temp->parent!=nullptr) temp->parent->next=temp->next;
    if(temp->next != nullptr) temp->next->parent = temp->parent;
    delete temp;
}

void PrintList(Node*& head){
    Node* temp=head;
    cout<<"Forward list: ";
    while (temp!=nullptr){
        cout<<temp->data<<" ";
        temp = temp->next;
    }
    cout<<"."<<endl;

}

int main(){
    Node* head = nullptr;
    Node* head1 = nullptr;
    char data;
    int pos=0;

    int count=0;
    bool flag_cikl=true;
    while(flag_cikl){
        // system("clear");
        switch (count)
        {
        case 0:
            cout<<"***************************************************"<<endl;
            cout<<"1-Add, 2-delete, 3-print, 4-Exit"<<endl;
            cin>>count;
            break;
        case 1:
            cout<<"***************************************************"<<endl;
            cout<<"1-AddAtBegin, 2-AddAtEnd, 3-AddAtPosition, 4-Back, 5-Exit"<<endl;
            cin>>count;
            count=count+10;
            break;
        case 2:
            cout<<"***************************************************"<<endl;
            cout<<"1-DeleteAtBegin, 2-DeleteAtEnd, 3-DeleteAtPosition, 4-Back, 5-Exit"<<endl;
            cin>>count;
            if (count==4 or count ==5) count=count+10;
            else count=count+20;
            break;
        case 3:
            cout<<"List 1: "<<endl;
            PrintList(head);
            cout<<"List 2: "<<endl;
            PrintList(head1);
            count=0;
            break;
        case 4:
            flag_cikl=0;
            count=0;
            break;
        case 11:
            cout<<"Vvedite Simvol"<<endl;
            cin>>data;
            AddAtBegin(head, data);
            AddAtBegin(head1, data);
            count=0;
            break;
        case 12:
            cout<<"Vvedite Simvol"<<endl;
            cin>>data;
            if (data!='$'){
                AddAtEnd(head, data);
            }
            else{
                DeleteEnd(head);
                AddAtEnd(head, data);
            }
            AddAtEnd(head1, data);
            count=0;
            break;
        case 13:
            cout<<"Vvedite Simvol"<<endl;
            cin>>data;
            cout<<"Vvedite position"<<endl;
            cin>>pos;
            if (data !='$'){
                AddAtPosition(head, data, pos);
            }
            else{
                AddAtPosition(head, data, pos);
                DeleteAtPosition(head, pos-1);
            }
            AddAtPosition(head1, data, pos);

            count=0;
            break;
        case 14:
            count=0;
            break;
        case 15:
            flag_cikl=false;
            count=0;
            break;
        case 21:
            DeleteBegin(head);
            DeleteBegin(head1);
            count=0;
            break;
        case 22:
            DeleteEnd(head);
            DeleteEnd(head1);
            count=0;
            break;
        case 23:
            cout<<"Vvedite position"<<endl;
            cin>>pos;
            DeleteAtPosition(head, pos);
            DeleteAtPosition(head1, pos);
            count=0;
            break;

        default:
            cout<<"Necorrectniy vvod, povtorite vvod zanovo"<<endl;
            count=0;
            break;
        }
    }
}