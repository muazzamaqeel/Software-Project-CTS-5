#ifndef TEAMMEMBER_PROJECTSWINDOW_H
#define TEAMMEMBER_PROJECTSWINDOW_H

#include <QMainWindow>
#include <QTableWidgetItem>
#include <QSqlDatabase>
namespace Ui {
class TeamMember_ProjectsWindow;
}

class TeamMember_ProjectsWindow : public QMainWindow {
    Q_OBJECT


public:
    explicit TeamMember_ProjectsWindow(QWidget *parent = nullptr);
    ~TeamMember_ProjectsWindow();
    int PassValueRole;

public slots:
    void RetrieveAndDisplayUser_Project();
    void Clear_User_Project();
    void ProjectRetrieval();
    void addProject(const QString& projectName, const QString& description, int idProject);
    void onProjectNameClicked(QTableWidgetItem *item);
    void setUsername(const QString& username);
    int getPassValueRole() const;
    void showParentBoard();
    void showLoadingScreen();
    void centerOnScreen();
    void BackButtonClicked();

private:
    Ui::TeamMember_ProjectsWindow *ui;
    int idProject; // Add this line to declare idProject as a member variable
    QString m_username;

};

#endif // TEAMMEMBER_PROJECTSWINDOW_H
