 
<?php

?>

<link rel="stylesheet" href="form.css" type="text/css">
<div class="body-content">
  <div class="module">
<div class="rezz">
    <center><h1 style="font-size: 40px">SensGlove    </h1>
          Projekt budowy stanowiska do pomiaru sygnałów z dłoni i biosygnałów <br>

          </center>
</div>

    <div class="rezz">
       <ul class="tab-group">
        <li class="tab"><a href="index.php" style="width:17.4%">Co robimy?</a></li>
       <li class="tab"><a href="team.php" style="width:17.4%">Team</a></li>
      <li class="tab"><a href="galery.php" style="width:17.4%">Zdjęcia</a></li>
        <li class="tab"><a href="movies.php" style="width:17.4%">Filmy</a></li>
        <li class="tab "><a href="https://github.com/Sensglove/SG" style="width:17.4%">GitHub</a></li>
      </ul>


<center><h1 > O projekcie </h1></center>
 <p style="text-align: justify">Strona ta przedstawia efekty pracy nad projektem zespołowym realizowanym w ramach zajęć na 6. semestrze na specjalności Robotyka, kierunek Automatyka i Robotyka, wydział Elektroniki Politechniki Wrocławskiej.
 </p>

<br><br>
<div class="rez">
 Data rozpoczęcia projektu: 03/2017r.<br>
 Data zakończenia projketu: 22/06/2017r.<br>
</div>


<center><h1 > Rękawiczka sensoryczna </h1></center>
 <p style="text-align: justify"> Na rozciągliwej rękawiczce sportowej zamocowane zostało 10 rezystancyjnych czujników nacisku w miejscach, które najczęściej są w kontakcie z chwytanym przedmiotem) oraz 5 czyjników zgięcia (po jednym na każdy palec). Czujniki umiejscowione są w takki sposób, aby jak najmniej krępować ruchy.
 </p>
 <center><h1 > Interfejs sprzętowy </h1></center>
 <p style="text-align: justify"> Sygnały wychodzące z czujników rekawiczki oraz z elektrod do pomiaru biosygnałów są pierwotnie wzmacniane przez zaprojektowany przez nas układ wzmacniaczy operacyjnych i podawane na wejścia mikrokontrolera STM32F4 skonfigurowane jako kanały przetwornika analogowo-cyfrowego. Są odczytywane, zamieniane na wiadomość, która jest wysyłana przez USB do komputera.
 </p>
 <center><h1 > Oprogramowanie </h1></center>
 <p style="text-align: justify"> Na oprogramowanie składają się dwa elementy.
 Program SENSGLOVE_data_acqusition umożliwia odczytywanie danych wysyłanych przez mikrokontroler oraz wykonywanie pomiarów, które mogą być zapisywane do bazy danych. Dodatkowo możliwe jest uruchomienie programu, który wizualizuje dane z czujników rękawiczki. Dane z czujników nacisku przedstawiane są w postaci zmieniających kolor punktów oraz wykresów, natomiast informacja sensoryczna z czujników zgięcia przedstawiona jest na wykresach oraz na modelu 3D dłoni. Działanie programów przedstawiono w sekcji Zdjęcia i Filmy.
 </p>
 

<br>
<br>
  <center>
  <h1 style="font-size: 10px">
   © SensGlove Group at Politechnika Wrocławska. All rights reserved.
           </h1>
          </center>
      </div>

  </div>


</div>
