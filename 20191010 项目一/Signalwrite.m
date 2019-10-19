function swrite = Signalwrite
swrite.csv = @signalwritecsv;
swrite.txt = @signalwritetxt;
swrite.mat = @signalwritemat;
swrite.xls = @signalwritexls;
end
% Main function, also interface function. Instantiate an object when use.
% input matrix data and new file name. Create data file with slected filetype.
% eg.
% example = signalwrite;
% example.txt(data,filename);


function signalwritecsv(data,filename)
if ischar(filename)
    csvwrite([filename,'.csv'],data);
    fprintf('%s\n','Writting succeeded!');
else
    fprintf('%s\n','Filename Error! Input filename must be char class.');
end
end

function signalwritetxt(data,filename)
if ischar(filename)
    fid = fopen([filename,'.txt'],'wt');
    sz = size(data);
    fprintf(fid,'%8.6f',data(1,:));
    if sz(1,1) >= 2        
        fprintf(fid,'\n%8.6f',data(2:end,:));
    end
    fprintf('%s\n','Writting succeeded!');
    fclose(fid);
else
    fprintf('%s\n','Filename Error! Input filename must be char class.');
end
end

function signalwritemat(data,filename)
if ischar(filename)
    save([filename,'.mat'],'data','-mat');
    fprintf('%s\n','Writting succeeded!');
else
    fprintf('%s\n','Filename Error! Input filename must be char class.');
end
end

function signalwritexls(data,filename)
if ischar(filename)
    xlswrite(filename,data);
    fprintf('%s\n','Writting succeeded!');
else
    fprintf('%s\n','Filename Error! Input filename must be char class.');
end
end