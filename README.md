ChamberCrawler3000
------------------

ChamberCrawler3000 (CC3k) is a simplified rogue-like (a genre of video game based upon the game Rogue -
http://en.wikipedia.org/wiki/Rogue_(video_game)

## Game

### Commands

- `no`, `so`, `ea`, `we`, `ne`, `nw`, `se`, `sw`: moves the player in the specified direction
- `u <direction>`: uses the potion indicated by the direction (e.g. `no`, `so`, ...)
- `a <direction>`: attack the enemy in the specified direction, if the enemy is in the
  immediately specifed block
- `k`, `w`, `s`: specifies the race the player wishes to be when starting a game
- `q`: exits the game
- `r`: restarts the game
- `stopwander`: stops all enemy movement
- `stopdeath`: Player becomes immortal

### Races
The player is denoted by the '@' symbol and is a valiant human adventurer of one of the following classes:
- Knight: 100 HP, 50 Atk, 50 Def
- Wizard: 60 HP, 25 Atk, 0 Def, has a powerful long-range attack, able to hit the first unit in a straight line in front of him
- Samurai: 80 HP, 50 Atk, 15 Def, who can go unnoticed by the denizens of the dungeon until he attacks an enemy

### Enemies

| Enemy    | Display |  HP | Atk | Def |  Item Dropped |         Special Abilities        |
|----------|:-------:|:---:|:---:|:---:|:-------------:|:--------------------------------:|
| GridBug  |    X    |  50 |  20 |  10 | Random Potion | Cannot move or attack diagonally |
| Goblin   |    g    |  75 |  30 |  20 |   Gold Pile   |         Can drink potions        |
| Merchant |    M    | 100 |  75 |  5  |   Gold Pile   |     Ignores player by default    |
| Orc      |    O    | 120 |  30 |  30 |   Gold Pile   |               None               |
| Dragon   |    D    | 150 | 50  | 10  |      None     |       Guards a Dragon Hoard      |

### Items

#### Potions

Positive Potions:
- Restore health (RH): increase HP by 30 (cannot exceed maximum prescribed by race)
- Boost Atk (BA): increase ATK by 10
- Boost Def (BD): increase Def by 10

Negative Potions:
- Poison health (PH): decrease HP by 15 (cannot fall below 0 HP)
- Wound Atk (WA): decrease Atk by 5
- Wound Def (WD): decrease Def by 5

#### Treasure

Treasure in CC3k consists only of gold. Gold comes in two forms but is always denoted '$' on the map. Treasure is accumulated with the 'u' command OR by simply walking onto it
- Gold Pile: This gives the player +10 gold when picked up.
- Dragon Hoard: This gives the player +50 gold when picked up, but cannot be picked up until the dragon is slain.
