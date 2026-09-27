#ifndef MINESWEEPER_SMILEBUTTON_HPP
#define MINESWEEPER_SMILEBUTTON_HPP

#include <memory>
#include "Button.hpp"

class SmileButton : public Button {
public:
    using Ptr = std::shared_ptr<SmileButton>;

    enum SmileReaction {
        SmileUsual,
        SmileReveal,
        SmileClick,
        SmileWin,
        SmileLose,
    };

    explicit SmileButton(bool isSmall);

    void setReaction(SmileReaction reaction);
    SmileReaction getReaction() const noexcept;
    bool isSmall() const noexcept;

private:
    void updateTexture();

    SmileReaction mReaction;
    bool mIsSmall;
};

#endif // MINESWEEPER_SMILEBUTTON_HPP
