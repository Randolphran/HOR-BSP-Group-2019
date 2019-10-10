% This function addpoints to exsisted animation line, given by linehandles.
% I/O data is given by (position,data).
function Realtimeplot(position,data,linehandles)

for j = 0:3
    
    addpoints(linehandles(j+1),position,data)
    drawnow limitrate
    
end
end