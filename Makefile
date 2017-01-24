# Nigels wizzzy "simple" makefile
# ###################################################################
#
LIBS:=$(shell ncursesw6-config --libs) -llua
CXXFLAGS:=$(shell ncursesw6-config --cflags) -g3 -w -Wall
EXECUTABLE:=tlua
INSTALLABLE_SCRIPTS:=
SOURCES:=main.cpp EditString.cpp LuaInterpreter.cpp
SOURCEDIR:=src
OBJDIR:=obj
DEPDIR:=deps
INSTALLDIR:=

# ###################################################################

SUFFIXES += .d
VPATH += src

#.SILENT: $(DEPS) $(DEPDIR) $(OBJDIR) clean
$(V).SILENT:

OBJECTS=$(addprefix $(OBJDIR)/,$(notdir $(SOURCES:.cpp=.o)))
DEPS=$(addprefix $(DEPDIR)/,$(notdir $(SOURCES:.cpp=.d)))

.PHONY: all
all:	$(OBJDIR) $(SOURCES) $(DEPS) gitversioning.h $(EXECUTABLE)
	@echo 'Up to date'

.PHONY: install
install:
	mkdir -p $(INSTALLDIR)
	cp $(EXECUTABLE) $(INSTALLABLE_SCRIPTS) $(INSTALLDIR)

$(EXECUTABLE):	$(OBJECTS)
	@echo 'Linking executable $@'
	$(CXX) $(LDFLAGS) $(OBJECTS) $(LIBS) -o $@

# Squeeky
# ########
.PHONY: clean
clean:
	echo 'Cleaning'
	rm -f $(OBJECTS) $(EXECUTABLE) gitversioning.h
	rm -rf $(DEPDIR)
	rm -rf $(OBJDIR)

# Object files
# #############
#
$(OBJDIR)/%.o: %.cpp | $(OBJDIR)
	@echo 'Compiling $<'
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

# Dependency files
# #################
#
# Make sure gitversioning.h is made before trying to make
# any dependency file

$(DEPDIR)/%.d: %.cpp gitversioning.h | $(DEPDIR)
	@echo "Caching dependency info for: $<"
	$(CC) $(CXXFLAGS) -MF"$@" -MG -MP -MM -MT"$(OBJDIR)/$(notdir $(<:.cpp=.o)) $@" "$<"

$(DEPDIR):
	mkdir -p $(DEPDIR)

ifeq (0,$(words $(findstring clean, $(MAKECMDGOALS))))
# Don't make these, only to clean them out again.
-include $(DEPS)
endif

# gitversioning.h is remade when either git tags or heads change.
gitversioning.h: .git/refs/tags .git/refs/heads .git/HEAD
	./gitversioning.sh
