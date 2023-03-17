#ifndef MINESWEEPER_SMILEBUTTON_HPP
#define MINESWEEPER_SMILEBUTTON_HPP

#include "Button.hpp"

class SmileButton : public Button {
public:
    typedef std::shared_ptr<SmileButton> Ptr;

    enum SmileReaction {
        SmileUsual,
        SmileReveal,
        SmileClick,
        SmileWin,
        SmileLose,
    };

public:
    SmileButton(bool isSmall);

    void setReaction(SmileReaction reaction);

private:
    void updateTexture();

private:
    SmileReaction mReaction;
    bool mIsSmall;
};


#endif //MINESWEEPER_SMILEBUTTON_HPP
