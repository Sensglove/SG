#include "okno.hh"

#include<QMessageBox>

using namespace std;

/*!
 * \brief Read_Thread::CheckData
 * Sprawdzanie sumy kontrolnej, suma wartości z wszystkich czujnikow modulo 2^16
 * \param wiadomosc -
 *
 * \return true - dane poprawne, false - dane niepoprawne
 */
bool Read_Thread::CheckData(QString *wiadomosc){
        bool ok;
        if(wiadomosc->mid(0,1)!="X"||wiadomosc->length()!=LENGTH) {
            cout<<"zła dlugosc"<<wiadomosc->length()<<endl;
            //cout<<wiadomosc->toStdString();
            return false;
        }
        else{
        int control_sum=0;
        for(int i = 0; i < 23; ++i) {
                QString subString = wiadomosc->mid(i*4+1, 4);
                int odczyt = subString.toInt(&ok, 16);

            control_sum+=odczyt;
                }
        QString subString = wiadomosc->mid(92, 4);
        int sum=subString.toInt(&ok,16);
        if (sum==control_sum%(2^16)) return true;
        else {
            return true;

        }
        }

        return false;

}

/*!
 * \brief Read_Thread::run
 *
 * Watek czytajacy z portu USB
 * W razie ustawienie odpowiednich flag zapisuje też dane do tablicy data[]
 */

void Read_Thread::run()
{
    start_flag=true;
    string bufor;

    int sample_nr=0;

    while(start_flag){
  if(RS232_Odbierz(window->takeDeskPort(), bufor, 1000, 150)){
    window->mySocket->write(bufor);

     QString *buf= new QString(bufor.c_str());
  if(CheckData(buf)){
          window->mySocket->write(bufor);

          // cout<<bufor.length()<<endl;

if(window->measure_flag==true){
window->data.push_back(bufor);
++sample_nr;

//cout<<sample_nr<<endl;
/*},

 */
if(sample_nr==SAMPLE_AMOUNT) {sample_nr=0; window->measure_flag==false; window->save_flag=true;}

}
}

}
/*{
   QMessageBox::StandardButton reply;
     reply=QMessageBox::question(this, "Error", "Data was incorrect. Would you like to try again?",
                                           QMessageBox::Yes|QMessageBox::No,  QMessageBox::Yes);
     if(reply==QMessageBox::No)
     {
         window->close();
          // exit(1);
     }
    }

    */}}

//zapis do socketu

/*
  !!!!!!tutaj jest wątek wczytywania danych z portu!!!!!!!!!!

  !!!!!!!napisać wezdeskportu i obsługe danych!!!!!!!!!!!!!!!
  !!!!!!!dodać sprawdzanie sumy kontrolnej!!!!!!!!!!!!!!!!!!!
  !!!!!!!dodać zapisywanie danych do jakiegos pliku tmp!!!!!!
  !!!!!!!dodać zwracanie bufora!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        }*/

/*!
 * \brief Okno::SaveToFile
 * zapisywanie do pliku z tablicy data[]
 * rozdzielenie danych na poszczegolne czujniki
 *
 * \return bool - czy zapis do pliku się powiodl czy nie
 */
bool Okno::SaveToFile(){

    cout<<"SAVE";
if(save_flag){

    cout<<"SAVEFLAG";
string name_file;
name_file=type_of_movement->currentText().toStdString()+"_"+name->text().toStdString()+".txt";
fstream file;
// cout<<data.size();
file.open(name_file.c_str(), std::ios::out);
if(file.good()){


   for(int i=0;i<SAMPLE_AMOUNT;i++){

        cout<<data[i]<<endl;
        bool ok;
        for(int i = 0; i < 23; ++i) {
                string subString = data[i].substr(i*4+1, 4);
                //int odczyt = subString; //.toInt(&ok, 16);
                //file<<subString<<" ";
                QString *str=new QString(subString.c_str());
                int a=str->toInt(&ok,16);
                if(ok) file<<a<<" ";
                else return false;
            //if (!ok) return false;
        }
      file<<endl;
    }
   data.clear();
    file.close();
    return true;

}
else return false;
save_flag=false;
}
else return false;
}
/*!
 * \brief Okno::Okno
 * \param parent
 * konstruktor okna głównego programu,
 * inicjalizacja wszystkich parametrow
 */

Okno::Okno(QWidget *parent) : QWidget(parent), start_flag(false), desk_portu(0), read_thread(this,this)//, write_thread(this,this)
{

    this->setGeometry(300, 300, 300, 200);
    timer=new QTimer;
    save_flag=false;
    measure_flag=false;
    bartim =new QTimer(this);
    progress_bar= new QProgressBar(this);
    usb_label=new QLabel("Choose Port:");
    usb_choice = new QComboBox(this);
    start_m=new QPushButton("Measurement");
    start_m->setObjectName("start_m");
    start_m->setDisabled(true);
    usb_choice->addItem("USB0");
    usb_choice->addItem("USB1");
    usb_choice->addItem("USB2");
    usb_choice->addItem("USB3");
    usb_choice->addItem("USB4");

    start = new QPushButton("START");
    start->setObjectName("start");
    accept =new QPushButton("SAVE");
    accept->setObjectName("accept");
    reject = new QPushButton("IGNORE");
    reject->setObjectName("reject");
    type_of_movement=new QComboBox(this);
type_of_movement->addItem("ruch1");
type_of_movement->addItem("ruch2");
type_of_movement->addItem("ruch3");
type_of_movement->addItem("ruch4");
type_of_movement->addItem("ruch5");
type_of_movement->addItem("ruch6");
type_of_movement->addItem("ruch7");
type_of_movement->addItem("ruch8");
type_of_movement->addItem("ruch9");
type_of_movement->setDisabled(true);
QVBoxLayout *vlayout=new QVBoxLayout(this);

name=new QLineEdit(this);
name_label=new QLabel("Name:");
QVBoxLayout *names_layout=new QVBoxLayout();
names_layout->addWidget(name_label);
names_layout->addWidget(name);
//name_label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
name->setDisabled(true);


QHBoxLayout *acceptance_layout=new QHBoxLayout();
acceptance_layout->addWidget(accept);
acceptance_layout->addWidget(reject);
accept->setDisabled(true);
reject->setDisabled(true);

QHBoxLayout *usb_layout= new QHBoxLayout();
usb_layout->addWidget(usb_label);
usb_layout->addWidget(usb_choice);

//move_name->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);

move_name=new QLabel("Choose type:");
QVBoxLayout *move_type = new QVBoxLayout();
move_type->addWidget(move_name);
move_type->addWidget(type_of_movement);


QHBoxLayout *choice_layout=new QHBoxLayout();


choice_layout->addLayout(move_type);
choice_layout->addLayout(names_layout);

vlayout->addLayout(usb_layout);
vlayout->addWidget(start);
vlayout->addWidget(start_m);
vlayout->addLayout(choice_layout);
vlayout->addLayout(acceptance_layout);


    vlayout->addWidget(progress_bar);

this->setLayout(vlayout);

    connect(timer, SIGNAL(timeout()),this, SLOT(setMeasureIcons()));
    connect(bartim, SIGNAL(timeout()),this, SLOT(SetProgressBar()));

    mySocket=new Socket(nullptr);

    QMetaObject::connectSlotsByName(this);

}



/*!
 * \brief Okno::on_start_clicked
 * Rozpoczęcie wątku odczytującego dane, sprawdzenie poprawności otwarcia portu USB wybranego, mozliwosc ponownego wyboru.
 *
 */

void Okno::on_start_clicked()
{


int    DeskPortu;

string USB;
USB="/dev/ttyACM"+usb_choice->currentText().mid(3,1).toStdString();
if ((DeskPortu = open(USB.c_str(),O_RDWR | O_NONBLOCK)) < 0) {
  //cerr << ":( Blad otwarcia portu " <<usb_choice->currentText().toStdString() << endl;
  QMessageBox::StandardButton reply;
    reply=QMessageBox::question(this, "Error", "Cannot open USB. Would you like to retry?",
                                          QMessageBox::Yes|QMessageBox::No,  QMessageBox::Yes);
    if(reply==QMessageBox::No)
    {
        this->close();
         // exit(1);
    }

}
else{

    usb_label->setVisible(false);
    usb_choice->setVisible(false);
    start_m->setDisabled(false);
    start->setVisible(false);
    SetTransParam(DeskPortu);
    setDeskPort(DeskPortu);
    read_thread.Start();
}


}

/*!
 * \brief Okno::on_start_m_clicked
 * uruchomienie pomiaru, ustawienie odpowiednich przycisków, uruchomienie timerów
 *
 */

void Okno::on_start_m_clicked()
{

    measure_flag=true;
    timer->setSingleShot(true);
    bartim->start(19);
    timer->start(2000);
    start_m->setDisabled(true);


}

/*!
 * \brief Okno::setMeasureIcons
 * public slot połaczony z sygnalem z timera, ktory odmierza 2s na pomiar
 */
void Okno::setMeasureIcons()
{
    measure_flag=false;
    accept->setDisabled(false);
    reject->setDisabled(false);
    type_of_movement->setDisabled(false);
    name->setDisabled(false);
    bartim->stop();
    save_flag=true;

}

/*!
 * \brief Okno::on_accept_clicked
 * uruchamia zapisywanie do pliku danych z tablicy data[]
 */

void Okno::on_accept_clicked()
{

//mySocket->newConnection();
   if(save_flag) {
       if(!SaveToFile()){
           QMessageBox::StandardButton reply;
             reply=QMessageBox::question(this, "Error", "Data was incorrect. Would you like to try again?",
                                                   QMessageBox::Yes|QMessageBox::No,  QMessageBox::Yes);
             if(reply==QMessageBox::No)
             {
                 this->close();
             }
       }

    } ////!!!!
    start_m->setDisabled(false);
    name->setDisabled(false);
    progress_bar->setValue(0);
    type_of_movement->setDisabled(true);
    accept->setDisabled(true);
    reject->setDisabled(true);
    name->setDisabled(true);
}

/*!
 * \brief Okno::on_reject_clicked
 * ignoruje dane zapisane do tablicy, powoduje pojawienie się odpowiednich przycisków
 */
void Okno::on_reject_clicked()
{
    type_of_movement->setVisible(false);
    accept->setVisible(false);
    reject->setVisible(false);
    start_m->setDisabled(false);
    progress_bar->setValue(0);
    data.clear();

}

/*!
 * \brief Okno::closeEvent
 *
 * zamknięcie watku read_thread
 */

void Okno::closeEvent(QCloseEvent *clevent){

    endReadThread();
    waitReadThread();

}


