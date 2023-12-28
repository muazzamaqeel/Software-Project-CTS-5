#include "pb_confluence_implemenation.h"
#include "parentboard.h"
#include <QCoreApplication>
#include <QDir>
#include <QFileInfo>
#include <QInputDialog>
#include <QStandardItemModel>
#include <QDebug> // Include qDebug for debugging
#include "parentboard.h"
#include <QTableView>

PB_Confluence_Implemenation::PB_Confluence_Implemenation(parentboard* parentBoardInstance)
{
    parentBoard = parentBoardInstance;
    parentBoard->getCreationBox_Confluence()->setVisible(false);
    parentBoard->get_InputTitle_2()->setVisible(false);
    parentBoard->get_InputGroup_Confluence_Heading()->setVisible(false);
    parentBoard->get_InputDescription_Confluence_Heading()->setVisible(false);
    parentBoard->get_Confluence_NameText()->setVisible(false);
    parentBoard->get_Confluence_HeadingText()->setVisible(false);
    parentBoard->get_Confluence_GroupText()->setVisible(false);
    parentBoard->get_Confluence_DescriptionText()->setVisible(false);
    parentBoard->get_Button_Create_Confluence()->setVisible(false);
    parentBoard->getuserTaskTreeWidget_2()->setVisible(true);

}

void PB_Confluence_Implemenation::HideCreationSection()
{
    QTreeWidget* ConfluenceTable = parentBoard->getuserTaskTreeWidget_2();
    ConfluenceTable->setGeometry(10, 75, 1250, 550);
    parentBoard->getCreationBox_Confluence()->setVisible(false);
    parentBoard->get_InputTitle_2()->setVisible(false);
    parentBoard->get_InputGroup_Confluence_Heading()->setVisible(false);
    parentBoard->get_InputDescription_Confluence_Heading()->setVisible(false);
    parentBoard->get_Confluence_NameText()->setVisible(false);
    parentBoard->get_Confluence_HeadingText()->setVisible(false);
    parentBoard->get_Confluence_GroupText()->setVisible(false);
    parentBoard->get_Confluence_DescriptionText()->setVisible(false);
    parentBoard->get_Button_Create_Confluence()->setVisible(false);
    parentBoard->getuserTaskTreeWidget_2()->setVisible(true);


}
void PB_Confluence_Implemenation::ShowCreateWindow(){
    QTreeWidget* ConfluenceTable = parentBoard->getuserTaskTreeWidget_2();
    ConfluenceTable->setGeometry(10, 75, 800, 550);

    parentBoard->getCreationBox_Confluence()->setVisible(true);
    parentBoard->get_InputTitle_2()->setVisible(true);
    parentBoard->get_InputGroup_Confluence_Heading()->setVisible(true);
    parentBoard->get_InputDescription_Confluence_Heading()->setVisible(true);
    parentBoard->get_Confluence_NameText()->setVisible(true);
    parentBoard->get_Confluence_HeadingText()->setVisible(true);
    parentBoard->get_Confluence_GroupText()->setVisible(true);
    parentBoard->get_Confluence_DescriptionText()->setVisible(true);
    parentBoard->get_Button_Create_Confluence()->setVisible(true);

}


void PB_Confluence_Implemenation::CreatePageFunction(){

    QTreeWidget* ConfluenceTable = parentBoard->getuserTaskTreeWidget_2();
    ConfluenceTable->setGeometry(10, 75, 1250, 550);
    parentBoard->getCreationBox_Confluence()->setVisible(false);
    parentBoard->get_InputTitle_2()->setVisible(false);
    parentBoard->get_InputGroup_Confluence_Heading()->setVisible(false);
    parentBoard->get_InputDescription_Confluence_Heading()->setVisible(false);
    parentBoard->get_Confluence_NameText()->setVisible(false);
    parentBoard->get_Confluence_HeadingText()->setVisible(false);
    parentBoard->get_Confluence_GroupText()->setVisible(false);
    parentBoard->get_Confluence_DescriptionText()->setVisible(false);
    parentBoard->get_Button_Create_Confluence()->setVisible(false);
}
