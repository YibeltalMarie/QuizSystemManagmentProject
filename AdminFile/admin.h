
#ifndef ADMIN_H
#define ADMIN_H
#include <string>
#include <vector>

extern std::vector<std::string> quizCollectors;
struct Question
{
    std::string questionText;
    std::string optionA;
    std::string optionB;
    std::string optionC;
    std::string optionD;
    std::string correctOption; // 'A', 'B', 'C', 'D'
};

class Admin
{
private:
    std::string username;
    std::string password;
    // std::string FolderPath = "../TextFiles/AdminText/";
    const std::string adminFile = "AdminFile/admin.txt";

    void createDefaultAdmin(); // Ensures default credentials exist
    bool loadCredentials(std::string &storedUsername, std::string &storedPassword);

public:
    void QuizCollector(std::vector<std::string> &quizCollector);
    Admin();
    bool login();
    bool changePassword();
    bool viewAllStudents();
    bool deleteStudentAccount();
    void createQuiz();
    void saveToFile(const std::vector<std::string> &data, const std::string &filename);
    void loadFromFile(std::vector<std::string> &data, const std::string &filename);
    void addQuestionToQuiz(const std::string &quizTitle);
    // int NextQuestionNumber(std::string &questionFile);
    int getLastQuestionNumber(const std::string &quizTitle, const std::string &filename);
    void updateQuestionNumber(const std::string &quizTitle, int newNumber, const std::string &filename);

    template <typename T>
    void saveQuizQuestionsToFile(const std::string &quizTitle, const std::vector<T> &questions);
    void viewQuiz(std::string &quizTitle);
    void modifyQuizQuestion(const std::string &QuizTitle, int questionNumber);
};

#endif
