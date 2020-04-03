#include "EventDispatcher.h"
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <iostream>

using namespace nebula;
using namespace std;

#define GPIO_NOTIFY "/dev/gpio_notify"
#define IRQ_EDGE "/sys/devices/soc:quec,quectel-low-consume/irq_edge"
static int notify_fd;


void Sighandler(int signal)
{
	switch (signal) {
		case SIGINT:
			printf("================ %d\n",__LINE__);
			break;
		default:
			printf("Receiver unexpected signal %d\n",signal);
			break;
	}
}

void gpio_cb_handler(int signal)
{
	char edge[8] = {0};
	int edge_fd;

	printf("gpio irq: Have caught signal %d from driver\n", signal);

	EventDispatcher *ed = &EventDispatcher::GetInstance();

	WakeLock *wl = ed->GetWakeLock();
	if (wl == NULL) {
		printf("- wakelock is null!\n");
		return;
	}

	edge_fd = open(IRQ_EDGE, O_RDONLY | O_NONBLOCK);
	if(edge_fd < 0) {
		printf("==================   err     %s: %d\n",__FUNCTION__,__LINE__);
		perror("open");
		return;
	}
	

	if(read(edge_fd, edge, sizeof(edge)) < 0) {
		printf("==================   err     %s: %d\n",__FUNCTION__,__LINE__);
		perror("read");
		return;
	}
	
    printf("==================   edge:%s       [%s] %d\n",edge,__FUNCTION__,__LINE__);

	if(strncmp(edge, "falling", 7) == 0) {
		printf("==================     %s: %d\n",__FUNCTION__,__LINE__);
		printf("do something before enter sleep mode\n");
		printf("module will enter sleep mode\n");
		//ioctl(notify_fd, 0);	//pull down notify mcu
		//printf("pull down notify mcu\n");
		wl->UnLock(ed->GetWakeIntLock());

		printf("================== wake unlock: %d\n",__LINE__);
	
	} else if(strncmp(edge, "rising", 6) == 0) {
		printf("==================     %s: %d\n",__FUNCTION__,__LINE__);

		int lockId = wl->Lock();

		cout << "lockId: " << lockId << endl;

		
		//ioctl(notify_fd, 1);	//pull up notify mcu
		//printf("pull up notify mcu\n");
	}
	close(edge_fd);
}


int register_gpio()
{
	int ret, Oflags;
	printf("================== %s: %d\n",__FUNCTION__,__LINE__);
	signal(SIGIO, gpio_cb_handler);
	notify_fd = open(GPIO_NOTIFY, O_RDWR);
	if (notify_fd < 0) {
		perror("open");
		goto err;
	}
	ret = fcntl(notify_fd, F_SETOWN, getpid());
	
	if(ret < 0) {
		perror("fcntl");
		goto err;
	}

	Oflags = fcntl(notify_fd, F_GETFL);
	if(Oflags < 0) {
		perror("fcntl");
		goto err;
	}
	
	ret = fcntl(notify_fd, F_SETFL, Oflags | FASYNC);
	if(ret < 0) {
		perror("fcntl");
		goto err;
	}
	
	printf("register gpio irq callback ok\n");
	return 0;
err:
	return -1;
}



EventDispatcher::EventDispatcher() :m_wakeIntLock(-1)
{
	signal(SIGTERM, Sighandler);
	signal(SIGINT, Sighandler);
	register_gpio();
}

EventDispatcher::~EventDispatcher()
{

}

void EventDispatcher::SetWakeLock(WakeLock * wl)
{
	//if (m_wakeLock == NULL) {
		m_wakeLock = wl;
	//}
}


EventDispatcher& EventDispatcher::GetInstance()
{
	static EventDispatcher instance__;
	//instance__.m_wakeLock = NULL;
	
	return instance__;
}






