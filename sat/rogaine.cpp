# include <iostream>
# include "checkpoint.h"
# include "team.h"
# include "rogaineEvent.h"
# include "graphConstructor.h"
# include "../adts/traversals.h"
# include "../time/time.h"

int main () {

    rogaineEvent rEvent(60 * 6);
    int scores[6 * 10];

    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 10; j++) {
            //rEvent.optimalRoute(team(1 + j * 0.1, i));
            std::cout << "team with walk speed " << 1 + 0.1 * j << " and in bracket " << i << '\n' << rEvent.optimalRoute(team(1 + 0.1 * j, i)) << '\n' << '\n';
        }
        std::cout << '\n' << '\n';
    }
    //std::cout << rEvent.optimalRoute(team(1 + 0.5, 0)) << '\n';
    std::string a;
    std::cin >> a;
}
