
#include "../Validater/Validater.h"
#include "../Menu/AllMenu.h"
#include "admin.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdio> // for remove() and rename()
#include <cctype> // for tolower()
#include <iomanip>
#include <vector>
#include <string>
#include <cstdlib>
#include <algorithm>
using namespace std;

std::vector<std::string> quizCollectors;
int QuestionNumber = 0;

// Constructor
Admin::Admin()
{
    createDefaultAdmin(); // Ensure credentials are set up
}

// Create default admin credentials if file doesn't exist
void Admin::createDefaultAdmin()
{
    // std::ifstream file("your_file.txt");
    // if (file.peek() == std::ifstream::traits_type::eof()) {
    //     std::cout << "File is empty.\n";
    // } else {
    //     std::cout << "File is not empty.\n";
    // }

    ifstream infile(adminFile);
    if (infile.eof())
    {
        ofstream outfile(adminFile);
        outfile << "yibeltal mot94her\n"; // Default admin credentials
        outfile.close();
    }
    infile.close();
}

// Load stored credentials from file
// bool Admin::loadCredentials(string &storedUsername, string &storedPassword)
// {
//     ifstream infile(adminFile);
//     if (infile)
//     {
//         // getline(infile, storedUsername);
//         // getline(infile, storedPassword);
//         infile >> storedUsername >> storedPassword;
//         infile.close();
//         return true;
//     }
//     return false;
// }

bool Admin::loadCredentials(string &storedUsername, string &storedPassword)
{
    ifstream infile(adminFile);
    if (infile)
    {
        string line;
        getline(infile, line);
        stringstream ss(line);
        ss >> storedUsername >> storedPassword;
        infile.close();
        return true;
    }
    return false;
}

// Login function
bool Admin::login()
{
    string inputUsername, inputPassword;
    string storedUsername, storedPassword;

    cout << "\n--- Admin Login ---\n";
    cout << "Username: ";
    cin >> inputUsername;
    if (!isValidUsername(inputUsername))
    {
        cout << "Invalid username. Use only letters and digits, min 4 characters.\n";
        // cout << "Invalid userName or password!";
        return false;
    }
    cout << "Password: ";
    cin >> inputPassword;

    // if (!isValidPassword(password))
    // {
    //     cout << "Invalid userName or password!\n";
    //     cout << "Password must be at least 6 characters and include letters and digits.\n";
    //     return false;
    // }

    if (loadCredentials(storedUsername, storedPassword))
    {
        if ((inputUsername == storedUsername) && (inputPassword == storedPassword))
        {
            cout << "Login successful!\n";
            return true;
        }
        else
        {
            cout << "Invalid username or password.\n";
        }
    }
    else
    {
        cout << "Error reading admin credentials.\n";
    }

    return false;
}

// for changing the password of admin
bool Admin::changePassword()
{
    string storedUsername, storedPassword;
    string inputUsername, inputPassword;
    string newPassword, confirmPassword;

    string FolderPath = "AdminFile/";
    string OriginalFile = adminFile;
    string TempFile = FolderPath + "temp.txt";

    ifstream infile(OriginalFile);
    ofstream outfile(TempFile);
    cout << "\n--- Change Admin Password ----\n";

    // Load existing credentials
    if (!loadCredentials(storedUsername, storedPassword))
    {
        cout << "Failed to load credentials.\n";
        return false;
    }

    // Verify current credentials
    cout << "Enter current username: ";
    cin >> inputUsername;
    if (!isValidUsername(inputUsername))
    {
        cout << "Invalid username. Use only letters and digits, min 4 characters.\n";
        return false;
    }
    cout << "Enter current password: ";
    cin >> inputPassword;

    if (!(isValidPassword(password) && isValidUsername(inputUsername)))
    {
        cout << "Invalid username or password.\n";
        cout << "Password must be at least 6 characters and include letters and digits.\n";
        cout << "Invalid username. Use only letters and digits, min 4 characters.\n";
        return false;
    }

    if (inputUsername != storedUsername || inputPassword != storedPassword)
    {
        cout << "Incorrect username or password.\n";
        return false;
    }

    // Prompt for new password
    cout << "Enter new password: ";
    cin >> newPassword;
    // if (!isValidPassword(password))
    // {
    //     cout << "Invalid password!\n";
    //     cout << "Password must be at least 6 characters and include letters and digits.\n";
    //     return false;
    // }

    cout << "Confirm new password: ";
    cin >> confirmPassword;

    if (newPassword != confirmPassword)
    {
        cout << "Passwords do not match.\n";
        return false;
    }

    // Save new credentials
    // ofstream outfile(adminFile);
    if (outfile)
    {
        outfile << storedUsername << " " << newPassword << "\n";
        outfile.close();
        infile.close();
        remove(OriginalFile.c_str()); // Delete old file
        rename(TempFile.c_str(), OriginalFile.c_str());
        cout << "Password changed successfully.\n";
        return true;
    }
    else
    {
        cout << "Error writing to admin file.\n";
        return false;
    }
}

// to see all registered students
bool Admin::viewAllStudents()
{
    string FolderPath = "StudentFile/StudentCpp/students.txt";

    ifstream infile(FolderPath);

    if (!infile)
    {
        cout << "Could not open student records.\n";
        return false;
    }

    string username, email, password;
    int count = 0;

    cout << "\n--- Registered Students ---\n";
    cout << left << setw(10) << "Username" << setw(10) << "Email" << setw(30) << "password";
    cout << "\n-------------------------------------------------------------\n";

    while (infile >> username >> email >> password)
    {
        cout << left << setw(10) << username << setw(10) << email << setw(30) << password << "\n";
        count++;
    }

    if (count == 0)
    {
        cout << "No students registered yet.\n";
    }

    infile.close();
    return true;
}

// To delete a student by userName
bool Admin::deleteStudentAccount()
{
    string targetUsername;
    cout << "Enter the username of the student to delete: ";
    cin >> targetUsername;

    string FolderPath = "StudentFile/StudentCpp/";
    string originalFile = FolderPath + "students.txt";
    string newFile = FolderPath + "temp.txt";
    ifstream infile(originalFile);
    ofstream tempFile(newFile);
    bool found = false;

    if (!infile || !tempFile)
    {
        cout << "Error opening files.\n";
        return false;
    }

    string username, email, password;
    while (infile >> username >> email >> password)
    {
        if (username == targetUsername)
        {
            char confirm;
            cout << "Are you sure you want to delete " << username << "? (y/n): ";
            cin >> confirm;
            if (confirm == 'y' || confirm == 'Y')
            {
                found = true;
                continue; // skip writing this line
            }
            else
            {
                tempFile << username << " " << email << " " << password << "\n"; // Keep it
            }
        }
        else
        {
            tempFile << username << " " << email << " " << password << "\n"; // Keep others
        }
    }

    infile.close();
    tempFile.close();

    if (found)
    {
        remove(originalFile.c_str());
        rename(newFile.c_str(), originalFile.c_str());
        cout << "Deleted successfully.\n";
    }
    else
    {
        remove(newFile.c_str());
        cout << "Student username not found or deletion canceled.\n";
    }

    return found;
}

// to get the last question number
int Admin::getLastQuestionNumber(const std::string &quizTitle, const std::string &filename)
{
    std::ifstream file(filename);
    std::string line;
    while (getline(file, line))
    {
        size_t pos = line.find(':');
        if (pos != std::string::npos && line.substr(0, pos) == quizTitle)
        {
            return std::stoi(line.substr(pos + 1));
        }
    }
    return 1; // Start from 1 if quiz not found
}

// Save the Vector to a file
void Admin::saveToFile(const std::vector<std::string> &data, const std::string &filename)
{
    std::ofstream outFile(filename, ios::app);
    for (const auto &item : data)
    {
        outFile << item << "\n";
    }
}

// Load vector data from a file
void Admin::loadFromFile(std::vector<std::string> &data, const std::string &filename)
{
    std::ifstream inFile(filename);
    std::string line;
    while (std::getline(inFile, line))
    {
        if (!line.empty())
        {
            data.push_back(line);
        }
    }
}
void Admin::QuizCollector(std::vector<string> &quizCollector)
{
    cout << "==== All Quizes =====\n";
    int count = 1;
    for (const auto &quiz : quizCollector)
    {
        cout << count << ". " << quiz << endl;
        count++;
    }
}
void Admin::createQuiz()
{
    string quizTitle;
    cout << "Enter quiz title: ";
    cin.ignore();
    getline(cin, quizTitle);
    quizCollectors.push_back(quizTitle);
    string filename = "TextFiles/Questions/quiz_" + quizTitle + ".txt";
    ofstream quizFile(filename);
    if (!quizFile.is_open())
    {
        cout << "Error: Could not create quiz file.\n";
        return;
    }
    quizFile.close();

    cout << "Quiz \"" << quizTitle << "\" created successfully.\n";

    //     // Prompt to add questions now
    char addNow;
    cout << "Do you want to add questions now? (y/n): ";
    cin >> addNow;
    if (addNow == 'y' || addNow == 'Y')
    {
        addQuestionToQuiz(quizTitle);
    }
}

void Admin::addQuestionToQuiz(const std::string &quizTitle)
{
    vector<Question> questions;
    string filename = "TextFiles/Quesitons/quiz_" + quizTitle + ".txt";

    // Input questions and answers
    int numQuestions;
    cout << "How many questions do you want to add? ";
    cin >> numQuestions;
    cin.ignore();

    for (int i = 0; i < numQuestions; ++i)
    {
        Question newQuestion;
        cout << "\nEnter Question #" << (i + 1) << ": ";
        getline(cin, newQuestion.questionText);
        cout << "Option A: ";
        getline(cin, newQuestion.optionA);
        cout << "Option B: ";
        getline(cin, newQuestion.optionB);
        cout << "Option C: ";
        getline(cin, newQuestion.optionC);
        cout << "Option D: ";
        getline(cin, newQuestion.optionD);
        cout << "Correct Option (A/B/C/D): ";
        cin >> newQuestion.correctOption;
        cin.ignore();
        // Add the question to the vector
        questions.push_back(newQuestion);
    }

    // Save the questions to the quiz file
    saveQuizQuestionsToFile(quizTitle, questions);
}

void Admin::updateQuestionNumber(const std::string &quizTitle, int newNumber, const std::string &filename)
{
    std::ifstream file(filename);
    std::vector<std::string> lines;
    std::string line;
    bool updated = false;

    while (getline(file, line))
    {
        size_t pos = line.find(':');
        if (pos != std::string::npos && line.substr(0, pos) == quizTitle)
        {
            lines.push_back(quizTitle + ":" + std::to_string(newNumber));
            updated = true;
        }
        else
        {
            lines.push_back(line);
        }
    }
    file.close();

    if (!updated)
    {
        lines.push_back(quizTitle + ":" + std::to_string(newNumber));
    }

    std::ofstream outFile(filename, std::ios::trunc);
    for (const auto &entry : lines)
    {
        outFile << entry << '\n';
    }
}

template <typename T>
void Admin::saveQuizQuestionsToFile(const std::string &quizTitle, const std::vector<T> &questions)
{
    std::ofstream quizFile("TextFiles/Questions/quiz_" + quizTitle + ".txt", std::ios::app);
    std::string counterFile = "TextFiles/QuestionNumber/LastQuestionNum.txt";

    if (!quizFile.is_open())
    {
        std::cout << "Error: Could not open quiz file.\n";
        return;
    }

    int QueNum = getLastQuestionNumber(quizTitle, counterFile);

    for (const auto &q : questions)
    {
        quizFile << QueNum << ". " << q.questionText << '\n';
        quizFile << "A. " << q.optionA << '\n';
        quizFile << "B. " << q.optionB << '\n';
        quizFile << "C. " << q.optionC << '\n';
        quizFile << "D. " << q.optionD << '\n';
        quizFile << "Answer: " << q.correctOption << '\n';
        quizFile << "---" << '\n';
        QueNum++;
    }

    updateQuestionNumber(quizTitle, QueNum, counterFile);
    quizFile.close();

    std::cout << questions.size() << " question(s) added to \"" << quizTitle << "\".\n";
}

void Admin::viewQuiz(std::string &quizTitle)
{
    string fileName = "TextFiles/Questions/quiz_" + quizTitle + ".txt";

    ifstream Quiz(fileName);
    if (!Quiz)
    {
        cout << "The file couldn't open!!!\n";
        return;
    }
    string line;
    int questionNumber = 1;
    bool questionStarted = false;

    cout << "===== " << quizTitle << " Questions =====\n";
    while (getline(Quiz, line))
    {
        if (line.empty())
        {
            questionStarted = false; // reset between questions
            continue;
        }
        if (line.find("Answer:") == 0)
        {
            // Hide the answer line
            continue;
        }

        if (!questionStarted)
        {
            std::cout << questionNumber++ << ". " << line << "\n";
            questionStarted = true;
        }
        else
        {
            std::cout << line << "\n";
        }
    }
    Quiz.close();
}

void Admin::modifyQuizQuestion(const std::string &QuizTitle, int questionNumber)
{
    std::string originalPath = "TextFiles/Questions/quiz_" + QuizTitle + ".txt";
    std::string tempPath = "TextFiles/Questions/temp.txt";
    std::ifstream originalFile(originalPath);
    std::ofstream tempFile(tempPath);

    if (!originalFile.is_open())
    {
        std::cout << "Error! Couldn't open quiz file." << std::endl;
        return;
    }

    int currentQuestionNumber;
    std::string line;
    Question modifyingQuestion;
    bool questionModified = false;

    while (getline(originalFile, line))
    {
        if (line.find(".") != std::string::npos)
        {
            std::string check = line.substr(0, line.find("."));
            if (!check.empty() && std::all_of(check.begin(), check.end(), ::isdigit))
            {
                currentQuestionNumber = std::stoi(check);
                if (currentQuestionNumber == questionNumber)
                {
                    std::cout << "Modifying question #" << questionNumber << ":\n";

                    std::cin.ignore(); // clear leftover newline from previous cin

                    std::cout << "Enter new question text: ";
                    std::getline(std::cin, modifyingQuestion.questionText);
                    tempFile << questionNumber << ". " << modifyingQuestion.questionText << std::endl;

                    std::cout << "Option A: ";
                    std::getline(std::cin, modifyingQuestion.optionA);
                    tempFile << "A. " << modifyingQuestion.optionA << std::endl;

                    std::cout << "Option B: ";
                    std::getline(std::cin, modifyingQuestion.optionB);
                    tempFile << "B. " << modifyingQuestion.optionB << std::endl;

                    std::cout << "Option C: ";
                    std::getline(std::cin, modifyingQuestion.optionC);
                    tempFile << "C. " << modifyingQuestion.optionC << std::endl;

                    std::cout << "Option D: ";
                    std::getline(std::cin, modifyingQuestion.optionD);
                    tempFile << "D. " << modifyingQuestion.optionD << std::endl;

                    std::cout << "Correct Option (A/B/C/D): ";
                    std::getline(std::cin, modifyingQuestion.correctOption);
                    tempFile << "Answer: " << modifyingQuestion.correctOption << std::endl;

                    tempFile << "---" << std::endl;

                    // Skip the next 6 lines (old options, answer, ---)
                    for (int i = 0; i < 6 && getline(originalFile, line); ++i)
                        ;

                    questionModified = true;
                    continue; // Skip to next iteration
                }
            }
        }

        // For all lines that aren't modified questions
        tempFile << line << std::endl;
    }

    originalFile.close();
    tempFile.close();

    if (!questionModified)
    {
        std::cout << "Question was not modified. Check quiz title or question number." << std::endl;
        return;
    }

    remove(originalPath.c_str());
    rename(tempPath.c_str(), originalPath.c_str());

    std::cout << "Question #" << questionNumber << " in \"" << QuizTitle << "\" quiz modified successfully." << std::endl;
}
