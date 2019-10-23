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
    data = dlmread(filename,'\t');
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
