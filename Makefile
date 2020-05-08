CC=c++
CFLAGS=`Magick++-config --cppflags --cxxflags --ldflags --libs`
SOURCES=./src/Pixel.cpp ./src/LionUtils.cpp ./src/LionFilters.cpp ./src/Resizer.cpp ./src/ToAscii.cpp ./src/main.cpp 
EXECUTABLE=limgtoasci
INSTALLDIR=/usr/local/bin


all: $(SOURCES)
	$(CC) $(SOURCES) $(CFLAGS) -o $(EXECUTABLE)

install:
	mkdir -p $(INSTALLDIR)
	cp $(EXECUTABLE) $(INSTALLDIR)

uninstall:
	rm $(INSTALLDIR)/$(EXECUTABLE)

clean:
	rm $(EXECUTABLE)