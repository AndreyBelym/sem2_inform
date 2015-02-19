procedure f1(var a:array of byte; var p:pointer);
var i:byte;
begin
	getmem(p,8);
	for i:=0 to 8 do
		a[i]:=i;
end;
procedure f2(var a:array of byte);
var i:byte;
begin
	for i:=1 to 8 do
		writeln(a[i]);
end;
type arr=array [1..1] of byte;
var p:^arr;
begin
	f1(p^,p);
	f2(p^);
end.
	