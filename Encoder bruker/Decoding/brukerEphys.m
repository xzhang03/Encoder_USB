function [ephys, timestamps] = brukerEphys(fn,nch, Fs, type)
% Read Bruker Ephys data into matlab. 

if nargin < 4
    type = 'int16';
    if nargin < 3
        Fs = 1000;
    end
end

%% Bit depths
switch type
    case 'int16'
        div = 2^15;
end

%% Read
fid = fopen(fn);
ephys = fread(fid, [nch, inf], type);
ephys = ephys / div * 10; % Convert to volage
fclose(fid);

%% Time
timestamps = 0 : size(ephys,2) - 1;
timestamps = timestamps / Fs * 1000;

end