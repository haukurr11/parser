Program test;
{A program without parsing errors}
Var X : integer;
Var y : real;

function test (x:real) : real;
var t : array[1..10] of real;
var I : integer;
begin
        i := 0;
        t[1] := -2.0*x;
        while (i < 4) do
          i := i + 1;
        test := t[1]
end;

begin
        y := 2.0*(3.14);
        if x>2 then
                y := 123.45E-3
        else 
	begin
          y := test(3.3);
	  x := x+2
	end  
end
.
     
