#include <kamek.hpp>
#include <Pulsar.hpp>

#define speedFactor 1.5f //a value of 1 is normal 150cc
#define CHECK_200 RaceData::sInstance->racesScenario.settings.engineClass == CC_100 && Pulsar::sInstance->Has200cc()
