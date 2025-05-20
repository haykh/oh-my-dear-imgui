EXECUTABLE = build/binary_to_compressed_c
ICON_NAMES = fa-regular-400 fa-solid-900
ICONS = $(foreach icon, $(ICON_NAMES), generated/$(icon).h)

FONT_NAMES = Cousine-Regular JetBrainsMono-Regular MonaspaceKryptonFrozen-Regular MonaspaceRadonFrozen-Regular HersheySimplex HersheyDuplex HersheyComplex xkcd-script
FONTS = $(foreach font, $(FONT_NAMES), generated/$(font).h)

${EXECUTABLE} : build/binary_to_compressed_c.o
	@printf "\033[0;32mLinking binary_to_compressed\033[0m\n"
	@g++ -o $@ $<

build/binary_to_compressed_c.cpp :
	@printf "\033[0;32mDownloading binary_to_compressed_c.cpp\033[0m\n"
	@mkdir -p build
	@wget -O $@ https://raw.githubusercontent.com/ocornut/imgui/refs/heads/master/misc/fonts/binary_to_compressed_c.cpp

build/binary_to_compressed_c.o : build/binary_to_compressed_c.cpp
	@printf "\033[0;32mCompiling binary_to_compressed_c.cpp\033[0m\n"
	@mkdir -p build
	@g++ -c $< -o $@

%.ttf:
	@printf "\033[0;32mDownloading $*.ttf\033[0m\n"
	@if echo "$(ICON_NAMES)" | grep -qw "$*"; then \
		wget --directory-prefix ttf https://github.com/FortAwesome/font-awesome-sass/raw/refs/heads/main/assets/fonts/font-awesome/$*.ttf; \
	elif [ "$*" = "Cousine-Regular" ]; then \
		wget --directory-prefix ttf https://github.com/google/fonts/raw/refs/heads/main/apache/cousine/Cousine-Regular.ttf; \
	elif [ "$*" = "JetBrainsMono-Regular" ]; then \
		wget --directory-prefix ttf https://github.com/JetBrains/JetBrainsMono/raw/refs/heads/master/fonts/ttf/JetBrainsMono-Regular.ttf; \
	elif [ "$*" = "MonaspaceKryptonFrozen-Regular" ]; then \
		wget --directory-prefix ttf https://github.com/githubnext/monaspace/raw/refs/heads/main/fonts/frozen/MonaspaceKryptonFrozen-Regular.ttf; \
	elif [ "$*" = "MonaspaceRadonFrozen-Regular" ]; then \
		wget --directory-prefix ttf https://github.com/githubnext/monaspace/raw/refs/heads/main/fonts/frozen/MonaspaceRadonFrozen-Regular.ttf; \
	elif [ "$*" = "xkcd-script" ]; then \
	  wget --directory-prefix ttf https://github.com/ipython/xkcd-font/blob/master/xkcd-script/font/xkcd-script.ttf; \
	elif [ "$*" = "HersheySimplex" ]; then \
		wget --directory-prefix ttf https://github.com/yangcht/Hershey_font_TTF/raw/refs/heads/main/ttf/AVHersheySimplexMedium.ttf; \
		mv ttf/AVHersheySimplexMedium.ttf ttf/HersheySimplex.ttf; \
	elif [ "$*" = "HersheyDuplex" ]; then \
		wget --directory-prefix ttf https://github.com/yangcht/Hershey_font_TTF/raw/refs/heads/main/ttf/AVHersheyDuplexMedium.ttf; \
		mv ttf/AVHersheyDuplexMedium.ttf ttf/HersheyDuplex.ttf; \
	elif [ "$*" = "HersheyComplex" ]; then \
		wget --directory-prefix ttf https://github.com/yangcht/Hershey_font_TTF/raw/refs/heads/main/ttf/AVHersheyComplexMedium.ttf; \
		mv ttf/AVHersheyComplexMedium.ttf ttf/HersheyComplex.ttf; \
	else \
		echo "Unknown font: $*"; exit 1; \
	fi

generated/%.h : $(EXECUTABLE) %.ttf
	@printf "\033[0;32mGenerating $*.h\033[0m\n"
	@mkdir -p generated
	@name=$*; \
	name=$${name//-/_}; \
	./$(EXECUTABLE) ttf/$*.ttf $$name > $@

icons : $(ICONS)

fonts : $(FONTS)

all : icons fonts

default : all

clean :
	rm -rf generated ttf build

.PHONY : all clean icons fonts

.SECONDARY: $(ICON_NAMES:=.ttf) $(FONT_NAMES:=.ttf)
