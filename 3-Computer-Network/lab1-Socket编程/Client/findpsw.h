#ifndef FINDPSW_H
#define FINDPSW_H

#include <QDialog>
#include "ClientSocket.h"

namespace Ui {
class findpsw;
}

class findpsw : public QDialog
{
    Q_OBJECT
protected:
    QSize sizeHint() const{
        return QSize(400,300);
    }
public:
    explicit findpsw(QWidget *parent = 0);
    ~findpsw();
signals:
    void display(int number);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::findpsw *ui;
    ClientSocket *pconnetcedServerSocket;
};

#endif // FINDPSW_H
