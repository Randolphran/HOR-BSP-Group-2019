clear global;

global  dataAI;     % Convey AI data to main workspace, as a storage.
global i;           % Indicate current sample amount.

i = 1;
dataAI(1:end,1:end) = 0;

% default 4 channels input, if any change happens here, track to
% InstantAI_Project1 channCount.

for j=0:3
    fhandles(j+1) = figure('NumberTitle', 'off', 'Name', ['Channel ',num2str(j)]);
    title(['Channel ',num2str(j)]);
    grid on;
    ax = get(fhandles(j+1),'CurrentAxes') ;
    linehandles(j+1) =  animatedline(ax);
    x = 0;
end


InstantAI_Project1(linehandles);

