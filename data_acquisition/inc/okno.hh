#ifndef OKNO_HH
#define OKNO_HH
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<ustat.h>
#include<QWidget>
#include<QProgressBar>
#include<QGridLayout>
#include<QComboBox>
#include<QPushButton>
#include<QLabel>
#include<QTimer>
#include<QThread>
#include<QString>
#include<string>
#include<fstream>
#include<iostream>
#include<QVector>
#include<QHBoxLayout>
#include<QVBoxLayout>
#include<QLineEdit>
#include<QValidator>
#include"odbieranie.hh"
#include"transparam.hh"
#include"socket.hh"

#define LENGTH 102
#define SAMPLE_AMOUNT 2000

using namespace std;



class Okno;

/*!
 * \brief The Read_Thread class
 * watek czytajacy z portu USB
 */
class Read_Thread: public QThread
{
    Okno *window;
    bool start_flag;
public:
    /*!
    * \brief Read_Thread
    * \param parent
    * \param _window
    * konstruktor watku
    */
   Read_Thread(QObject *parent, Okno *_window): QThread(parent), window(_window), start_flag(true)
   {}
   /*!
     * \brief Start - funkcja zaczynjąca wątek i ustawiająca mu start_flag=true
     */
    void Start(){start_flag=true; start();}
    /*!
     * \brief Stop - funkcja ustawiająca start_flag=false
     */
    void Stop(){start_flag=false;}
    void run();
    bool CheckData(QString *wiadomosc);


};


/*!
 * \brief The Okno class
 * okno główne programu
 */
class Okno : public QWidget
{
    Q_OBJECT


public:
    /*!
     * \brief start_flag - flaga oznaczająca początek czytanai wątku
     */
    bool start_flag;
    /*!
     * \brief desk_portu
     */
    int desk_portu;
    /*!
     * \brief measure_flag
     */
    bool measure_flag;
    /*!
     * \brief save_flag
     */
    bool save_flag;
    /*!
     * \brief read_thread
     */
    Read_Thread read_thread;
    /*!
     * \brief data - dane do przesyłu poprzez socket
     */
    QVector<string> data;
    /*!
     * \brief mySocket - socket, przez który wysyłane są dane
     */
    Socket *mySocket;

private:
    QTimer *timer;
    QTimer *bartim;
    QProgressBar *progress_bar;
    QLabel *usb_label;
    QComboBox *usb_choice;
    QPushButton *start;
    QPushButton *start_m;
    QPushButton *accept;
    QPushButton *reject;
    QGridLayout *layout;
    QComboBox *type_of_movement;
    QLabel *name_label;
    QLineEdit *name;
    QLabel *move_name;

   // Socket *mySocket;

public:

    Okno(QWidget *parent );
    /*!
     * \brief setDeskPort
     * \param DeskPortu
     */
    void setDeskPort(int DeskPortu){desk_portu=DeskPortu;}
    /*!
     * \brief takeDeskPort
     * \return zwraca desk_portu
     */
    int takeDeskPort() const {return desk_portu;}
    /*!
     * \brief endReadThread
     * konczenie watku czytajacego z USB
     */
    void endReadThread(){read_thread.Stop();}
    /*!
     * \brief waitReadThread
     * czekanie na zakonczenie watku
     */
    void waitReadThread(){read_thread.wait();}
    bool SaveToFile();
    ~Okno(){

        delete usb_label;
    }

signals:

public slots:
    void on_start_clicked();
    void on_start_m_clicked();
    /*!
     * \brief SetProgressBar
     * zwiekszanie wartosci progress_bar poloczone z sygnalem z timera bartim
     */
    void SetProgressBar() {progress_bar->setValue(progress_bar->value()+1);}
    void setMeasureIcons();
    void on_accept_clicked();
    void on_reject_clicked();
protected:
    void closeEvent(QCloseEvent *clevent);
};




#endif // OKNO_HH

