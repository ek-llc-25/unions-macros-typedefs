#include <stdio.h>
#include "inventory.h"

int main(void) {
    struct inv_item_t best_armor = create_armor(
        "This is not the best armor in the world, this is just a tribute",
        50,
        10'000);
    printf("Hvad hedder min armor? %s!\n", best_armor.name);
    return 0;
}
