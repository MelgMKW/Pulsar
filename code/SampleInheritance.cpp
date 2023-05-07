/*
//.hpp
#include <PulsarSystem.hpp>

class MyPack : public Pulsar::System {
public:
    MyPack(const Binary *bin, EGG::ExpHeap *heap): System(bin, heap), myVariable(50) {}; //MAKE SURE TO CALL PULSAR's CTOR
    static System *Create(const Binary *bin, EGG::ExpHeap *heap); //My Create function, needs to return Pulsar
    static MyPack *GetSInstance(){return (MyPack*)sInstance;} //for ease of use, optional

//From there, anything is possible
private:
    int myVariable;
    //if you want to inherit settigns for your own fields; don't forget to call the base init settings
    void InitSettings(const u16 *totalTrophyCount) override;

};

//.cpp
Pulsar::System *MyPack::Create(const Binary *bin, EGG::ExpHeap *heap) {
    return new MyPack(bin, heap); //now Pulsar::sInstance is of type MyPack
}
Pulsar::System::Inherit Test(MyPack::Create); //Create a Inherit that'll get called back by Pulsar::CreatePulsar

*/