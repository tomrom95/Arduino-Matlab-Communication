function [s] = startSerial( port )
% startSerial(port) 
% sets up serial communication with MATLAB for use to
% send data to Arduino or other software. This function deletes all
% previous open serial ports and then creates a new serial object, s, with
% a BaudRate of 115200. The function also pauses before ending, which is
% necessary before sending any data through the serial port.
%
%   Returns s, a serial object.

fclose('all');
close all
delete(instrfindall);
s = serial(port);
s.BaudRate = 115200;
fopen(s);
pause(2);

end

