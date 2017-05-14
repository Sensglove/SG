#ifndef ODBIERANIE_HH
#define ODBIERANIE_HH


#include <string>

bool RS232_Odbierz( int            DeskPortu, 
                    std::string   &Bufor, 
                    unsigned int   IloscZnakow,
                    unsigned int   CzasOczekiwania_ms = 2000
		  );


#endif
