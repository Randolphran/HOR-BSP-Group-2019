% This function addpoints to exsisted animation line, given by linehandle.
% I/O data is given by (position,data).
% Editter: Yuncong Ran 2019/10/14
% Create function.
function Realtimeplot_Project1(position,data,linehandles)
    
    addpoints(linehandles,position,data);
    drawnow limitrate
    
end
