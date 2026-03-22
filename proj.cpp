#include<format>
#include<iostream>
#include<utility>
#include<cstdlib>
#include<vector>


void clearScreen() {
#ifdef _WIN32
    std::system("cls"); // Command for Windows
#else
    // Assumes POSIX-compliant system (Linux, macOS, etc)
    std::system("clear"); // Command for Unix-based systems
#endif
}

class NewTask {
public:
    std::string start_date;
    std::string end_date;
    std::string name;
    NewTask(std::string task_name) : name(std::move(task_name)) {}
};


int main() {
    int choice;
    std::vector<NewTask> tasks;

    while(true) {
        std::cout
        <<"##################################\n"
        <<"WELCOME TO YOUR TO-DO LIST MANAGER\n"
        <<"##################################\n";

        // in case the vector is empty
        if (tasks.empty()) {
            std::string name;
            std::cout<<"Please add a new task to continue!\n";
            std::cout<<"Please enter the task name: \n";
            std::cin>>name;
            NewTask task(name);
            tasks.emplace_back(task);
        }

        // if the vector has contents
        else {
            program_start:
            std::cout
            <<"Please select your choice:\n"
            <<"1. Add a new task\n"
            <<"2. Edit existing tasks\n"
            <<"3. Delete existing tasks\n"
            <<"4. Print all tasks\n"
            <<"5. Exit\n";

            std::cin>> choice;
            switch (choice) {
                case 1:{
                    clearScreen();
                    std::cout<<"Please enter the task name:\n";
                    std::string new_task_name;
                    new_task_name.reserve(50);
                    std::cin>>new_task_name;
                    NewTask new_task(new_task_name);
                    tasks.emplace_back(new_task);
                    std::cout<<"TASK ADDED SUCCESSFULLY!\n";

                    // check if the user wants to add a date (start or end) to the task
                    std::cout<<"Do you want to add a start date? (y/n)\n";
                    char add_date; // holds the user choice whether to edit the date
                    std::cin>>add_date;
                    if (add_date == 'y' || add_date == 'Y') {
                        std::cout<<"Please enter the start date:\n";
                        std::string start_date;
                        start_date.reserve(20);
                        std::cin>>start_date;
                        // assign the start date added by the user to the task obj
                        tasks.at(-1).start_date = start_date;


                        std::cout<<"Please enter the end date:\n";
                        std::string end_date;
                        end_date.reserve(20);
                        std::cin>>end_date;
                        tasks.at(-1).end_date = end_date;
                    }
                    goto program_start;
            }
                case 2: {
                    clearScreen();
                    int index = 0;
                    for(const auto& task : tasks) {
                        index ++; // we will need to decrease by one after the user selects the one to edit
                        std::cout<<index<<"."<<task.name<<std::endl;
                    }
                    std::cout<<"Please enter the task number to edit:\n";
                    int task_to_edit;
                    char editing_choice;
                    std::cin>>task_to_edit;
                    task_to_edit--; // decrement because we added 1 to the indices shown to the user

                    while (task_to_edit < 0 || task_to_edit>=tasks.size()) {
                        std::cout<<"Invalid task number. Please try again!"<<std::endl;

                        std::cout<<"Enter the task number to edit: ";
                        std::cin>>task_to_edit; // let the user enter the task number again
                        task_to_edit--;
                    }
                    std::cout
                    <<"#################################\n"
                    <<"Task name: "<<tasks.at(task_to_edit).name<<std::endl
                    <<"#################################\n";

                    std::cout
                    <<"What do you want to edit?\n"
                    <<"1. Task Name\n"
                    <<"2. Start Date\n"
                    <<"3. End Date\n"
                    <<"4. Exit\n";

                    std::cin>>editing_choice;
                    if (editing_choice == '1') {
                        std::string edited_task_name;
                        edited_task_name.reserve(50);
                        std::cout << "Please enter the new task name: ";
                        std::cin >> edited_task_name;
                        tasks.at(task_to_edit).name = edited_task_name;
                        std::cout << "NAME CHANGED SUCCESSFULLY!\n";

                    } else if (editing_choice == '2') {
                        std::string edited_start_date;
                        edited_start_date.reserve(20);
                        std::cout << "Please enter the new start date: ";
                        std::cin >> edited_start_date;
                        tasks.at(task_to_edit).start_date = edited_start_date;
                        std::cout << "START DATE CHANGED SUCCESSFULLY!\n";

                    } else if (editing_choice=='3') {
                        std::string edited_end_date;
                        edited_end_date.reserve(20);
                        std::cout<<"Please enter the new end date: ";
                        std::cin >> edited_end_date;
                        std::cout << "END DATE CHANGED SUCCESSFULLY!\n";

                    }
                    else if (editing_choice=='4'){ // to exit
                        goto program_start;
                    }
                    goto program_start;
                }

                case 3: {
                    clearScreen();
                    int index = 0;
                    for(const auto& task : tasks) {
                        index ++; // we will need to decrease by one after the user selects the one to edit
                        std::cout<<index<<"."<<task.name<<std::endl;
                    }
                    delete_a_task:
                    std::cout<<"Please enter the task number to delete:\n";
                    int task_to_del;
                    std::cin>>task_to_del;
                    task_to_del--; // decrement because we added 1 to the indices shown to the user

                    while (task_to_del < 0 || task_to_del>=tasks.size()) {
                        std::cout<<"Invalid task number. Please try again!"<<std::endl;

                        std::cout<<"Enter the task number to delete: ";
                        std::cin>>task_to_del; // let the user enter the task number again
                        task_to_del--;
                    }

                    std::cout
                    <<"#################################\n"
                    <<"Task name: "<<tasks.at(task_to_del).name<<std::endl
                    <<"#################################\n";
                    char confirm_choice;
                    std::cout<<"Are you sure you want to delete "<<"\""<<tasks.at(task_to_del).name<<"\""<<"?(y/n)"<<std::endl;
                    std::cin>>confirm_choice;
                    if (confirm_choice == 'y') {
                        tasks.erase(tasks.cbegin()+task_to_del); // we use vector.begin() as erase() needs an iterator parameter
                    }
                    else {
                        goto delete_a_task;
                    }
                goto program_start;
                }
                    case 4: {
                    clearScreen();
                    std::cout
                    <<"TASKS:\n"
                    <<"#################"
                    <<std::endl;
                    if (tasks.empty()) {
                        std::cout<<"NO TASKS TO SHOW\n";
                    }
                    else {
                        for (const auto& task: tasks) {
                            int index=0;
                            index ++;
                            std::cout<<index<<". "<<task.name<<std::endl;
                        }
                    }
                        std::cout<<"#################"<<std::endl;
                        goto program_start;

                }
                default: break ;
            }
                    break;

            }
        }
    return 0;
    }

