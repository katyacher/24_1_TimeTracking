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

    Task(std::string name) : name(name), task_time_begin(std::time(nullptr)) {
    }

    void finish(){
        *task_time_finish = std::time(nullptr);
    }

    std::tm* duration(){
        std::time_t t = *task_time_finish - task_time_begin;
        return std::localtime(&t);
    }
    void info(){
        std::cout << "Task name: " << this->name << std::endl;
        if(this->task_time_finish){
            std::cout << "Duration: " << this->duration()->tm_min << ":" <<  this->duration()->tm_sec << std::endl;
        } else {
            std::cout << "In process..." << std::endl;
        }
    }
};


int main() {

    while(true){
        std::cout << "Choose command begin/finish/status/exit: ";
        std::string command;
        std::cin >> command;

        if(command == "exit") {
            std::cout << "Exit";
            return 0;
        }

        std::vector<Task> tasks;

        if(command == "begin"){
            if(!tasks.empty()){
                Task &current = *tasks.end();
                if(!current.task_time_finish) current.finish();
            }
            std::cout << "Enter tne name of your task: ";
            std::string name;
            std::cin >> name;
            Task current_task = Task(name);
            tasks.push_back(current_task);
        }else if(command == "finish") {
            if(!tasks.empty()){
                Task &current = *tasks.end();
                if(!current.task_time_finish) current.finish();
            }
        }else if(command == "status") {
            if(!tasks.empty()) {
                for(auto item: tasks){
                    item.info();
                }
            } else {
                std::cout << "There are no tasks." << std::endl;
            }
        }

    }


}


