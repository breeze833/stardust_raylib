#ifndef _StardustApp_h
#define _StardustApp_h

#include <optional>
#include <vector>
#include <raylib.h>
#include "Attractor.h"

using namespace std;

typedef struct _Particle {
    Vector2 position;
    Vector2 velocity;
    Color color;
} Particle;

typedef struct _StardustAppConf {
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
} StardustAppConf;

class StardustApp {
public:
    StardustApp();
    ~StardustApp();
    bool init();
    void run();
    void update();
    void draw();
    void cleanup();
    StardustAppConf& getConfig() { return config; }

protected:
    Particle random_particle();
    void update_particle(Particle &p, float dt, const optional<Vector2> gravityPosition);
    void draw_connection(const Particle &p1, const Particle &p2);

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
    vector<Particle> particles;
    const Color clearColor;
    MouseAttractor *mouseGravity;
    AutoAttractor *autoGravity;
    double lastAttract;
};

#endif
