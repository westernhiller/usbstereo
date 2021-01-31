#ifndef MAINDIALOG_H
#define MAINDIALOG_H

#include <QDialog>
#include <QLabel>
#include "calibdialog.h"
#include "capturethread.h"

class MainDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MainDialog(std::string stereocam = "/dev/video2", std::string ircam = "/dev/video4", QWidget *parent = nullptr);
    ~MainDialog();
signals:
    void save();

private:
    CalibDialog* m_pVisible;
    CalibDialog* m_pIr;
    CaptureThread* m_pIrCapturer;
    CaptureThread* m_pVisibleCapturer;

    std::string m_stereocam;
    std::string m_ircam;

public slots:
    void onVisibleChecked(int);
    void onIrChecked(int);
    void onSave();
    void onExit();
};

#endif // MAINDIALOG_H
