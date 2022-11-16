#include "wolf.h"
#include "sheep.h"
#include "grass.h"
#include "helper.h"

/**
 * TODO: TASK 4
 *
 * Place a copy of this Wolf onto nextGrid at the specified position.
 * You may implement this similar to Sheep::putSelf().
 */
void Wolf::putSelf(Grid *nextGrid, const int x, const int y)
{
    Wolf *wolf = new Wolf(*this);
    if (putAnimal(wolf, nextGrid, x, y))
    {
        setNextSelf(wolf);
    }
}

/**
 * TODO: TASK 4
 *
 * Place a brand new Wolf onto nextGrid at the specified position.
 * You may implement this similar to Sheep::putClone().
 */
void Wolf::putClone(Grid *nextGrid, const int x, const int y) const
{
    Wolf *wolf = new Wolf(getBoard());
    putAnimal(wolf, nextGrid, x, y);
}

/**
 * TODO: TASK 4
 *
 * Implement this function similar to Sheep::eat().
 * The only difference is that Wolf eats Sheep instead of Grass.
 */
void Wolf::eat(Grid *nextGrid)
{
    for (int i = 0; i < 9; ++i)
    {
        if (i == 4)
            continue;
        int adjX = getX() + getAdjX(i);
        int adjY = getY() + getAdjY(i);
        Entity *adjEntity = getBoard()->getGrid()->getCell(adjX, adjY);

        if (!adjEntity)
        {
            // Out of bounds or empty space, ignore
            continue;
        }
        if (typeid(*adjEntity) == typeid(Sheep))
        {
            if (!adjEntity->isRemoved())
            {

                adjEntity->removeSelf(nextGrid);
                setHungerCounter(WOLF_HUNGER_COOLDOWN);
                return;
            }
        }
    }
}

/**
 * TODO: TASK 4
 *
 * Implement this function similar to Sheep::breed().
 * The only difference is that Wolf breeds by finding a Wolf instead of Sheep.
 */
void Wolf::breed(Grid *nextGrid)
{
    for (int i = 0; i < 9; ++i)
    {
        if (i == 4)
            continue;
        int adjX = getX() + getAdjX(i);
        int adjY = getY() + getAdjY(i);
        Entity *adjEntity = getBoard()->getGrid()->getCell(adjX, adjY);

        if (!adjEntity)
        {
            // Out of bounds or empty space, ignore
            continue;
        }

        if (typeid(*adjEntity) == typeid(Wolf))
        {
            int randIndex = getRandomMovementIndex(nextGrid);
            if (randIndex != -1)
            {
                putClone(nextGrid, getX() + getAdjX(randIndex), getY() + getAdjY(randIndex));
                setBreedCounter(WOLF_BREED_COOLDOWN);
                return;
            }
        }
    }
}

/**
 * TODO: TASK 4
 *
 * If there is at least one Sheep on the board, Wolf tries to move towards it.
 *
 * You should loop over the board in the same order as Board calling update(),
 * calculate Euclidean distance to each cell containing a Sheep, and keep track of the shortest distance found.
 * Ignore sheeps that have been eaten (removed).
 * No need to keep track of Sheeps with the same distance as shortest one found so far.
 *
 * If a Sheep is found, move to the adjacent cell closest to that Sheep. If that cell is occupied with another Animal,
 * the Wolf stays at its position.
 *
 * If no Sheep is found, the Wolf moves randomly like a Sheep.
 *
 * You may follow the structure below to implement the function.
 */
void Wolf::move(Grid *nextGrid)
{
    // First, find a sheep to target

    // ?
    Grid *thisGrid = this->getBoard()->getGrid();
    Entity *targetSheep = nullptr;
    int shortestDistance = 100000;
    for (int x = 0; x < BOARD_SIZE_W; ++x)
    {
        for (int y = 0; y < BOARD_SIZE_H; ++y)
        {
            if (thisGrid->getCell(x, y) == nullptr)
            {
                continue;
            }
            Entity *thisEntity = thisGrid->getCell(x, y);
            if (typeid(*thisEntity) == typeid(Sheep))
            {
                if (thisEntity->isRemoved())
                {
                    continue;
                }
                else
                {
                    int distance = ((x - this->getX()) * (x - this->getX()) + (y - this->getY()) * (y - this->getY()));
                    if (distance < shortestDistance)
                    {
                        shortestDistance = distance;
                        targetSheep = thisEntity;
                    }
                }
            }
        }
    }
    if (targetSheep != nullptr)
    { // Edit this line with the appropriate condition
        // If a sheep with the closest distance is found, try to move towards it

        int newDistance = 100000;
        Entity *barrier = nullptr;
        Entity *barrier_ = nullptr;
        int _x = 0, _y = 0;
        for (int i = 0; i < 9; i++)
        {
            if (i == 4)
                continue;
            int adjX = getX() + getAdjX(i);
            int adjY = getY() + getAdjY(i);
            newDistance = ((adjX - targetSheep->getX()) * (adjX - targetSheep->getX()) + (adjY - targetSheep->getY()) * (adjY - targetSheep->getY()));
            if (newDistance < shortestDistance)
            {
                shortestDistance = newDistance;
                barrier = getBoard()->getGrid()->getCell(adjX, adjY);
                barrier_ = nextGrid->getCell(adjX, adjY);
                _x = adjX;
                _y = adjY;
            }
        }
        if (dynamic_cast<Animal *>(barrier))
        {
            // Adjacent cell is an animal, cannot move over
            putSelf(nextGrid, getX(), getY());
            return;
        }
        else if (dynamic_cast<Animal *>(barrier_))
        {
            // Adjacent cell in next grid has an animal, cannot move over
            putSelf(nextGrid, getX(), getY());
            return;
        }
        else
        {
            putSelf(nextGrid, _x, _y);
        }
    }
    else
    {
        // No sheep found, move randomly
        int randomIndex = getRandomMovementIndex(nextGrid);
        if (randomIndex != -1)
        {
            putSelf(nextGrid, getX() + getAdjX(randomIndex), getY() + getAdjY(randomIndex));
        }
        else
        {
            putSelf(nextGrid, getX(), getY());
        }

        // ?
    }
}