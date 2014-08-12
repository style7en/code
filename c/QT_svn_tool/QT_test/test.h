#ifndef TEST_H
#define TEST_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>
#include <QGridLayout>

class Test : public QWidget
{
    Q_OBJECT
public:
    Test(QWidget *parent=0);
    void setup_ui();
signals:
private slots:
private:
    QLabel *label_svn;
    QLineEdit *edit_svn;
    QPushButton *button_svn;
    QLabel *label_head;
    QLineEdit *edit_head;
    QLabel *label_list;
    QTextEdit *text_list;
    QLabel *label_version;
    QLineEdit *edit_version;
    QPushButton *button_import;
    QTextEdit *text_output;
};

#endif