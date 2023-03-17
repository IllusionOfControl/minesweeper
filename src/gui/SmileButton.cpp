#include "SmileButton.hpp"

#define SQUARE_SIZE 32
#define SMILE_SMALL_INT_RECT(pos_x)  {pos_x * SQUARE_SIZE, 0 * SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE}
#define SMILE_LARGE_INT_RECT(pos_x)  {pos_x * SQUARE_SIZE * 2 + (SQUARE_SIZE * 5), 0 * SQUARE_SIZE, SQUARE_SIZE * 2, SQUARE_SIZE}

SmileButton::SmileButton(bool isSmall)
        : mIsSmall(isSmall)
        , mReaction(SmileReaction::SmileUsual) {

}

void SmileButton::setReaction(SmileButton::SmileReaction reaction) {
    mReaction = reaction;
    updateTexture();
}

void SmileButton::updateTexture() {
    if (mIsSmall)
        setTextureRect(SMILE_SMALL_INT_RECT(mReaction));
    else setTextureRect(SMILE_LARGE_INT_RECT(mReaction));
}
