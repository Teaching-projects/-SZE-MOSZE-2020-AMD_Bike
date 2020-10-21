# -SZE-MOSZE-2020-AMD_Bike

## Csapat tagjai: 
* Hajdu Norbert
* Skrapits Róbert Ágoston
* Gergály Szabolcs

## A feladat leírása:
A program indulásakor 2 JSON kiterjesztésű fájl nevét szükséges megadni. Ezekben vannak meghatározva karaktereink adatai, azaz a nevük, az életerejük, a sebzésük és egy olyan paraméter mely az ütéseik között eltelt időt tárolja másodpercben, amiket beolvasunk a programba a fájlokból.<br/>
Például ezekben a fájlokban tárolt információk alapján az összecsapó két karakterünk: Luke Skywalker 2500 270 1.2 és Darth Vader 3800 440 3.2. Ezután az ütési gyorsaság figyelembe vételével egymást sebzi a két karakter és a végén amelyik karakter először éri el a 0 életerőt, az veszít, a másik pedig győzedelmeskedik. 

### A program lefutását egy Character osztály és a main *Fight()* függvénye teszi lehetővé:  
Az osztály 4 adattaggal rendelkezik, amelyek a karakterek nevét, életerejét, sebzését és a már említett paramétert határozzák meg, melyek közül a név, a sebzés és a paraméter konstans, mert ezek nem fognak változni a harc során sem.<br/> 
Az osztály az adattagokon kívül 4 konstans getter-rel, egy *DMGTaken()* függvénnyel, egy *IsDead()* függvénnyel, egy *pharseUnit()* és egy konstruktor-ral rendelkezik. Ezen függvények közül a *DMGTaken()* függvény negatív életerő kiküszöböléséért és a karakterek sebződéséért, míg a *IsDead()* a karakter halálának megállapításáért felelős.
A Character osztály *pharseUnit()* függvénye kizárólag csak a fájlból beolvasásért felelős.<br/>
A programban a harc lefutását a main-ben egy *Fight()* fügvénnyel valósítottuk meg, amelyben a karakterek támadásai az ütéseik gyorsaságának függvényében x időnként következnek be és vizsgáljuk a karakterek esetleges halálát a már említett *DMGTaken()* függvény meghívásával.<br/>
A *Units* könyvtárban találhatóak maguk a karakterek azaz unitok, szám szerint 3. <br/>
A *test.sh* shell script feladata hogy a 3 unitot (Yoda.json, Vader.yson, Luke.yson) mind a 6 lehetséges módon megütköztesse egymással (bár az ütések között eltelt időnek köszönhetően ritka, mikor a kimenetelt befolyásolja az, hogy ki indította a harcot). A diff parancs segítségével leellenőrzi, hogy a kapott eredmények megegyeznek-e a várt kimenettel, vagyis az *output.txt* megegyezik-e a *correct_output.txt*-ben tárolt adatokkal.

### Dokumentáció
https://teaching-projects.github.io/-SZE-MOSZE-2020-AMD_Bike/