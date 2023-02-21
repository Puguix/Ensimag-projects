#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

int main(void)
{
    uint8_t age = 25;

    printf("Le capitaine a %u ans.\n", age);
    age++;
    printf("C'est son anniversaire! Il a maintenant %u ans.\n", age);
    age += 5;
    printf("5 ans plus tard, alors qu'il a %u ans, il tombe sur une potion de jouvence...\n", age);
    age--;
    printf("Boire cette potion le fait rajeunir d'un an! Il a maintenant %u ans.\n", age);
    printf("Il s'est mis à chercher d'autres potions de ce type, mais s'est arrêté quand il a eu le double de l'âge qu'il avait juste après avoir bu la première potion.\n");
    age *= 2;
    printf("Ca lui fait quel âge maintenant? Ah oui! %u ans.\n", age);
    printf("Il commence à se faire vieux, et regrette le temps où il avait le tiers de son âge.\n");
    age /= 3;
    printf("Un temps que les moins de 2 fois %u ans ne peuvent pas connaitre.\n", age);

    return EXIT_SUCCESS;
}
