# MultiWii-BT
Modified version of the Multiwii flight control software that uses the HC-05 bluetooth modules as its control inputs instead of the traditional R/C receiver.
Thanks to Electronoobs https://www.youtube.com/channel/UCjiVhIvGmRZixSzupD0sS9Q for simplifing the R/C software, and laying out the variable for easy access.
The motor connections it the same as Electronoob's drone http://www.electronoobs.com/eng_arduino_tut23_4.php. But for the bluetooth module, connect pin 2 to Tx of HC-05 and pin 4 to Rx of HC-05
All the bluetooth magic happens in the NRF24_RX.cpp file, so it might be helpful if you read though it before you start using the code.
The code is still in its very early stage, so there might be problems here and there
