#include "worstclient.h"

#include <game/client/gameclient.h>
#include <game/client/ui.h>

#include <engine/graphics.h>
#include <engine/input.h>

#include <cmath>

void CWorstClient::OnInit()
{
	m_Active = false;
	m_Tab = 0;
	m_MenuAlpha = 0.0f;

	for(auto &Value : m_Visuals)
		Value = false;

	for(auto &Value : m_Training)
		Value = false;

	for(auto &Value : m_Other)
		Value = false;
}

void CWorstClient::OnConsoleInit()
{
	Console()->Register(
		"worstclient",
		"?i",
		CFGFLAG_CLIENT,
		[](IConsole::IResult *pResult, void *pUserData)
		{
			auto *pSelf = static_cast<CWorstClient *>(pUserData);
			pSelf->m_Active = !pSelf->m_Active;
		},
		this,
		"Toggle Worst Client menu");
}

void CWorstClient::OnRender()
{
	if(Input()->KeyPress(KEY_INSERT))
		m_Active = !m_Active;

	if(!m_Active)
	{
		m_MenuAlpha = 0.0f;
		return;
	}

	m_MenuAlpha += (1.0f - m_MenuAlpha) * 0.18f;

	RenderMenu();
}

void CWorstClient::RenderMenu()
{
	const float ScreenW = Graphics()->ScreenWidth();
	const float ScreenH = Graphics()->ScreenHeight();

	const float W = 760.0f;
	const float H = 500.0f;

	const float X = (ScreenW - W) * 0.5f;
	const float Y = (ScreenH - H) * 0.5f;

	Graphics()->TextureClear();

	// Основная glass-панель
	Graphics()->QuadsBegin();
	Graphics()->SetColor(0.05f, 0.06f, 0.09f, 0.94f * m_MenuAlpha);
	IGraphics::CQuadItem Panel(X, Y, W, H);
	Graphics()->QuadsDrawTL(&Panel, 1);
	Graphics()->QuadsEnd();

	// Заголовок
	TextRender()->Text(
		nullptr,
		X + 30,
		Y + 22,
		24.0f,
		"WORST CLIENT",
		-1.0f);

	TextRender()->Text(
		nullptr,
		X + W - 145,
		Y + 27,
		14.0f,
		"INSERT",
		-1.0f);

	const float TabY = Y + 75.0f;
	const float TabW = 150.0f;

	DrawTab("VISUAL", 0, X + 20, TabY, TabW, 38);
	DrawTab("GAMEPLAY", 1, X + 180, TabY, TabW, 38);
	DrawTab("OTHER", 2, X + 340, TabY, TabW, 38);
	DrawTab("INFO", 3, X + 500, TabY, TabW, 38);

	switch(m_Tab)
	{
	case 0:
		RenderVisualTab();
		break;
	case 1:
		RenderTrainingTab();
		break;
	case 2:
		RenderOtherTab();
		break;
	case 3:
		RenderInfoTab();
		break;
	}
}

void CWorstClient::DrawTab(
	const char *pText,
	int Tab,
	float X,
	float Y,
	float W,
	float H)
{
	const bool Active = m_Tab == Tab;

	Graphics()->QuadsBegin();

	if(Active)
		Graphics()->SetColor(0.20f, 0.45f, 0.95f, 0.85f);
	else
		Graphics()->SetColor(0.12f, 0.14f, 0.19f, 0.9f);

	IGraphics::CQuadItem Rect(X, Y, W, H);
	Graphics()->QuadsDrawTL(&Rect, 1);

	Graphics()->QuadsEnd();

	TextRender()->Text(
		nullptr,
		X + 20,
		Y + 10,
		14.0f,
		pText,
		-1.0f);

	if(Input()->MouseButton(0) &&
		Input()->MouseX() >= X &&
		Input()->MouseX() <= X + W &&
		Input()->MouseY() >= Y &&
		Input()->MouseY() <= Y + H)
	{
		m_Tab = Tab;
	}
}

void CWorstClient::DrawButton(
	const char *pText,
	float X,
	float Y,
	float W,
	float H,
	bool *pValue)
{
	const bool Hover =
		Input()->MouseX() >= X &&
		Input()->MouseX() <= X + W &&
		Input()->MouseY() >= Y &&
		Input()->MouseY() <= Y + H;

	const float Target = Hover ? 1.0f : 0.0f;

	const int Index = static_cast<int>(X + Y) % 64;

	m_HoverAnimation[Index] +=
		(Target - m_HoverAnimation[Index]) * 0.20f;

	const float Glow = m_HoverAnimation[Index];

	Graphics()->QuadsBegin();

	Graphics()->SetColor(
		0.10f + Glow * 0.06f,
		0.12f + Glow * 0.08f,
		0.17f + Glow * 0.15f,
		0.95f);

	IGraphics::CQuadItem Rect(X, Y, W, H);
	Graphics()->QuadsDrawTL(&Rect, 1);

	Graphics()->QuadsEnd();

	TextRender()->Text(
		nullptr,
		X + 16,
		Y + 12,
		14.0f,
		pText,
		-1.0f);

	const char *pState = *pValue ? "ON" : "OFF";

	TextRender()->Text(
		nullptr,
		X + W - 55,
		Y + 12,
		12.0f,
		pState,
		-1.0f);

	if(Input()->MouseButton(0) && Hover)
		*pValue = !*pValue;
}

void CWorstClient::RenderVisualTab()
{
	const float X = 250.0f;
	const float Y = 180.0f;

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
		"Entity Highlight"
	};

	for(int i = 0; i < 12; i++)
	{
		const float BX = X + (i % 2) * 250.0f;
		const float BY = Y + (i / 2) * 48.0f;

		DrawButton(
			pNames[i],
			BX,
			BY,
			230,
			38,
			&m_Visuals[i]);
	}
}

void CWorstClient::RenderTrainingTab()
{
	const float X = 250.0f;
	const float Y = 180.0f;

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
		const float BX = X + (i % 2) * 250.0f;
		const float BY = Y + (i / 2) * 48.0f;

		DrawButton(
			pNames[i],
			BX,
			BY,
			230,
			38,
			&m_Training[i]);
	}
}

void CWorstClient::RenderOtherTab()
{
	const float X = 250.0f;
	const float Y = 180.0f;

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
		const float BX = X + (i % 2) * 250.0f;
		const float BY = Y + (i / 2) * 48.0f;

		DrawButton(
			pNames[i],
			BX,
			BY,
			230,
			38,
			&m_Other[i]);
	}
}

void CWorstClient::RenderInfoTab()
{
	const float X = 270.0f;
	const float Y = 190.0f;

	TextRender()->Text(nullptr, X, Y, 18.0f,
		"WORST CLIENT", -1.0f);

	TextRender()->Text(nullptr, X, Y + 40, 14.0f,
		"Version: 0.1.0", -1.0f);

	TextRender()->Text(nullptr, X, Y + 70, 14.0f,
		"Custom DDNet Client", -1.0f);

	TextRender()->Text(nullptr, X, Y + 100, 14.0f,
		"Visual / Training Edition", -1.0f);

	TextRender()->Text(nullptr, X, Y + 150, 14.0f,
		"Insert - Toggle Menu", -1.0f);
}
