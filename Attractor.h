#ifndef _Attractor_h
#define _Attractor_h

#include <raylib.h>
#include <optional>

using namespace std;

class Attractor {
public:
    virtual const optional<Vector2> getPosition() const = 0;
    virtual void update() = 0;
};

class MouseAttractor : public Attractor {
public:
    virtual const optional<Vector2> getPosition() const override {
        return this->curPosition;
    }
    virtual void update() override {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            this->curPosition = GetMousePosition();
        } else {
            this->curPosition = nullopt;
	}
    }
private:
    optional<Vector2> curPosition;
};

#endif
