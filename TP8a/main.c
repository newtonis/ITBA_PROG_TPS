#include <stdio.h>
#include "port_utils.h"
#include "output.h"

int main(){
	microPorts_t mp;

	int ans = initPorts(&mp);

	show_port(&mp.A);
	show_port(&mp.B);
	show_port(&mp.D);

	bitSet(&mp.A,2);

	show_port(&mp.A);
	show_port(&mp.B);
	show_port(&mp.D);

	end_ports(&mp); /// free ports memory
	
	
	printf("%d ",ans);
}