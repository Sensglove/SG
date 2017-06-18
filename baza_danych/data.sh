#!/bin/bash
#przykladowe wywolanie programu:
#bash data 2017-06-18 
if [ -z "$1" ]
  then
    echo "Brak argumentu "; exit 1
  else
    path="$1"
fi

dir="$HOME/baza_danych"

wys=$(find $HOME/baza_danych -newermt "$1")

echo "$wys";
