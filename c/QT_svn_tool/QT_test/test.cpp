#include <QtGui>
#include "test.h"

Test::Test(QWidget *parent/* =0 */) : QWidget(parent)
{
    setup_ui();    
}

void Test::setup_ui()
{
    label_svn = new QLabel("SVN Path");
    edit_svn = new QLineEdit;
    button_svn = new QPushButton("...");
    label_head = new QLabel("Head");
    edit_head = new QLineEdit;
    label_list = new QLabel("List");
    text_list = new QTextEdit;
    label_version = new QLabel("Version");
    edit_version = new QLineEdit;
    button_import = new QPushButton("Import");
    text_output = new QTextEdit;

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(label_svn, 0, 0);
    layout->addWidget(edit_svn, 0, 1);
    layout->addWidget(button_svn, 0, 2);
    layout->addWidget(label_head, 1, 0, 1, 1);
    layout->addWidget(edit_head, 1, 1, 1, 2);
    layout->addWidget(label_list, 2, 0, 1, 1);
    layout->addWidget(text_list, 2, 1, 1, 2);
    layout->addWidget(label_version, 3, 0);
    layout->addWidget(edit_version, 3, 1);
    layout->addWidget(button_import, 3, 2);
    layout->addWidget(text_output, 4, 0, 1, 3);

    setLayout(layout);
}