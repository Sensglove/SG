#include "inc/okno.hh"

#include<QMessageBox>

using namespace std;

int licznik = 0;

/*!
 * \brief Read_Thread::CheckData
 * Sprawdzanie sumy kontrolnej, suma wartości z wszystkich czujników modulo 2^16.
 * \param wiadomosc
 * Bufor danych wejściowych, w którym srpawdzana jest suma kontrolna. *
 * \return true - dane poprawne, false - dane niepoprawne
 */
bool Read_Thread::CheckData(QString *wiadomosc){
        bool ok;
        //cout<<wiadomosc->toStdString() << endl;
        if(wiadomosc->mid(0,1)!="X") {
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
        QString subString = wiadomosc->mid(93, 4);
        int sum=subString.toInt(&ok,16);
        if (sum==control_sum%(1<<16)) return true;
        else {
            cout << "suma otrzymana: " << sum <<  endl;
            cout<< "obliczona suma ";
            cout << control_sum << endl;
            return true;

        }
        }

        return false;

}

/*!
 * \brief Read_Thread::run
 *
 * Wątek czytający z portu USB.
 * W razie ustawienie odpowiednich flag zapisuje też dane do tablicy data[].
 */

void Read_Thread::run()
{
    start_flag=true;
    string bufor;


    while(start_flag){
        licznik++;
        if(RS232_Odbierz(window->takeDeskPort(), bufor, 150, 150)){
            //cout<<"BUFOR "<<bufor<<endl;
            QString *buf= new QString(bufor.c_str());
            bool correct=CheckData(buf);


            if(CheckData(buf)){

                if(window->mySocket->connected()) window->mySocket->write(bufor);

                if(window->measure_flag==true)
                    window->data.push_back(bufor);


            }
}
}
}



/*!
 * \brief Okno::SaveToFile
 * Zapisywanie do pliku z tablicy data[].
 * Rozdzielenie danych na poszczególne czujniki.
 *
 * \return bool - czy zapis do pliku się powiodl czy nie
 */
bool Okno::SaveToFile(){

//    cout<<"SAVE";
if(save_flag){

 //   cout<<"SAVEFLAG";
string file_name="tmp.txt";
string move_name=type_of_movement->currentText().toStdString();
string name_name=name->text().toStdString();
string skrypt="sh przeniesPlik ";
        skrypt=skrypt+file_name+" "+name_name+" "+move_name;

fstream file;
cout<<"ROZMIAR"<<data.size()<<endl;
file.open(file_name.c_str(), std::ios::out);
if(file.good()){

cout << "rozmiar data: " << data.size() << endl;
   for(int i=0;i<data.size();++i){

        bool ok;
        for(int j= 0; j < 23; ++j) {
                string subString = data[i].substr(j*4+1, 4);
                //int odczyt = subString; //.toInt(&ok, 16);
                //file<<subString<<" ";
                QString *str=new QString(subString.c_str());
                float a=str->toInt(&ok,16)*3.3/(4096.0);
                file<<a<<" ";

            //if (!ok) return false;
        }
      file<<endl;
    }
   data.clear();
    file.close();
    system(skrypt.c_str());
    return true;

}
else return false;

}
else return false;
}
/*!
 * \brief Okno::Okno
 * \param parent
 * Konstruktor okna głównego programu,
 * inicjalizacja wszystkich parametrów.
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
type_of_movement->addItem("dlugopis");
type_of_movement->addItem("srobka");
type_of_movement->addItem("potencjometr");
type_of_movement->addItem("szklanka");
type_of_movement->addItem("kubek");
type_of_movement->addItem("czajnik");
type_of_movement->addItem("karta");
type_of_movement->addItem("telefon");
type_of_movement->addItem("myszka");
type_of_movement->setDisabled(true);
QVBoxLayout *vlayout=new QVBoxLayout(this);

name=new QLineEdit(this);
name_label=new QLabel("User's name:");
QVBoxLayout *names_layout=new QVBoxLayout();
names_layout->addWidget(name_label);
name_label->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
names_layout->addWidget(name);
name->setDisabled(true);


QHBoxLayout *acceptance_layout=new QHBoxLayout();
acceptance_layout->addWidget(accept);
acceptance_layout->addWidget(reject);
accept->setDisabled(true);
reject->setDisabled(true);

QHBoxLayout *usb_layout= new QHBoxLayout();
usb_layout->addWidget(usb_label);
usb_layout->addWidget(usb_choice);

move_name=new QLabel("Choose type:");
QVBoxLayout *move_type = new QVBoxLayout();
move_type->addWidget(move_name);
move_name->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
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
 * Rozpoczęcie wątku odczytującego dane, sprawdzenie poprawności otwarcia wybranego portu USB, możliwość ponownego wyboru portu USB.
 *
 */

void Okno::on_start_clicked()
{


int    DeskPortu;

string USB;
USB="/dev/ttyACM"+usb_choice->currentText().mid(3,1).toStdString();
if ((DeskPortu = open(USB.c_str(),O_RDWR | O_NONBLOCK)) < 0) {
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
 * Uruchomienie pomiaru, ustawienie odpowiednich przycisków, uruchomienie timerów.
 *
 */

void Okno::on_start_m_clicked()
{

    measure_flag=true;
    timer->setSingleShot(true);
    bartim->start(19);
    timer->start(2000);
    start_m->setDisabled(true);
    cout << "START " << licznik << endl;


}

/*!
 * \brief Okno::setMeasureIcons
 * Public slot połaczony z sygnałem z timera, który odmierza 2s na pomiar.
 */
void Okno::setMeasureIcons()
{
    cout << "STOP " << licznik << endl;
    measure_flag=false;
    save_flag=true;
    accept->setDisabled(false);
    reject->setDisabled(false);
    type_of_movement->setDisabled(false);
    name->setDisabled(false);
    bartim->stop();
    //save_flag=true;

}

/*!
 * \brief Okno::on_accept_clicked
 * Uruchamia zapisywanie do pliku danych z tablicy data[].
 */

void Okno::on_accept_clicked()
{

//mySocket->newConnection();
   if(save_flag) {
       if(error_flag){
           QMessageBox::StandardButton reply;
             reply=QMessageBox::question(this, "Error", "Data was incorrect. Would you like to try again?",
                                                   QMessageBox::Yes|QMessageBox::No,  QMessageBox::Yes);
             if(reply==QMessageBox::No)
             {
                 this->close();
             }
       }
       else{
       if(!SaveToFile()){
           QMessageBox::StandardButton reply;
             reply=QMessageBox::question(this, "Error", "Cannot save to file. Would you like to try again?",
                                                   QMessageBox::Yes|QMessageBox::No,  QMessageBox::Yes);
             if(reply==QMessageBox::No)
             {
                 this->close();
             }
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
    save_flag=false;
    error_flag=false;
    data.clear();
}

/*!
 * \brief Okno::on_reject_clicked
 * Ignoruje dane zapisane do tablicy, powoduje pojawienie się odpowiednich przycisków.
 */
void Okno::on_reject_clicked()
{
    type_of_movement->setDisabled(true);
    save_flag=false;
    name->setDisabled(true);
    accept->setDisabled(true);
    reject->setDisabled(true);
    start_m->setDisabled(false);
    progress_bar->setValue(0);
    data.clear();

}

/*!
 * \brief Okno::closeEvent
 *
 * Zamknięcie wątku read_thread.
 */
void Okno::closeEvent(QCloseEvent *clevent){

    endReadThread();
    waitReadThread();

}
