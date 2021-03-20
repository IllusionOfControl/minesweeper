//
// Created by Illusion of control on 20.03.2021.
//

#ifndef MINESWEEPER_STATE_H
#define MINESWEEPER_STATE_H


class State {
public:
    virtual void Init() = 0;

    virtual void HandleInput() = 0;
    virtual void Update() = 0;
    virtual void Draw() = 0;
};


#endif //MINESWEEPER_STATE_H
