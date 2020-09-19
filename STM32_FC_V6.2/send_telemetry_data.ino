
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//This part sends the telemetry data to the ground station.
//The output for the serial monitor is PB0. Protocol is 1 start bit, 8 data bits, no parity, 1 stop bit.
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void send_telemetry_data(void) {

/*
  short roll_angle;
  short pitch_angle;
  short bat1;
  short bat2;
  byte rssi;
  byte flight_mode;
  byte altitude_meters;
  byte error;
  byte number_used_sats;
  int l_lat_gps;
  int l_lon_gps;
  byte start;
 */

 data.flight_mode=flight_mode;
 data.altitude_meters= 1000 + ((ground_pressure - actual_pressure) * 0.0842);
 data.error=error;
 data.number_used_sats=number_used_sats;
// data.l_lat_gps=l_lat_gps;
 //data.l_lon_gps=l_lon_gps;
 
if(angle_roll<0){
 absroll=abs(angle_roll);
 data.roll_angle=absroll+1000;
}
else{
  data.roll_angle=angle_roll;
}

if(angle_pitch<0){
 abspitch=abs(angle_pitch);
 data.pitch_angle=abspitch+1000;
}
else{
  data.pitch_angle=angle_pitch;
}
 
 data.start=start;


data.rssi=channel_8;
data.bat1=map(analogRead(PA4),0,3903,0,1680);
data.bat2=map(analogRead(PA1),0,3811,0,840);

data.throttle1=(pid_p_gain_altitude + pid_error_gain_altitude) * pid_error_temp;
data.throttle2=pid_i_mem_altitude;
data.throttle3=pid_d_gain_altitude * parachute_throttle;
data.throttle=throttle;
radio.write(&data, sizeof(Data_Package));

/*
 //vbat2 8.07-->3662
//vbat1 3885-->16.72
 */
}
