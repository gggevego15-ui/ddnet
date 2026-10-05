#ifndef GAME_CLIENT_COMPONENTS_WORSTCLIENT_H
#define GAME_CLIENT_COMPONENTS_WORSTCLIENT_H

#include <game/client/component.h>

class CWorstClient : public CComponent
{
	bool m_Open = false;
	int m_Tab = 0;
	float m_Animation = 0.0f;

	bool m_Visual[12]{};
	bool m_Gameplay[12]{};
	bool m_Other[12]{};

	void RenderMenu();
	void RenderTabButton(const char *pText, int Tab, float X, float Y);
	void RenderToggle(const char *pText, bool &Value, float X, float Y);

public:
	void OnRender() override;
	bool OnInput(const IInput::CEvent &Event) override;
};

#endif
