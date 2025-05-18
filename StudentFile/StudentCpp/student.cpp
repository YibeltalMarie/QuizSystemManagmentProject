#include "student.h"
#include "../../Menu/AllMenu.h"
#include <iostream>
#include <fstream>
#include "../../Validater/Validater.h"
#include <string>
#include <vector>
using namespace std;

void Student::registerStudent()
{
  string student, student_password, email;
  string FolderPath = "StudentFile/StudentCpp/";
  string originalFile = Folder;
  string tempFile = FolderPath + "temp.txt";

  bool is_true = false;
  do
  {
    is_true = false;
    cout << "Enter username: ";
    cin >> username;
    ifstream file(originalFile);
    while (file >> student >> email >> student_password)
    {
      if (student == username)
      {
        cout << "Username already exists. Try again!" << endl;
        is_true = true;
      }
    }
    if (!isValidUsername(username))
    {
      cout << "Invalid username. Try again.\n";
      cout << "username must be at least 4.\n";
      is_true = true;
    }
  } while (is_true);

  do
  {
    cout << "Enter password: ";
    cin >> password;
    if (!isValidPassword(password))
    {
      cout << "Invalid password. Try again.\n";
      cout << "Password must be at least 6 characters and include letters and digits.\n";
    }
  } while (!isValidPassword(password));

  do
  {
    is_true = false;
    cout << "Enter email: ";
    cin >> email;
    if (!isValidEmail(email))
    {
      cout << "Invalid email format. Try again.\n";
      is_true = true;
    }
  } while (is_true);

  // Step 1: Check if file ends with a newline
  ifstream inFile(originalFile, ios::binary);
  bool addNewline = false;

  if (inFile)
  {
    inFile.seekg(0, ios::end);
    if (inFile.tellg() > 0)
    {
      inFile.seekg(-1, ios::end);
      char lastChar;
      inFile.get(lastChar);
      if (lastChar != '\n')
      {
        addNewline = true;
      }
    }
  }
  inFile.close();

  // Step 2: Append student to file
  ofstream outFile(originalFile, ios::app);
  if (!outFile)
  {
    cout << "Error opening file for writing.\n";
    return;
  }

  if (addNewline)
  {
    outFile << '\n'; // Add newline only if needed
  }

  outFile << username << " " << email << " " << password << '\n';
  outFile.close();

  cout << "Registration successful!\n";
}

bool Student::login()
{
  std::string RegisteredStudentsPath = "StudentFile/StudentCpp/students.txt";
  std::string student, student_password;
  string login_user_path = "TextFiles/Login/current_user.txt";
  ifstream infile;
  infile.open(Folder, ios::in); // file with registered students
  cout << "Enter userName: ";
  cin >> username;

  if (!isValidUsername(username))
  {
    cout << "Invalid username. Use only letters and digits, min 4 characters.\n";
    return false;
  }
  cout << "Enter password: ";
  cin >> password;
  if (!(isValidPassword(password) && isValidUsername(username)))
  {
    cout << "Invalid username or password.\n";
    cout << "Password must be at least 6 characters and include letters and digits.\n";
    cout << "Invalid username. Use only letters and digits, min 4 characters.\n";
    return false;
  }

  if (!infile)
  {
    cout << "Error: Could not open students file.\n";
    return false;
  }

  string fileUsername, fileEmail, filePassword;
  while (infile >> fileUsername >> fileEmail >> filePassword)
  {
    if (username == fileUsername && password == filePassword)
    {
      cout << "Login successful. Welcome, " << username << "!\n";
      ofstream file1;
      file1.open(login_user_path);
      file1 << username << " " << password;
      file1.close();
      // inputCredentials(username);
      return true;
    }
  }
  cout << "Login failed: Invalid username or password.\n";
  return false;
}

bool Student::changePassword()
{
  string cur_password, newPassword, userName;

  ifstream file2;
  file2.open("TextFiles/Login/current_user.txt");
  file2 >> userName >> password;
  file2.close();

label190:
  cout << "Enter the current password: ";
  cin >> cur_password;
  if (cur_password == password)
  {
    cout << "Enter new password: ";
    cin >> newPassword;
  }
  else
  {
    cout << "Incorrect password!!! " << endl;
    goto label190;
  }

  // string FolderPath = "StudentFile/StudentCpp/";
  ifstream infile(Folder);
  // string tempFile = FolderPath + "temp.txt";
  ofstream temp(Folder2);
  bool updated = false;

  if (!infile || !temp)
  {
    cout << "File opening error.\n ";
    return false;
  }

  string fileUsername, fileEmail, filePassword;

  while (infile >> fileUsername >> fileEmail >> filePassword)
  {
    if (fileUsername == userName)
    {
      temp << fileUsername << " " << fileEmail << " " << newPassword << endl;
      updated = true;
    }
    else
    {
      temp << fileUsername << " " << fileEmail << " " << filePassword << endl;
    }
  }

  infile.close();
  temp.close();

  if (updated)
  {
    int choice;
    remove(Folder.c_str());
    rename(Folder2.c_str(), Folder.c_str());
    password = newPassword; // Update current object too
    cout << "Password changed successfully.\n";
    cout << "1.Back" << endl;
    cout << "2.Exit" << endl;
    cout << "Enter Your choice: ";
    cin >> choice;
    if (choice == 1)
    {
      studentMenu();
    }
    else
    {
      cout << "Exit..... " << endl;
    }

    return true;
  }
  else
  {
    cout << "Student not found.\n";
    remove(Folder2.c_str());
    return false;
  }
}

void Student::saveQuizDetail(
    const std::string &username,
    const std::string &quizTitle,
    int score,
    int total,
    const std::vector<QuizQuestion> &questions)
{
  std::string filePath = "TextFiles/QuizHistory/" + username + "_" + quizTitle + ".txt";
  std::ofstream file(filePath, ios::out);

  if (!file.is_open())
  {
    std::cout << "Could not save quiz detail.\n";
    return;
  }

  file << quizTitle << ": " << score << "/" << total << "\n\n";

  for (size_t i = 0; i < (questions.size()); ++i)
  {
    file << questions[i].questionText << "\n";
    file << questions[i].choiceA << "\n";
    file << questions[i].choiceB << "\n";
    file << questions[i].choiceC << "\n";
    file << questions[i].choiceD << "\n";
    file << "Your Answer: " << questions[i].userAnswer << "\n";
    file << "Correct Answer: " << questions[i].correctAnswer << "\n";
    file << (questions[i].userAnswer == questions[i].correctAnswer ? "Correct" : "Wrong") << "\n\n";
  }

  file.close();
}

void Student::takeQuiz(const std::string &username)
{
  std::cout << "============= Quiz Test ====================" << std::endl;
  std::string selectedQuiz;
  std::cout << "Enter quiz Title to take: ";
  std::cin >> selectedQuiz;
  std::cin.ignore();

  std::string quizFilePath = "TextFiles/Questions/quiz_" + selectedQuiz + ".txt";
  std::ifstream quizFile(quizFilePath);
  if (!quizFile.is_open())
  {
    std::cout << "Failed to open quiz.\n";
    return;
  }

  std::vector<QuizQuestion> questions;
  std::string line;
  QuizQuestion currentQuestion;
  int lineCount = 0;

  while (std::getline(quizFile, line))
  {
    if (line == "---")
    {
      questions.push_back(currentQuestion);
      lineCount = 0;
      continue;
    }

    switch (lineCount)
    {
    case 0:
      currentQuestion.questionText = line;
      break;
    case 1:
      currentQuestion.choiceA = line;
      break;
    case 2:
      currentQuestion.choiceB = line;
      break;
    case 3:
      currentQuestion.choiceC = line;
      break;
    case 4:
      currentQuestion.choiceD = line;
      break;
    case 5:
      currentQuestion.correctAnswer = line.substr(8);
      break; // Remove "Answer: "
    }

    lineCount++;
  }

  quizFile.close();

  int score = 0;

  for (auto &q : questions)
  {
    std::cout << q.questionText << "\n"
              << q.choiceA << "\n"
              << q.choiceB << "\n"
              << q.choiceC << "\n"
              << q.choiceD << "\n";
    std::cout << "Your Answer (A/B/C/D): ";
    std::cin >> q.userAnswer;
    if (q.userAnswer == q.correctAnswer)
    {
      std::cout << "Correct.\n";
      score++;
    }
    else
    {
      std::cout << "Wrong.\n";
    }
  }

  // Score saving (same as before, can be reused)
  // Save detailed quiz result using questions vector
  saveQuizDetail(username, selectedQuiz, score, questions.size(), questions);
}

// void Student::takeQuiz(const std::string &username)
// {
//   cout << "============= Quiz Test ====================" << endl;
//   string selectedQuiz;
//   cout << "Enter quiz Title to take: ";
//   cin >> selectedQuiz;
//   cin.ignore();

//   string quizFilePath = "TextFiles/Questions/quiz_" + selectedQuiz + ".txt";
//   ifstream quizFile(quizFilePath);
//   if (!quizFile.is_open())
//   {
//     cout << "Failed to open quiz.\n";
//     return;
//   }

//   string line;
//   int score = 0;
//   vector<string> questions;
//   vector<string> userAnswers;
//   vector<string> correctAnswers;

//   while (getline(quizFile, line))
//   {
//     if (line.find("Answer: ") == 0)
//     {
//       correctAnswers.push_back(line.substr(8)); // Save the correct answer
//       cout << "Your Answer (A/B/C/D): ";
//       string userAnswer;
//       cin >> userAnswer;
//       userAnswers.push_back(userAnswer); // Save the user's answer
//       if (userAnswer == correctAnswers.back())
//       {
//         score++;
//         cout << "Correct." << endl;
//       }
//       else
//       {
//         cout << "Wrong." << endl;
//       }
//     }
//     else if (line != "---")
//     {
//       questions.push_back(line); // Save the question text
//       cout << line << "\n";      // Display the question
//     }
//   }

//   quizFile.close();

//   // Save score in user's score file
//   string scoreFilePath = "TextFiles/Scores/score_" + username + ".txt";
//   ifstream checkScore(scoreFilePath);
//   ofstream scoreFile("TextFiles/Scores/temp_score.txt");
//   bool updated = false;

//   string scoreLine;
//   while (getline(checkScore, scoreLine))
//   {
//     if (scoreLine.find(selectedQuiz + ":") == 0)
//     {
//       scoreFile << selectedQuiz << ": " << score << "\n";
//       updated = true;
//     }
//     else
//     {
//       scoreFile << scoreLine << "\n";
//     }
//   }

//   if (!updated)
//   {
//     scoreFile << selectedQuiz << ": " << score << "\n";
//   }

//   checkScore.close();
//   scoreFile.close();

//   remove(scoreFilePath.c_str());
//   rename("TextFiles/Scores/temp_score.txt", scoreFilePath.c_str());

//   cout << selectedQuiz << " Quiz completed.\n";

//   // Save detailed quiz result (questions, user answers, correct answers)
//   saveQuizDetail(username, selectedQuiz, score, questions.size(), questions, userAnswers, correctAnswers);
// }

void Student::viewQuizDetail(const std::string &username)
{
  cout << "============== View Student Quiz Detail ===============\n";
  std::string quizTitle;
  cout << "Enter the Quiz: ";
  cin >> quizTitle;
  std::string filePath = "TextFiles/QuizHistory/" + username + "_" + quizTitle + ".txt";
  std::ifstream file(filePath);

  if (!file.is_open())
  {
    std::cout << "No history found for " << quizTitle << " by user " << username << ".\n";
    return;
  }

  std::string line;
  std::cout << "\n==== Quiz Detail: " << quizTitle << " ====\n";
  while (getline(file, line))
  {
    std::cout << line << "\n";
  }

  file.close();
}

void Student::viewScore(const std::string &username)
{
  string quizTitle;
  cout << "Enter quiz title to view score: ";
  cin >> quizTitle;

  string scoreFilePath = "TextFiles/Scores/score_" + username + ".txt";
  ifstream scoreFile(scoreFilePath);

  if (!scoreFile.is_open())
  {
    cout << "Score file not found for user: " << username << "\n";
    return;
  }

  string line;
  bool found = false;

  while (getline(scoreFile, line))
  {
    if (line.find(quizTitle + ":") == 0)
    {
      cout << "Your score for '" << quizTitle << "' is: "
           << line.substr(quizTitle.length() + 2) << "\n";
      found = true;
      break;
    }
  }

  if (!found)
  {
    cout << "No score found for quiz: " << quizTitle << "\n";
  }

  scoreFile.close();
}
