/*
 * msg_queue_posix.cxx
 * 
 * Copyright 2016 olegartys <olegartys@olegartys-HP-Pavilion-15-Notebook-PC>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */


#include <iostream>
#include <fstream>
#include <cstring>

#include <mqueue.h>

int main(int argc, char **argv)
{
	mqd_t mqd = mq_open("/test.mq", O_RDONLY | O_CREAT, 0666, NULL);
	if (mqd < 0) {
		perror("mq_open");
		exit(errno);
	}
	
	struct mq_attr obuf;
	int ret = mq_getattr(mqd, &obuf);
	if (ret < 0) {
		perror("mq_getattr");
		exit(errno);
	}
	
	char *buf = new char[obuf.mq_msgsize];
	memset(buf, '\0', obuf.mq_msgsize);
	ret = mq_receive(mqd, buf, obuf.mq_msgsize, NULL); 
	if (ret < 0) {
		perror("mq-receive");
		exit(errno);
	}
	
	std::ofstream f("/home/box/message.txt");
	f << buf << std::endl;
	f.close();
	
	return 0;
}

