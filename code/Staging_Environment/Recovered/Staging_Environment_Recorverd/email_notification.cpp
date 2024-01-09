#include "Email_Notification.h"
#include <Python.h>
#include <iostream>  // Add this line to include iostream


bool Email_Notification::sendEmail(const std::string& recipient_email, const std::string& subject, const std::string& email_body) {
    std::string python_code = R"(
import smtplib
from email.mime.multipart import MIMEMultipart
from email.mime.text import MIMEText

def send_email(sender_email, sender_password, recipient, subject, body):
    try:
        smtp_server = "smtp.outlook.com"
        smtp_port = 587
        server = smtplib.SMTP(smtp_server, smtp_port)
        server.starttls()
        server.login(sender_email, sender_password)

        msg = MIMEMultipart()
        msg['From'] = sender_email
        msg['To'] = recipient
        msg['Subject'] = subject
        msg.attach(MIMEText(body, 'plain'))

        server.sendmail(sender_email, recipient, msg.as_string())
        server.quit()
        return "Success"
    except Exception as e:
        return f"Failed: {e}"
    )";

    PyRun_SimpleString("import sys\nsys.path.append('.')");
    PyRun_SimpleString(python_code.c_str());
    PyObject *pMainModule = PyImport_AddModule("__main__");
    PyObject *pResult = PyObject_CallMethod(pMainModule, "send_email", "(sssss)",
                                            "scrummy1.0@outlook.com",
                                            "SoftwareProject1234",
                                            recipient_email.c_str(),
                                            subject.c_str(),
                                            email_body.c_str());

    if (pResult != NULL) {
        std::string result = PyUnicode_AsUTF8(pResult);
        Py_DECREF(pResult);

        if (result == "Success") {
            return true;
        } else {
            std::cerr << result << std::endl;
            return false;
        }
    } else {
        PyErr_Print();
        return false;
    }
}
