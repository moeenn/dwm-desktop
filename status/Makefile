
dwmstatus: status.c
	gcc -Wall -pedantic -std=c99 -o dwmstatus status.c -lX11

clean:
	rm dwmstatus

install:
	@echo "Installing ..."
	cp -f dwmstatus /usr/local/bin/dwmstatus
