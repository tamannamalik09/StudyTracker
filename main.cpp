/* 
Study Tracker V1
Features: 
1. Add Task 
2. View Tasks
3. Save Tasks
4. Delete Tasks
5. Load Tasks
6. Start Timer
7. Stop Timer
8. Exit
*/
#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<chrono> 
using namespace std;
class Task
{
    string name;
    bool completed;
    int studyMinutes;
    chrono::steady_clock::time_point startTime; //creates a variable that can store a moment in time
    bool timerRunning;
    public: 
    Task(){}
    Task(string taskname)
    {
        name = taskname;
        completed = false;
        studyMinutes = 0;
        timerRunning = false;
    }
    string getName()
    {
        return name;
    }
    void markcomplete()
    {
        completed = true;
    }
    bool isCompleted()
    {
        return completed;
    }
    void startTimer()
    {
        startTime = chrono::steady_clock::now();//return current timestamp
        timerRunning = true;
    }
    void stopTimer()
    {
        if(timerRunning)
        {
            auto endTime = chrono::steady_clock::now(); // complier automatically understands endTime is a time_point 
            auto duration = chrono::duration_cast<chrono::minutes>(endTime - startTime);
            studyMinutes += duration.count();
            timerRunning = false;
        }
        else cout<<"No timer is currently running!"<<endl;
    }
    int getStudyTime()
    {
        return studyMinutes;
    }
};
void displayTasks(vector<Task> &tasks)
{
    for(int i = 0; i < tasks.size(); i++)
    {
        cout<< i+1<<". "<<tasks[i].getName();
        if(tasks[i].isCompleted())
        {
            cout<<" [Done]";
        }
        else cout<<" [Pending]";
        cout<<" | "<<tasks[i].getStudyTime()<<" min";
        cout<<endl;
    }
}
void showProgress(vector<Task> &tasks)
{
    if(tasks.size() == 0)
    {
        cout<<"No tasks available!"<<endl;
        return;
    }
    int completedCount = 0;
    for(int i = 0; i<tasks.size(); i++)
    {
        if(tasks[i].isCompleted())
          completedCount++;
    }
    cout<<"============ STATISTICS ============"<<endl;
    cout<<"Total Tasks: "<<tasks.size()<<endl;
    int pending = tasks.size() - completedCount;
    cout<<"Completed Tasks: "<<completedCount<<" / "<<tasks.size()<<endl;
    cout<<"Pending Tasks: "<<pending<<endl;
    double progress = (double)completedCount / tasks.size() * 100;
    cout<<"Progress: "<<progress<<"%"<<endl;
}
int main()
{
    cout<<"============================================"<<endl;
    cout<<"                STUDY TRACKER               "<<endl;
    cout<<"============================================"<<endl<<endl;
    vector<Task> tasks;
    string taskname; 
    int choice = 0;
    bool timerActive = false;
    int currentTask = -1;//represent no task is currently being timed
    while(choice != 10)
    {
        cout<<"\nChoose what you would like to do:"<<endl;
        cout<<"1. Add Task"<<endl;
        cout<<"2. View Tasks"<<endl;
        cout<<"3. Delete Task"<<endl;
        cout<<"4. Save Tasks"<<endl;
        cout<<"5. Load Tasks"<<endl;
        cout<<"6. Mark Task complete"<<endl;
        cout<<"7. Show Progress"<<endl;
        cout<<"8. Start Timer"<<endl;
        cout<<"9. Stop Timer"<<endl;
        cout<<"10. Exit"<<endl<<endl;
        cout<<"Enter choice: ";
        cin>>choice;
        cout<<endl;
        if(cin.fail())//detect when user enters wrong type of input
        {
            cin.clear();//removes the fail data
            cin.ignore(1000, '\n');
            cout<<"Invalid input!"<<endl;
            continue;
        }
        if(choice == 1)
        {
            cin.ignore();
            cout<<"Enter Task: ";
            getline(cin, taskname); // to get the whole line ex: web development
            tasks.push_back(Task(taskname));
            cout<<endl;
            cout<<"Task Added Successfully!"<<endl;
        }
        if(choice == 2)
        {
            if(tasks.size() == 0)
              cout<<"No tasks found!"<<endl;
            else
            {
                cout<<"Tasks List:"<<endl;
                displayTasks(tasks);
            }
        }
        if(choice == 3)
        {
            int del;
            if(tasks.size() == 0)
              cout<<"No tasks found!"<<endl;
            else
            {
                cout<<"Which task would u like to delete:"<<endl;
                displayTasks(tasks);
                cout<<"Enter Task number: ";
                cin>>del;
                if(del<1 || del>tasks.size())
                cout<<"Invalid Task number!"<<endl;
                else
                {
                    tasks.erase(tasks.begin()+(del-1));//coz the vector start from index 0
                    cout<<"Task Deleted Successfully!"<<endl;
                }
            }
        }
        if(choice == 4)
        {
            ofstream file("tasks.txt");
            displayTasks(tasks);
            file.close();
            cout<<"Tasks saved successfully!"<<endl;
        }
        if(choice == 5)
        {
            tasks.clear();// so same task can't be added twice
            ifstream file("tasks.txt");
            string line;
            while(getline(file,line))
            {
                tasks.push_back(Task(line));
            }
            file.close();
            cout<<"Tasks loaded successfully!"<<endl;
        }
        if(choice == 6)
        {
            cout<<"Which task would u like to mark as complete:"<<endl;
            displayTasks(tasks);
            int num;
            cout<<"Enter choice: ";
            cin>>num;
            if(num>=1 && num<=tasks.size())
            {
                tasks[num-1].markcomplete();
                cout<<"Task marked as completed!"<<endl;
            }
            else cout<<"Invalid Task number!"<<endl;
        }
        if(choice == 7)
        {
            showProgress(tasks);
        }
        if(choice == 8)
        {
            if(timerActive)
            {
                cout<<"A timer is already running!"<<endl;
            }
            else
            {
                if(tasks.size() == 0)
                {
                    cout<<"No tasks available! Add a task first."<<endl;
                }
                else
                {
                    int num;
                    displayTasks(tasks);
                    cout<<"Enter task number: ";
                    cin>>num;
                    tasks[num-1].startTimer();
                    timerActive = true;
                    currentTask = num - 1;
                    cout<<"Timer started!"<<endl;
                }
            }
        }
        if(choice == 9)
        {
            if(tasks.size() == 0)
            {
                cout<<"No tasks available!"<<endl;
            }
            else
            {
                if(!timerActive)
                {
                    cout<<"No timer is currently running!"<<endl;
                }
                else
                {
                    tasks[currentTask].stopTimer();
                    cout<<"Timer stopped for "<<tasks[currentTask].getName()<<endl;
                    timerActive = false;
                    currentTask = -1;
                }
            }
        }
    }
    cout<<endl;
    return 0;
}