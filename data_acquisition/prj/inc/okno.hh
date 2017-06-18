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

#define LENGTH 125
#define SAMPLE_AMOUNT 2000

using namespace std;



class Okno;

/*!
 * \brief The Read_Thread class
 * Wątek czytajacy z portu USB.
 */
class Read_Thread: public QThread
{
    /*!
     * \brief window
     * Okno główne programu.
     */
    Okno *window;
    /*!
     * \brief start_flag
     * Flaga sprawdzająca, czy mierzony jest pomair. true - jest, false - nie jest
     */
    bool start_flag;
public:
    /*!
    * \brief Read_Thread Konstruktor wątku fokonującego przesyłu danych.
    * \param parent
    * \param _window
    */
   Read_Thread(QObject *parent, Okno *_window): QThread(parent), window(_window), start_flag(true)
   {}
   /*!
     * \brief Start Funkcja zaczynjąca wątek i ustawiająca mu flagę start_flag na wartość true.
     */
    void Start(){start_flag=true; start();}
    /*!
     * \brief Stop Funkcja ustawiająca start_flag na wartość false.
     */
    void Stop(){start_flag=false;}
    void run();
    bool CheckData(QString *wiadomosc);


};


/*!
 * \brief The Okno class
 * Okno główne programu.
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
     * \brief error_flag
     */
    bool error_flag=false;
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
    /*!
     * \brief timer
     * Timer służący do odmierzania 2 s pomiaru.
     */
    QTimer *timer;
    /*!
     * \brief bartim
     * Timer odmierzający czas dla paska ładowania.
     */
    QTimer *bartim;
    /*!
     * \brief progress_bar
     * Pasek ładowania pokazujący postęp pomiaru danych.
     */
    QProgressBar *progress_bar;
    /*!
     * \brief usb_label
     * Napis z informacją o możliwości wyboru portu USB.
     */
    QLabel *usb_label;
    /*!
     * \brief usb_choice
     * Lista wyboru portu USB.
     */
    QComboBox *usb_choice;
    /*!
     * \brief start
     * Przycisk startu przesyłania danych do programu wizualizacji.
     */
    QPushButton *start;
    /*!
     * \brief start_m
     * Przycisk startu pomiaru.
     */
    QPushButton *start_m;
    /*!
     * \brief accept
     * Przycisk akceptacji pomiaru.
     */
    QPushButton *accept;
    /*!
     * \brief reject
     * Przycisk odrzucenia pomiaru.
     */
    QPushButton *reject;
    /*!
     * \brief layout
     * Warstwa potrzebna do ustawienia wzgledem siebie elementów.
     */
    QGridLayout *layout;
    /*!
     * \brief type_of_movement
     * Lista wyboru typu ruchu.
     */
    QComboBox *type_of_movement;
    /*!
     * \brief name_label
     * Napis informujący o możliwości podania imienia osoby wykonującej pomiar.
     */
    QLabel *name_label;
    /*!
     * \brief name
     * Pole do podania imienia osoby wykonujacej pomiar.
     */
    QLineEdit *name;
    /*!
     * \brief move_name
     * Napis informujacy o rodzaju wykonanego ruchu.
     */
    QLabel *move_name;

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

