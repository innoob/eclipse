Target=newproject
CFLAG=-g -I . `xml2-config --cflags --libs`
Objs=$(Target).o

all: $(Target)
	clear
	./$< -h

$(Target):%:%.o
	gcc -o $@ -L . $< $(CFLAG)

$(Objs):%.o:%.c
	gcc -o $@ -c $< $(CFLAG)

clean:
	-rm -rf $(Target) $(Objs)

install:$(Target)
	sudo mv $(Target) /bin

uninstall:
	sudo rm /bin/$(Target)
