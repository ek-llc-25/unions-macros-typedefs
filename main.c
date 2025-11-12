#include <stdio.h>
#include "inventory.h"

#define SQUARE_BAD(x) ((x) * (x))

#define DEBUG_PRINT(var) \
    (do { \
        printf("DEBUG: %s = %d (line %d)\n", #var, var, __LINE__); \
     } while(0))

int main(void) {
    struct inv_item_t best_armor = create_armor(
        "This is not the best armor in the world, this is just a tribute",
        50,
        10'000);

    printf("Hvad hedder min armor? %s!\n", best_armor.name);

    // Her bruger jeg felterne i min tagged union direkte
    // Det er et problem hvis jeg gør det i en anden funktion
    // hvor jeg har glemt hvilken slags item det er.
    int prot = best_armor.data.as_armor.protection;
    printf("Den er så stærk her: %d\n", prot);

    struct armor_t *armor = get_armor_stats(&best_armor);
    if (armor != NULL) {
        printf("Den er så stærk her: %d\n", armor->protection);
    }

    struct inv_item_t inventory[] = {
        create_weapon("Iron Sword", 25, 100),
        create_armor("Leather Vest", 15, 80),
        create_life_potion(50, 3),
        create_life_potion(50, 3),
    };

    printf("=== Player Inventory ===\n");
    for (int i = 0; i < 4; i++) {
        print_item_info(inventory[i]);
        printf("\n");
    }

    int result1 = SQUARE_BAD(3 + 2); // 3 + 2 * 3 + 2 = 3 + (2 * 3) + 2 // UPS!
    printf("SQUARE_BAD(3 * 2) = %d\n", result1);

    int result2 = (SQUARE_BAD((3 + 2))); // (3 + 2) * (3 + 2) = 25
    printf("SQUARE_BAD((3 * 2)) = %d\n", result2);

    return 0;
}
