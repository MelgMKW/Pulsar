#include <kamek.hpp>
#include <game/UI/Page/Other/FriendRoom.hpp>


namespace PulsarUI {

class ExpFroomMessages : public Pages::FriendRoomMessages {
public:
    static bool isOnModeSelection;
    void OnModeButtonClick(PushButton *button, u32 hudSlotId);
    void OnCourseButtonClick(PushButton *button, u32 hudSlotId);
};


}//namespace PulsarUI














