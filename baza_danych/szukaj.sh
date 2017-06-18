#!/bin/bash
#przykladowe wywolanie programu:
#bash szukaj 1 Dorota 1_RuchB  
if [ -z "$1" ]
  then
    echo "Brak argumentu "; exit 1
  else
    path="$1"
fi

dir="$HOME/baza_danych"

wys=$(find $HOME/baza_danych -name "$1")

#2>/dev/null

echo "$wys";
