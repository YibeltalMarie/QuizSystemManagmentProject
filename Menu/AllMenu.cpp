#include "../AdminFile/admin.h"
#include "../StudentFile/StudentCpp/student.h"
#include "AllMenu.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <algorithm>

using namespace std;

void WantBack();
string quizTitle, username;
int modifyingQuestionNumber;
char userchoice = 'y';
string quiz_list = "TextFiles/QuizList/quiz_lists.txt";
string login_user = "TextFiles/Login/current_user.txt";
ifstream file(login_user);

Admin admin;
Student s1;

void clearScreen()
{
#ifdef _WIN32
  system("cls");
#else
  system("clear");
#endif
}

template <typename t>
bool contains(const vector<t> &quizCollector, const t &value)
{
  return find(quizCollector.begin(), quizCollector.end(), value) != quizCollector.end();
}

void userDecision()
{
  int choice;
  cout << "1.Back to AdminMenu\n";
  cout << "2.Back to FirstMenu\n";
  cout << "3.Exit\n";
  cin >> choice;
  clearScreen();
  if (choice == 1)
  {
    Admin_Menu();
  }
  else if (choice == 2)
  {
    mainMenu();
  }
}

void caseForViewQuiz()
{
  admin.loadFromFile(quizCollectors, quiz_list);
  admin.QuizCollector(quizCollectors);
  do
  {
    cout << "Enter the quiz title you want to view: ";
    cin >> quizTitle;
    if (contains(quizCollectors, quizTitle))
    {
      admin.viewQuiz(quizTitle);
    }
    else
    {
      WantBack();
    }
    cout << "Want to another Quiz.(y/n)? ";
    cin >> userchoice;
  } while (userchoice == 'y' || userchoice == 'Y');
}

void WantBack()
{
  clearScreen();
  cout << "No quiz in that name!\n";
  int userchoice;
  cout << "1. Want to select again.\n";
  cout << "2. Go Back.\n";
  cout << "3. Exit.\n";
  cin >> userchoice;
  if (userchoice == 1)
  {
    caseForViewQuiz();
  }
  else if (userchoice == 2)
  {
    userDecision();
  }
  else
  {
    exit(1);
  }
}

void Admin_Menu()
{
  int choice;
  cout << "\n========== Admin Menu ============\n";
  cout << "1. Change Password\n";
  cout << "2. Delete Student Account\n";
  cout << "3. Create Quiz\n";
  cout << "4. Add Question to Quiz\n";
  cout << "5. Modify Question in Quiz\n";
  cout << "6. View All Quizzes\n";
  cout << "7. View Student Scores\n";
  cout << "8. View Student Detail by Username\n";
  cout << "9. View All Students\n";
  cout << "0. Exit\n";
  cout << "=============== Admin Menu ============= " << endl;
  cout << "Enter choice: ";
  cin >> choice;

  clearScreen();
  switch (choice)
  {
  case 1:
    admin.changePassword();
    break;

  case 2:
    admin.deleteStudentAccount();
    break;
  case 3:
    admin.createQuiz();
    admin.saveToFile(quizCollectors, quiz_list);
    clearScreen();
    userDecision();
    break;
  case 4:
    admin.loadFromFile(quizCollectors, quiz_list);
    admin.QuizCollector(quizCollectors);
  label1:
    cout << "Select/write the quiz title from the above lists: ";
    cin >> quizTitle;
    if (contains(quizCollectors, quizTitle))
    {
      admin.addQuestionToQuiz(quizTitle);
      userDecision();
    }
    else
    {
      clearScreen();
      cout << "No quiz in that name!\n";
      int userchoice;
      cout << "1. Want to select again.\n";
      cout << "2. Go Back.\n";
      cout << "3. Exit.\n";
      cin >> userchoice;
      if (userchoice == 1)
      {
        goto label1;
      }
      else if (userchoice == 2)
      {
        userDecision();
      }
    }
    break;
  case 5:
    admin.loadFromFile(quizCollectors, quiz_list);
    admin.QuizCollector(quizCollectors);
    cout << "Enter quiz Title you want to modify: ";
    cin >> quizTitle;
    if (contains(quizCollectors, quizTitle))
    {
      cout << "Enter Question Number: ";
      cin >> modifyingQuestionNumber;
      admin.modifyQuizQuestion(quizTitle, modifyingQuestionNumber);
    }
    else
    {
      cout << "Incorrect Quiz title.";
    }
    break;
  case 6:
    caseForViewQuiz();
    break;
  case 7:
    cout << "Enter Student's userName: ";
    cin >> username;
    s1.viewScore(username);
    break;
  case 8:
    cout << "Enter Student's userName: ";
    cin >> username;
    admin.loadFromFile(quizCollectors, quiz_list);
    admin.QuizCollector(quizCollectors);
    s1.viewQuizDetail(username);
    break;

  case 9:
    admin.viewAllStudents();
    break;

  case 0:
    exit(1);
    break;
  }
}

void studentMenu()
{
  int choice;
  cout << "\n========== Student Menu ==========\n";
  cout << "1. Change Password\n";
  cout << "2. Take Quiz\n";
  cout << "3. View Score\n";
  cout << "4. View Quiz History\n";
  cout << "5. Back\n";
  cout << "==================================\n";
  cout << "Enter your choice: ";
  cin >> choice;
  clearScreen();

  switch (choice)
  {
  case 1:
    s1.changePassword();
    break;
  case 2:
    admin.loadFromFile(quizCollectors, quiz_list);
    admin.QuizCollector(quizCollectors);
    s1.takeQuiz(username);
    break;
  case 3:
    admin.loadFromFile(quizCollectors, quiz_list);
    admin.QuizCollector(quizCollectors);
    s1.viewScore(username);
    break;
  case 4:
    admin.loadFromFile(quizCollectors, quiz_list);
    admin.QuizCollector(quizCollectors);
    s1.viewQuizDetail(username);
    break;
  case 5:
    mainMenu();
    break;
  default:
    cout << "Invalid choice. Try again.\n";
    break;
  }
}

void mainMenu()
{
  int choice;
  cout << " ========== Quiz System =========== " << endl;

  cout << "1.Admin Login.\n";
  cout << "2.Student Registration.\n";
  cout << "3.Stdent Login.\n";
  cout << "4.Log out.\n";

  cout << " ========== Quiz System =========== " << endl;
  cout << "Enter your choice: ";
  cin >> choice;
  clearScreen();

  switch (choice)
  {
  case 1:
    if (admin.login())
    {
      Admin_Menu();
    }
    break;
  case 2:
    s1.registerStudent();
    break;
  case 3:
    if (s1.login())
    {
      studentMenu();
    }
    break;
  case 4:
    cout << "log out sucessfully!!!";
    break;
  default:
    cout << "Invalid input!";
  }
}

int main()
{
  if (file.is_open())
  {
    file >> username;
    file.close();
  }
  mainMenu();

  return 0;
}