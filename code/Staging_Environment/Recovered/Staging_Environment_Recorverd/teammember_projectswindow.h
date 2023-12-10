#ifndef TEAMMEMBER_PROJECTSWINDOW_H
#define TEAMMEMBER_PROJECTSWINDOW_H

#include <QMainWindow>

namespace Ui {
class TeamMember_ProjectsWindow;
}

class TeamMember_ProjectsWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit TeamMember_ProjectsWindow(QWidget *parent = nullptr);
    ~TeamMember_ProjectsWindow();

private:
    Ui::TeamMember_ProjectsWindow *ui;
};

#endif // TEAMMEMBER_PROJECTSWINDOW_H
