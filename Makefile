discid: discid.c
	gcc discid.c -ldiscid -o discid
	strip discid

clean:
	rm -f discid
