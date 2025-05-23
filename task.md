# Data
## Types
  - Stat
## Classes:
  - Warrior
    - Name
    - int atk_debuff
    - constexpr array<Stat,3> default_stats{ int, int, int } // Pos 0 = STRENGTH, 1 = DEFENSE and 2 = HEALTH
    - array<Stat,2> mut_stats{ int, int } // Position: 0 = Attack {(STRENGTH - atk_debuff) ∘ (Some relation to HEALTH,
for example if HEALTH at 20%, attack is also reduced to 20%)} and 1 = CUR_HEALTH (Current Health)
    - Methods:
      - void afflict (int QNT, type) 
         - match (type)
           - ATTACK: At enemy CUR_HEALTH: QNT - atk_debuff - ENEMY_DEFENSE
           - DEFEND: At ENEMY_atk_debuff for one round: +QNT
           - HEAL  : At self in CUR_HEALTH: +QNT
      - void reset_debuff()
  - Arena
    - list_of_warriors
    - Methods:
      - void Combat( while at least 1 alive )
        - Shuffle who goes first with RNG
        - Warrior::Afflict( WRNG, WRNG for Enum action)
        - reset_debuff() for list_of_warriors
  - Dice
    - Method:
        - int RNG (min, max) // Random Number Generator)
        - int WRNG (min, max, bias) // Weighted RNG
## Enum
  - action:
    - ATTACK
    - DEFEND
    - HEAL
  - player:
    - PONE
    - PTWO
# Main:
  1. Add warriors to Arena-> Warrior List
  1. Perhaps add animation around here and inside loop too (maybe)
  3. Arena->Combat()

