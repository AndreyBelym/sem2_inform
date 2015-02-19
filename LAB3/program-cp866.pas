{-------��������� ������ ����� �������------}
program FunctionRoot;
type TestFunc=function(const x:real):real;

{$F+}
function f(const x:real):real; 
begin
    f:=sin(x);
end;
{$F-}
{------������� ����� ������������� ���������-----}
{��ࠬ����: 
paramName - ��� ����訢������ ��ࠬ���; 
paramCond - �������⥫쭠� ���ଠ�� � ��ࠬ���;
log - ��६����� ���ﭨ�}
function GetParam(const paramName,paramCond:string;var log:boolean):real;
var temp:real; buf:string; code:integer; ch:char;
begin
    ch:='Y'; temp:=0; {���樠������ ��६�����}
    repeat
        WriteLn('������ ',paramName,' - ����⢥���� �᫮. ',paramCond);
        Write(paramName,':');ReadLn(buf); Val(buf,temp,code);
        if code<>0 then begin {������� �� ����⢥���� �᫮?}
            WriteLn('�������⨬�� ���祭�� ',paramName,'.');
            WriteLn('������� ����?(y/n)');
            ReadLn(ch);
        end;
    until (Upcase(ch)='N') or (code=0);
    {���� ���짮��⥫� �� �⪠����� ��� �᫮ �����४⭮�}
    log:=code=0;{�᫮ ������� ���४⭮?}    
    GetParam:=temp;{���� ���祭��}
end;

{--------������� ����� ������-------}
{��ࠬ����:
a,b - �࠭��� ��१�� ���᪠ ����;
eps - �筮��� ���᫥���;
log - ��६����� ���ﭨ�}
function InputData(var a,b,eps:real):boolean;
var log:boolean; ch:char;
begin
    ch:='Y'; {���樠������ ⠪ � ⮫쪮 ⠪! �. ����, ��祬�}
    repeat
        case UpCase(ch) of
            'A':a:=GetParam('a','',log);
            'B':b:=GetParam('b','b>a.',log);
            else begin
                a:=GetParam('a','',log);
                if log then
                    b:=GetParam('b','b>a.',log);
            end;
        end;  
        if log and not (b>a) then begin
            WriteLn('�訡��! b<=a!');
            WriteLn('������� ����?');
            WriteLn('Y - ����� � � b;');
            WriteLn('A - ����� ⮫쪮 �;');
            WriteLn('B - ����� ⮫쪮 b;');
            WriteLn('N - �⬥��.');
            ReadLn(ch);  
        end;
    until not(log) or (b>a) or (UpCase(ch)='N');
    log:=log and (b>a);
    if log then 
        repeat
            eps:=GetParam('eps','eps>0.',log); 
            if log and not (eps>0) then begin
                WriteLn('�訡��! eps<=0!');
                WriteLn('������� ����?(Y/N)');
                ReadLn(ch);
            end;
        until not(log) or (eps>0) or (UpCase(ch)='N');
    log:=log and (eps>0);
    InputData:=log and (ch<>'N');
end;

{-------������� �������� ������------}
{��ࠬ����:
a,b - �࠭��� ��१�� ���᪠ ����;
eps - �筮��� ���᫥���}
function CheckData(const a,b,eps:real):boolean;
var ch:char;
begin
    WriteLn('�㤥� �믮���� ���� ����');
    WriteLn(' �� ���ࢠ�� �� ',a:1:4,' �� ',b:1:4,' � �筮���� ',eps:1:8);
    WriteLn('�த������?(Y/N)');
    ReadLn(ch);
    CheckData:=UpCase(ch)='Y';
end;

{------������� ��������� �����------}
{��ࠬ����:
f - ��������㥬�� �㭪��;
a,b - �࠭��� ��१�� ���᪠ ����;
eps - �筮��� ���᫥���;
f_root - �������� ��७�}
function GetRoot(const f:TestFunc; const a,b,eps:real;var f_root:real):byte;

{------������� ������� �����------}
{��ࠬ����:
f - ��������㥬�� �㭪��;
a,b - �࠭��� ��१�� ���᪠ ����;
eps - �筮��� ���᫥���;}
function Root(const f:TestFunc; const a,b,eps:real):real;
var c:real;
begin
    c:=(a+b)/2;
    if b-a>eps then
        if f(c)*f(a)<=0 then
            Root:=Root(f,a,c,eps) 
        else 
            Root:=Root(f,c,b,eps)      
    else
        Root:=c;
end;
begin
    if not(b>a) then 
        GetRoot:=1
    else
        if not(eps>0) then
            GetRoot:=2
        else
            if f(a)*f(b)>0 then
                GetRoot:=3 
            else begin
                GetRoot:=0;
                f_root:=Root(f,a,b,eps);
            end;
end;

{------�������� ���������-------}
{a,b - �࠭��� ��१�� ���᪠ ����;
eps - �筮��� ���᫥���;
log - ��६����� ���ﭨ�;
code - ��� �訡�� ���᪠ ����}
const func_name='sin(x)';
var a,b,eps,f_root:real;log:boolean; code:byte;
Begin
WriteLn('�ணࠬ�� ��室�� ��७� �㭪樨 ',func_name,' �� ��१�� [a,b] � �筮���� eps.');
log:=InputData(a,b,eps);
if log then
    log:=CheckData(a,b,eps);
if log then begin
    code:=GetRoot(f,a,b,eps,f_root);
    case code of
        0:WriteLn('��७� �� �஬���⪥ [',a:1:4,',',b:1:4,'] ࠢ�� ',f_root:1:8);
        1:WriteLn('������ �࠭�� ���ࢠ�� ���᪠ ���� ����� ������...');
        2:WriteLn('��筮��� ���᫥��� �����/ࠢ�� 0!');
        3:WriteLn('���� �� �஬���⪥ [',a:1:4,',',b:1:4,'] �� �������.');
    end
end
else
    WriteLn('�ணࠬ�� �����襭� ���짮��⥫��...');
end.
