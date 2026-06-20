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
    Task t("DSA");
    cout<< t.getName();
    return 0;
}