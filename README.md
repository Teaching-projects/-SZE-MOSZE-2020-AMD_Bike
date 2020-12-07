# -SZE-MOSZE-2020-AMD_Bike

## Csapat tagjai: 
* Hajdu Norbert
* Skrapits Róbert Ágoston
* Boja Richard

## A feladat leírása:
A feladatunk egy RPG játék létrehozása volt. Az említett játék ebben a végleges formájában úgy működik, hogy az általunk készített program üdvözli a felhasználót, majd ezután lehetősege nyílik kiválasztania a játék nehézségét.<br/>
A nehézségi szint megadása után pedig további lehetősegként megadható, hogy egy előre létrehozott pályán játszhassunk **PreparedGame**, vagy pedig mi magunk szeeretnénk összerakni azt **CustomGame**

##PreparedGame

####markedmap.txt

```
##############
# H #  ####  #
# ####22##  #
# 12# 3##  #
###1# ##  #
#     1   #
#########
```

####Jelmagyarázat

- `#` a falat jelöli
- `H` a Hősünket jelöli, akit mozgatni fogunk
- `1`, `2`, `3` pedig a különböző típusú szörnyeket jelöli, akikkel a Hősünk megküzd a játék során

####Nehézségi szintek:

- `Normal`: (Normál) A felhasználó/játékos az előre elkészített pálya egészét látja, így pontosan tisztában van azzal, hogy éppen milyen típusú szörnyek várnak rá, és hova kell lépnie, hogy azokat elkerülje
- `Hard`: (Nehéz) A felhasználó/játékos már nem a pálya egészét, hanem a Hősének megfelelő távolságra lát el, ami szintlépésenkként egy adott értékkel nő.

####Hős mozgatása

A nehézségi szint kiválasztása után elindul a játék, ahol a fent látható pálya alapján kirajzolódik a térkép, és elkezdhetjük irányítani Hősünket az égtájak megadásával, amiket angolul kell megadni `north`, `south`, `west`, `east`.
Ha szörny mezőre lépünk, a csata megkezdődik, melynek során Hősünkek lehetősége nyílik tapasztalatot szerezni a kiosztott sebzés mértékében. Amennyiben túléli a csatát tovább folytathatja harcát mindaddig, míg el nem fogynak a szörnyek a pályáról, vagy a hősünk meg nem hal. </br>
természetesen minél több szörnnyel küzdünk meg annál több szintet lépünk, és erőnk, azaz a Hős statisztikája is ennek fügvényében változik.

###Inputok
A korábban említett `markedmap.txt`-t illetve a rajta elhelyezkedő Hőst, illetve szörnyeket egy `[prepared]game.json` fogja tárolni, ahonnan minden szükséges információt kinyerünk. Ilyen adatok például a Hős sebzése, életereje, stb...

####[prepared]game.json

```json
  "map": "markedmap.txt",
  "hero": "Hero.json",
  "monster-1": "Troll.json",
  "monster-2": "Goblin.json",
  "monster-3": "WolfRider.json",
  "wall_texture" : "Wall.jpg",
  "free_texture" : "Free.jpg"
```

Tehát ahogyan azt említettük, a `markedmap.txt`-ben lévő `H`-t, illetve `számokat` a `[prepared]game.json`-ből kiolvasott json-őkből nyerjük ki, ahol minden létező adatot megtalálhatunk, ami a játék futásához szükséges.  

####hero.json
A hero.json a következőképpen néz ki:

```json
{
  "name": "Prince Aidan of Khanduras",
  "base_health_points": 30,
  "base_damage": 3,
  "base_magical_damage": 1,
  "base_defense": 2,
  "base_attack_cooldown": 1.1,
  "experience_per_level": 20,
  "health_point_bonus_per_level": 5,
  "damage_bonus_per_level": 1,
  "magical_damage_bonus_per_level": 1,
  "defense_bonus_per_level": 1,
  "cooldown_multiplier_per_level": 0.9,
  "light_radius": 2,
  "light_radius_bonus_per_level": 1,
  "texture": "Hero.jpg"
}
```

####Adatok:
- Név (_name_)
- Életerő - (_base_health_points_)
- Sebzés - (_damage_) (opcionális - alapértelmezetten 0)
- Varázs sebzés - (_magical_damage_) (opcionális - alapértelmezetten 0)
- Védelem - (_defense_)
- Két ütés között eltelt idő - (_base_attack_cooldown_)
- Tapasztalat szintlépéskor (_experience_per_level_)
- Életerő növekedése szintlépéskor - (_health_point_bonus_per_level_)
- Sebzés növekedése szintlépéskor - (_damage_bonus_per_level_) (opcionális - alapértelmezetten 0)
- Varázs sebzés növekedése szintlépéskor - (_magical_damage_bonus_per_level_) (opcionális - alapértelmezetten 0)
- Védelem növekedése szintlépéskor - (_defense_bonus_per_level_)
- Két ütés között eltelt idő csökkenése szintlépéskor - (_cooldown_multiplier_per_level_)
- Látó távolság - (_light_radius_)
- Látó távolság növekedése szintlépéskor - (_light_radius_bonus_per_level_) (alapértelmezetten 1)
- Kép - (_texture_)

####Goblin.json
Példa egy monsterre:
```json
{
  "name": "Fallen",
  "health_points": 4,
  "damage": 1,
  "magical_damage": 5,
  "defense": 2,
  "attack_cooldown": 1.6,
  "lore": "The Fallen Ones (a.k.a. the Fallen), and formally known as Namus Improbus are a race of demons.",
  "additional_info": "May be resurrected by a Shaman.", 
  "texture": "Monster1.jpg"
}
```

####Adatok:
- Név (_name_)
- Életerő - (_base_health_point_)
- Sebzés - (_damage_) (opcionális - alapértelmezetten 0)
- Varázs sebzés - (_magical_damage_) (opcionális - alapértelmezetten 0)
- Két ütés között eltelt idő - (_attack_cooldown_)
- Védelem - (_defense_)
- Kép - (_texture_)

##CustomGame
Hasonlóan a **PreparedGame**-hez, először itt is ki kell választania a felhasználónak a **Nehézségi szintet**, majd ezután a számok segítségével ki tudjuk választani melyik pályán szeretnénk játszani.</br>
Ezután kiválaszthatjuk, hogy melyik Hősel szeretnénk játszani, illetve az a pályán hol helyezkedjen el (természetesen egyszerre csak egy hős lehet a pályán...). 
Természetesen a szörnyeket is hasonlóképpen kell kiválasztani egy listából, és megadni azokat a koordinátákat, ahol szeretnénk, hogy legyenek a játék indulásakor. </br>
Fontos megjegyezni, hogy több szörny lehet egy mezőn, illetve a szörnyeket és a hőst tehetjük azonos mezőre. Ebben az esetben a játék úgy indul, hogy megküzdünk az összes olyan szörnnyel, amelyik a Hősünk koordinátáin helyezkedik el.

A **Nehézségi szinteken** kívül a Hős mozgatása is teljesen ugyanúgy működik mint a **Preparedgame**-nél.

###Inputok
A Hős és szörnyek megadása pontosan úgy történik, ahogyan a **Preparedgame**-nél. Viszont a térkép megadása üresen történik.

####Map1.json
Példa egy ilyen üres map-re:
```json
{
##############
#   #  ####  #
# ####  ##  #
#   #  ##  #
### # ##  #
#        #
#########
}
```

##Output
A fent említett két futtatási módban, azaz a **CustomGame** és a **[prepared]game.json** módban az output ugyan olyan módon jelenik meg, mely lehet parancsosorn kirajzolás szimbólumokkal és képekkel történő svg fájlba importálás egyaránt.<br/> 
Ezek a kiíratások természetesen a nehézségi szintet figyelmbe véve máshogy jelennek meg. <br/>

####Parancssori kirajzolás
Példa egy parancssori kirajzolásra amikor a hős az egész térképet látja:
```
╔════════════════════════════╗
║████████████████████████████║
║██MM░░┣┫██░░░░████████░░░░██║
║██░░████████░░░░████░░░░████║
║██M░░░MM██░░░░████░░░░██████║
║██████░░██░░████░░░░████████║
║██░░░░M░░░M░░░░░M░██████████║
║████████████████████████████║
╚════════════════════════════╝
```
Illetve egy példa arra, amikor a játék nehezítve van:
```
╔════════╗
║██░░░░░░║
║██░░████║
║██┣┫░░MM║
║██████░░║
║██░░░░M░║
╚════════╝
```

####SVG fájlba inportálás
Példa, mikor az egész térkép látható:
![ Példa, mikor az egész térkép látható: ](/test/examples/Observer.JPG?raw=true "Példa, mikor az egész térkép látható:")
Illetve, mikor csak egy része:
![ Illetve, mikor csak egy része: ](/test/examples/Caharcter.JPG?raw=true "Illetve, mikor csak egy része:")
##Scenarió

###Input
Ez esetben, ahogy neve is utal rá egy 'scenario' -t adunk a programnak parancssori argumentumként, mely tartalmazza a hőst, illetve szörnyek egy listáját, melyeket hősünk a megadott sorrendben megpróbál legyőzni.<br/>
Egy ilyen 'scenario' input a következőképpen néz ki:

####scenario1.json
```json
{
  "hero": "Dark_Wanderer.json",
  "monsters": [
    "Fallen.json",
    "Fallen.json",
    "Zombie.json",
    "Fallen.json",
    "Fallen.json",
    "Zombie.json",
    "Fallen.json",
    "Blood_Raven.json"
  ]
}
```

###Output
Abban az esetben, ha a játékot 'scenario' -val futtatjuk a parancsosri argumentumon keresztül, akkor az output az egyes csaták kimenetelét, illetve a végleges kimenetelt jeleníti meg szövegesen, mely a következő képpen néz ki a 'test/scenarios/scenario1' felhasználásával: <br/>

####scenario1_output.txt
```txt
Prince Aidan of Khanduras(1) vs Fallen
Prince Aidan of Khanduras(1) vs Fallen
Prince Aidan of Khanduras(1) vs Zombie
Prince Aidan of Khanduras(1) vs Fallen
Prince Aidan of Khanduras(2) vs Fallen
Prince Aidan of Khanduras(2) vs Zombie
Prince Aidan of Khanduras(2) vs Fallen
Prince Aidan of Khanduras(3) vs Blood Raven
The hero won.
Prince Aidan of Khanduras: LVL8
   HP: 62/65
  DMG: physical 10, magical 8
  ACD: 0.526127

```

### Dokumentáció
https://teaching-projects.github.io/-SZE-MOSZE-2020-AMD_Bike/