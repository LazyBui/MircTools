#include "stdafx.hpp"
#include "WinampCommunicator.hpp"

void winamp_communicator::init() {
	m_hwnd = FindWindow(_T("Winamp v1.x"), NULL);
	if (!m_hwnd) {
		throw std::runtime_error("Error: Unable to find Winamp");
	}
}

void winamp_communicator::send_action(WPARAM wParam) {
	init();
	SendMessage(m_hwnd, WM_COMMAND, wParam, NULL);
}

long long winamp_communicator::get_action(const winamp_command_pair &pair) {
	init();
	return SendMessage(m_hwnd, WM_USER, pair.w, pair.l);
}

LPCSTR winamp_communicator::get_title() {
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