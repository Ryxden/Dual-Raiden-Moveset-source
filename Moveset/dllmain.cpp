#include "pch.h"
#include <assert.h>
#include "gui.h"
#include <Events.h>

#include "imgui/imgui.h"
#include <cWeaponSelectMenu.h>
#include <PlayerManagerImplement.h>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <ctime>
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
#include <stdio.h>
#include <time.h>
#include <dos.h>
#include <shared.h>
#include <conio.h>
#include <Hw.h>
#include "d3dx9.h"
#include "cWeaponSelectMenu.h"
#include "cObj.h"
#include <BehaviorEmBase.h>
#include <EmBaseDLC.h>
#include "IniReader.h"
#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <sstream>
#include <XInput.h>
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
CIniReader iniReader("Keys.ini");
std::string KeyForDodge = iniReader.ReadString("Keys", "KeyForDodge", "45");
std::string KeyForBladeMode = iniReader.ReadString("Keys", "KeyForBladeMode", "09");
std::string KeyForFloorKick = iniReader.ReadString("Keys", "KeyForFloorKick", "59");
std::string KeyForJumpAttack = iniReader.ReadString("Keys", "KeyForJumpAttack", "56");
std::string KeyForStunAttack = iniReader.ReadString("Keys", "KeyForStunAttack", "55");
std::string KeyForAerialKick = iniReader.ReadString("Keys", "KeyForAerialKick", "4E");
std::string KeyForBladeModeCombo = iniReader.ReadString("Keys", "KeyForBladeModeCombo", "50");
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
std::string xinputdpadup = iniReader.ReadString("Controller Buttons", "XINPUT_GAMEPAD_DPAD_UP", "XINPUT_GAMEPAD_DPAD_UP");

int framespassed = 0;
int curranim = 0;

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
            if ((CancelableFramesEnd <= 0)                // Always cancelable
                || (CancelableFramesEnd >= framespassed)) // Cancelable until a point, currently cancelable
                return true;
        }
        else if (CancelableFramesStart <= framespassed)
        {
            if ((CancelableFramesEnd <= 0)                  // Cancelable after a point  
                || (CancelableFramesEnd >= framespassed)) // Cancelable only in a certain range
                return true;
        }

        return false; // While the animation is cancelable, the timing isn't currently right
    }

    return false; // Uncancelable animations
}
bool animationcanbeplayed = false;
static auto prevAnim = 0;
bool keypressed1 = false;
int inp = 0;
int anim = 0;
int pressed = 0;
int attack = 1;
int buttonpressed = 0;
/*
int amount = 0;
*/
int prevanim = 10;
int buttonpressed2 = 0;
int buttonpressed3 = 0;
int buttonpressed4 = 0;
int buttonpressed5 = 0;
int buttonpressed6 = 0;
int buttonpressed7 = 0;
int blademode = 0;
/*
float maxfc = 0.0;
*/
bool animationisntplayable = false;
class RAIDEN {
public:
    RAIDEN()
    {

        Events::OnTickEvent.before += []() {
            auto player = cGameUIManager::Instance.m_pPlayer;
            if (player)
            {
                prevAnim = ReadSinglePointer(player->field_774, 0x14);
            }
            };

        Events::OnTickEvent.after += []() {
            Pl0000* player = cGameUIManager::Instance.m_pPlayer;
            
            if (player)
            {/*
				maxfc = (((player->m_nCurrentFCUpgrades) - 1) * 280) + 400;
				*/
				if (inp==1)
				{
					requestAnimationByMap2(player, anim, 0, 0.0f, 1.0f, 0x8100000, -1.0f, 1.0f);
					AnimationPlayer(player, 1.0, 1.0);
					inp=0;
					/*Boss Raiden JCE if (anim == 1339)
					{
						pressed = 2;
					}
					else if ((anim != 1338) && anim != 1340)
						anim = 0;
					if (anim == 10)
					{
						prevanim = 10;
					}
					else if (anim == 11)
					{
						prevanim = 11;
					}
					*/
				}
				/*
				if ((ReadSinglePointer(player->field_774, 0x14) != 1339) && pressed == 2 && amount==1 && (!Trigger::StaFlags.STA_QTE) && (!player->isCodecTalk()) && (!player->isBladeModeActive()) && (Trigger::GameFlags.GAME_DEPRESSSION_RAIDEN == 0) && (Trigger::StaFlags.STA_PAUSE == 0))
				{
					player->setState(0x63, 0, 0, 0);
					anim = 1339;
					framespassed = 0;
					inp = 1;
					pressed = 0;
					amount = 2;
				}
				else if ((ReadSinglePointer(player->field_774, 0x14) != 1339) && pressed == 2 && amount == 2 && (!Trigger::StaFlags.STA_QTE) && (!player->isCodecTalk()) && (!player->isBladeModeActive()) && (Trigger::GameFlags.GAME_DEPRESSSION_RAIDEN == 0) && (Trigger::StaFlags.STA_PAUSE == 0))
				{
					player->setState(0x63, 0, 0, 0);
					anim = 1340;
					framespassed = 0;
					inp = 1;
					pressed = 0;
					player->setFuelCapacity(0);
				}
				*/
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
						if (Enemy->getCurrentAction() == 0x3000D || Enemy->getCurrentAction() == 0x10006 || Enemy->getCurrentAction() == 0x30012)
						{
							animationisntplayable = true;
						}
						else
							animationisntplayable = false;
					}
				}
				if (IsButtonPressed(xinputl3asstring) && IsButtonPressed(xinputbasstring) && (!player->isBladeModeActive()))
				{
					if (buttonpressed == 0)
					{
						MGR_PlaySound("core_se_sys_decide_l", 0);
						if (attack < 5)
						{
							attack++;
						}
						else
						{
							attack = 1;
						}
					}
					buttonpressed = 1;
				}
				else
					buttonpressed = 0;
                if (prevAnim != ReadSinglePointer(player->field_774, 0x14) && ReadSinglePointer(player->field_774, 0x14) != 1092 && ReadSinglePointer(player->field_774, 0x14) != 1093)
                {
                    framespassed = 0;
                }
                if (player->getCurrentAction() == 0x77 || ReadSinglePointer(player->field_774, 0x14) == 310 || player->getCurrentAction() == 0x6E)
                {
                    if (shared::IsKeyPressed(std::stoi(KeyForDodge, nullptr, 16), true) || (IsButtonPressed(xinputxasstring) && IsButtonPressed(xinputaasstring)))
                    {
                        player->setState(0x63, 0, 0, 0);
                    }
                    if (shared::IsKeyPressed(std::stoi(KeyForBladeMode, nullptr, 16), true) || IsButtonPressed(xinputl2asstring))
                    {
						player->setState(0x0, 0, 0, 0);
						player->setState(0x46, 0, 0, 0);
                    }
                }
				/* Boss Raiden JCE
				if (((shared::IsKeyPressed(VK_RBUTTON, true) || IsButtonPressed(xinputtriangleasstring)) && ReadSinglePointer(player->field_774, 0x14) == 654 && player->getCurrentFuelCapacity()==maxfc))
				{
					if (player->getCurrentAction() != 0x63)
					{
							player->setState(0x63, 0, 0, 0);
							anim = 1339;
							framespassed = 0;
							inp = 1;
							amount = 1;
					}
				}
				*/
                if ((shared::IsKeyPressed(std::stoi(KeyForFloorKick, nullptr, 16), true)) || (IsButtonPressed(xinputl1asstring) && IsButtonPressed(xinputl3asstring) && attack==1))
                {
					if (buttonpressed3 == 0)
					{
                    if ((!player->isInAir()) && (!Trigger::StaFlags.STA_QTE) && (!player->isCodecTalk()) && (!player->isBladeModeActive()) && (Trigger::GameFlags.GAME_DEPRESSSION_RAIDEN == 0) && (Trigger::StaFlags.STA_PAUSE == 0) && animationcanbeplayed && !animationisntplayable && (player->getCurrentAction() != 0x13D && player->getCurrentAction() != 0x13F && player->getCurrentAction() != 0x13E))
                    {
						if (player->getCurrentAction() != 0x63 || ReadSinglePointer(player->field_774, 0x14) == 672 || ReadSinglePointer(player->field_774, 0x14) == 694 || ReadSinglePointer(player->field_774, 0x14) == 691 || ReadSinglePointer(player->field_774, 0x14) == 670 || ReadSinglePointer(player->field_774, 0x14) == 310 || ReadSinglePointer(player->field_774, 0x14) == 1338 || ReadSinglePointer(player->field_774, 0x14) == 1339 || ReadSinglePointer(player->field_774, 0x14) == 1340 || ReadSinglePointer(player->field_774, 0x14) == 381 || ReadSinglePointer(player->field_774, 0x14) == 705 || ReadSinglePointer(player->field_774, 0x14) == 704 || ReadSinglePointer(player->field_774, 0x14) == 703)
						{
								player->setState(0x63, 0, 0, 0);
								anim = 672;
								framespassed = 0;
								inp = 1;
						}
					}
                    }
					buttonpressed3 = 1;
                }
				else
					buttonpressed3 = 0;
                if ((shared::IsKeyPressed(std::stoi(KeyForJumpAttack, nullptr, 16), true)) || (IsButtonPressed(xinputl1asstring) && IsButtonPressed(xinputl3asstring) && attack == 2))
                {
					if (buttonpressed5 == 0)
					{
						if ((!Trigger::StaFlags.STA_QTE) && (!player->isCodecTalk()) && (!player->isBladeModeActive()) && (Trigger::GameFlags.GAME_DEPRESSSION_RAIDEN == 0) && (Trigger::StaFlags.STA_PAUSE == 0) && animationcanbeplayed && !animationisntplayable && player->getCurrentAction() != 0x13D && player->getCurrentAction() != 0x13F && player->getCurrentAction() != 0x13E)
						{
							if (player->getCurrentAction() != 0x63 || ReadSinglePointer(player->field_774, 0x14) == 694 || ReadSinglePointer(player->field_774, 0x14) == 672 || ReadSinglePointer(player->field_774, 0x14) == 691 || ReadSinglePointer(player->field_774, 0x14) == 670 || ReadSinglePointer(player->field_774, 0x14) == 310 || ReadSinglePointer(player->field_774, 0x14) == 1338 || ReadSinglePointer(player->field_774, 0x14) == 1339 || ReadSinglePointer(player->field_774, 0x14) == 1340 || ReadSinglePointer(player->field_774, 0x14) == 381 || ReadSinglePointer(player->field_774, 0x14) == 705 || ReadSinglePointer(player->field_774, 0x14) == 704 || ReadSinglePointer(player->field_774, 0x14) == 703)
							{
								player->setState(0x63, 0, 0, 0);
								anim = 694;
								framespassed = 0;
								inp = 1;
							}
						}
					}
					buttonpressed5 = 1;
                }
				else
					buttonpressed5 = 0;
                if ((shared::IsKeyPressed(std::stoi(KeyForStunAttack, nullptr, 16), true)) || (IsButtonPressed(xinputl1asstring) && IsButtonPressed(xinputl3asstring) && attack == 3))
                {
					if (buttonpressed4 == 0)
					{
                    if ((!player->isInAir()) && (!Trigger::StaFlags.STA_QTE) && (!player->isCodecTalk()) && (!player->isBladeModeActive()) && (Trigger::GameFlags.GAME_DEPRESSSION_RAIDEN == 0) && (Trigger::StaFlags.STA_PAUSE == 0) && animationcanbeplayed && !animationisntplayable && player->getCurrentAction() != 0x13D && player->getCurrentAction() != 0x13F && player->getCurrentAction() != 0x13E)
                    {
						if (player->getCurrentAction() != 0x63 || ReadSinglePointer(player->field_774, 0x14) == 691 || ReadSinglePointer(player->field_774, 0x14) == 694 || ReadSinglePointer(player->field_774, 0x14) == 672 || ReadSinglePointer(player->field_774, 0x14) == 670 || ReadSinglePointer(player->field_774, 0x14) == 310 || ReadSinglePointer(player->field_774, 0x14) == 1338 || ReadSinglePointer(player->field_774, 0x14) == 1339 || ReadSinglePointer(player->field_774, 0x14) == 1340 || ReadSinglePointer(player->field_774, 0x14) == 381 || ReadSinglePointer(player->field_774, 0x14) == 705 || ReadSinglePointer(player->field_774, 0x14) == 704 || ReadSinglePointer(player->field_774, 0x14) == 703)
						{
							player->setState(0x63, 0, 0, 0);
							anim = 691;
							framespassed = 0;
							inp=1;
						}
                    }
					}
					buttonpressed4 = 1;
                }
				else
					buttonpressed4 = 0;
                if ((shared::IsKeyPressed(std::stoi(KeyForAerialKick, nullptr, 16), true)) || (IsButtonPressed(xinputl1asstring) && IsButtonPressed(xinputl3asstring) && attack == 4))
                {
					if (buttonpressed6 == 0)
					{
						if ((!player->isInAir()) && (!Trigger::StaFlags.STA_QTE) && (!player->isCodecTalk()) && (!player->isBladeModeActive()) && (Trigger::GameFlags.GAME_DEPRESSSION_RAIDEN == 0) && (Trigger::StaFlags.STA_PAUSE == 0) && animationcanbeplayed && !animationisntplayable && player->getCurrentAction() != 0x13D && player->getCurrentAction() != 0x13F && player->getCurrentAction() != 0x13E)
						{
							if (player->getCurrentAction() != 0x63 || ReadSinglePointer(player->field_774, 0x14) == 670 || ReadSinglePointer(player->field_774, 0x14) == 694 || ReadSinglePointer(player->field_774, 0x14) == 691 || ReadSinglePointer(player->field_774, 0x14) == 672 || ReadSinglePointer(player->field_774, 0x14) == 310 || ReadSinglePointer(player->field_774, 0x14) == 1338 || ReadSinglePointer(player->field_774, 0x14) == 1339 || ReadSinglePointer(player->field_774, 0x14) == 1340 || ReadSinglePointer(player->field_774, 0x14) == 381 || ReadSinglePointer(player->field_774, 0x14) == 705 || ReadSinglePointer(player->field_774, 0x14) == 704 || ReadSinglePointer(player->field_774, 0x14) == 703)
							{
								player->setState(0x63, 0, 0, 0);
								anim = 670;
								framespassed = 0;
								inp = 1;
							}
						}
					}
					buttonpressed6 = 1;
                }
				else
					buttonpressed6 = 0;
                if ((shared::IsKeyPressed(std::stoi(KeyForBladeModeCombo, nullptr, 16), true)) || (IsButtonPressed(xinputl1asstring) && IsButtonPressed(xinputl3asstring) && attack == 5))
                {
					if (buttonpressed7 == 0)
					{
						if ((!player->isInAir()) && (!Trigger::StaFlags.STA_QTE) && (!player->isBladeModeActive()) && (!player->isCodecTalk()) && (Trigger::GameFlags.GAME_DEPRESSSION_RAIDEN == 0) && (Trigger::StaFlags.STA_PAUSE == 0) && animationcanbeplayed && !animationisntplayable && player->getCurrentAction() != 0x13D && player->getCurrentAction() != 0x13F && player->getCurrentAction() != 0x13E)
						{
							if (player->getCurrentAction() != 0x63 || ReadSinglePointer(player->field_774, 0x14) == 694 || ReadSinglePointer(player->field_774, 0x14) == 691 || ReadSinglePointer(player->field_774, 0x14) == 670 || ReadSinglePointer(player->field_774, 0x14) == 672 || ReadSinglePointer(player->field_774, 0x14) == 1338 || ReadSinglePointer(player->field_774, 0x14) == 1339 || ReadSinglePointer(player->field_774, 0x14) == 1340 || ReadSinglePointer(player->field_774, 0x14) == 381 || ReadSinglePointer(player->field_774, 0x14) == 705 || ReadSinglePointer(player->field_774, 0x14) == 704 || ReadSinglePointer(player->field_774, 0x14) == 703)
							{
								player->setState(0x63, 0, 0, 0);
								anim = 310;
								framespassed = 0;
								inp = 1;
							}
						}
					}
					buttonpressed7 = 1;
                }
				else
					buttonpressed7 = 0;
                if (framespassed == 900)
                {
					if (player->getCurrentAction() == 0)
					{
						player->setState(0x3, 0, 0, 0);
						anim = 1229;
						inp = 1;
					}
                    framespassed = 0;
                }
				if (player->getCurrentAction() == 0xD0)
				{
					if (shared::IsKeyPressed(0x57, true) || shared::IsKeyPressed(0x53, true) || shared::IsKeyPressed(0x41, true) || shared::IsKeyPressed(0x44, true) || IsButtonPressed(xinputlthumbup) || IsButtonPressed(xinputlthumbleft) || IsButtonPressed(xinputlthumbdown) || IsButtonPressed(xinputlthumbright))
					{
						if (buttonpressed2 == 0)
						{
							framespassed = framespassed + 33;
						}
						buttonpressed2 = 1;
					}
					else
						buttonpressed2 = 0;
					if (framespassed > 200)
					{
						player->setState(0, 0, 0, 0);
					}
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

bool value3 = true;
bool bShowGUI2 = false;

void gui::RenderWindow()
{
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
							else if (player->m_nCurrentAction == 0x888 || player->m_nCurrentAction == 0x12DF)
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
	
}










