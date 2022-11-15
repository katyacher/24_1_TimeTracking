#include <iostream>
#include <ctime>
#include <iomanip>
#include <string>
#include <optional>
#include <vector>

class Task{
public:
    std::string name;
    std::time_t task_time_begin;
    std::optional<std::time_t> task_time_finish;

    Task(std::string& name) : name(name), task_time_begin(std::time(nullptr)) {
    }
    Task(const Task&) = default;

    void finish(){
        task_time_finish = std::time(nullptr);
    }

    std::tm* duration(){
        std::time_t diff = task_time_finish.value()- task_time_begin;
        return std::gmtime(&diff);
    }
    void info(){
        std::cout << "Task name: " << name << std::endl;
        if(task_time_finish){
            std::cout << "Duration: " << duration()->tm_hour << ":" << duration()->tm_min << ":";
            std::cout <<  duration()->tm_sec << std::endl << std::endl;
        } else {
            std::cout << "In process..." << std::endl;
        }
    }
};


int main() {
    std::vector<Task> tasks;

    auto finish_task = [&tasks]() {
        auto it = tasks.end();
        --it;
        Task &current = *it;
        if(!current.task_time_finish) current.finish();
    };

    while(true){
        std::cout << "Choose command begin/end/status/exit: ";
        std::string command;
        std::cin >> command;

        if(command == "exit") {
            std::cout << "Exit";
            return 0;
        }

        if(command == "begin"){
            if(!tasks.empty()){
                finish_task();
            }
            std::cout << "Enter tne name of your task: ";
            std::string name;
            std::cin >> name;
            Task tsk(name);
            tasks.push_back(tsk);

        }else if(command == "end") {
            if(!tasks.empty()){
                finish_task();
            }
        }else if(command == "status") {
            if(!tasks.empty()) {
                for(auto& item: tasks){
                    item.info();
                }
            } else {
                std::cout << "There are no tasks." << std::endl;
            }
        }
    }
}


