#ifndef GAME_CLIENT_COMPONENTS_WORSTCLIENT_H
#define GAME_CLIENT_COMPONENTS_WORSTCLIENT_H

#include <game/client/component.h>

class CWorstClient : public CComponent
{
public:
	void OnInit() override;
	void OnRender() override;
	void OnConsoleInit() override;

private:
	bool m_Active = false;
	int m_Tab = 0;

	bool m_Visuals[16]{};
	bool m_Training[16]{};
	bool m_Other[16]{};

	float m_MenuAlpha = 0.0f;
	float m_HoverAnimation[64]{};

	void RenderMenu();
	void RenderVisualTab();
	void RenderTrainingTab();
	void RenderOtherTab();
	void RenderInfoTab();

	void DrawButton(const char *pText, float X, float Y, float W, float H, bool *pValue);
	void DrawTab(const char *pText, int Tab, float X, float Y, float W, float H);
};

#endif
