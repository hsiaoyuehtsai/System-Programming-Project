SHELL = /bin/bash
CC = gcc
CFLAGS = -g
SRC = mybusybox.c
EXE = mybusybox
LINKS = ls cat chown cp

all: $(EXE) $(LINKS)

$(EXE): $(SRC)
	$(CC) $(CFLAGS) -o $(EXE) $(SRC)

# 為每個命令建立軟連結
$(LINKS): $(EXE)
	for cmd in $(LINKS); do \
		ln -sf $(EXE) $$cmd; \
	done

clean:
	# 移除執行檔
	rm -f $(EXE)

	# 移除所有軟連結
	for cmd in $(LINKS); do \
		rm -f $$cmd; \
	done
