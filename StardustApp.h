#ifndef _StardustApp_h
#define _StardustApp_h

#include <optional>
#include <vector>
#include <memory>
#include <raylib.h>
#include "Attractor.h"

struct Particle {
    Vector2 position;
    Vector2 velocity;
    Color color;
};

struct StardustAppConf {
    int screenWidth;
    int screenHeight;
    int FPS;
    float radius;
    int numParticles;
    float connectionThreshold;
    float gravityStrength;
    float minVelocity;
    float damping;
    unsigned char trailAlpha;
    double autoGravityInterval;
};

class StardustApp {
public:
    StardustApp();
    ~StardustApp();
    bool init();
    void run();
    void cleanup();
    StardustAppConf& getConfig() { return config; }

protected:
    void update();
    void draw() const;
    Particle random_particle() const;
    void update_particle(Particle &p, float dt, const std::optional<Vector2> gravityPosition) const;
    void draw_connection(const Particle &p1, const Particle &p2) const;

private:
    StardustAppConf config = {
      .screenWidth = 800,
      .screenHeight = 480,
      .FPS = 60,
      .radius = 3.0f,
      .numParticles = 50,
      .connectionThreshold = 100.0f,
      .gravityStrength = 10000.0f,
      .minVelocity = 50.0f,
      .damping = 0.998f,
      .trailAlpha = 20,
      .autoGravityInterval = 15.0,
    };
    std::vector<Particle> particles;
    const Color clearColor;
    std::unique_ptr<Attractor> mouseGravity;
    std::unique_ptr<AutoAttractor> autoGravity;
    double lastAttract;
};

#endif
