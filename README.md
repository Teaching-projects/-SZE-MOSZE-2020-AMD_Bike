# -SZE-MOSZE-2020-AMD_Bike

## Csapat tagjai: 
* Hajdu Norbert
* Skrapits R�bert �goston
* Gerg�ly Szabolcs

## A feladat le�r�sa:
A program indul�sakor 6 param�tert sz�ks�ges megadni (term�szetesen ez a k�s�bbiekben b�v�lhet, v�ltozhat). El�sz�r megadjuk a h�s�nk, karakter�nk nev�t, �leterej�t, �s sebz�s�t, majd ugyanilyen sorrendben megtessz�k ezt az ellenf�l karakter�hez is. 
P�lda egy ilyen bemenetre: Maple 150 10 Sally 45 30. Ezut�n k�r�kre lebontva lefut a program, �s a v�g�n amelyik karakter el�sz�r �ri el a 0 �leter�t, az vesz�t, a m�sik pedig gy�zedelmeskedik. 

### A program lefut�s�t egy Character oszt�ly �s a main *Fight()* f�ggv�nye teszi lehet�v�:  
Az oszt�ly 3 adattaggal rendelkezik, amelyek a karakterek nev�t, �leterej�t �s sebz�s�t hat�rozz�k meg, melyek k�z�l a n�v �s a sebz�s konstans, mert ezek nem fognak v�ltozni a harc sor�n sem. 
Az oszt�ly az adattagokon k�v�l 3 konstans getter-rel, egy *DMGTaken()* f�ggv�nnyel, *Dead()* f�ggv�nnyel �s egy konstruktor-ral rendelkezik. Ezen f�ggv�nyek k�z�l a *DMGTaken()* f�ggv�ny a karakterek sebz�d�s��rt, m�g a *Dead()* f�ggv�ny a negat�v �leter� kik�sz�b�l�s��rt felel�s.
A programban a harc lefut�s�t a main-ben egy *Fight()* f�gv�nnyel val�s�tottuk meg, amelyben vizsg�ljuk a karakterek hal�l�t (teh�t, hogy az adott karakter el�rte-e a 0 �leter�t), illetve azt is, hogy a t�mad�sok egym�s ut�n k�vetkezzenek (egyszer Maple �t, egyszer Sally).