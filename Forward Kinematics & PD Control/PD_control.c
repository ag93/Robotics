#include <stdio.h>
#include <math.h>


double kp=0.0;
double kv=0.0;
double om=0.0;
double torque=0.0;
double difference=0.0;


double PD_control(theta, theta_dot, theta_ref, theta_dot_ref)
double theta, theta_dot, theta_ref, theta_dot_ref;
{
	om=((theta-theta_ref)/0.002)/1000;
	kp=om*om;
	kv=om*2;
	torque=(kp*(theta_ref))+(kv*theta_dot)+9.81*sin((theta_ref-theta));

	double torque_org=12.00;
	if(torque<=torque_org)
	{
		difference=torque_org-torque;
	}

	return(torque);
}
