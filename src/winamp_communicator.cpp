#include "stdafx.hpp"
#include "winamp_communicator.hpp"

auto winamp_communicator::init() -> void {
	m_hwnd = FindWindow(_T("Winamp v1.x"), NULL);
	if (!m_hwnd) {
		throw std::runtime_error("Error: Unable to find Winamp");
	}
}

auto winamp_communicator::send_action(WPARAM wParam) -> void {
	init();
	SendMessage(m_hwnd, WM_COMMAND, wParam, NULL);
}

auto winamp_communicator::get_action(const winamp_command_pair &pair) -> long long {
	init();
	return SendMessage(m_hwnd, WM_USER, pair.w, pair.l);
}

auto winamp_communicator::get_title() -> LPCSTR {
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