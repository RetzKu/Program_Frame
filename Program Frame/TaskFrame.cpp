#include "TaskFrame.h"


struct TriggerTimer
{
public:
	TriggerTimer(){}
	TriggerTimer(std::string Name, std::chrono::system_clock::time_point Now, bool Triggered) { TaskName = Name; TimeNow = Now; TimeToTrigger = Triggered; }
	std::string TaskName;
	std::chrono::system_clock::time_point TimeNow;
	bool TimeToTrigger;

}TriggerTime;

class Task
{
public:
	Task() {};
	Task(struct TriggerTimer * a) { _TaskData = a; };

	std::function<void(TriggerTimer*)> asds;


private:
	TriggerTimer* _TaskData;
};

TaskFrame::TaskFrame()
{
}


TaskFrame::~TaskFrame()
{
}

void TaskFrame::CreateTask(std::string TaskName, float Duration, bool Triggered)
{
	std::chrono::system_clock::time_point TimeNow = std::chrono::system_clock::now();
	struct TriggerTimer a = TriggerTimer(TaskName, TimeNow, false);
	struct TriggerTimer c(TaskName, TimeNow, false);

	Task B(&c);

	TaskList.push_back(&B);

}




