function data = Signalread(filename)
if ischar(filename) == 0
    fprintf('Filename Error! Must be Char class');
    exit();
end

filetype = filename(strfind(filename,'.')+1:end);
flag = 0;

if filetype == 'csv'
    data = csvread(filename);
    flag = 1;
end

if filetype == 'txt'
%     data(:,1) = dlmread(filename,'\n',[0 0 end 0]);% default separator for .txt file is '\n'
%     data(:,2) = dlmread(filename,'\n',[0 1 end 1]);
%     data(:,3) = dlmread(filename,'\n',[0 2 end 2]);
%     data(:,4) = dlmread(filename,'\n',[0 3 end 3]);
    data = dlmread(filename,'\n');
    flag = 1;
    
end

if filetype == 'mat'
    load(filename,'data');
    flag = 1;
end

if filetype == 'xls'
    data = xlsread(filename);
    flag = 1;
end

if ~flag
    disp('Error! Cannot read filetype');
end

end
