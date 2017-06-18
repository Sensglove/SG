#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include "transparam.hh"
#include <cstring>



/*!
 * Opis flag patrz: man tcsetattr
 */
void SetTransParam_InputModes( struct termios *pTransParam,
                               Type4Parity     Parity
                             )
{
  pTransParam->c_iflag = 0
   | IGNBRK  /* - Ustawiona - ignoruje polecenie BREAK. */
   /* BRKINT - nie ustawiona */
   /* IGNPAR -ignoruje błedy ramki i błędy parzystości */
   /* PARMRK - nie ustawiona */
   | (Parity != P_None ? INPCK : 0)
   /* ISTRIP -*/
   /* INLCR  -tłumacz <NL> na <CR> */
   /* IGNCR  -ignoruj <CR>         */
   /* ICRNL  -tłumacz <CR> na <NL> (o ile nie jest ustawiona IGNCR)*/
   /* IUCLC  -zamieniaj duże litery na małe */
   /* IXON   -aktywuj sprzętową kontrolę przepływu XON/XOFF na wyjściu */
   /* IXANY  -dowolny znak restartuje wyjście, gdy jest ono w stanie 
                               wstrzymania                                              */
   /* IXOFF  -aktywuje sprzętową kontrolę przepływu XON/XOFF na wejściu*/
   /* IUTF8 -znaki na wejściu są kodowane w UTF-8 */;
}


/*!
 * Opis flag patrz: man tcsetattr
 */
void SetTransParam_OutputModes( struct termios *pTransParam )
{
  pTransParam->c_oflag = 0
    /* OPOST - nie ustawiona */
    /* OLCUC - zmienia małe litery na duże */
    /* ONLCR - zmienia <NL> na <CR><NL> */
    /* OCRNL - zmienia <CR> na <NL> */
    /* ON0CR - nie wysyła pustej linii (wielokrotne <CR>)*/
    /* ONLRET - nie wysyła znaku <CR> */
    /* OFILL - wysyła znak "wypełnienia" zamiast ciszy na linii */
    | NL0 /* NLDLY - maska dla opóźnienie po <NL>. Wartości NL0 i NL1 */
    | CR0 /* CRDLY - maska dla wartości opóźnienia po <CR>. 
                     Wartości CR0, CR1, CR2, CR3 */
    /* TABDLY - maska dla wartości TAB0, TAB1, TAB2, TAB3 lub XTABS*/
    /* BSDLY  - maska dla opóźnienia po znaku "backspace". Wartości: BS0, BS1
                    (nie jest to zaimplementowane)*/
    /* VTDLY - maska dla opóźnienia wertykalnego znaku tab. Wartości: VT0, VT1*/
    | FF0 /* FFDLY - maska dla opoźnienie "form feed". Wartości: FF0, FF1 */
    ;
  // pTransParam->c_oflag = 0 | NL0 | CR0 | FF0; // TMP
}




/*!
 * Ustawia parametry transmisji:
 *     \li 8 bitów w znaku,
 *     \li 1 bit stopu,
 *  \param[in] Parity - pozwala na ustawienie rodzaju kontroli parzystości.
 */
void SetTransParam_ControlModes( struct termios      *pTransParam,
			         Type4Parity          Parity,
                                 Type4CharacterSize   CSize
                               )
{
  pTransParam->c_cflag = 0
    /*CBAUD - (poza normą POSIX) maska dla szybkości transmisji  */
    /*CBAUDEX - (poza normą POSIX) dodatkowa prędkość transmisji */
    | CS8 /*CSIZE - maska ilości bitów w znaku. Wartości to: CS5, CS6 CS7, CS8 */
    /* CSTOPB - dwa bity stopu */
    | CREAD  /* aktywuje odbiór */
    | (Parity != P_None ? PARENB : 0) /*ustawienie generowanie bitu parzystości 
                                                i jego kontrolę na wejściu */
    | (Parity == P_Odd ? PARODD : 0) /* Zamiast znacznika parzystości,
                                         generowany jest znacznik nieparzystości.
			               */
    /* HUPCL - sprowadza stan linii kontroli modemu do poziomu niskiego, gdy
           ostatni proces "zamyka" urządzenie. */
    | CLOCAL /* Ignoruje linie sterujące */
    | (Parity == P_Mark ? CMSPAR : 0 )
            /* (poza normą POSIX) Użyj znacznika parzystości. Jeśli będzie 
               ustawiony PARODD, to bit parzystości będzie miał zawsze wartość 1.
               W przypadku przeciwnym wartość 0. */
    /*CRTSCTS - (poza normą POSIX) uaktywniej sprzętową kontrolę przepływu RTS/CTS. */
    ;
}




void SetTransParam_LocalModes( struct termios *pTransParam )
{
  pTransParam->c_lflag = 0
    /* ISIG  - generuje odpowiednie sygnały (w sensie Uniksa) gdy odbierze
               znaki INTR, QUIT, SUSP lub DSUSP. */
    /* ICANON - uwaktywania tryb kanoniczny */
    /* ECHO - uaktywnia automatyczne echo dla odbieranego znaku */
    /* ECHOE - gdy ICANON jest ustawiona, to znak ERASE kasuje odebrany
               wcześniej znak, WERASE kasuje całe słowo. */
    /* ECHOK -  gdy ICANON jest ustawiona, to znak KILL kasuje całą 
                bieżącą linię */
    /* ECHONL - gdy ICANON jest ustawiona, to generowane jest echo znaku <NL>
               (nawet wtedy, gdy nie jest ustawione ECHO) */
    /* ECHOCTL - (poza normą POSIX) gdy jest ustawiona flaga ECHO, 
               to znaki, które są spoza ASCII są sygnalizowane jak ^X, 
               gdzie X jest kodem znaku                                */
    /* ECHOPRT - (poza normą POSIX) */
    /* ECHOKE - (poza normą POSIX) */
    | NOFLSH    /* uniemożliwia opróżnienie bufora wejściowego i wyjściowego, 
                gdy generowane są sygnały SIGINT, SIGQUIT i SIGSUSP */
    /* TOSTOP */
    /* IEXTEN */
    ;
}






/*!
 * Ustawianie parametrów transmisji
 */
bool SetTransParam( int                  PortDesc,
                    Type4BaudRate        BRate,
                    Type4Parity          Parity,
                    Type4CharacterSize   CSize
                  )
{
  struct termios   TransParam;


  SetTransParam_InputModes(&TransParam,Parity);
  SetTransParam_OutputModes(&TransParam);
  SetTransParam_ControlModes( &TransParam, Parity, CSize );
  SetTransParam_LocalModes(&TransParam);

  for (int i=0; i < NCCS; ++i) TransParam.c_cc[i] = 0;
  cfsetispeed(&TransParam,BRate);
  cfsetospeed(&TransParam,BRate);


  tcflush(PortDesc, TCIFLUSH); 
 
  return tcsetattr(PortDesc,TCSANOW,&TransParam) == 0;
}

