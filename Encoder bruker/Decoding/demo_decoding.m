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

figure
for i = 1 : nfiles
    subplot(nfiles, 1, i)
    plot(vdata{i})
end

%% Decode
% Decode
qdata = cell(nfiles,1);

for i = 1 : nfiles
    qdata{i} = AnalogQuadDecoder(vdata{i});
end

figure
for i = 1 : nfiles
    subplot(nfiles, 1, i)
    plot(qdata{i})
end