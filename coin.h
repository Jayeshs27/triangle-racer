#if !defined(__COIN_H__)
#define __COIN_H__

#include "libraries.h"
#include "triangle_mesh.h"
#include "color.h"
#include "shaders.h"
#include "player.h"

class Coin{
    public:
        glm::vec3 translateVec;
        Coin(unsigned int lane);
        void draw(glm::vec3 &position, glm::vec3 &rotation, glm::vec3 &scale, glm::vec3 &camera_pos, glm::vec3 &camera_target,
            glm::vec3 &up, unsigned int &shader);
        ~Coin();
        bool is_player_collide(Player* player);
    private:
        std::vector<TriangleMesh *> CoinTriangles;
        unsigned int lane;
        float radius;
        void changeLane(unsigned int lane);
};


#endif // __COIN_H__
