%% MatlabArdCom.m

% Shift register control for the Arduino using serial communication. The
% script begins a serial communication with a specified serial port using
% the startSerial function. This script features two settings, either array
% or random. Array uses a user specified array of 1s and 0s to specify
% which LEDs should be turned on. Random produces a random array. This data
% is then converted to a string of 8 bit integers (between 0 and 255) and
% this data is sent over serial to the Arduino. After communication has
% finished, the serial port is closed.

% The Arduino MUST be running the sketch 'ShiftRegControlWithSPI.ino' or
% some variant to work.

% Created Friday June 27, 2014
% by Tommy Romano


%% Setup Serial Communication

s = startSerial('/dev/tty.usbmodem1411'); %specify serial port here


%% Setup Parameters
numSR = 3; %number of Shift Registers
data = zeros(8*numSR,1); % if no program input is given, the array will be 0s
srDataArray = zeros(1, numSR);

% **INPUT DATA HERE**
%userData = zeros(1,8*numSR);
userData = [1,1,0,0,1,0,0,1,0,0,0,0,0,0,0,0,1,1,1,0,0,0,1,1];
program = 'ARRAY';

%% Run specified program

if strcmp(program, 'ARRAY')
    data = userData;
elseif strcmp(program, 'RANDOM')
    data = randi(2,1,8*numSR)-1; % Fills array randomly with 0s and 1s
    disp(data); %Displays what it randomly output
end
  
%% Convert array to decimal
for i=1:numSR
    offset = 8*(i-1);
    byte = data((1+offset):(8+offset));
    str_x = num2str(byte);
    str_x(isspace(str_x)) = '';
    srDataArray(i) = bin2dec(str_x); 
end

%% Send to Arduino
%disp(srDataArray); %[For debugging]
dataString = strcat(num2str(1),',',mat2str(srDataArray)); %converts to string
fprintf(s,dataString); %sends string via serial

%% Finishing
disp('Lights should be on...');

fclose(s); %closes serial port

