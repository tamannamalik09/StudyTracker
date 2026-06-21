/* 
Time TRACKER V1
Features: 
1. Add Task 
2. View Tasks
3. Save Tasks
4. Load Tasks
5. Exit

Future Features:
1. Start Timer
2. Stop Timer
3. Analytics
4. Bar charts
*/
#include<iostream>
#include<vector>
#include<string>
using namespace std;
class Task
{
    string name;
    public: 
    Task(){}
    Task(string taskname)
    {
        name = taskname;
    }
    string getName()
    {
        return name;
    }
};
int main()
{
    cout<<"============= STUDY TRACKER ============="<<endl<<endl;
    vector<Task> tasks;
    string taskname; 
    cout<<"Enter Task: ";
    getline(cin, taskname); // to get the whole line ex: web development
    tasks.push_back(Task(taskname));
    for(int i = 0; i < tasks.size(); i++)
    {
        cout<< tasks[i].getName() << endl;
    }
    cout<<endl;
    return 0;
}