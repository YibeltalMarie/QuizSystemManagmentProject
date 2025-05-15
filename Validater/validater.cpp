
#include "validater.h"
#include <cctype>
#include <regex>
using namespace std;

bool isValidUsername(const std::string &username)
{
    if (username.length() < 4)
        return false;
    for (char c : username)
    {
        if (!isalnum(c))
            return false; // only letters and digits
    }
    return true;
}

bool isValidPassword(const std::string &password)
{
    if (password.length() < 6)
        return false;

    bool hasLetter = false, hasDigit = false;
    for (char c : password)
    {
        if (isalpha(c))
            hasLetter = true;
        if (isdigit(c))
            hasDigit = true;
    }

    return hasLetter && hasDigit;
}

bool isValidEmail(const std::string &email)
{
    const regex pattern(R"(^[A-Za-z0-9._%+-]{8,}+@[A-Za-z0-9.-]+\.[A-Za-z]{2,}$)");
    return regex_match(email, pattern);
}
