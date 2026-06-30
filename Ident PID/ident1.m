clear all ;
close all ;
clc;
%w = warning('query','last');
%id = w.identifier;
%warning('off',id)
%rmpath('folderthatisnotonpath')
%Com serial
oldobj = instrfind; %elimina residuos en el puerto serial
if not(isempty(oldobj))
    fclose(oldobj);
    delete(oldobj);
end
if ~exist('s','var')
    s=serial('COM3','BaudRate',57600,'DataBits',8,'Parity','None','StopBits',1);
end
if strcmp(get(s,'status'),'closed')
    fopen(s);
end
pause(4)
i=1;
%inicializar botones y grafico


f = figure;
c = uicontrol(f,'Style','togglebutton','String','Leer','Position',... 
[10 10 40 40]);
d = uicontrol(f,'Style','togglebutton','String','Salir','Position',... 
[515 380 40 40]);
axis([0 inf 0 inf])
%hold on

data=uint8.empty(); %crear vector vacio

while d.Value==0
     while c.Value==0
        pause(0.01)
        if d.Value==1
            break;
        end
     end
    disp('Comienza'); 
    fwrite(s,'A')
    while c.Value==1
        str=string(fscanf(s));
        str_1=strsplit(str,',');
        str_2{i,1}=str2double(str_1{1});
        str_2{i,2}=str2double(str_1{2});     
        str_3=cell2mat(str_2);
        plot(str_3)
        i=i+1;
        pause(0.001)
    end
    fwrite(s,'B')
    disp('Termino'); 
    pause(0.001)
end
%clear all ;
%close all ;
%clc;
fclose(s);
%%
%eliminar filas malas
str=str';   
%%
%str2=cell2mat(str);
str2=char(str);
n=length(str2)-1;
i=1;
for i=1:1:n
    strf1m1(i,1)=str2double(str2(i,1:7));
    strf1m1(i,2)=str2double(str2(i,8:14));
    %strf1m1(i,3)=str2double(strf1m(i,15:21));
    %strf1m1(i,4)=str2double(strf1m(i,22:28));
end
plot(strf1m1)
%csvwrite('M1_1.csv',str_3)