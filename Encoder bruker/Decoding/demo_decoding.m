% Decode quadrature steps from voltage recordings in a system designed for
% Bruke scope

%% Read data
fns = {'VoltageRecording_run1', 'VoltageRecording_run2', 'VoltageRecording_run3'};
nfiles = length(fns);
vdata = cell(nfiles, 1);

for i = 1 : nfiles
    fid = fopen(fns{i});
    vdata{i} = fread(fid, inf, 'int16');
    vdata{i} = vdata{i} / 2^15 * 10; % Convert to volage
    fclose(fid);
end

% Plot
figure
for i = 1 : nfiles
    subplot(nfiles, 2, (i-1)*2+1)
    plot(vdata{i})
    
    if i == 1
        title('Encoder output')
    end
    ylabel('V')
end

%% Decode
% Decode
qdata = cell(nfiles,1);

for i = 1 : nfiles
    qdata{i} = AnalogQuadDecoder(vdata{i});
end


for i = 1 : nfiles
    subplot(nfiles, 2, i*2)
    plot(qdata{i})

    if i == 1
        title('Decoded position')
    end
    ylabel('Steps')
end