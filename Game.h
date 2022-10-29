#pragma once
#include <vector>
#include "Bag.h"
#include "Reserve.h"
#include "Actions.h"
#include "Action.h"
#include "PlayerSheet.h"
#include "Discard.h"
#include "Dice.h"

struct Game {
    Dice dice;
    Bag bag;
    Reserve reserve;
    Discard discard;
    std::vector<PlayerSheet> players;
    int playerShift{};

    void Init(int nplayers);

    bool TakeFromBag(int n);

    bool PlayNumber(int n);

    bool PlayColor(Colours color);

    bool PlayStars(int n, bool restToBag);

    void PrintBag();

    void PrintReserve();

    void PrintDiscard();

    int nextPlayer();

    PlayerSheet& currentPlayer();

    Actions ActionsForCurrentPlayer();

    bool DoAction(Action& action);


};