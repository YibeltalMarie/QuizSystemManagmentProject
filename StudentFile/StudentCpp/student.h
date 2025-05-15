#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <vector>

struct QuizQuestion
{
  std::string questionText;
  std::string choiceA;
  std::string choiceB;
  std::string choiceC;
  std::string choiceD;
  std::string correctAnswer;
  std::string userAnswer;
};

struct Student
{
  std::string Folder = "StudentFile/StudentCpp/students.txt";
  std::string Folder2 = "StudentFile/StudentCpp/temp.txt";

  std::string username;
  std::string email;
  std::string password;

  void registerStudent();
  bool login();
  // void inputCredentials(string &userName);
  bool changePassword();
  bool deleteStudentAccount();
  void takeQuiz(const std::string &username);
  void saveQuizDetail(
      const std::string &username,
      const std::string &quizTitle,
      int score,
      int total,
      const std::vector<QuizQuestion> &questions);
  void viewQuizDetail(const std::string &username);
  void viewScore(const std::string &username);
};

#endif
