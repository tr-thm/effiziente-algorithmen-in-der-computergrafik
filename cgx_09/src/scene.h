/**
 * Effiziente Algorithmen in der Computergrafik
 * Copyright (C) 2023 Tobias Reimann
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#pragma once
#include <string>
#include <vector>

#include "entity.h"

typedef bool (*Comparator)(Entity *a, Entity *b, int axis);

class Scene
{
    public:
        Scene(std::string filename);
        ~Scene();
        void update(const double time);
        void switchEntity();
        void switchCamera();

    private:
        std::vector<Entity*> entities;
        std::vector<Entity*> activeEntities;
        std::vector<Entity*> collidableEntities;

        std::vector<Entity*> sortedCollidableEntities[3];
        int selectedSortedAxis = 0;

        int activeEntity = -1;
        inline void sortEntities(std::vector<Entity*> &A);
        inline bool compareEntities(Entity *a, Entity *b);
        std::vector<std::pair<Entity*,Entity*>> sortAndSweep();
        inline std::vector<std::pair<Entity*,Entity*>> determineCollisions();
        void resolveCollisions(std::vector<std::pair<Entity*,Entity*>> &collisions, const double time);
};
