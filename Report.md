# Tagok

| Név | Github azonosito  | Javasolt relatív érdemjegy | Becsült óra | Indoklás  | 
| --- | ---- | --- | ------------------ | --------- |
| Szabolcs Gergály | @Szabi1104 | -1 | 50-60 | Ami feladat rá volt bízva, azt megcsinálta, de a közös összeüléseket többször kihagyta. |
| Skrapits Róbert | @skrobi12 | +1 | 80-90 | Mindig ott volt a közös fejtöréseknél, egyéni feladatait is elátta. |
| Hajdu Norbert | @hajdunorbi | +1 | 80-90 | Mindent megcsinált, mindig lehetett rá számítani, szépen végezte a dolgát. |


# Videók

 - [Gameplay](/videos/gameplay.mp4)
 - [CodeBaseDefense](/videos/codebasedefense.mp4)

# Befejezett feladatok

| Feladat | Merge ideje a határidóhöz (nap) | Change request körök | Reviewer | 
| ------- | ------------------------------- | -------------------- | -------- |
| Feladat 1 | +7 | 3 | @hegyhati | 
| Feladat 2 | +7 | 2 | @hegyhati |
| jsonparser | +19  (késői review) | 3 | @wajzy |
| levelup | +11  (késői review) | 6 | @oliverosz |
| attackspeed | +5 | 1 | @vizvezetek |
| documentation | 0 | 1 | @Teaching-projects/segitseg  / @k-kristof, @kreutzoga |
| unittest | 0 | 1 | @Teaching-projects/segitseg  / @k-kristof, @kreutzoga |
| makefile | 0 | 1 | @hegyhati |
| refactor | +4 | 1 | @hegyhati |
| docker | -3 | 0 | @hegyhati |
| jsonpimp | Merge: 11.24 | 1 | @Teaching-projects/mortar_kombat / @gboldi19, @balazs482 |
| map | Merge: 11.25 | 0 | @Teaching-projects/mortar_kombat / @gboldi19, @balazs482 |
| game | Merge: 12.08 | 0 | @Teaching-projects/mortar_kombat  / @gboldi19, @balazs482 |
| defense | Merge: 11.24 | 0 | @Teaching-projects/mortar_kombat  / @gboldi19, @balazs482 |
| damage | Merge: 11.25 | 0 | @Teaching-projects/mortar_kombat  / @gboldi19, @balazs482  |
| markedmap | Merge: 12.08 | 0 | @Teaching-projects/mortar_kombat  / @gboldi19, @balazs482 |
| preparedgame | Merge: 12.08 | 0 | @Teaching-projects/mortar_kombat  / @gboldi19, @balazs482 |
| light radius | Merge: 12.08 | 0 | @Teaching-projects/mortar_kombat  / @gboldi19, @balazs482 |
| rendering | Merge: 12.10 | 0 | @Teaching-projects/amd_bike  / @skrobi12 , @hajdunorbi, @Szabi1104 (időhiány miatt) |

# Unit tesztek

| Osztály | Publikus metódusok száma | Unit tesztelt metódusok száma | Unit tesztek száma |
| --- | --- | --- | --- |
| `JSON` | 6 | 4 | 5 |
| `Monster` | 8 | 7 | 5 |
| `Hero` | 14 | 11 | 7 | 
| `Game` | 15 | 4 | 6 |
| `PreparedGame` | 3 | 0 | 0 |
| `Map` | 5 | 0 | 0 | 
| `MarkedMap` | 2 | 2 | 2 |  
| `Renderer` | 1 | 0 | 0 | 
| `TextRenderer` | 2 | 0 | 0 |
| `HeroTextRenderer` | 1 | 0 | 0 | 
| `ObserverTextRenderer` | 1 | 0 | 0 | 
| `SVGRenderer` | 1 | 0 | 0 |  
| `CharacterSVGRenderer` | 1 | 0 | 0 | 
| `ObserverSVGRenderer` | 1 | 0 | 0 | 

# Kód dokumentáció

| Teljesen dokumentált osztályok | Részben dokumentált osztályok | Nem dokumentált osztályok |
| --- | --- | --- | 
| `JSON` | ... | ... | 
| `Hero` | ... | ... | 
| `Monster` | ... | ... | 
| `Game` | ... | ... | 
| `PreparedGame` | ... | ... |
| `Map` | ... | ... | 
| `MarkedMap` | ... | ... |  
| `Renderer` | ... | ... | 
| `TextRenderer` | ... | ... | 
| `HeroTextRenderer` | ... | ... | 
| `ObserverTextRenderer` | ... | ... |
| `SVGRenderer` | ... | ... | 
| `CharacterSVGRenderer` | ... | ... | 
| `ObserverSVGRenderer` | ... | ... | 

# Mindenféle számok

 - Összes cpp kódsor : 1092
 - Egyéb kódsor (make,doxyfile,shellscript, ...) : 2851
 - cppcheck
   - warning : 0
   - style : 9
   - performance : 0
   - unusedFunction : 1
   - missingInclude : 1
 
# Implicit megtanult dolgok
Olyanok, amik nem a tárgy anyaga, de muszáj/hasznos volt elsajátítani:
 - alapvető shell/python scripting
 - `std::variant`
 - rendering
 - parsing
 - import images to svg
 - get template
 - using cmd arguments
 - `std::filesystem`
 - ...

# Feedback (optional)
 
Legélvezetesebbnek a képek svg-be importálását találtuk, leghasznosabbnak pedig a shell scriptekkel való megismerkedést, illetve a unittestek és makefile használatát.
A shell scripteknél tanultakat fel tudtuk használni más tárgyaknál.
Az online videós oktatás szerintünk kifejezetten kedvező volt, mert így mindenki akkor szentelhetett rá időt amikor a legjobb volt neki, illetve a nehezebben érthető dolgokat egyből újra megtudtuk tekinteni.

# Üzenet a jövőbe (optional)

Bár kötelezővé nem lehet tenni, de szerintünk fel lehetett volna hívni a figyelmet arra, hogy a VS Code-ra átálljanak az emberek első héttől fogva. Első hetekben nekünk nehézségek voltak az alap VS és a github összehangolásával.
A belefektetett óraszámokat, folyamatos készüléseket illetve más tárgyak követelményeit figyelembe véve pedig a 3 kreditet minimálisan kevesteltük.
