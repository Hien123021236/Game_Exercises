#include "Text.h"


void Text::DrawLabel(std::string message, RECT rect, DWORD dword) {
	if (font != NULL) {
		font->DrawTextA(NULL, message.c_str(), -1, &rect, DT_LEFT, D3DCOLOR_XRGB(0, 0, 0));
	}
}
bool Text::Init(LPDIRECT3DDEVICE9 d3ddv) {
	font = NULL;
	fontResult = D3DXCreateFont(d3ddv, 20, 0, FW_NORMAL, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"Arial", &font);
	if (!SUCCEEDED(fontResult)) {
		return false;
	}
}
Text::Text()
{
}


Text::~Text()
{
	if (font != NULL) {
		font->Release();
	}
}
