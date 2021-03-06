/*
 * Socket.cpp
 *
 *  Created on: Mar 5, 2017
 *      Author: kolban
 */

#include "Socket.h"
#include <unistd.h>
#include <lwip/sockets.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <esp_log.h>
#include "sdkconfig.h"

static char tag[] = "Socket";

Socket::Socket() {
	sock = -1;
}

Socket::~Socket() {
	close_cpp();
}

void Socket::close_cpp() {
	::close(sock);
	sock = -1;
}

int Socket::connect_cpp(struct in_addr address, uint16_t port) {
	struct sockaddr_in serverAddress;
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr   = address;
	serverAddress.sin_port   = htons(port);
	char msg[50];
	inet_ntop(AF_INET, &address, msg, sizeof(msg));
	ESP_LOGD(tag, "Connecting to %s:[%d]", msg, port);
	sock = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	int rc = ::connect(sock, (struct sockaddr *)&serverAddress, sizeof(struct sockaddr_in));
	if (rc == -1) {
		ESP_LOGE(tag, "connect_cpp: Error: %s", strerror(errno));
		close_cpp();
		return -1;
	} else {
		ESP_LOGD(tag, "Connected to partner");
		return 0;
	}
}

int Socket::receive_cpp(uint8_t* data, size_t length) {
	int rc = ::recv(sock, data, length, 0);
	if (rc == -1) {
		ESP_LOGE(tag, "receive_cpp: %s", strerror(errno));
	}
	return rc;
}

void Socket::send_cpp(const uint8_t* data, size_t length) {
	int rc = ::send(sock, data, length, 0);
	if (rc == -1) {
		ESP_LOGE(tag, "receive_cpp: %s", strerror(errno));
	}
}

int Socket::connect_cpp(char* strAddress, uint16_t port) {
	struct in_addr address;
	inet_pton(AF_INET, (char *)strAddress, &address);
	return connect_cpp(address, port);
}

void Socket::send_cpp(std::string value) {
	send_cpp((uint8_t *)value.data(), value.size());
}

void Socket::init() {

}
