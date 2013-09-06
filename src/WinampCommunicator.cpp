#include "stdafx.hpp"
#include "WinampCommunicator.hpp"

void WinampCommunicator::init() {
	m_hwnd = FindWindow(_T("Winamp v1.x"), NULL);
	if (!m_hwnd) {
		throw std::runtime_error("Error: Unable to find Winamp");
	}
}

void WinampCommunicator::sendAction(WPARAM wParam) {
	init();
	SendMessage(m_hwnd, WM_COMMAND, wParam, NULL);
}

long long WinampCommunicator::getAction(const CommandPair &pair) {
	init();
	return SendMessage(m_hwnd, WM_USER, pair.w, pair.l);
}

LPCSTR WinampCommunicator::getTitle() {
	init();

	char *p;
	GetWindowText(m_hwnd, m_title, sizeof(m_title));
	p = m_title + lstrlen(m_title) - 8;
	while (p >= m_title) {
		if (!lstrcmpi(p,"- Winamp"))
			break;
		p--;
	}
	if (p >= m_title)
		p--;
	while (p >= m_title && *p == ' ')
		p--;
	*++p = 0;

	return m_title;
}