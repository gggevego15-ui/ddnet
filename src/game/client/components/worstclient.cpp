#include "worstclient.h"

#include <game/client/gameclient.h>
#include <game/client/ui.h>

#include <engine/graphics.h>
#include <engine/input.h>
#include <engine/textrender.h>

void CWorstClient::OnRender()
{
	const float Target = m_Open ? 1.0f : 0.0f;

	m_Animation += (Target - m_Animation) * 0.18f;

	if(m_Animation < 0.01f)
		return;

	RenderMenu();
	m_MouseWasPressed = m_MousePressed;
}

bool CWorstClient::OnInput(const IInput::CEvent &Event)
{
	if(Event.m_Flags & IInput::FLAG_PRESS)
	{
		if(Event.m_Key == KEY_INSERT)
		{
			m_Open = !m_Open;
			return true;
		}
	}

	return false;
}

void CWorstClient::RenderMenu()
{
	m_MousePressed = Input()->NativeMousePressed(0);
	const vec2 MousePos = Input()->NativeMousePos();
	const float W = Graphics()->ScreenWidth();
	const float H = Graphics()->ScreenHeight();

	const float MenuW = 760.0f;
	const float MenuH = 500.0f;

	const float X = (W - MenuW) / 2.0f;
	const float Y = (H - MenuH) / 2.0f;

	// Основная панель
	Graphics()->TextureClear();
	Graphics()->QuadsBegin();

	Graphics()->SetColor(
		0.035f,
		0.045f,
		0.065f,
		0.96f * m_Animation);

	IGraphics::CQuadItem Background(X, Y, MenuW, MenuH);
	Graphics()->QuadsDrawTL(&Background, 1);

	Graphics()->QuadsEnd();

	// Заголовок
	TextRender()->Text(
		X + 28,
		Y + 22,
		25.0f,
		"WORST CLIENT",
		-1.0f);

	TextRender()->Text(
		X + 29,
		Y + 51,
		12.0f,
		"VISUAL / TRAINING CLIENT",
		-1.0f);

	// Вкладки
	RenderTabButton("VISUAL", 0, X + 25, Y + 90);
	RenderTabButton("GAMEPLAY", 1, X + 205, Y + 90);
	RenderTabButton("OTHER", 2, X + 385, Y + 90);
	RenderTabButton("INFO", 3, X + 565, Y + 90);

	if(m_Tab == 0)
	{
		const char *pNames[] =
		{
			"Custom Crosshair",
			"Player Trail",
			"Ghost Trail",
			"Speedometer",
			"FPS Graph",
			"Ping Display",
			"Hook Visualization",
			"Zoom Indicator",
			"Damage Numbers",
			"Particle Effects",
			"HUD Customizer",
			"Screen Effects"
		};

		for(int i = 0; i < 12; i++)
		{
			const float BX = X + 30.0f + (i % 2) * 350.0f;
			const float BY = Y + 155.0f + (i / 2) * 50.0f;

			RenderToggle(pNames[i], m_Visual[i], BX, BY);
		}
	}
	else if(m_Tab == 1)
	{
		const char *pNames[] =
		{
			"Run Timer",
			"Checkpoints",
			"Ghost Replay",
			"Movement Timer",
			"Hook Timer",
			"Jump Counter",
			"Input Display",
			"Route Recorder",
			"Accuracy Trainer",
			"Reaction Trainer",
			"Training Stats",
			"Speedometer"
		};

		for(int i = 0; i < 12; i++)
		{
			const float BX = X + 30.0f + (i % 2) * 350.0f;
			const float BY = Y + 155.0f + (i / 2) * 50.0f;

			RenderToggle(pNames[i], m_Gameplay[i], BX, BY);
		}
	}
	else if(m_Tab == 2)
	{
		const char *pNames[] =
		{
			"Dark Theme",
			"Large UI",
			"Menu Animation",
			"Menu Sounds",
			"Click Effects",
			"Notifications",
			"Config Manager",
			"Keybind Manager",
			"Screenshot Mode",
			"Debug Overlay",
			"Performance Mode",
			"Compact HUD"
		};

		for(int i = 0; i < 12; i++)
		{
			const float BX = X + 30.0f + (i % 2) * 350.0f;
			const float BY = Y + 155.0f + (i / 2) * 50.0f;

			RenderToggle(pNames[i], m_Other[i], BX, BY);
		}
	}
	else
	{
		TextRender()->Text(
			nullptr,
			X + 50,
			Y + 165,
			20.0f,
			"WORST CLIENT",
			-1.0f);

		TextRender()->Text(
			nullptr,
			X + 50,
			Y + 205,
			14.0f,
			"Version 0.1.0",
			-1.0f);

		TextRender()->Text(
			nullptr,
			X + 50,
			Y + 235,
			14.0f,
			"Custom DDNet client",
			-1.0f);

		TextRender()->Text(
			nullptr,
			X + 50,
			Y + 280,
			14.0f,
			"Insert - open / close menu",
			-1.0f);
	}
}

void CWorstClient::RenderTabButton(
	const char *pText,
	int Tab,
	float X,
	float Y)
{
	const bool Active = m_Tab == Tab;

	Graphics()->QuadsBegin();

	if(Active)
		Graphics()->SetColor(0.18f, 0.42f, 0.90f, 0.95f);
	else
		Graphics()->SetColor(0.10f, 0.12f, 0.17f, 0.95f);

	IGraphics::CQuadItem Rect(X, Y, 160.0f, 40.0f);
	Graphics()->QuadsDrawTL(&Rect, 1);

	Graphics()->QuadsEnd();

	TextRender()->Text(
		X + 18,
		Y + 11,
		13.0f,
		pText,
		-1.0f);

	if((m_MousePressed && !m_MouseWasPressed) &&
		MousePos.x >= X &&
		MousePos.x <= X + 160.0f &&
		MousePos.y >= Y &&
		MousePos.y <= Y + 40.0f)
	{
		m_Tab = Tab;
	}
}

void CWorstClient::RenderToggle(
	const char *pText,
	bool &Value,
	float X,
	float Y)
{
	const bool Hover =
		MousePos.x >= X &&
		MousePos.x <= X + 320.0f &&
		MousePos.y >= Y &&
		MousePos.y <= Y + 38.0f;

	Graphics()->QuadsBegin();

	if(Hover)
		Graphics()->SetColor(0.15f, 0.18f, 0.25f, 1.0f);
	else
		Graphics()->SetColor(0.09f, 0.11f, 0.15f, 1.0f);

	IGraphics::CQuadItem Rect(X, Y, 320.0f, 38.0f);
	Graphics()->QuadsDrawTL(&Rect, 1);

	Graphics()->QuadsEnd();

	TextRender()->Text(
		X + 14,
		Y + 10,
		13.0f,
		pText,
		-1.0f);

	TextRender()->Text(
		X + 270,
		Y + 10,
		12.0f,
		Value ? "ON" : "OFF",
		-1.0f);

	if((m_MousePressed && !m_MouseWasPressed) && Hover)
		Value = !Value;
}
