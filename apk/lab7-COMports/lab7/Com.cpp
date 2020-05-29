#include "Com.h"


void Com::setDefaultSettings() {
	DCB com_settings{};

	GetCommState(handle, &com_settings);
	com_settings.BaudRate = CBR_115200;
	com_settings.ByteSize = 8;
	com_settings.StopBits = ONESTOPBIT;
	com_settings.Parity = NOPARITY;
	com_settings.fDtrControl = DTR_CONTROL_ENABLE;
	SetCommState(handle, &com_settings);
}

size_t Com::read(char* buffer, size_t size) {
	size_t amount{};
	DWORD bytes_readen{};
	ClearCommError(handle, &errors, &stat);

	if (stat.cbInQue) {
		amount = size < stat.cbInQue ? size : stat.cbInQue;
	}

	return ReadFile(handle, buffer, amount, &bytes_readen, NULL) ? bytes_readen : 0;
}

bool Com::write(char* buffer, size_t size) {
	DWORD bytesWritten{};
	if (WriteFile(handle, buffer, size, &bytesWritten, NULL)) {
		ClearCommError(handle, &errors, &stat);
		return true;
	}
	return false;
}

bool Com::isConnected() {
	return connected;
}