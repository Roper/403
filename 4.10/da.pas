var
	n, m, i : longint;

begin
	randomize;
	assign(output, 'a.in'); rewrite(output);
	n := random(10) + 1;
	m := random(4) + 1;
	writeln(n, ' ', m);
	for i := 1 to n do begin
		writeln(chr(ord('0') + random(10)),chr(ord('0') + random(10)),chr(ord('0') + random(10)),chr(ord('0') + random(10)));
	end;
	close(output);
end.