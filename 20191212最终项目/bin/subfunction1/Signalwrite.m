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
    csvwrite(filename,data);
    fprintf('%s\n','Writting succeeded!');
else
    fprintf('%s\n','Filename Error! Input filename must be char class.');
end
end

function signalwritetxt(data,filename)
if ischar(filename)
    fid = fopen(filename,'w');
    fprintf(fid,'%.4f\t%.4f\t%.4f\t%.4f\n',data');
% Edittor: Yuncong Ran 2019/10/21
% fprintf fill in data in column order, thus the matrix DATA is transferred to
% fill in row order.
    fclose(fid);
else
    fprintf('%s\n','Filename Error! Input filename must be char class.');
end
end

function signalwritemat(data,filename)
if ischar(filename)
    save(filename,'data','-mat');
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