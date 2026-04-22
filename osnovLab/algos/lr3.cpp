#include <iostream>
using namespace std;


struct Task
{
    int durationTime;
    int taskTime;
    int preority;
    string name;

    Task(int durationTime, int taskTime, int preority, string name){
        this->durationTime=durationTime;
        this->taskTime=taskTime;
        this->preority=preority;
        this->name=name;
    }
    Task(){
        durationTime=0;
        taskTime=0;
        preority=0;
        name="";
    }
};

struct TaskList
{
    Task *taskValues;
    TaskList* next;
    TaskList* parent;

};

void Add_to_begin(TaskList*& head, int durationTime, int taskTime, int preority, string name){
    TaskList* newts = new TaskList();
    newts->taskValues = new Task(durationTime, taskTime, preority, name);
    if (head == nullptr){
        head = newts;
        return;
    }
    newts->next = head;
    head->parent=newts;
    head=newts;
}
void Add_to_end(TaskList*& head,int durationTime, int taskTime, int preority, string name){
    TaskList* newts = new TaskList();
    newts->taskValues = new Task(durationTime, taskTime, preority, name);


    if (head == nullptr){
        head=newts;
        return;
    }
    TaskList* temp = head;
    while (temp->next != nullptr){
        temp=temp->next;
    }
    temp->next = newts;
    newts->parent = temp;
}
void DeleteEnd(TaskList*& head){
    if (head == nullptr){
        cout<<"List uze pust"<<endl;
        return;
    }
    TaskList* temp= head;

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

void DeleteBegin(TaskList *& head){
    if (head == nullptr){
        cout<<"List uze pust"<<endl;
        return;
    }
    TaskList* temp = head;
    head = head->next;
    if (head!=nullptr){
        head->parent = nullptr;
    }
    delete temp;
}
void DeleteTask(Task *& head){
    if (head == nullptr){
        cout<<"List uze pust"<<endl;
        return;
    }
    delete head;
}

bool Empity_test(TaskList*& head){
    if (head == nullptr)return true;
    else return false;
}

void PrintList(TaskList*& head, string name_list){
    TaskList* temp=head;
    cout<<name_list<<endl;
    while (temp!=nullptr){
        cout<<"durationTime: "<<temp->taskValues->durationTime<<" TaskTime: "<<temp->taskValues->taskTime<<" Priorety: "<<temp->taskValues->preority<<" Name: "<<temp->taskValues->name<<endl;
        temp = temp->next;
    }
}

void PrintTask(Task*& head, string name_list){
    Task* temp=head;
    cout<<name_list<<endl;
    cout<<"durationTime: "<<temp->durationTime<<" TaskTime: "<<temp->taskTime<<" Priorety: "<<temp->preority<<" Name: "<<temp->name<<endl;
    
}

void processorLoop(){
    TaskList *Stack0= nullptr;
    TaskList *Stack1= nullptr;
    TaskList *Queue= nullptr; 
    Task *Proccesor;
    bool QueueEmpty=true;
    bool Stack0Empty=true;
    bool Stack1Empty=true;
    bool ProccesorEmpty=true;
    bool allTaskGone = false;

    Task allTask[5];
    allTask[0] = {1, 4, 0, "Task 1"};
    allTask[1] = {2, 2, 1, "Task 2"};
    allTask[2] = {3, 1, 0, "Task 3"};
    allTask[3] = {4, 3, 1, "Task 4"};
    allTask[4] = {5, 2, 0, "Task 5"};

    //Заполняю очередь начальными задачами
    for(int i=0; i<5; i++){
        Add_to_end(Queue, allTask[i].durationTime, allTask[i].taskTime, allTask[i].preority, allTask[i].name);
        QueueEmpty=false;
    }
    while (true){
        if (!ProccesorEmpty){
            if(Proccesor->taskTime>0){
                Proccesor->taskTime--;
            }
            else{
                DeleteTask(Proccesor);
                ProccesorEmpty=true;
            }
        }
        if (!QueueEmpty){
            if(Queue->taskValues->preority==0){
                Add_to_begin(Stack0, Queue->taskValues->durationTime, Queue->taskValues->taskTime, Queue->taskValues->preority, Queue->taskValues->name);
                DeleteBegin(Queue);
                Stack0Empty=false;
            }
            else{
                Add_to_begin(Stack1, Queue->taskValues->durationTime, Queue->taskValues->taskTime, Queue->taskValues->preority, Queue->taskValues->name);
                DeleteBegin(Queue);
                Stack1Empty=false;
            }
            if (Empity_test(Queue))QueueEmpty=true;
        }
        if (!Stack0Empty){
            if(ProccesorEmpty){
                Proccesor=Stack0->taskValues;
                DeleteBegin(Stack0);

                ProccesorEmpty=false;
            }
            if (Empity_test(Stack0)) Stack0Empty=true;
            
        }
        else if (!Stack1Empty){
            if(ProccesorEmpty){
                Proccesor=Stack1->taskValues;
                DeleteBegin(Stack1);

                ProccesorEmpty=false;
            }
            if (Empity_test(Stack1))Stack1Empty=true;
        }
        if (Stack0Empty && Stack1Empty && QueueEmpty && ProccesorEmpty){
            allTaskGone=true;
            break;
        }
        cout<<"Tackt: "<<time<<endl;
        PrintList(Queue, "Queue: ");
        PrintList(Stack0, "\nStack0: ");
        PrintList(Stack1, "\nStack1: ");
        PrintTask(Proccesor, "\nProccessor");
        cout<<"**************************************************"<<endl;

    }
    
    cout<<endl<<"End"<<endl;
    


}

int main() {
    cout<<"Processor Task Scheduler Simulation\n"<<endl;
    processorLoop();
    return 0;

}