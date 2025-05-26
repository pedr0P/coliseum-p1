/*!
 * @file battle.h
 * @description Describes the signature of enums, classes, methods and functions for the game. 
 * @author Pedro V. B. Pereira
 * @date   May 25th, 2025.
*/

#include <array>
#include <string>

/** Unsigned Short for tracking stats. */
typedef unsigned short stat;

//== Enumerations
/** Enum to indicate which action to take.
 * ATTACK
 * DEFEND
 * HEAL
*/
enum action {
    ATTACK,
    DEFEND,
    HEAL
};

/** Enum to indicate which action to take. */
enum stat_fields {
    STRENGTH, /**< First field of stat_fields */
    DEFENSE, /**< Second field of stat_fields */
    HEALING, /**< Third field of stat_fields */
};

/** Enum to indicate which action to take. */
enum atk_stat {
    MISS, /**< No damage was done */
    HIT, /**< Damage was done */
    CRIT /**< Double damage was done */
};

/** Enum to indicate which whether Warrior is blocking */
enum def_stat {
    UNSET, /**< Did not try to block */
    NONE, /**< Tried to block and failed */
    PARTIAL, /**< Blocked half damage */
    FULL /**< Completely blocked damage */
};

/** Enum to indicate the player */
enum player {
    PONE, /**< Player One */
    PTWO /**< Player Two */
};

/** Enum that indicates a guaranteed FAIL or CRIT */
enum roll_status {
    NAT_FAIL = 1, /**< 1 */
    NAT_CRIT = 20 /**< 20 */
};

/** Enum that indicates TRUE or FALSE */
enum boolean {
    FALSE,
    TRUE
};


/** Enum to indicate column of scoreboard */
enum column {
    HUD_NAME, /**< First column */
    HUD_HEALTH, /**< Second column */
    HUD_LIFE_STATUS /**< Third column */
};

/** Warrior Class.
 * @brief A Class for all Warrior related data/manipulations.
*/
class Warrior {
public:
    /** Warrior's name.
     *  The name of the warrior set by user/main.
    */
    std::string name;

    /** Warrior's DEFENSE status.
     * Possible options:
     *   UNSET, NONE, PARTIAL, FULL.
    */
    def_stat block = UNSET;

    /** Warrior's Max Health.
     * Default set by main/user.
    */
    signed max_health{1};

    /** Warrior's Current Health.
     * Default set by Warrior's Max Health.
    */
    signed health;

    /** Warrior's Static Stats.
     * Static Stats: Strength, Defense, and Healing (All out of 5).
    */
    std::array<stat, 3> stat_stats;


    /** A middlepoint to other functions: attack, defend, or heal.
     * @param choice The ENUM: action.
     * @param target The address of a Warrior class.
     * @see attack(Warrior &target)
     * @see defend()
     * @see heal()
    */
    void afflict(action choice, Warrior &target);

    /** Execute an attack.
     * @detail Reduce the target's health. Can MISS, HIT or CRIT ( 2x the damage ).
     * @param target The adress of a Warrior class.
    */
    void attack(Warrior &target);

    /** Prepare for an attack.
     * @detail Reduce incoming damage. Potentially reduce damage by NONE, PARTIAL ( halve ), of FULL.
    */

    void defend();
    /** Heal self.
     * @detail Restore health. Always succeeds, but the amount restored is random.
    */
    void heal();

    /** Reset block action status.
     * @detail Sets block to UNSET.
    */
    void reset_defense();

    /** Output statuses.
     * @detail Show a table with NAME, HEALTH, and if ALIVE or DEAD.
    */
};

/** Arena Class.
 * @brief A Class for managing the "game".
*/
class Arena {
public:
    /** Array to store Warriors.
     * @brief An array containing the Warrior Class
    */
    std::array<Warrior*, 2> list_of_warriors;


    /** Output a scoreboard.
     * @detail Show a table with NAME, HEALTH, and if ALIVE or DEAD.
    */
    void scoreboard();

    /** Mediate the combat between Warriors.
     * @detail Randomly choose who goes first, randomly choose the attacks,
     check if an attack "killed" a Warrior, call scoreboard and reset defense.
    */
    void combat();
};

/** Function to report what happened.
 * @detail Send occurences to STDOUT.
 * @param output A string with what will be sent to STDOUT.
 * @param newline A boolean indicating if a newline should be included.
*/
void loglog(std::string output, boolean newline);

/** Random Number Generator
 * @detail Randomly generate a number in the indicated range.
 * @param min: Mininum value possible.
 * @param max: Maximum value possible.
 * @ret A random value between min and max.
*/
int RNG(int min, int max);
