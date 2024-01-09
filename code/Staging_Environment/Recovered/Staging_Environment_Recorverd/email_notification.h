#ifndef EMAIL_NOTIFICATION_H
#define EMAIL_NOTIFICATION_H

#include <string>

// Email_Notification.h

class Email_Notification {
public:
    Email_Notification() = default;
    ~Email_Notification() = default;
    bool sendEmail(const std::string& recipient_email, const std::string& subject, const std::string& email_body);
};

// Email_Notification.cpp - Remove Py_Initialize() and Py_Finalize() from constructor and destructor


#endif // EMAIL_NOTIFICATION_H
