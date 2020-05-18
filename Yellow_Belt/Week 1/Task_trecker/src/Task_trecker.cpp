#include <iostream>
#include <map>
#include <utility>
#include <tuple>

using namespace std;

enum class TaskStatus {
	NEW = 0,
	IN_PROGRESS = 1,
	TESTING = 2,
	DONE = 3
};

using TasksInfo = map<TaskStatus, int>;

void PrintTasksInfo(TasksInfo& tasks_info) {
  cout << tasks_info[TaskStatus::NEW] << " new tasks" <<
      ", " << tasks_info[TaskStatus::IN_PROGRESS] << " tasks in progress" <<
      ", " << tasks_info[TaskStatus::TESTING] << " tasks are being tested" <<
      ", " << tasks_info[TaskStatus::DONE] << " tasks are done" << endl;
}

class TeamTasks{
private:
	map<string, TasksInfo> Team;
public:
	 const TasksInfo& GetPersonTasksInfo(const string& person) const
	 {
		 auto result = Team.at(person);
		 PrintTasksInfo(result);
		 return result;
	 }
	 void AddNewTask(const string& person)
	 {
		 Team[person][TaskStatus::NEW]++;
		 PrintTasksInfo(Team[person]);
	 }
	  tuple<TasksInfo, TasksInfo> PerformPersonTasks(
	      const string& person, int task_count){
		  int unperformed = Team[person][TaskStatus::NEW] +
				  Team[person][TaskStatus::IN_PROGRESS] +
				  Team[person][TaskStatus::TESTING];
		  if(task_count > unperformed){
			  task_count = unperformed;
		  }
		  TasksInfo Updated;
		  for(const auto& item: Team[person]){
			  if(task_count != 0)
			  {
				  Updated[item.first] = task_count - item.second;
				  if(Updated[item.first] >= 0){
					  task_count = Updated[item.first];
					  Updated[item.first] = 0;
					  Updated[item.first+1] = item.second;
				  }
				  else{
					  Updated[item.first] *= -1;
					  Updated[item.first+1] = item.second - Updated[item.first];
					  task_count = 0;
				  }
			  }
		  }
		  cout << "Updated tasks:" << endl;
		  PrintTasksInfo(Updated);
		  for(const auto& item: Updated)
		  {
			  Team[person][item.first] -= item.second;
		  }
		  cout << "Not updated tasks:" << endl;
		  PrintTasksInfo(Team[person]);
		  return tie(Updated, Team.at(person));
	  }
};

int main() {
	TeamTasks ti;
	for(int i = 1 ; i <= 5; i++ ){
		ti.AddNewTask("Alice");
	}
	ti.PerformPersonTasks("Alice", 5);
	return 0;
}
