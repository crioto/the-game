CC=g++
CXXLIBS=
CXXINCLUDES=
BINARY=wip
OUTPUT_DIRECTORY=bin
CONFIGFILE=config.make

include $(CONFIGFILE)

directories:
	@mkdir -p $(OUTPUT_DIRECTORY)

clean:
	-rm -f $(OUTPUT_DIRECTORY)/$(BINARY)

mrproper: clean
	-rm -f $(CONFIGFILE)
	-rm -rf $(OUTPUT_DIRECTORY)