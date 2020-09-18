# -SZE-MOSZE-2020-AMD_Bike

## Csapat tagjai: 
* Hajdu Norbert
* Skrapits Róbert Ágoston
* Gergály Szabolcs

## A feladat leírása:
A program indulásakor 6 paramétert szükséges megadni (természetesen ez a késõbbiekben bõvülhet, változhat). Elõször megadjuk a hõsünk, karakterünk nevét, életerejét, és sebzését, majd ugyanilyen sorrendben megtesszük ezt az ellenfél karakteréhez is. 
Példa egy ilyen bemenetre: Maple 150 10 Sally 45 30. Ezután körökre lebontva lefut a program, és a végén amelyik karakter elõször éri el a 0 életerõt, az veszít, a másik pedig gyõzedelmeskedik. 

### A program lefutását egy Character osztály és a main *Fight()* függvénye teszi lehetõvé:  
Az osztály 3 adattaggal rendelkezik, amelyek a karakterek nevét, életerejét és sebzését határozzák meg, ezeket a paramétereket a kód jelenlegi állapotában konstansra állítottuk be. 
Az osztály az adattagokon kívül kizárólag csak 3 konstans getter-rel és egy konstruktor-ral rendelkezik.
A programban a harc lefutását a main-ben egy *Fight()* fügvénnyel valósítottuk meg, amelyben vizsgáljuk a karakterek halálát (tehát, hogy az adott karakter elérte-e a 0 életerõt), illetve azt is, hogy a támadások egymás után következzenek (egyszer Maple üt, egyszer Sally).