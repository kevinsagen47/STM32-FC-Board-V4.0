///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//In this file the timers for reading the receiver pulses and for creating the output ESC pulses are set.
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//More information can be found in these two videos:
//STM32 for Arduino - Connecting an RC receiver via input capture mode: https://youtu.be/JFSFbSg0l2M
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void handler_channel_1(void) {
  measured_time = TIMER2_BASE->CCR1 - measured_time_start;
  if (measured_time < 0)measured_time += 0xFFFF;
  measured_time_start = TIMER2_BASE->CCR1;
  if (measured_time > 3000)channel_select_counter = 0;
  else channel_select_counter++;
//actual_pressure_slow = actual_pressure_slow * (float)0.985 + actual_pressure_fast * (float)0.015;
  
  if (channel_select_counter == 1){
   if(flight_mode==1){ 
    now1 = map(measured_time,1000,2000,1200,1800);
    channel_1=now1*(float)0.8+channel_1*(float)0.2;
   }
   else{
     now1 = map(measured_time,1000,2000,1250,1750);
    channel_1=now1*(float)0.8+channel_1*(float)0.2;
   }
  
  }
  
  if (channel_select_counter == 2){
    if(flight_mode==1){
    now2 = map(measured_time,1000,2000,1200,1800);
    channel_2=now2*(float)0.8+channel_2*(float)0.2;
    }
    else{
      now2 = map(measured_time,1000,2000,1250,1750);//1350,1650
    channel_2=now2*(float)0.8+channel_2*(float)0.2;
    }
    }
  if (channel_select_counter == 3){
  if(flight_mode==1){
    channel_3 = map(measured_time,1000,2000,1000,1700);
  }
  else {
    channel_3 = measured_time;
  }
  }
  
  if (channel_select_counter == 4)channel_4 = map(measured_time,1000,2000,1200,1800);
  if (channel_select_counter == 5)channel_5 = measured_time;
  if (channel_select_counter == 6)channel_6 = measured_time;


}

/*
  void handler_channel_1(void) {
  measured_time = TIMER2_BASE->CCR1 - measured_time_start;
  if (measured_time < 0)measured_time += 0xFFFF;
  measured_time_start = TIMER2_BASE->CCR1;
  if (measured_time > 3000)channel_select_counter = 0;
  else channel_select_counter++;

  if (channel_select_counter == 1)channel_1 = map(measured_time,1000,2000,1200,1800);
  if (channel_select_counter == 2)channel_2 = map(measured_time,1000,2000,1200,1800);
  if (channel_select_counter == 3)channel_3 = map(measured_time,1000,2000,1000,1700);
  if (channel_select_counter == 4)channel_4 = map(measured_time,1000,2000,1200,1800);
  if (channel_select_counter == 5)channel_5 = measured_time;
  if (channel_select_counter == 6)channel_6 = measured_time;
}
 */
