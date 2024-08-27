#include "pch.h"
#include <assert.h>
#include "gui.h"
#include <Events.h>
#include "imgui/imgui.h"
#include <cWeaponSelectMenu.h>
#include <PlayerManagerImplement.h>
#include <string>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <random>
#include <Trigger.h>
#include <GameMenuStatus.h>
#include <Pl0000.h>
#include <EntitySystem.h>
#include <Entity.h>
#include <cGameUIManager.h>
#include "cSlowRateManager.h"
#include <AnimationMapManagerImplement.h>
#include "KeyBinds.h"
#include "KeyBind.h"
#include <Windows.h>
#include <WinUser.h>
#include <shared.h>
#include <Hw.h>
#include "d3dx9.h"
#include "cWeaponSelectMenu.h"
#include "cObj.h"
#include <BehaviorEmBase.h>
#include <EmBaseDLC.h>
#include "IniReader.h"
#include <iostream>
#include <sstream>
#include <XInput.h>
#include <format>

using namespace std;
#pragma comment(lib, "d3dx9.lib")

DWORD dwResult;
XINPUT_STATE state;
bool IsButtonPressed(const std::string& button)
{
	XINPUT_STATE state;
	DWORD dwResult = XInputGetState(0, &state);

	if (dwResult == ERROR_SUCCESS)
	{
		if (button == "XINPUT_GAMEPAD_A" && (state.Gamepad.wButtons & XINPUT_GAMEPAD_A) != 0)
			return true;
		else if (button == "XINPUT_GAMEPAD_B" && (state.Gamepad.wButtons & XINPUT_GAMEPAD_B) != 0)
			return true;
		else if (button == "XINPUT_GAMEPAD_X" && (state.Gamepad.wButtons & XINPUT_GAMEPAD_X) != 0)
			return true;
		else if (button == "XINPUT_GAMEPAD_Y" && (state.Gamepad.wButtons & XINPUT_GAMEPAD_Y) != 0)
			return true;
		else if (button == "XINPUT_GAMEPAD_LEFT_SHOULDER" && (state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) != 0)
			return true;
		else if (button == "XINPUT_GAMEPAD_RIGHT_SHOULDER" && (state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) != 0)
			return true;
		else if (button == "XINPUT_GAMEPAD_BACK" && (state.Gamepad.wButtons & XINPUT_GAMEPAD_BACK) != 0)
			return true;
		else if (button == "XINPUT_GAMEPAD_START" && (state.Gamepad.wButtons & XINPUT_GAMEPAD_START) != 0)
			return true;
		else if (button == "XINPUT_GAMEPAD_LEFT_THUMB" && (state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB) != 0)
			return true;
		else if (button == "XINPUT_GAMEPAD_RIGHT_THUMB" && (state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB) != 0)
			return true;
		else if (button == "XINPUT_GAMEPAD_DPAD_UP" && (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP) != 0)
			return true;
		else if (button == "XINPUT_GAMEPAD_DPAD_DOWN" && (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN) != 0)
			return true;
		else if (button == "XINPUT_GAMEPAD_DPAD_LEFT" && (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT) != 0)
			return true;
		else if (button == "XINPUT_GAMEPAD_DPAD_RIGHT" && (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) != 0)
			return true;
		else if (button == "XINPUT_GAMEPAD_LEFT_THUMB_UP" && state.Gamepad.sThumbLY > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
			return true;
		else if (button == "XINPUT_GAMEPAD_LEFT_THUMB_DOWN" && state.Gamepad.sThumbLY < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
			return true;
		else if (button == "XINPUT_GAMEPAD_LEFT_THUMB_LEFT" && state.Gamepad.sThumbLX < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
			return true;
		else if (button == "XINPUT_GAMEPAD_LEFT_THUMB_RIGHT" && state.Gamepad.sThumbLX > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
			return true;
		else if (button == "XINPUT_GAMEPAD_RIGHT_THUMB_UP" && state.Gamepad.sThumbRY > XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
			return true;
		else if (button == "XINPUT_GAMEPAD_RIGHT_THUMB_DOWN" && state.Gamepad.sThumbRY < -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
			return true;
		else if (button == "XINPUT_GAMEPAD_RIGHT_THUMB_LEFT" && state.Gamepad.sThumbRX < -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
			return true;
		else if (button == "XINPUT_GAMEPAD_RIGHT_THUMB_RIGHT" && state.Gamepad.sThumbRX > XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
			return true;
		else if (button == "VK_PAD_LTRIGGER" && state.Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
			return true;
	}

	return false;
}

int requestAnimationByMap2(Behavior* behavior, int a2, int a3, float a4, float a5, float a6, float a7, float a8)
{
    return ((int(__thiscall*)(Behavior * behavior, int a2, int a3, int a4, float a5, float a6, float a7, float a8))(shared::base + 0x6A4080))(behavior, a2, a3, a4, a5, a6, a7, a8);
}

void AnimationPlayer(Behavior* behavior, float a2, float a3)
{
    ((void(__thiscall*)(Behavior * behavior, float a2, float a3))(shared::base + 0x794790))(behavior, a2, a3);
}

void AnimationStop(Behavior* behavior, int a2, float a3)
{
    ((void(__thiscall*)(Behavior * behavior, int a2, float a3))(shared::base + 0x694BC0))(behavior, a2, a3);
}

void requestAnimation(Behavior* self, int id, int a3, float fInterpolation, float a5, int nFlags, float fStartFrame, float a8)
{
    ((void(__thiscall*)(Behavior*, int, int, float, float, int, float, float))(shared::base + 0x6A4080))(self, id, a3, fInterpolation, a5, nFlags, fStartFrame, a8);
}

int MGR_PlaySound(const char* se, int a2)
{
    return ((int(__cdecl*)(const char* se, int a2))(shared::base + 0xA5E050))(se, a2);
}
void __cdecl Se_PlayEvent(const char* event)
{
    ((void(__cdecl*)(const char*))(shared::base + 0xA5E1B0))(event);
}

static const char* GetAnimationNameById(void* pAnimUnit, int animId)
{
	return ((const char* (__thiscall*)(void*, int))(shared::base + 0x4D7D70))(pAnimUnit, animId);
}

static unsigned int ReadSinglePointer(unsigned int baseAddress, unsigned int offset) noexcept
{
    return injector::ReadMemory<unsigned int>(baseAddress + offset, true);
}

std::random_device rd;
std::mt19937 gen(rd());
#ifdef _MSC_VER < 1700 //pre 2012
#pragma comment(lib,"Xinput.lib")
#else
#pragma comment(lib,"Xinput9_1_0.lib")
#endif

CIniReader iniReader("Keysanims.ini");
std::string KeyForDodge = iniReader.ReadString("Keys", "KeyForDodge", "45");
std::string KeyForBladeMode = iniReader.ReadString("Keys", "KeyForBladeMode", "09");
std::string xinputl1asstring = iniReader.ReadString("Controller Buttons", "XINPUT_GAMEPAD_LEFT_SHOULDER", "XINPUT_GAMEPAD_LEFT_SHOULDER");
std::string xinputl3asstring = iniReader.ReadString("Controller Buttons", "XINPUT_GAMEPAD_LEFT_THUMB", "XINPUT_GAMEPAD_LEFT_THUMB");
std::string xinputtriangleasstring = iniReader.ReadString("Controller Buttons", "XINPUT_GAMEPAD_Y", "XINPUT_GAMEPAD_Y");
std::string xinputbasstring = iniReader.ReadString("Controller Buttons", "XINPUT_GAMEPAD_B", "XINPUT_GAMEPAD_B");
std::string xinputxasstring = iniReader.ReadString("Controller Buttons", "XINPUT_GAMEPAD_X", "XINPUT_GAMEPAD_X");
std::string xinputaasstring = iniReader.ReadString("Controller Buttons", "XINPUT_GAMEPAD_A", "XINPUT_GAMEPAD_A");
std::string xinputl2asstring = iniReader.ReadString("Controller Buttons", "VK_PAD_LTRIGGER", "VK_PAD_LTRIGGER");
std::string xinputlthumbup = iniReader.ReadString("Controller Buttons", "XINPUT_GAMEPAD_LEFT_THUMB_UP", "XINPUT_GAMEPAD_LEFT_THUMB_UP");
std::string xinputlthumbdown = iniReader.ReadString("Controller Buttons", "XINPUT_GAMEPAD_LEFT_THUMB_DOWN", "XINPUT_GAMEPAD_LEFT_THUMB_DOWN");
std::string xinputlthumbleft = iniReader.ReadString("Controller Buttons", "XINPUT_GAMEPAD_LEFT_THUMB_LEFT", "XINPUT_GAMEPAD_LEFT_THUMB_LEFT");
std::string xinputlthumbright = iniReader.ReadString("Controller Buttons", "XINPUT_GAMEPAD_LEFT_THUMB_RIGHT", "XINPUT_GAMEPAD_LEFT_THUMB_RIGHT");

int AnimationAmount = iniReader.ReadInteger("Animations", "AnimationAmount", 0);

std::string Key = iniReader.ReadString("Animation 1", "Key", "0");
std::string AnimationAction = iniReader.ReadString("Animation 1", "AnimationAction", "0");
int AnimationMapID = iniReader.ReadInteger("Animation 1", "AnimationMapID", 4);
bool AirCondition = iniReader.ReadBoolean("Animation 1", "AirAnimation", false);
bool AirAnimation = iniReader.ReadBoolean("Animation 1", "AirAnimation", false);
int AttackSlot = iniReader.ReadInteger("Animation 1", "AttackSlot", 0);

std::string Key2 = iniReader.ReadString("Animation 2", "Key", "0");
std::string AnimationAction2 = iniReader.ReadString("Animation 2", "AnimationAction", "0");
int AnimationMapID2 = iniReader.ReadInteger("Animation 2", "AnimationMapID", 4);
bool AirAnimation2 = iniReader.ReadBoolean("Animation 2", "AirAnimation", false);
int AttackSlot2 = iniReader.ReadInteger("Animation 2", "AttackSlot", 0);

std::string Key3 = iniReader.ReadString("Animation 3", "Key", "0");
std::string AnimationAction3 = iniReader.ReadString("Animation 3", "AnimationAction", "0");
int AnimationMapID3 = iniReader.ReadInteger("Animation 3", "AnimationMapID", 4);
bool AirAnimation3 = iniReader.ReadBoolean("Animation 3", "AirAnimation", false);
int AttackSlot3 = iniReader.ReadInteger("Animation 3", "AttackSlot", 0);

std::string Key4 = iniReader.ReadString("Animation 4", "Key", "0");
std::string AnimationAction4 = iniReader.ReadString("Animation 4", "AnimationAction", "0");
int AnimationMapID4 = iniReader.ReadInteger("Animation 4", "AnimationMapID", 4);
bool AirAnimation4 = iniReader.ReadBoolean("Animation 4", "AirAnimation", false);
int AttackSlot4 = iniReader.ReadInteger("Animation 4", "AttackSlot", 0);

std::string Key5 = iniReader.ReadString("Animation 5", "Key", "0");
std::string AnimationAction5 = iniReader.ReadString("Animation 5", "AnimationAction", "0");
int AnimationMapID5 = iniReader.ReadInteger("Animation 5", "AnimationMapID", 4);
bool AirAnimation5 = iniReader.ReadBoolean("Animation 5", "AirAnimation", false);
int AttackSlot5 = iniReader.ReadInteger("Animation 5", "AttackSlot", 0);

std::string Key6 = iniReader.ReadString("Animation 6", "Key", "0");
std::string AnimationAction6 = iniReader.ReadString("Animation 6", "AnimationAction", "0");
int AnimationMapID6 = iniReader.ReadInteger("Animation 6", "AnimationMapID", 4);
bool AirAnimation6 = iniReader.ReadBoolean("Animation 6", "AirAnimation", false);
int AttackSlot6 = iniReader.ReadInteger("Animation 6", "AttackSlot", 0);

std::string Key7 = iniReader.ReadString("Animation 7", "Key", "0");
std::string AnimationAction7 = iniReader.ReadString("Animation 7", "AnimationAction", "0");
int AnimationMapID7 = iniReader.ReadInteger("Animation 7", "AnimationMapID", 4);
bool AirAnimation7 = iniReader.ReadBoolean("Animation 7", "AirAnimation", false);
int AttackSlot7 = iniReader.ReadInteger("Animation 7", "AttackSlot", 0);

std::string Key8 = iniReader.ReadString("Animation 8", "Key", "0");
std::string AnimationAction8 = iniReader.ReadString("Animation 8", "AnimationAction", "0");
int AnimationMapID8 = iniReader.ReadInteger("Animation 8", "AnimationMapID", 4);
bool AirAnimation8 = iniReader.ReadBoolean("Animation 8", "AirAnimation", false);
int AttackSlot8 = iniReader.ReadInteger("Animation 8", "AttackSlot", 0);

std::string Key9 = iniReader.ReadString("Animation 9", "Key", "0");
std::string AnimationAction9 = iniReader.ReadString("Animation 9", "AnimationAction", "0");
int AnimationMapID9 = iniReader.ReadInteger("Animation 9", "AnimationMapID", 4);
bool AirAnimation9 = iniReader.ReadBoolean("Animation 9", "AirAnimation", false);
int AttackSlot9 = iniReader.ReadInteger("Animation 9", "AttackSlot", 0);

std::string Key10 = iniReader.ReadString("Animation 10", "Key", "0");
std::string AnimationAction10 = iniReader.ReadString("Animation 10", "AnimationAction", "0");
int AnimationMapID10 = iniReader.ReadInteger("Animation 10", "AnimationMapID", 4);
bool AirAnimation10 = iniReader.ReadBoolean("Animation 10", "AirAnimation", false);
int AttackSlot10 = iniReader.ReadInteger("Animation 10", "AttackSlot", 0);

int framespassed = 0;
int curranim = 0;
bool animationcanbeplayed = false;
bool animationisntplayable = false;

bool CurrentAnimationCurrentlyCancelable(string curranim_as_string, int framespassed)
{
    CIniReader iniReader("animations.ini");
    bool IsCancelable = iniReader.ReadBoolean(curranim_as_string, "IsCancelable", "true");
    int CancelableFramesStart = iniReader.ReadInteger(curranim_as_string, "CancelableFramesStart", 0);
    int CancelableFramesEnd = iniReader.ReadInteger(curranim_as_string, "CancelableFramesEnd", 0);
    if (IsCancelable)
    {
        if (CancelableFramesStart <= 0)
        {
            if ((CancelableFramesEnd <= 0) // Cancelable until a point, currently cancelable
				|| (CancelableFramesEnd >= framespassed))
                return true;
        }
        else if (CancelableFramesStart <= framespassed)
        {
            if ((CancelableFramesEnd <= 0)                  // Cancelable after a point  
                || (CancelableFramesEnd >= framespassed))
				 // Cancelable only in a certain range
                return true;
        }

        return false; // While the animation is cancelable, the timing isn't currently right
    }

    return false; // Uncancelable animations
}

static auto prevAnim = 0;
bool keypressed1 = false;
bool inp = false;
int anim = 0;
int attack = 1;
bool buttonpressed = false;
bool buttonpressed2 = false;
int prevanim = 0;
bool blademode = false;
int i = 0;

class RAIDEN {
public:
    RAIDEN()
    {

        Events::OnTickEvent.before += []() {
            auto player = cGameUIManager::Instance.m_pPlayer;
            if (player)
                prevAnim = ReadSinglePointer(player->field_774, 0x14);
            };

        Events::OnTickEvent.after += []() {
            Pl0000* player = cGameUIManager::Instance.m_pPlayer;
            
			if (player)
			{
				if (inp)
				{
					requestAnimationByMap2(player, anim, 0, 0.0f, 1.0f, 0x8100000, -1.0f, 1.0f);
					AnimationPlayer(player, 1.0, 1.0);
					inp=false;
				}
				if ((shared::IsKeyPressed(std::stoi(Key, nullptr, 16), true)) || (IsButtonPressed(xinputl1asstring) && IsButtonPressed(xinputl3asstring) && attack == AttackSlot))
				{
					if (!buttonpressed)
					{
						if (!Trigger::StaFlags.STA_QTE
							&& !Trigger::GameFlags.GAME_DEPRESSSION_RAIDEN
							&& !Trigger::StaFlags.STA_PAUSE
							&& !Trigger::GameFlags.GAME_PLAYER_ATTACK_OFF
							&& !player->isCodecTalk()
							&& !player->isBladeModeActive()
							&& player->getCurrentAction() != 0x13D
							&& player->getCurrentAction() != 0x13F
							&& player->getCurrentAction() != 0x13E
							&& !animationisntplayable
							&& animationcanbeplayed)
						{
							if (player->isInAir() == AirAnimation)
							{
									player->setState(std::stoi(AnimationAction, nullptr, 16), 0, 0, 0);
									anim = AnimationMapID;
									framespassed = 0;
									inp = true;
							}
						}
					}
					buttonpressed=true;
				}
				else
					buttonpressed=false;
				if ((shared::IsKeyPressed(std::stoi(Key2, nullptr, 16), true)) || (IsButtonPressed(xinputl1asstring) && IsButtonPressed(xinputl3asstring) && attack == AttackSlot2))
				{
					if (!buttonpressed)
					{
						if (!Trigger::StaFlags.STA_QTE
							&& !Trigger::GameFlags.GAME_DEPRESSSION_RAIDEN
							&& !Trigger::StaFlags.STA_PAUSE
							&& !Trigger::GameFlags.GAME_PLAYER_ATTACK_OFF
							&& !player->isCodecTalk()
							&& !player->isBladeModeActive()
							&& player->getCurrentAction() != 0x13D
							&& player->getCurrentAction() != 0x13F
							&& player->getCurrentAction() != 0x13E
							&& !animationisntplayable
							&& animationcanbeplayed)
						{
							if (player->isInAir() == AirAnimation2)
							{
									player->setState(std::stoi(AnimationAction2, nullptr, 16), 0, 0, 0);
									anim = AnimationMapID2;
									framespassed = 0;
									inp = true;
							}
						}
					}
					buttonpressed = true;
				}
				else
					buttonpressed = false;
				if ((shared::IsKeyPressed(std::stoi(Key3, nullptr, 16), true)) || (IsButtonPressed(xinputl1asstring) && IsButtonPressed(xinputl3asstring) && attack == AttackSlot3))
				{
					if (!buttonpressed)
					{
						if (!Trigger::StaFlags.STA_QTE
							&& !Trigger::GameFlags.GAME_DEPRESSSION_RAIDEN
							&& !Trigger::StaFlags.STA_PAUSE
							&& !Trigger::GameFlags.GAME_PLAYER_ATTACK_OFF
							&& !player->isCodecTalk()
							&& !player->isBladeModeActive()
							&& player->getCurrentAction() != 0x13D
							&& player->getCurrentAction() != 0x13F
							&& player->getCurrentAction() != 0x13E
							&& !animationisntplayable
							&& animationcanbeplayed)
						{
							if (player->isInAir() == AirAnimation3)
							{
									player->setState(std::stoi(AnimationAction3, nullptr, 16), 0, 0, 0);
									anim = AnimationMapID3;
									framespassed = 0;
									inp = true;
							}
						}
					}
					buttonpressed = true;
				}
				else
					buttonpressed = false;
				if ((shared::IsKeyPressed(std::stoi(Key4, nullptr, 16), true)) || (IsButtonPressed(xinputl1asstring) && IsButtonPressed(xinputl3asstring) && attack == AttackSlot4))
				{
					if (!buttonpressed)
					{
						if (!Trigger::StaFlags.STA_QTE
							&& !Trigger::GameFlags.GAME_DEPRESSSION_RAIDEN
							&& !Trigger::StaFlags.STA_PAUSE
							&& !Trigger::GameFlags.GAME_PLAYER_ATTACK_OFF
							&& !player->isCodecTalk()
							&& !player->isBladeModeActive()
							&& player->getCurrentAction() != 0x13D
							&& player->getCurrentAction() != 0x13F
							&& player->getCurrentAction() != 0x13E
							&& !animationisntplayable
							&& animationcanbeplayed)
						{
							if (player->isInAir() == AirAnimation4)
							{
									player->setState(std::stoi(AnimationAction4, nullptr, 16), 0, 0, 0);
									anim = AnimationMapID4;
									framespassed = 0;
									inp = true;
							}
						}
					}
					buttonpressed = true;
				}
				else
					buttonpressed = false;
				if ((shared::IsKeyPressed(std::stoi(Key5, nullptr, 16), true)) || (IsButtonPressed(xinputl1asstring) && IsButtonPressed(xinputl3asstring) && attack == AttackSlot5))
				{
					if (!buttonpressed)
					{
						if (!Trigger::StaFlags.STA_QTE
							&& !Trigger::GameFlags.GAME_DEPRESSSION_RAIDEN
							&& !Trigger::StaFlags.STA_PAUSE
							&& !Trigger::GameFlags.GAME_PLAYER_ATTACK_OFF
							&& !player->isCodecTalk()
							&& !player->isBladeModeActive()
							&& player->getCurrentAction() != 0x13D
							&& player->getCurrentAction() != 0x13F
							&& player->getCurrentAction() != 0x13E
							&& !animationisntplayable
							&& animationcanbeplayed)
						{
							if (player->isInAir() == AirAnimation5)
							{
									player->setState(std::stoi(AnimationAction5, nullptr, 16), 0, 0, 0);
									anim = AnimationMapID5;
									framespassed = 0;
									inp = true;
							}
						}
					}
					buttonpressed = true;
				}
				else
					buttonpressed = false;
				if ((shared::IsKeyPressed(std::stoi(Key6, nullptr, 16), true)) || (IsButtonPressed(xinputl1asstring) && IsButtonPressed(xinputl3asstring) && attack == AttackSlot6))
				{
					if (!buttonpressed)
					{
						if (!Trigger::StaFlags.STA_QTE
							&& !Trigger::GameFlags.GAME_DEPRESSSION_RAIDEN
							&& !Trigger::StaFlags.STA_PAUSE
							&& !Trigger::GameFlags.GAME_PLAYER_ATTACK_OFF
							&& !player->isCodecTalk()
							&& !player->isBladeModeActive()
							&& player->getCurrentAction() != 0x13D
							&& player->getCurrentAction() != 0x13F
							&& player->getCurrentAction() != 0x13E
							&& !animationisntplayable
							&& animationcanbeplayed)
						{
							if (player->isInAir() == AirAnimation6)
							{
									player->setState(std::stoi(AnimationAction6, nullptr, 16), 0, 0, 0);
									anim = AnimationMapID6;
									framespassed = 0;
									inp = true;
							}
						}
					}
					buttonpressed = true;
				}
				else
					buttonpressed = false;
				if ((shared::IsKeyPressed(std::stoi(Key7, nullptr, 16), true)) || (IsButtonPressed(xinputl1asstring) && IsButtonPressed(xinputl3asstring) && attack == AttackSlot7))
				{
					if (!buttonpressed)
					{
						if (!Trigger::StaFlags.STA_QTE
							&& !Trigger::GameFlags.GAME_DEPRESSSION_RAIDEN
							&& !Trigger::StaFlags.STA_PAUSE
							&& !Trigger::GameFlags.GAME_PLAYER_ATTACK_OFF
							&& !player->isCodecTalk()
							&& !player->isBladeModeActive()
							&& player->getCurrentAction() != 0x13D
							&& player->getCurrentAction() != 0x13F
							&& player->getCurrentAction() != 0x13E
							&& !animationisntplayable
							&& animationcanbeplayed)
						{
							if (player->isInAir() == AirAnimation7)
							{
									player->setState(std::stoi(AnimationAction7, nullptr, 16), 0, 0, 0);
									anim = AnimationMapID7;
									framespassed = 0;
									inp = true;
							}
						}
					}
					buttonpressed = true;
				}
				else
					buttonpressed = false;
				if ((shared::IsKeyPressed(std::stoi(Key8, nullptr, 16), true)) || (IsButtonPressed(xinputl1asstring) && IsButtonPressed(xinputl3asstring) && attack == AttackSlot8))
				{
					if (!buttonpressed)
					{
						if (!Trigger::StaFlags.STA_QTE
							&& !Trigger::GameFlags.GAME_DEPRESSSION_RAIDEN
							&& !Trigger::StaFlags.STA_PAUSE
							&& !Trigger::GameFlags.GAME_PLAYER_ATTACK_OFF
							&& !player->isCodecTalk()
							&& !player->isBladeModeActive()
							&& player->getCurrentAction() != 0x13D
							&& player->getCurrentAction() != 0x13F
							&& player->getCurrentAction() != 0x13E
							&& !animationisntplayable
							&& animationcanbeplayed)
						{
							if (player->isInAir() == AirAnimation8)
							{
									player->setState(std::stoi(AnimationAction8, nullptr, 16), 0, 0, 0);
									anim = AnimationMapID8;
									framespassed = 0;
									inp = true;
							}
						}
					}
					buttonpressed = true;
				}
				else
					buttonpressed = false;
				if ((shared::IsKeyPressed(std::stoi(Key9, nullptr, 16), true)) || (IsButtonPressed(xinputl1asstring) && IsButtonPressed(xinputl3asstring) && attack == AttackSlot9))
				{
					if (!buttonpressed)
					{
						if (!Trigger::StaFlags.STA_QTE
							&& !Trigger::GameFlags.GAME_DEPRESSSION_RAIDEN
							&& !Trigger::StaFlags.STA_PAUSE
							&& !Trigger::GameFlags.GAME_PLAYER_ATTACK_OFF
							&& !player->isCodecTalk()
							&& !player->isBladeModeActive()
							&& player->getCurrentAction() != 0x13D
							&& player->getCurrentAction() != 0x13F
							&& player->getCurrentAction() != 0x13E
							&& !animationisntplayable
							&& animationcanbeplayed)
						{
							if (player->isInAir() == AirAnimation9)
							{
									player->setState(std::stoi(AnimationAction9, nullptr, 16), 0, 0, 0);
									anim = AnimationMapID9;
									framespassed = 0;
									inp = true;
							}
						}
					}
					buttonpressed = true;
				}
				else
					buttonpressed = false;
				if ((shared::IsKeyPressed(std::stoi(Key10, nullptr, 16), true)) || (IsButtonPressed(xinputl1asstring) && IsButtonPressed(xinputl3asstring) && attack == AttackSlot10))
				{
					if (!buttonpressed)
					{
						if (!Trigger::StaFlags.STA_QTE
							&& !Trigger::GameFlags.GAME_DEPRESSSION_RAIDEN
							&& !Trigger::StaFlags.STA_PAUSE
							&& !Trigger::GameFlags.GAME_PLAYER_ATTACK_OFF
							&& !player->isCodecTalk()
							&& !player->isBladeModeActive()
							&& player->getCurrentAction() != 0x13D
							&& player->getCurrentAction() != 0x13F
							&& player->getCurrentAction() != 0x13E
							&& !animationisntplayable
							&& animationcanbeplayed)
						{
							if (player->isInAir() == AirAnimation10)
							{
									player->setState(std::stoi(AnimationAction10, nullptr, 16), 0, 0, 0);
									anim = AnimationMapID10;
									framespassed = 0;
									inp = true;
							}
						}
					}
					buttonpressed = true;
				}
				else
					buttonpressed = false;
				if (blademode 
					&& framespassed>3)
				{
					Trigger::GameFlags.GAME_ZANGEKIMODE=false;
					blademode=false;
				}
                curranim = ReadSinglePointer(player->field_774, 0x14);
                string curranim_as_string = to_string(curranim); 
				animationcanbeplayed = CurrentAnimationCurrentlyCancelable(curranim_as_string, framespassed);
                framespassed++;
				for (auto i = (Entity**)EntitySystem::Instance.m_EntityList.m_pFirst; i != (Entity**)EntitySystem::Instance.m_EntityList.m_pEnd; i = (Entity**)i[2])
				{
					Entity* entity = *i;
					if (!entity) {
						continue;
					}
					BehaviorEmBase* Enemy = (BehaviorEmBase*)entity->m_pInstance;
					if (entity->m_nEntityIndex == 0x20310)
					{
						if (Enemy->getCurrentAction() == 0x3000D 
							|| Enemy->getCurrentAction() == 0x10006 
							|| Enemy->getCurrentAction() == 0x30012)
							animationisntplayable=true;
						else
							animationisntplayable=false;
					}
				}
				if (IsButtonPressed(xinputl3asstring) 
					&& IsButtonPressed(xinputbasstring)
					&& (!player->isBladeModeActive()))
				{
					if (!buttonpressed)
					{
						MGR_PlaySound("core_se_sys_decide_l", 0);
						if (attack < AnimationAmount)
							attack++;
						else
							attack = 1;
					}
					buttonpressed=true;
				}
				else
					buttonpressed=false;
                if (prevAnim != ReadSinglePointer(player->field_774, 0x14) 
					&& ReadSinglePointer(player->field_774, 0x14) != 1092 
					&& ReadSinglePointer(player->field_774, 0x14) != 1093)
                    framespassed = 0;
                if (player->getCurrentAction() == 0x77 
					|| ReadSinglePointer(player->field_774, 0x14) == 310 
					|| player->getCurrentAction() == 0x6E)
                {
                    if (shared::IsKeyPressed(std::stoi(KeyForDodge, nullptr, 16), true) 
						|| (IsButtonPressed(xinputxasstring) 
						&& IsButtonPressed(xinputaasstring)))
                        player->setState(0x63, 0, 0, 0);

                    if (shared::IsKeyPressed(std::stoi(KeyForBladeMode, nullptr, 16), true) 
						|| IsButtonPressed(xinputl2asstring))
                    {
						framespassed = 0;
						player->setState(0x0, 0, 0, 0);
						Trigger::GameFlags.GAME_ZANGEKIMODE=true;
						blademode=true;
                    }
                }
				
				
                if (framespassed == 900)
                {
					if (player->getCurrentAction() == 0)
					{
						player->setState(0x3, 0, 0, 0);
						anim = 1229;
						inp = true;
					}
                    framespassed = 0;
                }
				if (player->getCurrentAction() == 0xD0)
				{
					if (shared::IsKeyPressed(0x57, true) 
						|| shared::IsKeyPressed(0x53, true) 
						|| shared::IsKeyPressed(0x41, true) 
						|| shared::IsKeyPressed(0x44, true) 
						|| IsButtonPressed(xinputlthumbup) 
						|| IsButtonPressed(xinputlthumbleft) 
						|| IsButtonPressed(xinputlthumbdown) 
						|| IsButtonPressed(xinputlthumbright))
					{
						if (!buttonpressed2)
						framespassed = framespassed + 33;

						buttonpressed2=true;
					}
					else
						buttonpressed2=false;
					if (framespassed > 200)
						player->setState(0, 0, 0, 0);

				}
            }
            };
    }
}_RAIDEN;

double dValue = 1.0;
float fValue = static_cast<float>(dValue);
class Plugin
{
public:
	static inline void InitGUI()
	{
		Events::OnDeviceReset.before += gui::OnReset::Before;
		Events::OnDeviceReset.after += gui::OnReset::After;
		Events::OnEndScene += gui::OnEndScene;
		/* // Or if you want to switch it to Present
		Events::OnPresent += gui::OnEndScene;
		*/
	}

	Plugin()
	{
		InitGUI();

		// and here's your code
	}
} plugin;
/*
bool value3 = true;
bool bShowGUI2 = false;
*/
void gui::RenderWindow()
{/**
	if (shared::IsKeyPressed(0x4A, false))
		bShowGUI2 ^= true;
	if (bShowGUI2)
	{
		Trigger::StpFlags.STP_MOUSE_UPDATE = 1;
		keypressed1 = true;
		ImGui::Begin("Action Viewer Menu");
		{
			if (ImGui::BeginTabBar("NOTITLE", ImGuiTabBarFlags_NoTooltip))
			{

				if (ImGui::BeginTabItem("CurrentAction")) {


					Pl0000* player = (Pl0000*)cGameUIManager::Instance.m_pPlayer;


					if (player) {

						Entity* targetEnemyEntity = *(Entity**)(shared::base + 0x19BFF60);
						BehaviorEmBase* targetEnemy = (BehaviorEmBase*)targetEnemyEntity->m_pInstance;
						ImGui::Text("Player/Enemy Action");
						if (!player->m_nBladeModeType)
						{
							if (!Trigger::StaFlags.STA_QTE)
							{

								ImGui::Separator();
								ImGui::Value("Player Current Animation ID", ReadSinglePointer(player->field_774, 0x14));
								ImGui::Text("Player Animation Name: %s", GetAnimationNameById((int**)player->m_ppAnimationMap, ReadSinglePointer(player->field_774, 0x14)));
								ImGui::Text("Player Current Action: %X", player->getCurrentAction());
								ImGui::Value("Player Current Action ID", player->getCurrentActionId());
								ImGui::Value("animationcanbeplayed", animationcanbeplayed);
								ImGui::Value("framespassed", framespassed);
								ImGui::Value("prevAnim", prevAnim);
								ImGui::Value("inp", inp);
								ImGui::Value("anim", anim);
								ImGui::Value("attack", attack); 
								ImGui::Separator();
								ImGui::Value("Enemy Current Animation ID", targetEnemy->getCurrentActionId());
								ImGui::Text("Enemy Animation Name: %s", GetAnimationNameById((int**)targetEnemy->m_ppAnimationMap, ReadSinglePointer(targetEnemy->field_774, 0x14)));
								ImGui::Text("Enemy Current Action: %X", (unsigned int)targetEnemy->getCurrentAction());
								ImGui::Value("Enemy Current Action ID", targetEnemy->getCurrentActionId());
								ImGui::Separator();

								ImGui::Checkbox("Pause", &value3);
								if (value3 == true)
								{
									Trigger::StpFlags.STP_PL_CAM_KEY = 1;
									Trigger::StpFlags.STP_PL_ATTACK_KEY = 1;
									Trigger::StpFlags.STP_EM = 1;
									Trigger::StpFlags.STP_GAME_UPDATE = 1;
								}
								if (value3 == false)
								{
									Trigger::StpFlags.STP_PL_CAM_KEY = 0;
									Trigger::StpFlags.STP_PL_ATTACK_KEY = 0;
									Trigger::StpFlags.STP_EM = 0;
									Trigger::StpFlags.STP_GAME_UPDATE = 0;
								}

								ImGui::Separator();

							}
							else if (player->m_nCurrentAction == 0x888 
								|| player->m_nCurrentAction == 0x12DF)
							{
								ImGui::Separator();
								ImGui::Value("Player Current Animation ID", ReadSinglePointer(player->field_774, 0x14));
								ImGui::Text("Player Animation Name: %s", GetAnimationNameById((int**)player->m_ppAnimationMap, ReadSinglePointer(player->field_774, 0x14)));
								ImGui::Text("Player Current Action: %X", player->getCurrentAction());
								ImGui::Value("Player Current Action ID", player->getCurrentActionId());
								ImGui::Value("animationcanbeplayed", animationcanbeplayed);
								ImGui::Value("framespassed", framespassed);
								ImGui::Value("prevAnim", prevAnim);
								ImGui::Value("inp", inp);
								ImGui::Value("anim", anim);
								ImGui::Value("attack", attack);
								ImGui::Separator();

								ImGui::Text("Enemy Current Action: %X", (unsigned int)player->getCurrentAction());
								ImGui::Value("Enemy Current Action ID", player->getCurrentActionId());

								ImGui::Separator();

								ImGui::Checkbox("Pause", &value3);
								if (value3 == true)
								{
									Trigger::StpFlags.STP_PL_CAM_KEY = 1;
									Trigger::StpFlags.STP_PL_ATTACK_KEY = 1;
									Trigger::StpFlags.STP_EM = 1;
									Trigger::StpFlags.STP_GAME_UPDATE = 1;
								}
								if (value3 == false)
								{

									Trigger::StpFlags.STP_PL_CAM_KEY = 0;
									Trigger::StpFlags.STP_PL_ATTACK_KEY = 0;
									Trigger::StpFlags.STP_EM = 0;
									Trigger::StpFlags.STP_GAME_UPDATE = 0;
								}

								ImGui::Separator();
							}

							else
							{

								ImGui::Separator();
								ImGui::Value("Player Current Animation ID", ReadSinglePointer(targetEnemy->field_774, 0x14));
								ImGui::Text("Player Animation Name: %s", GetAnimationNameById((int**)targetEnemy->m_ppAnimationMap, ReadSinglePointer(player->field_774, 0x14)));
								ImGui::Text("Player Current Action: %X", player->getCurrentAction());
								ImGui::Value("Player Current Action ID", player->getCurrentActionId());
								ImGui::Value("animationcanbeplayed", animationcanbeplayed);
								ImGui::Value("framespassed", framespassed);
								ImGui::Value("prevAnim", prevAnim);
								ImGui::Value("inp", inp);
								ImGui::Value("anim", anim);
								ImGui::Value("attack", attack);
								ImGui::Value("Fuel", player->getCurrentFuelCapacity());
								ImGui::Separator();
								ImGui::Value("Enemy Current Animation ID", targetEnemy->getCurrentActionId());
								ImGui::Text("Enemy Animation Name: %s", GetAnimationNameById((int**)targetEnemy->m_ppAnimationMap, ReadSinglePointer(targetEnemy->field_774, 0x14)));
								ImGui::Text("Enemy Current Action: %X", (unsigned int)targetEnemy->getCurrentAction());
								ImGui::Value("Enemy Current Action ID", targetEnemy->getCurrentActionId());

								ImGui::Separator();

								ImGui::Checkbox("Pause", &value3);
								if (value3 == true)
								{
									Trigger::StpFlags.STP_PL_CAM_KEY = 1;
									Trigger::StpFlags.STP_PL_ATTACK_KEY = 1;
									Trigger::StpFlags.STP_EM = 1;
									Trigger::StpFlags.STP_GAME_UPDATE = 1;
								}
								if (value3 == false)
								{

									Trigger::StpFlags.STP_PL_CAM_KEY = 0;
									Trigger::StpFlags.STP_PL_ATTACK_KEY = 0;
									Trigger::StpFlags.STP_EM = 0;
									Trigger::StpFlags.STP_GAME_UPDATE = 0;
								}

								ImGui::Separator();
							}



						}
						else
						{
							ImGui::Separator();
							ImGui::Value("Player Current Animation ID", ReadSinglePointer(player->field_774, 0x14));
							ImGui::Text("Player Animation Name: %s", GetAnimationNameById((int**)player->m_ppAnimationMap, ReadSinglePointer(player->field_774, 0x14)));
							ImGui::Text("Player Current Action: %X", player->getCurrentAction());
							ImGui::Value("Player Current Action ID", player->getCurrentActionId());
							ImGui::Value("animationcanbeplayed", animationcanbeplayed);
							ImGui::Value("framespassed", framespassed);
							ImGui::Value("prevAnim", prevAnim);
							ImGui::Value("inp", inp);
							ImGui::Value("anim", anim);
							ImGui::Value("attack", attack);

							ImGui::Separator();

							ImGui::Value("Enemy Current Animation ID", player->getCurrentActionId());
							ImGui::Text("Enemy Animation Name: %s", GetAnimationNameById((int**)player->m_ppAnimationMap, ReadSinglePointer(player->field_774, 0x14)));

							ImGui::Separator();

							ImGui::Checkbox("Pause", &value3);
							if (value3 == true)
							{
								Trigger::StpFlags.STP_PL_CAM_KEY = 1;
								Trigger::StpFlags.STP_PL_ATTACK_KEY = 1;
								Trigger::StpFlags.STP_EM = 1;
								Trigger::StpFlags.STP_GAME_UPDATE = 1;
							}
							if (value3 == false)
							{

								Trigger::StpFlags.STP_PL_CAM_KEY = 0;
								Trigger::StpFlags.STP_PL_ATTACK_KEY = 0;
								Trigger::StpFlags.STP_EM = 0;
								Trigger::StpFlags.STP_GAME_UPDATE = 0;
							}
							ImGui::Separator();


						}



					}



					else { ImGui::Text("Player/Enemy Action"); }

					ImGui::EndTabItem();
				}


				ImGui::EndTabBar();
			}
			ImGui::End();



		}













	}
	else
	{
		if (keypressed1 == true)
		{
			Trigger::StpFlags.STP_MOUSE_UPDATE = 0;
			Trigger::StpFlags.STP_PL_CAM_KEY = 0;
			Trigger::StpFlags.STP_PL_ATTACK_KEY = 0;
			Trigger::StpFlags.STP_EM = 0;
			Trigger::StpFlags.STP_GAME_UPDATE = 0;
			keypressed1 = false;
		}
	}
	*/
}










