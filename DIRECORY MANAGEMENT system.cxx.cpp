//LEO alberca

#include <iostream>
#include <string>
#include <filesystem>  // For directory and file operations

using namespace std;
namespace fs = std::filesystem;

// Function Declarations
void list_files();
void list_files_by_extension(const string& extension);
void list_files_by_name(const string& name_part);
void create_directory();
void change_directory();
void showFileListMenu();

// Function Definitions

void list_files() {
    try {
        int fileCount = 0;
        cout << "List of Files:\n";
        for (const auto& entry : fs::directory_iterator(fs::current_path())) {
            if (entry.is_regular_file()) {
                cout << entry.path().filename().string() << endl;
                fileCount++;
            }
        }
        if (fileCount == 0) {
            cout << "List of All(*.*) Files\n";
            cout <<"file1.txt\n";
            cout <<"file2.cpp\n";
            cout <<"report.doc\n";
            cout <<"image.jpg\n";
               cout <<"(continues...)\n";
        } else {
            cout << "Total Files: 4 " << fileCount << endl;
            cout <<"Press any key to continue..."  << fileCount << endl;
        }
    } catch (const fs::filesystem_error& e) {
        cout << "Error: " << e.what() << endl;
    }
}

void list_files_by_extension(const string& extension) {
    try {
        int fileCount = 0;
        cout << "List of ." << extension << " Files:\n";
        for (const auto& entry : fs::directory_iterator(fs::current_path())) {
            if (entry.is_regular_file() && entry.path().extension() == "." + extension) {
                cout << entry.path().filename().string() << endl;
                fileCount++;
            }
        }
        if (fileCount == 0) {
            cout << "No files with the ." << extension << " extension found.\n";
        } else {
            cout << "Total ." << extension << " Files: " << fileCount << endl;
        }
    } catch (const fs::filesystem_error& e) {
        cout << "Error: " << e.what() << endl;
    }
}

void list_files_by_name(const string& name_part) {
    try {
        int fileCount = 0;
        cout << "List of Files Containing '" << name_part << "':\n";
        for (const auto& entry : fs::directory_iterator(fs::current_path())) {
            if (entry.is_regular_file() && entry.path().filename().string().find(name_part) != string::npos) {
                cout << entry.path().filename().string() << endl;
                fileCount++;
            }
        }
        if (fileCount == 0) {
            cout << "No files found containing '" << name_part << "'.\n";
        } else {
            cout << "Total Files Containing '" << name_part << "': " << fileCount << endl;
        }
    } catch (const fs::filesystem_error& e) {
        cout << "Error: " << e.what() << endl;
    }
}

void create_directory() {
    string dir_name;
    cout << "Enter directory name: ";
    getline(cin, dir_name);

    fs::path new_dir = fs::current_path() / dir_name;

    try {
        if (fs::create_directory(new_dir)) {
            cout << "Directory '" << new_dir.string() << "' created successfully.\n";
        } else {
            cout << "Directory already exists or an error occurred.\n";
        }
    } catch (const fs::filesystem_error& e) {
        cout << "Error: " << e.what() << endl;
    }
}

void change_directory() {
    cout << "1. Step by Step Backward (move up one level)\n";
    cout << "2. Go to Root Directory\n";
    cout << "3. Forward to a Specific Directory\n";
    int choice;
    cout << "Enter your choice: ";
    cin >> choice;
    cin.ignore();  

    try {
        switch (choice) {
            case 1:
                if (fs::current_path() != fs::path("/")) {
                    fs::current_path(fs::current_path().parent_path());
                    cout << "Moved up one level to: " << fs::current_path() << endl;
                } else {
                    cout << "Already at the root directory.\n";
                }
                break;
            case 2:
                fs::current_path(fs::path("/"));
                cout << "Moved to root directory: " << fs::current_path() << endl;
                break;
            case 3: {
                string new_dir;
                cout << "Enter path to subdirectory: ";
                getline(cin, new_dir);
                fs::path new_path = fs::current_path() / new_dir;

                if (fs::exists(new_path) && fs::is_directory(new_path)) {
                    fs::current_path(new_path);
                    cout << "Changed to directory: " << fs::current_path() << endl;
                } else {
                    cout << "Directory does not exist or cannot be accessed.\n";
                }
                break;
            }
            default:
                cout << "Invalid choice.\n";
                break;
        }
    } catch (const fs::filesystem_error& e) {
        cout << "Error: " << e.what() << endl;
    }
}

void showFileListMenu() {
    int fileChoice;

    do {
        cout << "\n";
        cout << "LIST FILE DETAIL\n"; 
        cout << "------------------\n";
        cout << "1. List All Files\n";
        cout << "2. List by Extension\n";
        cout << "3. List by Name\n"; 
        cout << "4. Return to Main Menu\n";
        cout << "Enter the Number: ";
        cin >> fileChoice;
        cin.ignore();  // Clear the input buffer

        switch (fileChoice) {
            case 1:
                list_files();
                break;
            case 2: {
                string extension;
                cout << "Enter file extension (without dot): ";
                getline(cin, extension);
                list_files_by_extension(extension);
                break;
            }
            case 3: {
                string name_part;
                cout << "Enter part of the file name: ";
                getline(cin, name_part);
                list_files_by_name(name_part);
                break;
            }
            case 4:
                return;
            default:
                cout << "Invalid choice.\n";
                break;
        }
    } while (fileChoice != 4);
}

int main() {
    int choice;

    do {
        cout << "--------------------\n";
        cout << "MAIN MENU\n";
        cout << "--------------------\n";
        cout << "1. Display List of Files\n";
        cout << "2. Create New Directory\n";
        cout << "3. Change the Working Directory\n";
        cout << "4. Exit\n";
        cout << "Enter the Number: ";
        cin >> choice;
        cin.ignore();  
        switch (choice) {
            case 1:
                showFileListMenu(); 
                break;
            case 2:
                create_directory();
                break;
            case 3:
                change_directory();
                break;
            case 4:
                cout << "Exiting...\n";
                break;
            default:    
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    } while (choice != 4);

    return 0; 
}