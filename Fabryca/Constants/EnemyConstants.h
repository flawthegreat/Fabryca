#ifndef EnemyConstants_h
#define EnemyConstants_h

#include "Foundation.h"
#include "Utility/NumericAttribute.h"

#include <vector>
#include <string>


const std::vector<std::string> possibleNames = {
    "Lueacybdvwfoi",
    "Lvomyoe",
    "Cewdohygai",
    "Uhyhzqeemxcy",
    "Ggukybtybxicxvrk",
    "Heqbpzgoeivfygpi",
    "Ftgyycxrrxgiq",
    "Fmevjli",
    "Mwcbfhuzil",
    "Hbijbyewexr",
    "Xehoayntsup",
    "Jemvtkjwmn",
    "Uknehuguswmiv",
    "Aajuiiipagze",
    "Yxcujaxjmcbw",
    "Mister Morgan",
    "Eayezaqy",
    "Oopcavkkx",
    "Yshhvoaxaokjfvbi",
    "Lijdspdpk",
    "Dtvfaejeaki",
    "Eagjcofszkzboom",
    "Niqcpzeyxroiinua",
    "Zedscnei",
    "Bjqmeiijhl",
    "Nlbygawuo",
    "Zizswlaxdv",
    "Vhaipqev",
    "Vljtxxvjodh",
    "Gmrmudy",
    "Oxiayoxbuwldohrv",
    "Hofbfyboiwog",
    "Fjzqsrhhyni",
    "Wpsnpqlqsozscv",
    "Xoijvyz",
    "Ciiqdyygwlhif",
    "Hisljuka",
    "Wqrkyaifujnort",
    "Aemuuuuigls",
    "Yhtryngaq",
    "Yczoeroxo",
    "Zoosvsv",
    "Skeahpyeh",
    "Uezprtxoaso",
    "Bgpelgacuy",
    "Daoygyhjvqavhpu",
    "Xcnqmncayhgmigm",
    "Pstqtalu",
    "Abseetpxlihqeu",
    "Fhzrkeriyknrqpu",
    "Uazmtuqbhxmi",
    "Osdsbeoaviiisc"
};


std::vector<std::vector<std::vector<NumericAttribute>>> parameters = {
    // (health range, attack damage range}
    {                                                                // Forest demon
        { { 15, 30 }, { 5, 10 } },       // weak
        { { 31, 72 }, { 12, 28 } },      // dangerous
        { { 80, 117 }, { 36, 49 } }      // superior
    },
    {                                                                // Hovering beast
        { { 20, 36 }, { 4, 6 } },        // weak
        { { 37, 78 }, { 8, 20 } },       // dangerous
        { { 86, 130 }, { 21, 35 } }      // superior
    },
    {                                                                // Poisonous monster
        { { 10, 20 }, { 4, 8 } },        // weak
        { { 24, 40 }, { 10, 24 } },      // dangerous
        { { 62, 90 }, { 30, 42 } }       // superior
    }
};


#endif /* EnemyConstants_h */
