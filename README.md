# [![OXOcard][OXOcard_logo]][OXOcard]

## Intro
Du möchtest einmal hinter die Kulissen deines Computers oder Handys schauen und verstehen, wie alles funktioniert? Die OXOcard ist Teil eines Programmierkurses für Kids und Junggebliebene, welche gerne mit [Arduino][Arduino] programmieren lernen möchten.

## Installation
Eine ausführliche Installationsanleitung findest du auf unserer [Homepage][Installation].  
In dieser wird primär beschrieben, wie du die OXOcard mittels _Arduino Boards Manager_ deinen verfügbaren Boards hinzufügen kannst.

Möchtest du anschliessend einzelne Code-Teile der OXOcard anpassen, so kannst du die entsprechende Bibliothek (Library) von dieser oder nachfolgend beschriebenen Github-Seiten herunterladen und in deinen _Arduino/libraries_ Ordner verschieben.
Sobald die Files in deinem persönlichen _Arduino/libraries_ Ordner gefunden werden, werden diejenigen im OXOcard-Board-Packet ignoriert.

## Libraries
Die OXOcard besteht aus verschiedenen Hardware-Modulen, die mit nachfolgenden durch OXON entwickelten Bibliotheken angesteuert werden können:
* [Beschleunigungssensor][Accelerometer]
* [Bluetooth-Modul][BLE]
* [LED-Matrix][LED-Matrix]
* [LED-Matrix-Treiber][LED-Matrix_driver]
* [OXOcard][OXOcard_files]

Bei Änderungswünschen oder gefundenen Fehlern darf ohne Scheu ein Issue im entsprechenden Repository erstellt werden.
Wir werden versuchen, diese schnellstmöglich zu bearbeiten.

## Loslegen
Die einfachste Art die OXOcard nach der Installation anzusteuern, ist es das [OXOcardRunner.h-File][OXOcardRunner.h] in dein Arduino-Projekt einzubinden:
```Arduino
#include <OXOcardRunner.h>
```
Dieses stellt einfache Funktionen zur Verfügung, die ebenfalls auf unserer [Homepage][Referenzen] näher beschrieben sind.

Eine Alternative für Fortgeschrittene ist es, das [OXOcard.h-File][OXOcard.h] einzubinden und selbst ein OXOcard Objekt zu erzeugen. Dieses kann anschlissend verwendet werden um die einzelnen Hardware-Module direkt anzusteuern:
```Arduino
#include <OXOcard.h>

OXOcard myOXOcard;

myOXOcard.accel->...    // siehe Beschleunigungssensor-Funktionen
myOXOcard.ble->...      // siehe Bluetooth-Modul-Funktionen
myOXOcard.matrix->...   // siehe LED-Matrix-Treiber-Funktionen
```

Bibliotheken die so in ein Arduino-Projekt eingebunden werden, werden beim Upload automatisch mit kompiliert und auf die OXOcard hochgeladen.

Viel Spass beim Programmieren und Lernen!

[![Hello][OXOcard_gif]][OXOcard]

## License
This project is licensed under the terms of the [GNU Lesser General Public License][License].



[OXOcard_logo]:http://www.oxocard.ch/wp-content/uploads/2017/04/logo_oxocard_inverted.png
[OXOcard]:http://www.oxocard.ch/
[Arduino]:http://www.arduino.cc/
[Installation]:http://www.oxocard.ch/installation/
[Accelerometer]:https://github.com/oxon/dingg_lib_Accelerometer_MMA7660FC
[BLE]:https://github.com/oxon/dingg_lib_BLE_HM11
[LED-Matrix]:https://github.com/oxon/dingg_lib_LED-Matrix
[LED-Matrix_driver]:https://github.com/oxon/dingg_lib_LED-Matrix_driver_IS31FL3731
[OXOcard_files]:https://github.com/oxon/dingg_lib_OXOcard
[OXOcardRunner.h]:https://github.com/oxon/dingg_lib_OXOcard/blob/master/OXOcardRunner.h
[OXOcard.h]:https://github.com/oxon/dingg_lib_OXOcard/blob/master/OXOcard.h
[Referenzen]:http://www.oxocard.ch/oxocard-befehle/
[OXOcard_gif]:http://www.oxocard.ch/wp-content/uploads/2017/04/oxocard_animiert.gif
[License]:https://github.com/oxon/dingg_lib_OXOcard/blob/master/LICENSE
