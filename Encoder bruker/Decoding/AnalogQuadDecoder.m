function position = AnalogQuadDecoder(vin, varargin)
% AnalogQuadDecoder decodes position data from voltage recordings of the
% Trinket M0-based quad encoder.

%% Parse inputs
if nargin < 2
    varargin = {};
end

p = inputParser;
addOptional(p, 'fs', 1000); % Digitizer sampling rate in Hz

% Encoder setting (do not change)
addOptional(p, 'vmax', 3.3); % Max voltage of M0's DAC
addOptional(p, 'qsteps',      [-1,        -2,    -3,    -4,     0,     4,     3,     2,   1]); % Quadrature steps

% Unpack if needed
if iscell(varargin) && size(varargin,1) * size(varargin,2) == 1
    varargin = varargin{:};
end

parse(p, varargin{:});
p = p.Results;

%% Digitize data
% Length
l = length(vin);

% Find steps
nsteps = length(p.qsteps);
neutralstep = (nsteps - 1) / 2 + 1;
vthresh = p.vmax / (nsteps - 1);

% Digitize
vdin = round(vin / vthresh) + 1;

%% Parse
% Find  pulses
step_chains = chainfinder(vdin ~= neutralstep);
step_chains(:,2) = step_chains(:,1) + step_chains(:,2) - 1;

% Output
position = zeros(l, 1);

for i = 1 : size(step_chains, 1)
    % Inds
    ind = median(vdin(step_chains(i,1) : step_chains(i,2)));
    position(step_chains(i,1)) = p.qsteps(ind);
end

% Output
position = cumsum(position);

end