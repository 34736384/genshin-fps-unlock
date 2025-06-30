CC = x86_64-w64-mingw32-g++
SRCS = dllmain.cpp
OBJS = $(SRCS:.cpp=.o)
DLL = UnlockerStub.dll

all: $(DLL)

$(DLL): $(OBJS)
	$(CC) -v -shared -o $@ $^ -Wl,--out-implib,lib$(basename $@).a -lntdll

%.o: %.cpp
	$(CC) -c $< -o $@

clean:
	rm -f $(OBJS) $(DLL)
