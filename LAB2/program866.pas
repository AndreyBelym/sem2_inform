{-----��������� ������� ������� 2-� ��������� � 2-�� ������������-----}
Program SysSolver;
const maxvars=2;{���-�� ��६����� ��⥬�}
type MatColumn=array[1..maxvars] of real; {⨯ "�����-�⮫���"}

{------������� ����� ������������� ���������-----}
{��ࠬ����: ��� ����訢������ ��ࠬ���; ����� ��ࠬ���; ��६����� ���ﭨ�}
function GetParam(const paramName:char;const paramNum:integer; var log:boolean):real;
var temp:real; buf:string; code:integer; ch:char;
begin
    ch:='Y'; temp:=0; {���樠������ ��६�����}
    repeat
        WriteLn('������ ',paramName,paramNum,' - ����⢥���� �᫮.');
        Write(paramName,paramNum,':');ReadLn(buf); Val(buf,temp,code);
        if code<>0 then begin {������� �� ����⢥���� �᫮?}
            WriteLn('�������⨬�� ���祭�� ',paramName,paramNum,'.');
            WriteLn('������� ����?(y/n)');
            ReadLn(ch);
        end;
    until (Upcase(ch)='N') or (code=0);
    {���� ���짮��⥫� �� �⪠����� ��� �᫮ �����४⭮�}
    log:=code=0;{�᫮ ������� ���४⭮?}
    if log then    
        GetParam:=temp;{���� ���祭��}
end;

{------������� ����� ������-----}
{��ࠬ����:�����樥��� �� �; �����樥��� �� �; ᢮����� �����樥���}
function InputData(var A,B,C:MatColumn):boolean;
var i:byte; log:boolean;
begin
    
    log:=true;i:=1; {���樠������ ��६�����}
    while (i<=maxvars) and log do begin
        A[i]:=GetParam('a',i,log);
        if log then
            B[i]:=GetParam('b',i,log);
        if log then
            C[i]:=GetParam('c',i,log);
        inc(i);
    end;
    InputData:=log;
end;

{------������� �������� ��������-----}
{��ࠬ����:�����樥��� �� �; �����樥��� �� �; ᢮����� �����樥���}
function CheckData(const A,B,C:MatColumn):boolean;
var ch:char; 
begin
    WriteLn('�� �����:');
    WriteLn(A[1]:1:4,'x + ',B[1]:1:4,'y = ',C[1]:1:4);
	WriteLn(A[2]:1:4,'x + ',B[2]:1:4,'y = ',C[2]:1:4);
	WriteLn('a1=',A[1]:1:4,'; b1=',B[1]:1:4,'; c1=',C[1]:1:4);
	WriteLn('a2=',A[2]:1:4,'; b2=',B[2]:1:4,'; c2=',C[2]:1:4);
	WriteLn('OK?(y/n)');
	Readln(ch);
	CheckData:=UpCase(ch)='Y';
end;

{------������� �������� ������������-----}
{��ࠬ����: ���� �⮫��� ��।���⥫�; ��ன �⮫��� ��।���⥫�}
function GetDet(const A,B:MatColumn):real;
begin
    GetDet:=A[1]*B[2]-B[1]*A[2];
end;

{------������� ������� �������-----}
{��ࠬ����:�����樥��� �� �; �����樥��� �� �; ᢮����� �����樥���
                        ��������� ���祭�� �; ���祭�� �}
function SolveSys(const A,B,C:MatColumn; var x,y:real):boolean;
var d,dx,dy:real;
begin
    d:=GetDet(A,B);
    if d<>0 then begin
        dx:=GetDet(C,B);
	    dy:=GetDet(A,C);
	    x:=dx/d;
	    y:=dy/d;
	    SolveSys:=true;
	end else SolveSys:=false;
end;

{------��������� ������ ������ �������-----}
{��ࠬ����: ���祭�� �; ���祭�� �}
procedure PrintData(const x,y:real);
begin
    WriteLn('�⢥�:');
	WriteLn('x =',x);
	WriteLn('y =',y);
end;

{------�������� ���������-----}
var A,B,C:MatColumn;
{�����樥��� �� x; �� y; ᢮����� �����樥���}	
	x,y:real;
{���祭�� x; ���祭�� �}
    log:boolean;
{��६����� ���ﭨ�}
BEGIN

	WriteLn('������ �ணࠬ�� ��室�� ��୨ ��⥬� �ࠢ�����');
	WriteLn('(a1)x+(b1)y=(c1);');
	WriteLn('(a2)x+(b2)y=(c2);');
	log:=InputData(A,B,C);
	if log then
	    log:=CheckData(A,B,C);
	if log then begin
	    log:=SolveSys(A,B,C,x,y);
	    if log then 
	        PrintData(x,y)
	    else 
	        WriteLn('���⥬� �� ᮢ���⭠!');
	end else 
	    WriteLn('�ணࠬ�� �����襭�.');
	WriteLn('������ <Enter>...');
    ReadLn;
END.
