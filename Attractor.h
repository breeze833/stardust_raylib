#ifndef _Attractor_h
#define _Attractor_h

#include <raylib.h>
#include <optional>
#include <cmath>

class Attractor {
public:
    virtual ~Attractor() = default;
    virtual const std::optional<Vector2> getPosition() const = 0;
    virtual void update() = 0;
};

class MouseAttractor : public Attractor {
public:
    virtual const std::optional<Vector2> getPosition() const override {
        return this->curPosition;
    }
    virtual void update() override {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            this->curPosition = GetMousePosition();
        } else {
            this->curPosition = std::nullopt;
	}
    }
private:
    std::optional<Vector2> curPosition;
};

class AutoAttractor : public Attractor {
public:
    AutoAttractor(int screenWidth, int screenHeight)
    : lastAppear(GetTime()), A(screenWidth/2), B(screenHeight/2), a(0.7), b(1.1), delta(M_PI/2) {}
    virtual const std::optional<Vector2> getPosition() const override {
        return lessajous();
    }
    virtual void update() override {
        this->lastAppear = GetTime();
    }
    const Vector2 lessajous() const;
private:
    double lastAppear;
    double A, B, a, b, delta; // parameters for Lissajous curve
};

#endif
