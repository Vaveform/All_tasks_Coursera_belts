#include "test_runner.h"

#include <iostream>
#include <map>
#include <string>
#include <unordered_map>
#include <vector>



using namespace std;

// Перечислимый тип для статуса задачи
enum class TaskStatus {
  NEW,          // новая
  IN_PROGRESS,  // в разработке
  TESTING,      // на тестировании
  DONE          // завершена
};

// Объявляем тип-синоним для map<TaskStatus, int>,
// позволяющего хранить количество задач каждого статуса
using TasksInfo = map<TaskStatus, int>;

class TeamTasks {
public:
  // Получить статистику по статусам задач конкретного разработчика
  const TasksInfo& GetPersonTasksInfo(const string& person) const{
	  return team_tasks.at(person);
  }

  // Добавить новую задачу (в статусе NEW) для конкретного разработчитка
  void AddNewTask(const string& person){
	  team_tasks[person][TaskStatus::NEW]++;
  }

  // Обновить статусы по данному количеству задач конкретного разработчика,
  // подробности см. ниже
  tuple<TasksInfo, TasksInfo> PerformPersonTasks(
      const string& person, int task_count){
	  TasksInfo& current_tasks = team_tasks[person];
	  TasksInfo approved_tasks;
	  TasksInfo old_tasks;
	  DeleteZeroValuesForPerson(
			  FillApprovedAndOldTasks(person, task_count, approved_tasks, old_tasks),
			  current_tasks);
      RefreshCurrentTasks(approved_tasks, current_tasks);
	  return tie(approved_tasks, old_tasks);

  }
private:
  // Returned value - vector, where in current tasks for person was exceeded 0 for any type
  vector<TasksInfo::iterator> FillApprovedAndOldTasks(const string& person, int task_count,
		  TasksInfo& for_approved_tasks, TasksInfo& for_remained_tasks){
	  TasksInfo& current_tasks = team_tasks[person];
	  vector<TasksInfo::iterator> iterators_to_zero;
	  for(auto it = current_tasks.begin(); it != current_tasks.end(); it++){
		  int next_val = (int)it->first + 1;
		  if(next_val <= 3){
			  while(it->second > 0 && task_count > 0){
				  for_approved_tasks[(TaskStatus)next_val]++;
				  it->second--;
				  if(it->second == 0){
					  iterators_to_zero.push_back(it);
				  }
				  task_count--;
			  }
		  }
		  if(it->second > 0 && (int)it->first < 3){
			  for_remained_tasks[it->first] = it->second;
		  }
	  }
	  return iterators_to_zero;
  }
  void DeleteZeroValuesForPerson(const vector<TasksInfo::iterator>& iterators_to_zero, TasksInfo& current_tasks){
	  for(const auto& it : iterators_to_zero)
		  current_tasks.erase(it);
  }
  void RefreshCurrentTasks(const TasksInfo& approved_tasks, TasksInfo& current_tasks){
	  for(const auto& pair : approved_tasks)
		  current_tasks[pair.first] += pair.second;
  }
  unordered_map<string, TasksInfo> team_tasks;
};

void disp_task_info(const TasksInfo& info){
	for(const auto& element : info){
		cout << (int)element.first << " : " << element.second << endl;
	}
}

void TestSimple(){
	TeamTasks tasks;
	tasks.AddNewTask("Alice");
	tasks.AddNewTask("Alice");
	tasks.AddNewTask("Alice");
	tasks.AddNewTask("Alice");
	tasks.AddNewTask("Alice");
	auto result = tasks.PerformPersonTasks("Alice", 5);
	TasksInfo asked = {{TaskStatus::IN_PROGRESS, 5}};
	Assert(asked == get<0>(result), "Simple test");
	asked = {};
	Assert(asked == get<1>(result), "Empty");
	result = tasks.PerformPersonTasks("Alice", 5);
	asked = {{TaskStatus::TESTING, 5}};
	Assert(asked == get<0>(result), "To testing");
	asked = {};
	Assert(asked == get<1>(result), "Empty");
	result = tasks.PerformPersonTasks("Alice", 1);
	asked = {{TaskStatus::DONE, 1}};
	Assert(asked == get<0>(result), "Approved");
	asked = {{TaskStatus::TESTING, 4}};
	Assert(asked == get<1>(result), "Stay old");
	tasks.AddNewTask("Alice");
	tasks.AddNewTask("Alice");
	tasks.AddNewTask("Alice");
	tasks.AddNewTask("Alice");
	tasks.AddNewTask("Alice");
	result = tasks.PerformPersonTasks("Alice", 2);
	asked = {{TaskStatus::IN_PROGRESS, 2}};
	Assert(asked == get<0>(result), "Two tasks add1");
	asked = {{TaskStatus::NEW, 3}, {TaskStatus::TESTING, 4}};
	disp_task_info(get<1>(result));
	Assert(asked == get<1>(result), "Two tasks add2");
	TasksInfo got = tasks.GetPersonTasksInfo("Alice");
	asked = {{TaskStatus::NEW, 3}, {TaskStatus::IN_PROGRESS, 2}, {TaskStatus::TESTING, 4}, {TaskStatus::DONE, 1}};
	Assert(asked == got, "GetPerson - first");
	result = tasks.PerformPersonTasks("Alice", 4);
	asked = {{TaskStatus::IN_PROGRESS, 3}, {TaskStatus::TESTING, 1}};
	Assert(asked == get<0>(result), "End");
	asked = {{TaskStatus::IN_PROGRESS, 1}, {TaskStatus::TESTING, 4}};
	Assert(asked == get<1>(result), "End after");
	got = tasks.GetPersonTasksInfo("Alice");
	asked = {{TaskStatus::IN_PROGRESS, 4}, {TaskStatus::TESTING, 5}, {TaskStatus::DONE, 1}};
	Assert(asked == got, "GetPerson - second");
}

int main(){
	TestRunner tr;
	tr.RunTest(TestSimple, "Test Simple");
	return 0;
}
